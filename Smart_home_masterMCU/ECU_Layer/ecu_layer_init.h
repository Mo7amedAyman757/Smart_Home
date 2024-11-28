/* 
 * File:   ecu_layer_init.h
 * Author: LEGION
 *
 * Created on September 2, 2024, 3:10 PM
 */

#ifndef ECU_LAYER_INIT_H
#define	ECU_LAYER_INIT_H

/* Section : Includes */
#include "LED/ecu_led.h"
#include "button/ecu_button.h"
#include "relay/ecu_relay.h"
#include "motor/ecu_motor.h"
#include "7_segment/ecu_seven_seg.h"
#include "keypad/ecu_keypad.h"
#include "chr_lcd/chr_lcd.h"
#include "RealTimeDS1307/RealTimeDS1307.h"
#include "UARTLoggingDebugData/UART_LoggingDebugData.h"
#include "EEPROM_24C02C/EEPROM_24C02C.h"
#include "TempSensor_TC74/TempSensor_TC74.h"
void ecu_layer_initialize(void);

#endif	/* ECU_LAYER_INIT_H */

