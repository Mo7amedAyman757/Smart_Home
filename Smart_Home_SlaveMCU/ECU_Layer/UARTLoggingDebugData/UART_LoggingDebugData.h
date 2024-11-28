/* 
 * File:   UART_LoggingDebugData.h
 * Author: LEGION
 *
 * Created on November 24, 2024, 2:12 PM
 */

#ifndef UART_LOGGINGDEBUGDATA_H
#define	UART_LOGGINGDEBUGDATA_H

#include "../../MCAL_Layer/eusart/hal_eusart.h"

void UART_LoggingDebugData_Send_String(const uint8 *Str, uint16 str_len);

#endif	/* UART_LOGGINGDEBUGDATA_H */

