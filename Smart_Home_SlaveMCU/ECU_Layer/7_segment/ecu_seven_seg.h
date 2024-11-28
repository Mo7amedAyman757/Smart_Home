/* 
 * File:   ecu_seven_seg.h
 * Author: LEGION
 *
 * Created on September 3, 2024, 5:55 PM
 */

#ifndef ECU_SEVEN_SEG_H
#define	ECU_SEVEN_SEG_H

/* Section : Includes */
#include "ecu_seven_seg_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/*Section : Macro Declaration*/
#define  SEGMENT_PIN0 0
#define  SEGMENT_PIN1 1
#define  SEGMENT_PIN2 2
#define  SEGMENT_PIN3 3
/*Section : Macro Function Declaration*/

/*Section : Data Type Declaration*/
typedef enum {
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE,
} segment_type_t;

typedef struct {
    pin_config_t segment_pins[4];
    segment_type_t segment_type;
} segment_t;
/*Section : Function Declaration*/
STD_ReturnType seven_segment_initialize(const segment_t *segment);

STD_ReturnType seven_segment_write_number(const segment_t *segment, uint8 number);
#endif	/* ECU_SEVEN_SEG_H */

