/* 
 * File:   application.h
 * Author: LEGION
 *
 * Created on September 2, 2024, 2:20 PM
 */

#include "application.h"
#include "MCAL_Layer/I2C/hal_i2c.h"

#define SLAVE1 0x60 //7-bit address 0x30 + <<(shift left) write bit
#define SLAVE2 0x62 //7-bit address 0x31 + <<(shift left) write bit

STD_ReturnType ret = E_OK;

static volatile uint8 i2c_slave2_rec_data;
void MSSP_I2C_DefaultHandler(void);

mssp_i2c_t i2c_obj = {
    .clock = 100000,
    .i2c_config.i2c_mode = I2C_SLAVE_MODE,
    .i2c_config.i2c_mode_config = MSSP_I2C_SLAVE_MODE_7_BIT_ADDRESS,
    .i2c_config.i2c_smbus = MSSP_I2C_SMBUS_DISABLE,
    .i2c_config.i2c_slew_rate = MSSP_I2C_SLEW_RATE_DISABLE,
    .i2c_config.i2c_slave_address = SLAVE2,
    .i2c_config.i2c_generel_call = I2C_GENERAL_CALL_DISABLE,
    .I2C_Report_Write_Collision = NULL,
    .I2C_Report_Recieve_Overflow = NULL,
    .I2C_DefaultInterruptHandler = MSSP_I2C_DefaultHandler,
};

void MSSP_I2C_DefaultHandler(void) {
    /*Hold Clock*/
    uint8 dummy_buffer;
    I2C_CLOCK_STRETCH_ENABLE();
    if ((SSPSTATbits.R_nW == 0) && (SSPSTATbits.D_nA == 0)) {
        dummy_buffer = SSPBUF; /*Read the Last Byte to clear the buffer*/
        while (!SSPSTATbits.BF);
        i2c_slave2_rec_data = SSPBUF; /*Read Data Byte */
    } else if (SSPSTATbits.R_nW == 1) {

    } else {
        /*Nothing*/
    }
    /*Release Clock*/
    I2C_CLOCK_STRETCH_DISABLE();
}

int main() {
    application_initialize();

    while (1) {
        if (i2c_slave2_rec_data == 'b') {
            led_turn_on(&led1);
        } else if (i2c_slave2_rec_data == 'd') {
            led_turn_off(&led1);
        }
    }
}

void application_initialize(void) {
    ecu_layer_initialize();
    MSSP_I2C_Init(&i2c_obj);
}




