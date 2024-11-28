/* 
 * File:   TempSensor_TC74.c
 * Author: LEGION
 *
 * Created on November 26, 2024, 11:09 AM
 */

#include "TempSensor_TC74.h"

uint8 ack = 0;
extern mssp_i2c_t mssp_i2c1;

uint8 TempSensor_TC74_Read_Temp(uint8 TC74_Address) {
    uint8 TC74_TempVal = 0;
    //TC74_Address --> 1001 111 lSB-> (0) for write :(1) for read
    uint8 TC74_Read_Address = TC74_Address | 0x01;
    MSSP_I2C_Master_Send_Start(&mssp_i2c1);
    /*Send TC74 Address Address with write bit*/
    MSSP_I2C_Master_Write_Blocking(&mssp_i2c1, TC74_Address, &ack);
    /*Send TC74 register Address*/
    MSSP_I2C_Master_Write_Blocking(&mssp_i2c1, 0x00, &ack);
    // Send a repeated start to switch to read mode
    MSSP_I2C_Master_Send_Repeated_Start(&mssp_i2c1);
    /*Send TC74 Address Address with Read bit*/
    MSSP_I2C_Master_Write_Blocking(&mssp_i2c1, TC74_Read_Address, &ack);
    /* Read the byte from the EEPROM and send NACK */
    MSSP_I2C_Master_Read_Blocking(&mssp_i2c1, 1, &TC74_TempVal);
    // Stop I2C communication
    MSSP_I2C_Master_Send_Stop(&mssp_i2c1);
    return TC74_TempVal;
}