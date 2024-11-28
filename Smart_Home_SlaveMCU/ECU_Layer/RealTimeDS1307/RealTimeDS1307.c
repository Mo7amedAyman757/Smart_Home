/* 
 * File:   RealTimeDS1307.c
 * Author: LEGION
 *
 * Created on November 23, 2024, 1:26 PM
 */

#include "RealTimeDS1307.h"

static RealTimeDS1307_t RealTimeDS1307;
uint8 ack = 0;
extern mssp_i2c_t mssp_i2c1;
static uint8 Print_Pack_Date[18]; /* "Year" : "Month" : "Day" * "Hours" : "Minutes" : "Seconds" */

RealTimeDS1307_t RealTimeClockDS1307_Get_Date_Time(void) {
    uint8 buffer[7];
    /*Send Start*/
    MSSP_I2C_Master_Send_Start(&mssp_i2c1);
    /*Send Ds1307 Address with write bit*/
    MSSP_I2C_Master_Write_Blocking(&mssp_i2c1, 0xD0, &ack);
    /*Send starting register address (0x00)*/
    MSSP_I2C_Master_Write_Blocking(&mssp_i2c1, 0x00, &ack);
    // Send a repeated start to switch to read mode
    MSSP_I2C_Master_Send_Repeated_Start(&mssp_i2c1);
    // Send the DS1307 address with the read bit (0xD1)
    MSSP_I2C_Master_Write_Blocking(&mssp_i2c1, 0xD1, &ack);
    for (uint8 i = 0; i < 7; i++) {
        MSSP_I2C_Master_Read_Blocking(&mssp_i2c1, (i < 6) ? 0 : 1, &buffer[i]);
    }
    // Stop I2C communication
    MSSP_I2C_Master_Send_Stop(&mssp_i2c1);

    RealTimeDS1307.seconds = buffer[0];
    RealTimeDS1307.minutes = buffer[1];
    RealTimeDS1307.hours = buffer[2];
    RealTimeDS1307.day = buffer[4];
    RealTimeDS1307.month = buffer[5];
    RealTimeDS1307.year = buffer[6];
    return RealTimeDS1307;
}

void Print_Date(void) {
    Print_Pack_Date[0] = ((RealTimeDS1307.day >> 4) + 0x30);
    Print_Pack_Date[1] = ((RealTimeDS1307.day & 0x0F) + 0x30);
    Print_Pack_Date[2] = '-';

    Print_Pack_Date[3] = ((RealTimeDS1307.month >> 4) + 0x30);
    Print_Pack_Date[4] = ((RealTimeDS1307.month & 0x0F) + 0x30);
    Print_Pack_Date[5] = '-';

    Print_Pack_Date[6] = ((RealTimeDS1307.year >> 4) + 0x30);
    Print_Pack_Date[7] = ((RealTimeDS1307.year & 0x0F) + 0x30);
    Print_Pack_Date[8] = ' ';

    Print_Pack_Date[9] = ((RealTimeDS1307.hours >> 4) + 0x30);
    Print_Pack_Date[10] = ((RealTimeDS1307.hours & 0x0F) + 0x30);
    Print_Pack_Date[11] = '-';

    Print_Pack_Date[12] = ((RealTimeDS1307.minutes >> 4) + 0x30);
    Print_Pack_Date[13] = ((RealTimeDS1307.minutes & 0x0F) + 0x30);
    Print_Pack_Date[14] = '-';

    Print_Pack_Date[15] = ((RealTimeDS1307.seconds >> 4) + 0x30);
    Print_Pack_Date[16] = ((RealTimeDS1307.seconds & 0x0F) + 0x30);
    Print_Pack_Date[17] = '\r';

    UART_LoggingDebugData_Send_String("Date & time : ", 15);
    UART_LoggingDebugData_Send_String(Print_Pack_Date, 18);
}