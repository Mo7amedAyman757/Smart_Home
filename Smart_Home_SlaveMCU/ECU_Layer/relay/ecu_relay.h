/* 
 * File:   ecu_relay.h
 * Author: LEGION
 *
 * Created on September 3, 2024, 3:38 PM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/* Section : Includes */
#include "ecu_relay_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/*Section : Macro Declaration*/
#define RELAY_ON_STATUS   0x01U
#define RELAY_OFF_STATUS  0x00U
/*Section : Macro Function Declaration*/

/*Section : Data Type Declaration*/
typedef struct {
    uint8 relay_port : 4;
    uint8 relay_pin : 3;
    uint8 relay_status : 1;
} relay_t;


/*Section : Function Declaration*/
STD_ReturnType relay_initialization(const relay_t *relay);
STD_ReturnType relay_turn_on(const relay_t *relay);
STD_ReturnType relay_turn_off(const relay_t *relay);
#endif	/* ECU_RELAY_H */

