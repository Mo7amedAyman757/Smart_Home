/* 
 * File:   ecu_motor.c
 * Author: LEGION
 *
 * Created on September 3, 2024, 4:40 PM
 */

#include "ecu_motor.h"

/**
 * 
 * @param motor
 * @return 
 */
STD_ReturnType motor_initialization(const motor_t *motor) {
    STD_ReturnType ret = E_OK;
    if (NULL == motor) {
        ret = E_NOK;
    } else {
        gpio_pin_initialization(&(motor->motor[0]));
        gpio_pin_initialization(&(motor->motor[1]));
    }
    return ret;
}

/**
 * 
 * @param motor
 * @return 
 */
STD_ReturnType motor_move_forward(const motor_t *motor) {
    STD_ReturnType ret = E_OK;
    if (NULL == motor) {
        ret = E_NOK;
    } else {
        gpio_pin_write_logic(&(motor->motor[0]), GPIO_HIGH);
        gpio_pin_write_logic(&(motor->motor[1]), GPIO_LOW);
    }
    return ret;
}

/**
 * 
 * @param motor
 * @return 
 */
STD_ReturnType motor_move_backward(const motor_t *motor) {
    STD_ReturnType ret = E_OK;
    if (NULL == motor) {
        ret = E_NOK;
    } else {
        gpio_pin_write_logic(&(motor->motor[0]), GPIO_LOW);
        gpio_pin_write_logic(&(motor->motor[1]), GPIO_HIGH);
    }
    return ret;
}

/**
 * 
 * @param motor
 * @return 
 */
STD_ReturnType motor_stop(const motor_t *motor) {
    STD_ReturnType ret = E_OK;
    if (NULL == motor) {
        ret = E_NOK;
    } else {
        gpio_pin_write_logic(&(motor->motor[0]), GPIO_LOW);
        gpio_pin_write_logic(&(motor->motor[1]), GPIO_LOW);
    }
    return ret;
}