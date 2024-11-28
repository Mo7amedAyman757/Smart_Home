/* 
 * File:   ecu_seven_seg.c
 * Author: LEGION
 *
 * Created on September 3, 2024, 5:55 PM
 */

#include "ecu_seven_seg.h"

STD_ReturnType seven_segment_initialize(const segment_t *segment) {
    STD_ReturnType ret = E_OK;
    if (NULL == segment) {
        ret = E_NOK;
    } else {
        ret = gpio_pin_initialization(&(segment->segment_pins[SEGMENT_PIN0]));
        ret = gpio_pin_initialization(&(segment->segment_pins[SEGMENT_PIN1]));
        ret = gpio_pin_initialization(&(segment->segment_pins[SEGMENT_PIN2]));
        ret = gpio_pin_initialization(&(segment->segment_pins[SEGMENT_PIN3]));

    }
    return ret;
}

STD_ReturnType seven_segment_write_number(const segment_t *segment, uint8 number) {
    STD_ReturnType ret = E_OK;
    if (NULL == segment) {
        ret = E_NOK;
    } else {
        ret = gpio_pin_write_logic(&(segment->segment_pins[SEGMENT_PIN0]), (number >> 0) & 0x01);
        ret = gpio_pin_write_logic(&(segment->segment_pins[SEGMENT_PIN1]), (number >> 1) & 0x01);
        ret = gpio_pin_write_logic(&(segment->segment_pins[SEGMENT_PIN2]), (number >> 2) & 0x01);
        ret = gpio_pin_write_logic(&(segment->segment_pins[SEGMENT_PIN3]), (number >> 3) & 0x01);
    }
    return ret;
}