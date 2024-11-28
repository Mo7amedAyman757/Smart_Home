/* 
 * File:   UART_LoggingDebugData.c
 * Author: LEGION
 *
 * Created on November 24, 2024, 2:12 PM
 */

#include "UART_LoggingDebugData.h"

extern usart_t usart1;

void UART_LoggingDebugData_Send_String(const uint8 *Str, uint16 str_len) {
    EUSART_ASYNC_WRITE_STRING_BLOCKING(&usart1, Str, str_len);
}