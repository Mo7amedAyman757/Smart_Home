/* 
 * File:   ecu_motor.h
 * Author: LEGION
 *
 * Created on September 3, 2024, 4:40 PM
 */

#ifndef ECU_MOTOR_H
#define	ECU_MOTOR_H

/* Section : Includes */
#include "ecu_motor_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/*Section : Macro Declaration*/
#define MOTOR_ON_STATUS  0x01U
#define MOTOR_OFF_STATUS 0x00U
/*Section : Macro Function Declaration*/

/*Section : Data Type Declaration*/
typedef struct {
    pin_config_t motor[2];
} motor_t;

/*Section : Function Declaration*/
STD_ReturnType motor_initialization(const motor_t *motor);
STD_ReturnType motor_move_forward(const motor_t *motor);
STD_ReturnType motor_move_backward(const motor_t *motor);
STD_ReturnType motor_stop(const motor_t *motor);
#endif	/* ECU_MOTOR_H */

