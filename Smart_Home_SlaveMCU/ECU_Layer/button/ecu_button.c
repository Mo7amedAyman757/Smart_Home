/* 
 * File:   ecu_button.c
 * Author: LEGION
 *
 * Created on September 2, 2024, 10:16 PM
 */

#include "ecu_button.h"

/**
 * 
 * @param btn
 * @return Status of function
 *         (E_OK): function success
 *         (E_NOK): function failed
 */
STD_ReturnType button_initialization(const button_t *btn) {
    STD_ReturnType ret = E_OK;
    if (NULL == btn) {
        ret = E_NOK;
    } else {
        ret = gpio_pin_direction_initializion(&(btn->button_pin));
    }
    return ret;
}

/**
 * 
 * @param btn
 * @param btn_state
 * @return Status of function
 *         (E_OK): function success
 *         (E_NOK): function failed
 */
STD_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state) {
    STD_ReturnType ret = E_OK;
    logic_t pin_logic_state = GPIO_LOW;
    if (NULL == btn) {
        ret = E_NOK;
    } else {
        gpio_pin_read_logic(&(btn->button_pin), &pin_logic_state);
        if (BUTTON_ACTIVE_HIGH == btn->button_connection) {
            if (GPIO_HIGH == pin_logic_state) {
                *btn_state = BUTTON_PRESSED;
            } else {
                *btn_state = BUTTON_RELEASED;
            }
        } else if (BUTTON_ACTIVE_LOW == btn->button_connection) {
            if (GPIO_HIGH == pin_logic_state) {
                *btn_state = BUTTON_RELEASED;
            } else {
                *btn_state = BUTTON_PRESSED;
            }
        }
    }
    return ret;
}