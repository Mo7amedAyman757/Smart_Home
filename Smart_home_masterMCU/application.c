/* 
 * File:   application.h
 * Author: LEGION
 *
 * Created on September 2, 2024, 2:20 PM
 */

#include "application.h"

uint8 ack = 0;
STD_ReturnType ret = E_OK;
RealTimeDS1307_t RealTimeDS1307;

uint8 U4Program = 0;
uint8 TC74_A7_TempVal = 0;
uint8 last_temp_sent = 0xFF;

int main() {
    application_initialize();

    UART_LoggingDebugData_Send_String((uint8 *) "System Started\r", 16);

    while (1) {
        RealTimeDS1307 = RealTimeClockDS1307_Get_Date_Time();
        Print_Date();
        TC74_A7_TempVal = TempSensor_TC74_Read_Temp(0x9E);
        //EEPROM_24C02C_Write_Byte(0xA2, 0x00, TC74_A7_TempVal);
        //I2C_Master_Call_Slave(0x70, TC74_A7_TempVal);
        // Send the temperature to the slave only if it has changed
        if (TC74_A7_TempVal != last_temp_sent) {
            EEPROM_24C02C_Write_Byte(0xA2, 0x00, TC74_A7_TempVal);
            I2C_Master_Call_Slave(0x70, TC74_A7_TempVal);
            last_temp_sent = TC74_A7_TempVal; // Update the last sent temperature
        }
        __delay_ms(1000);
    }
}

void application_initialize(void) {
    ecu_layer_initialize();
    EUSART_ASYNC_INIT(&usart1);
    MSSP_I2C_Init(&mssp_i2c1);
}

void I2C_Master_Call_Slave(uint8 Slave_Address, uint8 temp) {
    //Slave_Address --> 0x70
    MSSP_I2C_Master_Send_Start(&mssp_i2c1);
    /*Send Slave Address with write bit*/
    MSSP_I2C_Master_Write_Blocking(&mssp_i2c1, Slave_Address, &ack);
    // Send temperature value
    MSSP_I2C_Master_Write_Blocking(&mssp_i2c1, temp, &ack);
    // Stop I2C communication
    MSSP_I2C_Master_Send_Stop(&mssp_i2c1);
}

//void INT0_App_ISR(void) {
//    EEPROM_24C02C_Write_Byte(0xA2, 0x00, 0x01);
//    __delay_ms(5);
//    U4Program = EEPROM_24C02C_Read_Byte(0xA2, 0x00);
//}
//
//void INT1_App_ISR(void) {
//    EEPROM_24C02C_Write_Byte(0xA2, 0x00, 0x02);
//    __delay_ms(5);
//    U4Program = EEPROM_24C02C_Read_Byte(0xA2, 0x00);
//}
//
//void INT2_App_ISR(void) {
//    EEPROM_24C02C_Write_Byte(0xA2, 0x00, 0x03);
//    __delay_ms(5);
//    U4Program = EEPROM_24C02C_Read_Byte(0xA2, 0x00);
//}