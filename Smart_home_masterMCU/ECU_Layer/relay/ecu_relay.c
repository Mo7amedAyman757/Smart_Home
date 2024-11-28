/* 
 * File:   ecu_relay.c
 * Author: LEGION
 *
 * Created on September 3, 2024, 3:38 PM
 */

#include "ecu_relay.h"

/**
 * 
 * @param relay
 * @return 
 */
STD_ReturnType relay_initialization(const relay_t *relay) {
    STD_ReturnType ret = E_OK;
    if (NULL == relay) {
        ret = E_NOK;
    } else {
        pin_config_t pin_obj = {
            .port = relay->relay_port,
            .pin = relay->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = relay->relay_status,
        };
        gpio_pin_initialization(&pin_obj);
    }
    return ret;
}

/**
 * 
 * @param relay
 * @return 
 */
STD_ReturnType relay_turn_on(const relay_t *relay) {
    STD_ReturnType ret = E_OK;
    if (NULL == relay) {
        ret = E_NOK;
    } else {
        pin_config_t pin_obj = {
            .port = relay->relay_port,
            .pin = relay->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = relay->relay_status,
        };
        gpio_pin_write_logic(&pin_obj, GPIO_HIGH);
    }
    return ret;
}

/**
 * 
 * @param relay
 * @return 
 */
STD_ReturnType relay_turn_off(const relay_t *relay) {
    STD_ReturnType ret = E_OK;
    if (NULL == relay) {
        ret = E_NOK;
    } else {
        pin_config_t pin_obj = {
            .port = relay->relay_port,
            .pin = relay->relay_pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = relay->relay_status,
        };
        gpio_pin_write_logic(&pin_obj, GPIO_LOW);
    }
    return ret;
}