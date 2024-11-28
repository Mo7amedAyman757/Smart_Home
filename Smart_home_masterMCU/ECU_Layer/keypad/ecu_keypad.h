/* 
 * File:   ecu_keypad.h
 * Author: LEGION
 *
 * Created on September 6, 2024, 9:02 PM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/* Section : Includes */
#include "ecu_keypad_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
/*Section : Macro Declaration*/
#define ECU_KEYPAD_ROWS    4
#define ECU_KEYPAD_COLUMNS 3

/*Section : Macro Function Declaration*/

/*Section : Data Type Declaration*/
typedef struct {
    pin_config_t keypad_rows_pin[ECU_KEYPAD_ROWS];
    pin_config_t keypad_columns_pins[ECU_KEYPAD_COLUMNS];
} keypad_t;
/*Section : Function Declaration*/
STD_ReturnType keypad_initialization(const keypad_t *keypad);
STD_ReturnType keypad_get_value(const keypad_t *keypad, uint8 *value);

#endif	/* ECU_KEYPAD_H */

