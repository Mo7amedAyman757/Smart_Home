/* 
 * File:   application.h
 * Author: LEGION
 *
 * Created on September 2, 2024, 2:20 PM
 */


#include "application.h"
#include "MCAL_Layer/I2C/hal_i2c.h"

#define SLAVE1 0x60 // 7-bit address 0x30 + <<(shift left) write bit
#define SLAVE2 0x62 // 7-bit address 0x31 + <<(shift left) write bit

STD_ReturnType ret = E_OK;
uint8 ack;


void MSSP_I2C_Send_1_byte(uint8 slave_add, uint8 data);

mssp_i2c_t i2c_obj = {
    .clock = 100000,
    .i2c_config.i2c_mode = I2C_MASTER_MODE,
    .i2c_config.i2c_mode_config = MSSP_I2C_MASTER_MODE_CLOCK,
    .i2c_config.i2c_smbus = MSSP_I2C_SMBUS_DISABLE,
    .i2c_config.i2c_slew_rate = MSSP_I2C_SLEW_RATE_DISABLE,
    .I2C_Report_Write_Collision = NULL,
    .I2C_Report_Recieve_Overflow = NULL,
    .I2C_DefaultInterruptHandler = NULL,
};

int main() {
    application_initialize();

    while (1) {
        MSSP_I2C_Send_1_byte(SLAVE1, 'a');
        __delay_ms(1000);
        MSSP_I2C_Send_1_byte(SLAVE2, 'b');
        __delay_ms(1000);
        MSSP_I2C_Send_1_byte(SLAVE1, 'c');
        __delay_ms(1000);
        MSSP_I2C_Send_1_byte(SLAVE2, 'd');
        __delay_ms(1000);
    }
}

void application_initialize(void) {
    ecu_layer_initialize();
    MSSP_I2C_Init(&i2c_obj);
}

void MSSP_I2C_Send_1_byte(uint8 slave_add, uint8 data) {
    ret = MSSP_I2C_Master_Send_Start(&i2c_obj);
    ret = MSSP_I2C_Master_Write_Blocking(&i2c_obj, slave_add, &ack);
    ret = MSSP_I2C_Master_Write_Blocking(&i2c_obj, data, &ack);
    ret = MSSP_I2C_Master_Send_Stop(&i2c_obj);
}


