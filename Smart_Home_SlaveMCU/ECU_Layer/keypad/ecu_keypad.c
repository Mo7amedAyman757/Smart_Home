/* 
 * File:   ecu_keypad.h
 * Author: LEGION
 *
 * Created on September 6, 2024, 9:02 PM
 */

#include "ecu_keypad.h"

static const uint8 keypad_value [ECU_KEYPAD_ROWS][ECU_KEYPAD_COLUMNS] = {
    {'7', '8', '9'},
    {'4', '5', '6'},
    {'1', '2', '3'},
    {'*', '0', '#'},
};

STD_ReturnType keypad_initialization(const keypad_t *keypad) {
    STD_ReturnType ret = E_OK;
    uint8 rows_counter = 0, columns_counter = 0;
    if (NULL == keypad) {
        ret = E_NOK;
    } else {
        for (rows_counter = 0; rows_counter < ECU_KEYPAD_ROWS; rows_counter++) {
            gpio_pin_initialization(&(keypad->keypad_rows_pin[rows_counter]));
        }
        for (columns_counter = 0; columns_counter < ECU_KEYPAD_COLUMNS; columns_counter++) {
            gpio_pin_initialization(&(keypad->keypad_columns_pins[columns_counter]));
        }
    }
    return ret;
}

STD_ReturnType keypad_get_value(const keypad_t *keypad, uint8 * value) {
    STD_ReturnType ret = E_OK;
    uint8 rows_counter = 0, columns_counter = 0, l_counter = 0;
    logic_t column_logic = 0;
    if ((NULL == keypad) || (NULL == value)) {
        ret = E_NOK;
    } else {
        for (rows_counter = 0; rows_counter < ECU_KEYPAD_ROWS; rows_counter++) {
            // make all rows logic zero
            for (l_counter = 0; l_counter < ECU_KEYPAD_ROWS; l_counter++) {
                gpio_pin_write_logic(&(keypad->keypad_rows_pin[l_counter]), GPIO_LOW);
            }
            gpio_pin_write_logic(&(keypad->keypad_rows_pin[rows_counter]), GPIO_HIGH);
            for (columns_counter = 0; columns_counter < ECU_KEYPAD_COLUMNS; columns_counter++) {
                gpio_pin_read_logic(&(keypad->keypad_columns_pins[columns_counter]), &column_logic);
                if (column_logic == GPIO_HIGH) {
                    __delay_ms(10); // Add debouncing delay
                    gpio_pin_read_logic(&(keypad->keypad_columns_pins[columns_counter]), &column_logic);
                    if (column_logic == GPIO_HIGH) { // Confirm key press after debounce
                        *value = keypad_value[rows_counter][columns_counter]; // Assign the correct key value
                        return ret; // Exit after detecting the first key press
                    }
                }
            }
        }
    }
    return ret;
}