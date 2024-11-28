/* 
 * File:   EEPROM_24C02C.c
 * Author: LEGION
 *
 * Created on November 25, 2024, 10:32 PM
 */

#include "EEPROM_24C02C.h"

uint8 ack = 0;
extern mssp_i2c_t mssp_i2c1;

void EEPROM_24C02C_Write_Byte(uint8 EEPROM_Address, uint8 Byte_Address, uint8 data) {
    MSSP_I2C_Master_Send_Start(&mssp_i2c1);
    /*Send EEPROM_24C02C Address with write bit*/
    MSSP_I2C_Master_Write_Blocking(&mssp_i2c1, EEPROM_Address, &ack);
    /*Send EEPROM Byte address */
    MSSP_I2C_Master_Write_Blocking(&mssp_i2c1, Byte_Address, &ack);
    /*Send Data to EEPROM Byte address */
    MSSP_I2C_Master_Write_Blocking(&mssp_i2c1, data, &ack);
    // Stop I2C communication
    MSSP_I2C_Master_Send_Stop(&mssp_i2c1);
}

uint8 EEPROM_24C02C_Read_Byte(uint8 EEPROM_Address, uint8 Byte_Address) {
    uint8 RecVal = 0;
    uint8 Read_Address = EEPROM_Address | 0x01; // Add the read bit to the address
    MSSP_I2C_Master_Send_Start(&mssp_i2c1);
    /*Send EEPROM_24C02C Address with write bit*/
    MSSP_I2C_Master_Write_Blocking(&mssp_i2c1, EEPROM_Address, &ack);
    /*Send EEPROM Byte address */
    MSSP_I2C_Master_Write_Blocking(&mssp_i2c1, Byte_Address, &ack);
    // Send a repeated start to switch to read mode
    MSSP_I2C_Master_Send_Repeated_Start(&mssp_i2c1);
    /* Send EEPROM Address with read bit (set LSB) */
    MSSP_I2C_Master_Write_Blocking(&mssp_i2c1, Read_Address, &ack);
    /* Read the byte from the EEPROM and send NACK */
    MSSP_I2C_Master_Read_Blocking(&mssp_i2c1, 1, &RecVal);
    // Stop I2C communication
    MSSP_I2C_Master_Send_Stop(&mssp_i2c1);
    return RecVal;
}