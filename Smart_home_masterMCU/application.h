/* 
 * File:   application.h
 * Author: LEGION
 *
 * Created on September 2, 2024, 2:20 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* Section : Includes */
#include "ECU_Layer/ecu_layer_init.h"
#include "MCAL_Layer/interrupt/external_interrupt.h"
#include "MCAL_Layer/eeprom/hal_eeprom.h"
#include "MCAL_Layer/ADC/hal_adc.h"
#include "MCAL_Layer/Timers/hal_timer0.h"
#include "MCAL_Layer/Timers/hal_timer1.h"
#include "MCAL_Layer/Timers/hal_timer2.h"
#include "MCAL_Layer/Timers/hal_timer3.h"
#include "MCAL_Layer/CCP/hal_ccp.h"
#include "MCAL_Layer/eusart/hal_eusart.h"
#include "MCAL_Layer/I2C/hal_i2c.h"
/*Section : Macro Declaration*/

/*Section : Macro Function Declaration*/

/*call back function*/
void INT0_App_ISR(void);
void INT1_App_ISR(void);
void INT2_App_ISR(void);
/*Section : Data Type Declaration*/
extern led_t led1;
extern keypad_t keypad;

usart_t usart1 = {
    .baudrate_gen = EUSART_8BIT_ASYNCHRONOUS_LOW_SPEED,
    .baudrate_value = 9600,
    .usart_tx_cfg.usart_tx_enable = EUSART_ASYNCHRONOUS_TX_ENABLE,
    .usart_tx_cfg.usart_tx_interupt_enable = EUSART_ASYNCHRONOUS_INTURREPT_TX_ENABLE

};

mssp_i2c_t mssp_i2c1 = {
    .clock = 100000,
    .i2c_config.i2c_mode = I2C_MASTER_MODE,
    .i2c_config.i2c_mode_config = MSSP_I2C_MASTER_MODE_CLOCK,
    .i2c_config.i2c_slew_rate = MSSP_I2C_SLEW_RATE_DISABLE
};

//interrupt_INTx_t int0_obj = {
//    .EXT_InterruptHandler = INT0_App_ISR,
//    .source = INTERRUPT_EXTERNAL_INT0,
//    .mcu_pin.port = PORTB_INDEX,
//    .mcu_pin.pin = GPIO_PIN0,
//    .mcu_pin.direction = GPIO_DIRECTION_INPUT,
//    .edge = INTERRUPT_RISING_EDGE,
//};
//
//interrupt_INTx_t int1_obj = {
//    .EXT_InterruptHandler = INT1_App_ISR,
//    .source = INTERRUPT_EXTERNAL_INT1,
//    .mcu_pin.port = PORTB_INDEX,
//    .mcu_pin.pin = GPIO_PIN1,
//    .mcu_pin.direction = GPIO_DIRECTION_INPUT,
//    .edge = INTERRUPT_RISING_EDGE,
//};
//
//interrupt_INTx_t int2_obj = {
//    .EXT_InterruptHandler = INT2_App_ISR,
//    .source = INTERRUPT_EXTERNAL_INT2,
//    .mcu_pin.port = PORTB_INDEX,
//    .mcu_pin.pin = GPIO_PIN2,
//    .mcu_pin.direction = GPIO_DIRECTION_INPUT,
//    .edge = INTERRUPT_RISING_EDGE,
//};
/*Section : Function Declaration*/
void application_initialize(void);
void I2C_Master_Call_Slave(uint8 Slave_Address, uint8 temp);

#endif	/* APPLICATION_H */

