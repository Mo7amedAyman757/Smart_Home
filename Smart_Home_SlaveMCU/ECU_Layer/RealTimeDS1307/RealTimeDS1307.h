/* 
 * File:   RealTimeDS1307.h
 * Author: LEGION
 *
 * Created on November 23, 2024, 1:26 PM
 */

#ifndef REALTIMEDS1307_H
#define	REALTIMEDS1307_H

#include "../../MCAL_Layer/I2C/hal_i2c.h"
#include "../UARTLoggingDebugData/UART_LoggingDebugData.h"

typedef struct {
    uint8 seconds;
    uint8 minutes;
    uint8 hours;
    uint8 day;
    uint8 month;
    uint8 year;
} RealTimeDS1307_t;

RealTimeDS1307_t RealTimeClockDS1307_Get_Date_Time(void);
void Print_Date(void);
#endif	/* REALTIMEDS1307_H */

