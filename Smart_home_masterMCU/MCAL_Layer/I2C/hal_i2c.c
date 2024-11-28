/* 
 * File:   hal_i2c.c
 * Author: LEGION
 *
 * Created on October 27, 2024, 1:56 PM
 */

#include "hal_i2c.h"

#if I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void (*I2C_Report_Write_Collision_Interrupt_Handler)(void) = NULL;
static void (*I2C_Default_Interrupt_Handler)(void) = NULL;
static void (*I2C_Report_Recieve_Overflow_Interrupt_Handler)(void) = NULL;
#endif

static inline void MSSP_I2C_MODE_GPIO_CFG(void);
static inline void I2C_Slave_Mode_Config(const mssp_i2c_t *i2c_obj);
static inline void I2C_MASTER_MODE_CLOCK_CONFIG(const mssp_i2c_t *i2c_obj);
static inline void MSSP_I2C_Interrupt_config(const mssp_i2c_t *i2c_obj);

/**
 * @brief Initializes the MSSP module for I2C operation.
 * @param i2c_obj Pointer to the MSSP I2C configuration structure.
 * @return Returns E_OK if successful, otherwise E_NOK.
 */
STD_ReturnType MSSP_I2C_Init(const mssp_i2c_t *i2c_obj) {
    STD_ReturnType ret = E_NOK;
    if (i2c_obj == NULL) {
        ret = E_NOK;
    } else {
        /*Disable MSSP*/
        MSSP_MODULE_DISABLE_CFG();
        /*Master/Slave Mode*/
        if (i2c_obj->i2c_config.i2c_mode == I2C_MASTER_MODE) {
            I2C_MASTER_MODE_CLOCK_CONFIG(i2c_obj);
        } else if (i2c_obj->i2c_config.i2c_mode == I2C_SLAVE_MODE) {
            /*I2C Slave Mode General Call Configurations*/
            if (i2c_obj->i2c_config.i2c_generel_call == I2C_GENERAL_CALL_ENABLE) {
                I2C_GENERAL_CALL_ENABLE_CFG();
            } else if (i2c_obj->i2c_config.i2c_generel_call == I2C_GENERAL_CALL_DISABLE) {
                I2C_GENERAL_CALL_DISABLE_CFG();
            } else {
                /* Nothing */
            }
            /*Clear Write Collision bit*/
            SSPCON1bits.WCOL = 0;
            /*Clear Receive Overflow bit*/
            SSPCON1bits.SSPOV = 0;
            /*Release The Clock*/
            SSPCON1bits.CKP = 1;
            /*Assign the I2C Slave Address*/
            SSPADD = i2c_obj->i2c_config.i2c_slave_address;
            /*I2C Slave Mode Clock Configurations*/
            I2C_Slave_Mode_Config(i2c_obj);
        }
        /*I2C Slave Mode GPIO Configurations / I2C Master Mode GPIO Configurations*/
        MSSP_I2C_MODE_GPIO_CFG();
        /*MSSP I2C Slew Rate Control*/
        if (i2c_obj->i2c_config.i2c_slew_rate == MSSP_I2C_SLEW_RATE_ENABLE) {
            I2C_SLEW_RATE_ENABLE_CFG();
        } else if (i2c_obj->i2c_config.i2c_slew_rate == MSSP_I2C_SLEW_RATE_DISABLE) {
            I2C_SLEW_RATE_DISABLE_CFG();
        } else {
            /*Nothing*/
        }
        /*MSSP SMBus Control*/
        if (i2c_obj->i2c_config.i2c_smbus == MSSP_I2C_SMBUS_ENABLE) {
            I2C_SMBus_ENABLE_CFG();
        } else if (i2c_obj->i2c_config.i2c_smbus == MSSP_I2C_SMBUS_DISABLE) {
            I2C_SMBus_DISABLE_CFG();
        } else {
            /*Nothing*/
        }
        /*Interrupt Configurations*/
        MSSP_I2C_Interrupt_config(i2c_obj);
        /*Enable MSSP*/
        MSSP_MODULE_ENABLE_CFG();
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief De initializes the MSSP module for I2C operation.
 * @param i2c_obj Pointer to the MSSP I2C configuration structure.
 * @return Returns E_OK if successful, otherwise E_NOK.
 */
STD_ReturnType MSSP_I2C_DeInit(const mssp_i2c_t *i2c_obj) {
    STD_ReturnType ret = E_NOK;
    if (i2c_obj == NULL) {
        ret = E_NOK;
    } else {
        /*Disable MSSP*/
        MSSP_MODULE_DISABLE_CFG();
#if I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        MSSP_I2C_INTERRUPT_DISABLE();
        MSSP_BUS_COLLISION_INTERRUPT_DISABLE();
#endif
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Sends a start condition on the I2C bus in master mode.
 * @param i2c_obj Pointer to the MSSP I2C configuration structure.
 * @return Returns E_OK if successful, otherwise E_NOK.
 */
STD_ReturnType MSSP_I2C_Master_Send_Start(const mssp_i2c_t *i2c_obj) {
    STD_ReturnType ret = E_NOK;
    if (i2c_obj == NULL) {
        ret = E_NOK;
    } else {
        /*Initiates the start condition on SDA and SDL*/
        SSPCON2bits.SEN = 1;
        /*Wait for the completion if Start Condition*/
        while (SSPCON2bits.SEN);
        /*Report Start Condition Detection*/
        if (SSPSTATbits.S == MSSP_I2C_START_DETECTED) {
            ret = E_OK;
        } else {
            ret = E_NOK;
        }
    }
    return ret;
}

/**
 * @brief Sends a repeated start condition on the I2C bus in master mode.
 * @param i2c_obj Pointer to the MSSP I2C configuration structure.
 * @return Returns E_OK if successful, otherwise E_NOK.
 */
STD_ReturnType MSSP_I2C_Master_Send_Repeated_Start(const mssp_i2c_t *i2c_obj) {
    STD_ReturnType ret = E_NOK;
    if (i2c_obj == NULL) {
        ret = E_NOK;
    } else {
        /*Initiates the Repeated start condition on SDA and SDL*/
        SSPCON2bits.RSEN = 1;
        /*Wait for the completion if Repeated start Condition*/
        while (SSPCON2bits.RSEN);
        /*Clear MSSP Interrupt Flag*/
        PIR1bits.SSPIF = 0;
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Sends a stop condition on the I2C bus in master mode.
 * @param i2c_obj Pointer to the MSSP I2C configuration structure.
 * @return Returns E_OK if successful, otherwise E_NOK.
 */
STD_ReturnType MSSP_I2C_Master_Send_Stop(const mssp_i2c_t *i2c_obj) {
    STD_ReturnType ret = E_NOK;
    if (i2c_obj == NULL) {
        ret = E_NOK;
    } else {
        /*Initiates the stop condition on SDA and SDL*/
        SSPCON2bits.PEN = 1;
        /*Wait for the completion if Stop Condition*/
        while (SSPCON2bits.PEN);
        /*Report Stop Condition Detection*/
        if (SSPSTATbits.P == MSSP_I2C_STOP_DETECTED) {
            ret = E_OK;
        } else {
            ret = E_NOK;
        }

    }
    return ret;
}

/**
 * @brief Sends data on the I2C bus in master mode.
 * @param i2c_obj Pointer to the MSSP I2C configuration structure.
 * @param i2c_data Data byte to send.
 * @return Returns E_OK if successful, otherwise E_NOK.
 */
STD_ReturnType MSSP_I2C_Master_Write_Blocking(const mssp_i2c_t *i2c_obj, uint8 i2c_data, uint8 *ack) {
    STD_ReturnType ret = E_NOK;
    if ((i2c_obj == NULL) || (ack == NULL)) {
        ret = E_NOK;
    } else {
        /*Write data to Data register*/
        SSPBUF = i2c_data;
        /*Wait for the transmission is completed*/
        while ((SSPSTATbits.BF || SSPSTATbits.R_W));
        /*Report the acknowledge received from the slave*/
        if (I2C_ACK_RECEIVED_FROM_SLAVE == SSPCON2bits.ACKSTAT) {
            *ack = I2C_ACK_RECEIVED_FROM_SLAVE;
        } else {
            *ack = I2C_ACK_NOT_RECEIVED_FROM_SLAVE;
        }
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Reads data from the I2C bus in master mode.
 * @param i2c_obj Pointer to the MSSP I2C configuration structure.
 * @param ack Acknowledgment option after the read operation (0 for NACK, 1 for ACK).
 * @param i2c_data Pointer to the variable where the received data will be stored.
 * @return Returns E_OK if successful, otherwise E_NOK.
 */
STD_ReturnType MSSP_I2C_Master_Read_Blocking(const mssp_i2c_t *i2c_obj, uint8 ack, uint8 *i2c_data) {
    STD_ReturnType ret = E_NOK;
    if ((i2c_obj == NULL) || (i2c_data == NULL)) {
        ret = E_NOK;
    } else {
        /*Master mode receive Enable*/
        I2C_MASTER_RECEIVE_ENABLE_CFG();
        /*Wait for buffer full flag*/
        while (!SSPSTATbits.BF);
        /*Copy the data registers to buffer variable*/
        *i2c_data = SSPBUF;
        /*Send ACK or NACK after read*/
        if (ack == I2C_MASTER_SEND_ACK) {
            SSPCON2bits.ACKDT = 0;
            SSPCON2bits.ACKEN = 1;
            while (SSPCON2bits.ACKEN); // Wait until ACK is sent
        } else if (ack == I2C_MASTER_SEND_NACK) {
            SSPCON2bits.ACKDT = 1;
            SSPCON2bits.ACKEN = 1;
            while (SSPCON2bits.ACKEN); // Wait until NACK is sent
        } else {
            /*Nothing*/
        }
        ret = E_OK;
    }
    return ret;
}

void MSSP_I2C_ISR(void) {
#if I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    MSSP_I2C_INTERRUPT_CLEAR_FLAG();
    if (I2C_Default_Interrupt_Handler) {
        I2C_Default_Interrupt_Handler();
    }
#endif
}

void MSSP_I2C_BC_ISR(void) {
#if I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    MSSP_BUS_COLLISION_INTERRUPT_CLEAR_FLAG();
    if (I2C_Report_Write_Collision_Interrupt_Handler) {
        I2C_Report_Write_Collision_Interrupt_Handler();
    }
#endif
}

/**
 * @brief Configures the I2C clock frequency for master mode operation.
 * 
 * @param i2c_obj Pointer to an `mssp_i2c_t` structure that contains the I2C configuration.
 * 
 * This function sets the I2C mode configuration in the SSPCON1 register and calculates the
 * value for the SSPADD register to set the desired I2C clock frequency. The clock value is 
 * determined based on the system oscillator frequency (_XTAL_FREQ) and the desired I2C clock 
 * speed specified in `i2c_obj->clock`.
 */
static inline void I2C_MASTER_MODE_CLOCK_CONFIG(const mssp_i2c_t *i2c_obj) {
    SSPCON1bits.SSPM = i2c_obj->i2c_config.i2c_mode_config;
    SSPADD = (uint8) (((_XTAL_FREQ / 4.0) / i2c_obj->clock) - 1);

}

/**
 * @brief Configures GPIO pins for I2C mode.
 * 
 * This function sets TRISC3 and TRISC4 as input pins, enabling them to be used 
 * for the I2C clock (SCL) and data (SDA) lines, respectively.
 */
static inline void MSSP_I2C_MODE_GPIO_CFG(void) {
    SETBIT(TRISC, _TRISC_TRISC3_POSITION);
    SETBIT(TRISC, _TRISC_TRISC4_POSITION);
}

/**
 * @brief Configures the I2C module for slave mode operation.
 * 
 * @param i2c_obj Pointer to an `mssp_i2c_t` structure that holds I2C configuration settings.
 * 
 * This function sets the SSPM bits in the SSPCON1 register based on the mode configuration
 * specified in the `i2c_config.i2c_mode_config` field of the `i2c_obj` structure.
 */
static inline void I2C_Slave_Mode_Config(const mssp_i2c_t *i2c_obj) {
    SSPCON1bits.SSPM = i2c_obj->i2c_config.i2c_mode_config;
}

/**
 * @brief Configures and enables I2C interrupts and their priority levels.
 * 
 * @param i2c_obj Pointer to an `mssp_i2c_t` structure that holds interrupt configuration settings.
 * 
 * This function enables the I2C interrupt and bus collision interrupt based on the configuration.
 * If interrupt priority levels are enabled, it configures the priority of the I2C interrupt 
 * and bus collision interrupt. Additionally, it assigns the default interrupt handler functions 
 * for I2C events, write collisions, and receive overflow based on the handlers provided in `i2c_obj`.
 */
static inline void MSSP_I2C_Interrupt_config(const mssp_i2c_t *i2c_obj) {
#if I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    MSSP_I2C_INTERRUPT_ENABLE();
    MSSP_I2C_INTERRUPT_CLEAR_FLAG();
    MSSP_BUS_COLLISION_INTERRUPT_ENABLE();
    MSSP_BUS_COLLISION_INTERRUPT_CLEAR_FLAG();
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
    INTERRUPT_Priority_level_Enable();
    if (i2c_obj->i2c_config.I2C_priority_cfg == INTERRUPT_HIGH_PRIORITY) {
        INTERRUPT_Global_InterruptHighEnable();
        MSSP_I2C_HIGH_PRIORITY();
    } else if (i2c_obj->i2c_config.I2C_priority_cfg == INTERRUPT_LOW_PRIORITY) {
        INTERRUPT_Global_InterruptLowEnable();
        MSSP_I2C_LOW_PRIORITY();
    } else {
    }
    if (i2c_obj->i2c_config.I2C_BUS_Collision_priority_cfg == INTERRUPT_HIGH_PRIORITY) {
        INTERRUPT_Global_InterruptHighEnable();
        MSSP_BUS_COLLISION_HIGH_PRIORITY();
    } else if (i2c_obj->i2c_config.I2C_BUS_Collision_priority_cfg == INTERRUPT_LOW_PRIORITY) {
        INTERRUPT_Global_InterruptLowEnable();
        MSSP_BUS_COLLISION_LOW_PRIORITY();
    } else {
    }
#else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
#endif
    I2C_Default_Interrupt_Handler = i2c_obj->I2C_DefaultInterruptHandler;
    I2C_Report_Write_Collision_Interrupt_Handler = i2c_obj->I2C_Report_Write_Collision;
    I2C_Report_Recieve_Overflow_Interrupt_Handler = i2c_obj->I2C_Report_Recieve_Overflow;
#endif
}

