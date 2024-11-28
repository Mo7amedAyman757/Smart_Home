/* 
 * File:   hal_eusart.h
 * Author: LEGION
 *
 * Created on October 16, 2024, 9:59 AM
 */

#ifndef HAL_EUSART_H
#define	HAL_EUSART_H

/* Section : Includes */
#include "../GPIO/hal_gpio.h"
#include "../interrupt/internal_interrupt.h"
/*Section : Macro Declaration*/
/*Enable EUSART*/
#define EUSART_MODULE_ENABLE     1
/*Disable EUSART*/
#define EUSART_MODULE_DISABLE    0
/*synchronous module*/
#define EUSART_SYNCHRONOUS_MODE  1
/*Asynchronous module*/
#define EUSART_ASYNCHRONOUS_MODE 0
/*Baud Rate Asynchronous Speed Mode */
#define EUSART_ASYNCHRONOUS_HIGH_SPEED  1
#define EUSART_ASYNCHRONOUS_LOW_SPEED   0
/*Baud Rate Generator Register Size*/
#define EUSART_16BIT_BAUDRATE_GEN  1
#define EUSART_8BIT_BAUDRATE_GEN   0 
/*Enable Transmit */
#define EUSART_ASYNCHRONOUS_TX_ENABLE    1
/*Disable Transmit */
#define EUSART_ASYNCHRONOUS_TX_DISABLE   0
/*Eusart Transmit Interrupt Enable*/
#define EUSART_ASYNCHRONOUS_INTURREPT_TX_ENABLE   1
#define EUSART_ASYNCHRONOUS_INTURREPT_TX_DISABLE  0
/*Enable 9-bit Transmit */
#define EUSART_ASYNCHRONOUS_TX_9_BIT_ENABLE    1
/*Disable 9-bit Transmit */
#define EUSART_ASYNCHRONOUS_TX_9_BIT_DISABLE   0
/*Enable Receive */
#define EUSART_ASYNCHRONOUS_RX_ENABLE    1
/*Disable Receive */
#define EUSART_ASYNCHRONOUS_RX_DISABLE   0
/*Eusart Receive Interrupt Enable*/
#define EUSART_ASYNCHRONOUS_INTURREPT_RX_ENABLE   1
#define EUSART_ASYNCHRONOUS_INTURREPT_RX_DISABLE  0
/*Enable 9-bit Receive */
#define EUSART_ASYNCHRONOUS_RX_9_BIT_ENABLE    1
/*Disable 9-bit Receive */
#define EUSART_ASYNCHRONOUS_RX_9_BIT_DISABLE   0
/*EUSART framing error*/
#define EUSART_FRAMING_ERROR_DETECTED  1
#define EUSART_FRAMING_ERROR_CLEARED   0
/*EUSART over return*/
#define EUSART_OVERRUN_DETECTED  1
#define EUSARTOVERRUN_ERROR_CLEARED   0
/*Section : Macro Function Declaration*/

/**@brief  Enables the EUSART module by setting the SPEN bit in RCSTA.*/
#define EUSART_MODULE_ENABLE_CFG(_CFG)   ( RCSTAbits.SPEN = _CFG)

/*@brief  Disables the EUSART module by clearing the SPEN bit in RCSTA.*/
#define EUSART_MODULE_DISABLE_CFG(_CFG)   ( RCSTAbits.SPEN = _CFG)

/*Section : Data Type Declaration*/
typedef enum {
    EUSART_8BIT_ASYNCHRONOUS_LOW_SPEED, /**< 8-bit asynchronous mode with low-speed baud rate. */
    EUSART_8BIT_ASYNCHRONOUS_HIGH_SPEED, /**< 8-bit asynchronous mode with high-speed baud rate. */
    EUSART_16BIT_ASYNCHRONOUS_LOW_SPEED, /**< 16-bit asynchronous mode with low-speed baud rate. */
    EUSART_16BIT_ASYNCHRONOUS_HIGH_SPEED, /**< 16-bit asynchronous mode with high-speed baud rate. */
    EUSART_8BIT_SYNCHRONOUS_SPEED, /**< 8-bit synchronous mode for baud rate. */
    EUSART_16BIT_SYNCHRONOUS_SPEED, /**< 16-bit synchronous mode for baud rate. */
} baudrate_gen_t;

typedef struct {
    uint8 usart_tx_enable : 1; /**< Enable EUSART transmitter (1 = enabled, 0 = disabled). */
    uint8 usart_tx_interupt_enable : 1; /**< Enable EUSART TX interrupt (1 = enabled, 0 = disabled). */
    uint8 usart_tx_9bit_enable : 1; /**< Enable 9-bit transmission mode (1 = enabled, 0 = disabled). */
    priority_level_t usart_tx_priority; /**< Priority level for the TX interrupt. */
    uint8 usart_tx_reserved : 5; /**< Reserved bits for future use, set to 0. */
} usart_tx_cfg_t;

typedef struct {
    uint8 usart_rx_enable : 1; /**< Enable EUSART receiver (1 = enabled, 0 = disabled). */
    uint8 usart_rx_interupt_enable : 1; /**< Enable EUSART RX interrupt (1 = enabled, 0 = disabled). */
    uint8 usart_rx_9bit_enable : 1; /**< Enable 9-bit reception mode (1 = enabled, 0 = disabled). */
    priority_level_t usart_rx_priority; /**< Priority level for the RX interrupt. */
    uint8 usart_rx_reserved : 5; /**< Reserved bits for future use, set to 0. */
} usart_rx_cfg_t;

typedef union {

    struct {
        uint8 usart_ferr : 1; /**< Framing error flag. */
        uint8 usart_oerr : 1; /**< Overrun error flag. */
        uint8 usart_rx_reserve : 6; /**< Reserved bits. */
    };
    uint8 status; /**< Full status byte. */
} usart_error_status_t;

typedef struct {
    uint32 baudrate_value; /**< EUSART baud rate value. */
    baudrate_gen_t baudrate_gen; /**< Baud rate generation mode. */
    usart_tx_cfg_t usart_tx_cfg; /**< Transmitter configuration. */
    usart_rx_cfg_t usart_rx_cfg; /**< Receiver configuration. */
    usart_error_status_t usart_error_status; /**< Current EUSART error status (framing/overrun). */
    void(* EUSART_TX_INTERRUPT_HANDLER)(void); /**< Pointer to TX interrupt handler function. */
    void(* EUSART_RX_INTERRUPT_HANDLER)(void); /**< Pointer to RX interrupt handler function. */
    void(* EUSART_FRAMING_INTERRUPT_HANDLER)(void); /**< Pointer to framing error interrupt handler function. */
    void(* EUSART_OVERRUN_INTERRUPT_HANDLER)(void); /**< Pointer to overrun error interrupt handler function. */
} usart_t;

/*Section : Function Declaration*/
STD_ReturnType EUSART_ASYNC_INIT(const usart_t *usart);
STD_ReturnType EUSART_ASYNC_DEINIT(const usart_t *usart);

STD_ReturnType EUSART_ASYNC_READ_BYTE_BLOCKING(const usart_t *usart, uint8 *data);
STD_ReturnType EUSART_ASYNC_READ_BYTE_NON_BLOCKING(const usart_t *usart, uint8 *data);

STD_ReturnType EUSART_ASYNC_WRITE_BYTE_BLOCKING(const usart_t *usart, uint8 data);
STD_ReturnType EUSART_ASYNC_WRITE_STRING_BLOCKING(const usart_t *usart,const uint8 *data, uint16 str_len);

STD_ReturnType EUSART_ASYNC_WRITE_BYTE_NON_BLOCKING(const usart_t *usart, uint8 data);
STD_ReturnType EUSART_ASYNC_WRITE_STRING_NON_BLOCKING(const usart_t *usart, uint8 *data, uint16 str_len);
#endif	/* HAL_EUSART_H */

