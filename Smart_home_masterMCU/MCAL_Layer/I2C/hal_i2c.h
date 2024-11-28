/* 
 * File:   hal_i2c.h
 * Author: LEGION
 *
 * Created on October 27, 2024, 1:56 PM
 */

#ifndef HAL_I2C_H
#define	HAL_I2C_H

/* Section : Includes */
#include "../GPIO/hal_gpio.h"
#include "../interrupt/internal_interrupt.h"
/*Section : Macro Declaration*/
/*Slew Rate Enable/Disable*/
#define MSSP_I2C_SLEW_RATE_DISABLE  1
#define MSSP_I2C_SLEW_RATE_ENABLE   0
/*SMBus Enable/Disable*/
#define MSSP_I2C_SMBUS_DISABLE  0
#define MSSP_I2C_SMBUS_ENABLE   1
/*Slave Mode Data/Address Indication*/
#define I2C_LAST_BYTE_DATA    1
#define I2C_LAST_BYTE_ADDRESS 0
/*Stop Bit Indication*/
#define MSSP_I2C_STOP_DETECTED       1
#define MSSP_I2C_STOP_NOT_DETECTED   0
/*Start Bit Indication*/
#define MSSP_I2C_START_DETECTED       1
#define MSSP_I2C_START_NOT_DETECTED   0
/*I2C : Master or Slave*/
#define I2C_MASTER_MODE 1
#define I2C_SLAVE_MODE  0
/*Synchronous Serial Port Mode Select bits*/
#define MSSP_I2C_MASTER_MODE_CLOCK                        0x08U
#define MSSP_I2C_MASTER_MODE_FIRMWARE                     0x0BU
#define MSSP_I2C_SLAVE_MODE_7_BIT_ADDRESS                 0x06U
#define MSSP_I2C_SLAVE_MODE_10_BIT_ADDRESS                0x07U
#define MSSP_I2C_SLAVE_MODE_7_BIT_ADDRESS_SS_INTERRUPT    0x0EU
#define MSSP_I2C_SLAVE_MODE_10_BIT_ADDRESS_SS_INTERRUPT   0x0FU
/*General Call Enable/Disable*/
#define I2C_GENERAL_CALL_ENABLE  1
#define I2C_GENERAL_CALL_DISABLE 0
/*Master Mode Recieve enable*/
#define I2C_MASTER_RECEIVE_ENABLE  1
#define I2C_MASTER_RECEIVE_DISABLE 0
/*Acknowledge Status bit (Master Transmit Mode only)*/
#define I2C_ACK_RECEIVED_FROM_SLAVE     0
#define I2C_ACK_NOT_RECEIVED_FROM_SLAVE 1
/*Acknowledge Status bit (Master Receive Mode only)*/
#define I2C_MASTER_SEND_ACK   0
#define I2C_MASTER_SEND_NACK  1
/*Section : Macro Function Declaration*/
/*Slew Rate Enable/Disable*/
#define I2C_SLEW_RATE_ENABLE_CFG()   (SSPSTATbits.SMP = 0)
#define I2C_SLEW_RATE_DISABLE_CFG()  (SSPSTATbits.SMP = 1)
/*SMBus Enable/Disable*/
#define I2C_SMBus_ENABLE_CFG()   (SSPSTATbits.CKE = 1)
#define I2C_SMBus_DISABLE_CFG()  (SSPSTATbits.CKE = 0)
/*General Call Enable/Disable*/
#define I2C_GENERAL_CALL_ENABLE_CFG()  (SSPCON2bits.GCEN = 1)
#define I2C_GENERAL_CALL_DISABLE_CFG() (SSPCON2bits.GCEN = 0)
/*Master Mode Receive enable*/
#define I2C_MASTER_RECEIVE_ENABLE_CFG()  (SSPCON2bits.RCEN = 1)
#define I2C_MASTER_RECEiVE_DISABLE_CFG() (SSPCON2bits.RCEN = 0)
/*Master Synchronous Serial Port Enable/Disable */
#define MSSP_MODULE_ENABLE_CFG()          (SSPCON1bits.SSPEN = 1)
#define MSSP_MODULE_DISABLE_CFG()         (SSPCON1bits.SSPEN = 0)
/*Clock Strecth*/
#define I2C_CLOCK_STRETCH_ENABLE()        (SSPCON1bits.CKP = 0)
#define I2C_CLOCK_STRETCH_DISABLE()       (SSPCON1bits.CKP = 1)
/*Section : Data Type Declaration*/
typedef struct {
    uint8 i2c_mode; // 1-bit flag to specify the I2C mode (Master/Slave)
    uint8 i2c_mode_config; // 8-bit value to hold additional I2C mode configuration settings
    uint8 i2c_slew_rate : 1; // 1-bit flag to control the slew rate (enable/disable)
    uint8 i2c_smbus : 1; // 1-bit flag to enable or disable SMBus control
    uint8 i2c_generel_call : 1; // 1-bit flag to enable or disable general call address recognition
    uint8 i2c_master_rec_mode : 1; // 1-bit flag to specify whether the master is in receive mode
    uint8 i2c_slave_address; // I2c Slave Address
#if I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    priority_level_t I2C_priority_cfg;
    priority_level_t I2C_BUS_Collision_priority_cfg;
#endif
} i2c_config_t;

typedef struct {
    uint32 clock; // 32-bit value to set the clock speed for the I2C bus (in Hz)
    i2c_config_t i2c_config; // Configuration structure to hold I2C settings (mode, slew rate, etc.)
#if I2C_INTERRUPT_FEATURE_ENABLE ==  INTERRUPT_FEATURE_ENABLE
    void(*I2C_Report_Write_Collision)(void); // Pointer to a function to handle I2C write collision events
    void(*I2C_DefaultInterruptHandler)(void); // Pointer to a default interrupt handler function for I2C events
    void(*I2C_Report_Recieve_Overflow)(void); // Pointer to a function to handle I2C receive overflow events
#endif
} mssp_i2c_t;


/*Section : Function Declaration*/
STD_ReturnType MSSP_I2C_Init(const mssp_i2c_t *i2c_obj);
STD_ReturnType MSSP_I2C_DeInit(const mssp_i2c_t *i2c_obj);
STD_ReturnType MSSP_I2C_Master_Send_Start(const mssp_i2c_t *i2c_obj);
STD_ReturnType MSSP_I2C_Master_Send_Repeated_Start(const mssp_i2c_t *i2c_obj);
STD_ReturnType MSSP_I2C_Master_Send_Stop(const mssp_i2c_t *i2c_obj);
STD_ReturnType MSSP_I2C_Master_Write_Blocking(const mssp_i2c_t *i2c_obj, uint8 i2c_data, uint8 *ack);
STD_ReturnType MSSP_I2C_Master_Read_Blocking(const mssp_i2c_t *i2c_obj, uint8 ack, uint8 *i2c_data);
#endif	/* HAL_I2C_H */

