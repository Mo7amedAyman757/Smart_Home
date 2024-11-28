/*
 * File:   hal_eusart.c
 * Author: LEGION
 *
 * Created on October 16, 2024, 9:59 AM
 */

#include "hal_eusart.h"

#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*EUSART_TX_Interrupt_Handler)(void) = NULL; /**< Pointer to the transmit interrupt handler function. */
#endif
#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*EUSART_RX_Interrupt_Handler)(void) = NULL; /**< Pointer to the receive interrupt handler function. */
static void (*EUSART_FramingError_Handler)(void) = NULL; /**< Pointer to the framing error interrupt handler function. */
static void (*EUSART_OverrunError_Handler)(void) = NULL; /**< Pointer to the overrun error interrupt handler function. */
#endif

static STD_ReturnType EUSART_Baud_Rate_Calculation(const usart_t *usart);
static STD_ReturnType EUSART_ASYNC_TX_INIT(const usart_t *usart);
static STD_ReturnType EUSART_ASYNC_RX_INIT(const usart_t *usart);

/**
 * @brief Initializes the EUSART module for asynchronous communication.
 *
 * This function configures the EUSART module according to the settings provided
 * in the `usart_t` structure for asynchronous communication.
 *
 * @param usart Pointer to the EUSART configuration structure.
 * @return Returns E_OK if initialization is successful, otherwise E_NOK if the pointer is NULL.
 */
STD_ReturnType EUSART_ASYNC_INIT(const usart_t *usart) {
    STD_ReturnType ret = E_OK;
    if (NULL == usart) {
        ret = E_NOK;
    } else {
        EUSART_MODULE_DISABLE_CFG(EUSART_MODULE_DISABLE);
        SETBIT(TRISC, _TRISC_TRISC7_POSITION);
        SETBIT(TRISC, _TRISC_TRISC6_POSITION);
        EUSART_Baud_Rate_Calculation(usart);
        EUSART_ASYNC_TX_INIT(usart);
        EUSART_ASYNC_RX_INIT(usart);
        EUSART_MODULE_ENABLE_CFG(EUSART_MODULE_ENABLE);
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Deinitializes the EUSART module.
 *
 * This function resets or disables the EUSART module, releasing any resources allocated
 * during the initialization phase.
 *
 * @param usart Pointer to the EUSART configuration structure.
 * @return Returns E_OK if deinitialization is successful, otherwise E_NOK if the pointer is NULL.
 */
STD_ReturnType EUSART_ASYNC_DEINIT(const usart_t *usart) {
    STD_ReturnType ret = E_OK;
    if (NULL == usart) {
        ret = E_NOK;
    } else {
        EUSART_MODULE_ENABLE_CFG(EUSART_MODULE_DISABLE);
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Reads a byte of data from the EUSART in blocking mode.
 *
 * This function waits until a byte is received from the EUSART module, then stores the byte
 * in the memory location pointed to by `data`.
 *
 * @param usart Pointer to the EUSART configuration structure.
 * @param data Pointer to the memory location where the received byte will be stored.
 * @return Returns E_OK if the byte is successfully read, otherwise E_NOK if the pointer is NULL.
 */
STD_ReturnType EUSART_ASYNC_READ_BYTE_BLOCKING(const usart_t *usart, uint8 *data) {
    STD_ReturnType ret = E_OK;
    if (NULL == usart) {
        ret = E_NOK;
    } else {
        while (!PIR1bits.RCIF)
            ;
        *data = RCREG;
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Reads a byte of data from the EUSART in non-blocking mode.
 *
 * This function attempts to read a byte from the EUSART module without waiting. If a byte is available,
 * it is stored in the memory location pointed to by `data`.
 *
 * @param usart Pointer to the EUSART configuration structure.
 * @param data Pointer to the memory location where the received byte will be stored.
 * @return Returns E_OK if a byte is successfully read, otherwise E_NOK if the pointer is NULL.
 */
STD_ReturnType EUSART_ASYNC_READ_BYTE_NON_BLOCKING(const usart_t *usart, uint8 *data) {
    STD_ReturnType ret = E_OK;
    if (NULL == usart) {
        ret = E_NOK;
    } else {
        if (PIR1bits.RCIF == 1) {
            *data = RCREG;
            ret = E_OK;
        } else {
            ret = E_NOK;
        }
    }
    return ret;
}

/**
 * @brief Writes a byte of data to the EUSART in blocking mode.
 *
 * This function waits until the EUSART transmitter is ready, then sends a byte of data.
 * The transmission is repeated for `str_len` bytes.
 *
 * @param usart Pointer to the EUSART configuration structure.
 * @param data Byte to be transmitted.
 * @param str_len Number of bytes to be transmitted.
 * @return Returns E_OK if transmission is successful, otherwise E_NOK if the pointer is NULL.
 */
STD_ReturnType EUSART_ASYNC_WRITE_BYTE_BLOCKING(const usart_t *usart, uint8 data) {
    STD_ReturnType ret = E_OK;
    if (NULL == usart) {
        ret = E_NOK;
    } else {
        while (!TXSTAbits.TRMT)
            ;
        TXREG = data;
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        EUSART_TX_INTERRUPT_ENABLE();
#endif
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Writes a string of data to the EUSART in blocking mode.
 *
 * This function waits until the EUSART transmitter is ready, then sends a string of bytes.
 * The function waits for each byte to be transmitted before continuing to the next byte.
 * The length of the string is specified by `str_len`.
 *
 * @param usart Pointer to the EUSART configuration structure.
 * @param data Pointer to the memory location containing the string to be transmitted.
 * @param str_len Number of bytes to be transmitted.
 * @return Returns E_OK if the string is successfully transmitted,
 *         otherwise E_NOK if the pointer is NULL or an error occurs.
 */
STD_ReturnType EUSART_ASYNC_WRITE_STRING_BLOCKING(const usart_t *usart,const uint8 *data, uint16 str_len) {
    STD_ReturnType ret = E_OK;
    uint8 str_ctr = 0;
    if (NULL == usart) {
        ret = E_NOK;
    } else {
        for (str_ctr = 0; str_ctr < str_len; str_ctr++) {
            EUSART_ASYNC_WRITE_BYTE_BLOCKING(usart, data[str_ctr]);
        }
    }
    return ret;
}

/**
 * @brief Writes a byte of data to the EUSART in non-blocking mode.
 *
 * This function attempts to transmit a byte of data without waiting. The transmission
 * is repeated for `str_len` bytes.
 *
 * @param usart Pointer to the EUSART configuration structure.
 * @param data Byte to be transmitted.
 * @param str_len Number of bytes to be transmitted.
 * @return Returns E_OK if transmission is successful, otherwise E_NOK if the pointer is NULL.
 */
STD_ReturnType EUSART_ASYNC_WRITE_BYTE_NON_BLOCKING(const usart_t *usart, uint8 data) {
    STD_ReturnType ret = E_OK;
    if (NULL == usart) {
        ret = E_NOK;
    } else {
        if (TXSTAbits.TRMT) {
            TXREG = data;
            ret = E_OK;
        } else {
            ret = E_NOK;
        }
    }
    return ret;
}

/**
 * @brief Writes a string of data to the EUSART in non-blocking mode.
 *
 * This function attempts to transmit a string of bytes to the EUSART module without waiting.
 * The function will return immediately without waiting for the transmission to complete.
 * The length of the string is specified by `str_len`, and the data is transmitted byte-by-byte.
 *
 * @param usart Pointer to the EUSART configuration structure.
 * @param data Pointer to the memory location containing the string to be transmitted.
 * @param str_len Number of bytes to be transmitted.
 * @return Returns E_OK if the string is successfully queued for transmission,
 *         otherwise E_NOK if the pointer is NULL or an error occurs.
 */
STD_ReturnType EUSART_ASYNC_WRITE_STRING_NON_BLOCKING(const usart_t *usart, uint8 *data, uint16 str_len) {
    STD_ReturnType ret = E_OK;
    uint8 str_ctr = 0;
    if (NULL == usart) {
        ret = E_NOK;
    } else {
        for (str_ctr = 0; str_ctr < str_len; str_ctr++) {
            EUSART_ASYNC_WRITE_BYTE_NON_BLOCKING(usart, data[str_ctr]);
        }
    }
    return ret;
}

/**
 * @brief  Calculates and sets the baud rate for the EUSART module based on the provided configuration.
 *
 * This function calculates the baud rate for the EUSART based on the system's crystal frequency
 * (_XTAL_FREQ) and the desired baud rate value specified in the `usart_t` structure. The function
 * also configures the EUSART's registers (TXSTA, BAUDCON) for the appropriate mode (synchronous
 * or asynchronous), baud rate generator (8-bit or 16-bit), and high or low-speed settings.
 *
 * @param usart   A pointer to a `usart_t` structure containing the baud rate generation mode
 *                and the desired baud rate value. If this pointer is NULL, the function will
 *                return with an error.
 *
 * @return  STD_ReturnType
 *          - `E_OK` if the baud rate calculation and configuration were successful.
 *          - `E_NOK` if the `usart` pointer is NULL or the configuration failed.
 *
 * @note    The function updates the global `SPBRG` and `SPBRGH` registers based on the
 *          calculated baud rate. These registers control the baud rate for the EUSART module.
 */
static STD_ReturnType EUSART_Baud_Rate_Calculation(const usart_t *usart) {
    STD_ReturnType ret = E_OK;
    float baudrate_temp = 0;
    if (NULL == usart) {
        ret = E_NOK;
    } else {
        switch (usart->baudrate_gen) {
            case EUSART_8BIT_ASYNCHRONOUS_LOW_SPEED:
                TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
                TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
                BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN;
                baudrate_temp = ((_XTAL_FREQ / (float) usart->baudrate_value) / 64) - 1;
                ret = E_OK;
                break;
            case EUSART_8BIT_ASYNCHRONOUS_HIGH_SPEED:
                TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
                TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
                BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN;
                baudrate_temp = ((_XTAL_FREQ / (float) usart->baudrate_value) / 16) - 1;
                ret = E_OK;
                break;
            case EUSART_16BIT_ASYNCHRONOUS_LOW_SPEED:
                TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
                TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_LOW_SPEED;
                BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
                baudrate_temp = ((_XTAL_FREQ / (float) usart->baudrate_value) / 16) - 1;
                ret = E_OK;
                break;
            case EUSART_16BIT_ASYNCHRONOUS_HIGH_SPEED:
                TXSTAbits.SYNC = EUSART_ASYNCHRONOUS_MODE;
                TXSTAbits.BRGH = EUSART_ASYNCHRONOUS_HIGH_SPEED;
                BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
                baudrate_temp = ((_XTAL_FREQ / (float) usart->baudrate_value) / 4) - 1;
                ret = E_OK;
                break;
            case EUSART_8BIT_SYNCHRONOUS_SPEED:
                TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
                BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN;
                baudrate_temp = ((_XTAL_FREQ / (float) usart->baudrate_value) / 4) - 1;
                ret = E_OK;
                break;
            case EUSART_16BIT_SYNCHRONOUS_SPEED:
                TXSTAbits.SYNC = EUSART_SYNCHRONOUS_MODE;
                BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
                baudrate_temp = ((_XTAL_FREQ / (float) usart->baudrate_value) / 4) - 1;
                ret = E_OK;
                break;
            default:
                ret = E_NOK;
                break;
        }
        SPBRG = (uint8) ((uint32) baudrate_temp);
        SPBRGH = (uint8) (((uint32) baudrate_temp) >> 8);
    }
    return ret;
}

/**
 * @brief  Initializes the EUSART module for asynchronous transmit mode.
 *
 * This function configures the EUSART for asynchronous transmit operation based on the provided
 * `usart_t` configuration structure. It enables/disables the transmitter, configures interrupts
 * (if enabled), and sets up 9-bit data transmission if specified.
 *
 * @param usart   A pointer to a `usart_t` structure containing the configuration for asynchronous TX.
 *
 * @return  STD_ReturnType
 *          - `E_OK` if initialization is successful.
 *          - `E_NOK` if the `usart` pointer is NULL or invalid configuration is found.
 */
static STD_ReturnType EUSART_ASYNC_TX_INIT(const usart_t *usart) {
    STD_ReturnType ret = E_OK;
    if (NULL == usart) {
        ret = E_NOK;
    } else {
        if (usart->usart_tx_cfg.usart_tx_enable == EUSART_ASYNCHRONOUS_TX_ENABLE) {
            TXSTAbits.TXEN = EUSART_ASYNCHRONOUS_TX_ENABLE;
            /*EUSART Interrupt Configuration*/
            if (usart->usart_tx_cfg.usart_tx_interupt_enable == EUSART_ASYNCHRONOUS_INTURREPT_TX_ENABLE) {
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
                EUSART_TX_INTERRUPT_ENABLE();
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_Priority_level_Enable();
                if (usart->usart_tx_cfg.usart_tx_priority == INTERRUPT_HIGH_PRIORITY) {
                    INTERRUPT_Global_InterruptHighEnable();
                    EUSART_TX_HIGH_PRIORITY()
                } else if (usart->usart_tx_cfg.usart_tx_priority == INTERRUPT_LOW_PRIORITY) {
                    INTERRUPT_Global_InterruptLowEnable();
                    EUSART_TX_LOW_PRIORITY()
                } else {
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EUSART_TX_Interrupt_Handler = usart->EUSART_TX_INTERRUPT_HANDLER;
#endif
            }
        } else if (usart->usart_tx_cfg.usart_tx_interupt_enable == EUSART_ASYNCHRONOUS_INTURREPT_TX_DISABLE) {
            EUSART_TX_INTERRUPT_DISABLE();
        } else {
        }
        /*EUSART 9BIT Configuration*/
        if (usart->usart_tx_cfg.usart_tx_9bit_enable == EUSART_ASYNCHRONOUS_TX_9_BIT_ENABLE) {
            TXSTAbits.TX9D = EUSART_ASYNCHRONOUS_TX_9_BIT_ENABLE;
        } else if (usart->usart_tx_cfg.usart_tx_9bit_enable == EUSART_ASYNCHRONOUS_TX_9_BIT_DISABLE) {
            TXSTAbits.TX9D = EUSART_ASYNCHRONOUS_TX_9_BIT_DISABLE;
        } else {
        }
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief  Initializes the EUSART module for asynchronous receive mode.
 *
 * This function configures the EUSART for asynchronous receive operation based on the provided
 * `usart_t` configuration structure. It enables/disables the receiver, sets up interrupt handling
 * (if enabled), and configures 9-bit data reception if specified.
 *
 * @param usart   A pointer to a `usart_t` structure containing configuration options for the
 *                asynchronous receiver (enable/disable RX, enable/disable interrupts, 9-bit mode).
 *
 * @return  STD_ReturnType
 *          - `E_OK` if the initialization was successful.
 *          - `E_NOK` if the `usart` pointer is NULL or an invalid configuration is provided.
 *
 * @note    If interrupts are enabled, it sets up the interrupt handlers for framing, overrun,
 *          and receive interrupts. The function also configures the RX mode to either 8-bit or 9-bit.
 */
static STD_ReturnType EUSART_ASYNC_RX_INIT(const usart_t *usart) {
    STD_ReturnType ret = E_OK;
    if (NULL == usart) {
        ret = E_NOK;
    } else {
        if (usart->usart_rx_cfg.usart_rx_enable == EUSART_ASYNCHRONOUS_RX_ENABLE) {
            RCSTAbits.CREN = EUSART_ASYNCHRONOUS_RX_ENABLE;
            /*EUSART Interrupt Configuration*/
            if (usart->usart_rx_cfg.usart_rx_interupt_enable == EUSART_ASYNCHRONOUS_INTURREPT_RX_ENABLE) {
#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
                EUSART_RX_INTERRUPT_ENABLE();
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_Priority_level_Enable();
                if (usart->usart_rx_cfg.usart_rx_priority == INTERRUPT_HIGH_PRIORITY) {
                    INTERRUPT_Global_InterruptHighEnable();
                    EUSART_RX_HIGH_PRIORITY()
                } else if (usart->usart_rx_cfg.usart_rx_priority == INTERRUPT_LOW_PRIORITY) {
                    INTERRUPT_Global_InterruptLowEnable();
                    EUSART_RX_LOW_PRIORITY()
                } else {
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EUSART_RX_Interrupt_Handler = usart->EUSART_RX_INTERRUPT_HANDLER;
                EUSART_FramingError_Handler = usart->EUSART_FRAMING_INTERRUPT_HANDLER;
                EUSART_OverrunError_Handler = usart->EUSART_OVERRUN_INTERRUPT_HANDLER;
#endif
            }
        } else if (usart->usart_rx_cfg.usart_rx_interupt_enable == EUSART_ASYNCHRONOUS_INTURREPT_RX_DISABLE) {
            EUSART_RX_INTERRUPT_DISABLE();
        } else {
        }
        /*EUSART 9BIT Configuration*/
        if (usart->usart_rx_cfg.usart_rx_9bit_enable == EUSART_ASYNCHRONOUS_RX_9_BIT_ENABLE) {
            RCSTAbits.RC9 = EUSART_ASYNCHRONOUS_RX_9_BIT_ENABLE;
        } else if (usart->usart_rx_cfg.usart_rx_9bit_enable == EUSART_ASYNCHRONOUS_RX_9_BIT_DISABLE) {
            RCSTAbits.RC9 = EUSART_ASYNCHRONOUS_RX_9_BIT_DISABLE;
        } else {
        }
        ret = E_OK;
    }
    return ret;
}

void EUSART_TX_ISR(void) {
    if (EUSART_TX_Interrupt_Handler) {
        EUSART_TX_Interrupt_Handler();
    } else {
    }
    EUSART_TX_INTERRUPT_DISABLE();
}

void EUSART_RX_ISR(void) {
    if (EUSART_RX_Interrupt_Handler) {
        EUSART_RX_Interrupt_Handler();
    } else {
    }
    if (EUSART_FramingError_Handler) {
        EUSART_FramingError_Handler();
    } else {
    }
    if (EUSART_OverrunError_Handler) {
        EUSART_OverrunError_Handler();
    } else {
    }
}