/* 
 * File:   ecu_layer_init.c
 * Author: LEGION
 *
 * Created on September 2, 2024, 3:10 PM
 */

#include "ecu_layer_init.h"


led_t led1 = {
    .port = PORTD_INDEX,
    .pin = GPIO_PIN0,
    .led_status = GPIO_LOW
};
//
//led_t led2 = {
//    .port = PORTC_INDEX,
//    .pin = GPIO_PIN1,
//    .led_status = GPIO_LOW
//};
//
//led_t led3 = {
//    .port = PORTC_INDEX,
//    .pin = GPIO_PIN2,
//    .led_status = GPIO_LOW
//};
//
//led_t led4 = {
//    .port = PORTC_INDEX,
//    .pin = GPIO_PIN3,
//    .led_status = GPIO_HIGH
//};

//button_t btn1 = {
//    .button_pin.port = PORTD_INDEX,
//    .button_pin.pin = GPIO_PIN1,
//    .button_pin.direction = GPIO_DIRECTION_INPUT,
//    .button_pin.logic = GPIO_LOW,
//    .button_connection = BUTTON_ACTIVE_HIGH,
//    .button_state = BUTTON_RELEASED,
//};
//
//button_t btn2 = {
//    .button_pin.port = PORTD_INDEX,
//    .button_pin.pin = GPIO_PIN2,
//    .button_pin.direction = GPIO_DIRECTION_INPUT,
//    .button_pin.logic = GPIO_HIGH,
//    .button_connection = BUTTON_ACTIVE_LOW,
//    .button_state = BUTTON_RELEASED,
//};
//
//relay_t relay = {
//    .relay_port = PORTC_INDEX,
//    .relay_pin = GPIO_PIN4,
//    .relay_status = RELAY_OFF_STATUS,
//};
//
//motor_t motor1 = {
//    .motor[0].port = PORTC_INDEX,
//    .motor[0].pin = GPIO_PIN0,
//    .motor[0].direction = GPIO_DIRECTION_OUTPUT,
//    .motor[0].logic = MOTOR_OFF_STATUS,
//
//    .motor[1].port = PORTC_INDEX,
//    .motor[1].pin = GPIO_PIN1,
//    .motor[1].direction = GPIO_DIRECTION_OUTPUT,
//    .motor[1].logic = MOTOR_OFF_STATUS,
//};
//
//motor_t motor2 = {
//    .motor[0].port = PORTC_INDEX,
//    .motor[0].pin = GPIO_PIN2,
//    .motor[0].direction = GPIO_DIRECTION_OUTPUT,
//    .motor[0].logic = MOTOR_OFF_STATUS,
//
//    .motor[1].port = PORTC_INDEX,
//    .motor[1].pin = GPIO_PIN3,
//    .motor[1].direction = GPIO_DIRECTION_OUTPUT,
//    .motor[1].logic = MOTOR_OFF_STATUS,
//};

//segment_t seg = {
//    .segment_pins[0].port = PORTB_INDEX,
//    .segment_pins[0].pin = GPIO_PIN0,
//    .segment_pins[0].direction = GPIO_DIRECTION_OUTPUT,
//    .segment_pins[0].logic = GPIO_LOW,
//
//    .segment_pins[1].port = PORTB_INDEX,
//    .segment_pins[1].pin = GPIO_PIN1,
//    .segment_pins[1].direction = GPIO_DIRECTION_OUTPUT,
//    .segment_pins[1].logic = GPIO_LOW,
//
//    .segment_pins[2].port = PORTB_INDEX,
//    .segment_pins[2].pin = GPIO_PIN2,
//    .segment_pins[2].direction = GPIO_DIRECTION_OUTPUT,
//    .segment_pins[2].logic = GPIO_LOW,
//
//    .segment_pins[3].port = PORTB_INDEX,
//    .segment_pins[3].pin = GPIO_PIN3,
//    .segment_pins[3].direction = GPIO_DIRECTION_OUTPUT,
//    .segment_pins[3].logic = GPIO_LOW,
//
//    .segment_type = SEGMENT_COMMON_ANODE,
//};
//
keypad_t keypad = {
    .keypad_rows_pin[0].port = PORTD_INDEX,
    .keypad_rows_pin[0].pin = GPIO_PIN0,
    .keypad_rows_pin[0].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pin[0].logic = GPIO_LOW,

    .keypad_rows_pin[1].port = PORTD_INDEX,
    .keypad_rows_pin[1].pin = GPIO_PIN1,
    .keypad_rows_pin[1].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pin[1].logic = GPIO_LOW,

    .keypad_rows_pin[2].port = PORTD_INDEX,
    .keypad_rows_pin[2].pin = GPIO_PIN2,
    .keypad_rows_pin[2].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pin[2].logic = GPIO_LOW,

    .keypad_rows_pin[3].port = PORTD_INDEX,
    .keypad_rows_pin[3].pin = GPIO_PIN3,
    .keypad_rows_pin[3].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pin[3].logic = GPIO_LOW,

    .keypad_columns_pins[0].port = PORTD_INDEX,
    .keypad_columns_pins[0].pin = GPIO_PIN4,
    .keypad_columns_pins[0].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[0].logic = GPIO_LOW,

    .keypad_columns_pins[1].port = PORTD_INDEX,
    .keypad_columns_pins[1].pin = GPIO_PIN5,
    .keypad_columns_pins[1].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[1].logic = GPIO_LOW,

    .keypad_columns_pins[2].port = PORTD_INDEX,
    .keypad_columns_pins[2].pin = GPIO_PIN6,
    .keypad_columns_pins[2].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[2].logic = GPIO_LOW,
};

//chr_lcd_4bit_t lcd_1 = {
//    .lcd_rs.port = PORTC_INDEX,
//    .lcd_rs.pin = GPIO_PIN4,
//    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
//    .lcd_rs.logic = GPIO_LOW,
//
//    .lcd_en.port = PORTC_INDEX,
//    .lcd_en.pin = GPIO_PIN5,
//    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
//    .lcd_en.logic = GPIO_LOW,
//
//    .lcd_data[0].port = PORTC_INDEX,
//    .lcd_data[0].pin = GPIO_PIN6,
//    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
//    .lcd_data[0].logic = GPIO_LOW,
//
//    .lcd_data[1].port = PORTC_INDEX,
//    .lcd_data[1].pin = GPIO_PIN7,
//    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
//    .lcd_data[1].logic = GPIO_LOW,
//
//    .lcd_data[2].port = PORTD_INDEX,
//    .lcd_data[2].pin = GPIO_PIN0,
//    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
//    .lcd_data[2].logic = GPIO_LOW,
//
//    .lcd_data[3].port = PORTD_INDEX,
//    .lcd_data[3].pin = GPIO_PIN1,
//    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
//    .lcd_data[3].logic = GPIO_LOW,
//};

void ecu_layer_initialize(void) {
    led_initialization(&led1);
    //    led_initialization(&led2);
    //    led_initialization(&led3);
    //    led_initialization(&led4);
    keypad_initialization(&keypad);
    //    lcd_4bit_initialize(&lcd_1);
}