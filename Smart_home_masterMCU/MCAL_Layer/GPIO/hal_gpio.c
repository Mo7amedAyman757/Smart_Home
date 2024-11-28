/* 
 * File:   hal_gpio.h
 * Author: LEGION
 *
 * Created on September 2, 2024, 2:24 PM
 */

#include "hal_gpio.h"
/*Reference to the data direction control register*/
volatile uint8 *tris_register[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
/*Reference to the data latch register (read and write to data latch)*/
volatile uint8 *lat_register[] = {&LATA, &LATB, &LATC, &LATD, &LATE};
/*Reference to the port status register*/
volatile uint8 *port_register[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};

/**
 *  
 * @param _pin_config pointer to configuration @ref pin_config_t 
 * @return Status of function
 *         (E_OK): function success
 *         (E_NOK): function failed
 */
STD_ReturnType gpio_pin_direction_initializion(const pin_config_t *pin_config) {
    STD_ReturnType ret = E_OK;
    if ((NULL == pin_config) || (pin_config->pin > PORT_PIN_MAX_NUMBER - 1)) {
        ret = E_NOK;
    } else {
        switch (pin_config->direction) {
            case GPIO_DIRECTION_OUTPUT:
                CLEARBIT(*tris_register[pin_config->port], pin_config->pin);
                break;
            case GPIO_DIRECTION_INPUT:
                SETBIT(*tris_register[pin_config->port], pin_config->pin);
                break;
            default: ret = E_NOK;
        }
    }
    return ret;
}

/**
 * @breif
 * @param pin_config pointer to configuration 
 * @param direction_status
 * @return Status of function
 *         (E_OK): function success
 *         (E_NOK): function failed
 */
STD_ReturnType gpio_pin_direction_status(const pin_config_t *pin_config, direction_t *direction_status) {
    STD_ReturnType ret = E_OK;
    if ((NULL == pin_config) || (pin_config->pin > PORT_PIN_MAX_NUMBER - 1) || (NULL == direction_status)) {
        ret = E_NOK;
    } else {
        *direction_status = READBIT(*tris_register[pin_config->port], pin_config->pin);
    }
    return ret;

}

/**
 * @breif
 * @param pin_config pointer to configuration 
 * @param logic_status
 * @return Status of function
 *         (E_OK): function success
 *         (E_NOK): function failed
 */
STD_ReturnType gpio_pin_write_logic(const pin_config_t *pin_config, logic_t logic) {
    STD_ReturnType ret = E_OK;
    if ((NULL == pin_config) || (pin_config->pin > PORT_PIN_MAX_NUMBER - 1)) {
        ret = E_NOK;
    } else {
        switch (logic) {
            case GPIO_LOW:
                CLEARBIT(*lat_register[pin_config->port], pin_config->pin);
                break;
            case GPIO_HIGH:
                SETBIT(*lat_register[pin_config->port], pin_config->pin);
                break;
            default:
                ret = E_NOK;
        }
    }
    return ret;

}

/**
 * @breif
 * @param pin_config pointer to configuration 
 * @param logic_status
 * @return Status of function
 *         (E_OK): function success
 *         (E_NOK): function failed
 */
STD_ReturnType gpio_pin_read_logic(const pin_config_t *pin_config, logic_t *logic_status) {
    STD_ReturnType ret = E_OK;
    if ((NULL == pin_config) || (pin_config->pin >= PORT_PIN_MAX_NUMBER - 1) || (NULL == logic_status)) {
        ret = E_NOK;
    } else {
        *logic_status = READBIT(*port_register[pin_config->port], pin_config->pin);
    }
    return ret;

}

/**
 * @breif
 * @param pin_config pointer to configuration 
 * @return Status of function
 *         (E_OK): function success
 *         (E_NOK): function failed
 */
STD_ReturnType gpio_pin_toggle_logic(const pin_config_t *pin_config) {
    STD_ReturnType ret = E_OK;
    if ((NULL == pin_config) || (pin_config->pin > PORT_PIN_MAX_NUMBER - 1)) {
        ret = E_NOK;
    } else {
        TOGGLEBIT(*port_register[pin_config->port], pin_config->pin);
    }
    return ret;

}

/**
 * @breif
 * @param _pin_config pointer to configuration 
 * @return Status of function
 *         (E_OK): function success
 *         (E_NOK): function failed
 */
STD_ReturnType gpio_pin_initialization(const pin_config_t *pin_config) {
    STD_ReturnType ret = E_OK;
    if ((NULL == pin_config) || (pin_config->pin > PORT_PIN_MAX_NUMBER - 1)) {
        ret = E_NOK;
    } else {
        gpio_pin_direction_initializion(pin_config);
        gpio_pin_write_logic(pin_config, pin_config->logic);
    }
    return ret;


}

/**
 * @breif
 * @param port
 * @param direction
 * @return Status of function
 *         (E_OK): function success
 *         (E_NOK): function failed
 */
STD_ReturnType gpio_port_direction_initializion(const port_index_t port, uint8 direction) {
    STD_ReturnType ret = E_OK;
    if (port > PORT_MAX_NUMBER - 1) {
        ret = E_NOK;
    } else {
        *tris_register[port] = direction;
    }
    return ret;
}

STD_ReturnType gpio_port_direction_status(const port_index_t port, uint8 *direction_status) {
    STD_ReturnType ret = E_OK;
    if (port > PORT_MAX_NUMBER - 1) {
        ret = E_NOK;
    } else {
        *direction_status = *tris_register[port];
    }
    return ret;


}

STD_ReturnType gpio_port_write_logic(const port_index_t port, uint8 logic) {
    STD_ReturnType ret = E_OK;
    if (port > PORT_MAX_NUMBER - 1) {
        ret = E_NOK;
    } else {
        *lat_register[port] = logic;
    }
    return ret;


}

STD_ReturnType gpio_port_read_logic(const port_index_t port, uint8 *logic) {
    STD_ReturnType ret = E_OK;
    if (port > PORT_MAX_NUMBER - 1) {
        ret = E_NOK;
    } else {
        *logic = *lat_register[port];
    }
    return ret;


}

STD_ReturnType gpio_port_toggle_logic(const port_index_t port) {
    STD_ReturnType ret = E_OK;
    if (port > PORT_MAX_NUMBER - 1) {
        ret = E_NOK;
    } else {
        *lat_register[port] ^= PORT_MASK;
    }
    return ret;


}
