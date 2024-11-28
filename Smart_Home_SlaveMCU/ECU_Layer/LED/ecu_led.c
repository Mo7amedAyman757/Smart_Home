/* 
 * File:   ecu_led.c
 * Author: LEGION
 *
 * Created on September 2, 2024, 9:43 PM
 */

#include "ecu_led.h"

/**
 * @breif Initialize the assigned pin to be output and turn the led off
 * @param led
 * @return Status of function
 *         (E_OK): function success
 *         (E_NOK): function failed
 */
STD_ReturnType led_initialization(const led_t *led) {
    STD_ReturnType ret = E_OK;
    if (NULL == led) {
        ret = E_NOK;
    } else {
        pin_config_t pin_obj = {
            .port = led->port,
            .pin = led->pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = led->led_status
        };
        gpio_pin_initialization(&pin_obj);
    }
    return ret;
}

STD_ReturnType led_turn_on(const led_t *led) {
    STD_ReturnType ret = E_OK;
    if (NULL == led) {
        ret = E_NOK;
    } else {
        pin_config_t pin_obj = {
            .port = led->port,
            .pin = led->pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = led->led_status
        };
        ret = gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    }
    return ret;

}

STD_ReturnType led_turn_off(const led_t *led) {
    STD_ReturnType ret = E_OK;
    if (NULL == led) {
        ret = E_NOK;
    } else {
        pin_config_t pin_obj = {
            .port = led->port,
            .pin = led->pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = led->led_status
        };
        ret = gpio_pin_write_logic(&pin_obj, GPIO_LOW);

    }
    return ret;

}

STD_ReturnType led_toggle(const led_t *led) {
    STD_ReturnType ret = E_OK;
    if (NULL == led) {
        ret = E_NOK;
    } else {
        pin_config_t pin_obj = {
            .port = led->port,
            .pin = led->pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = led->led_status
        };
        ret = gpio_pin_toggle_logic(&pin_obj);
    }
    return ret;


}