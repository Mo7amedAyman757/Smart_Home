/* 
 * File:   application.h
 * Author: LEGION
 *
 * Created on September 2, 2024, 2:20 PM
 */

<<<<<<< HEAD
#include <pic18f46k20.h>

#include "application.h"

STD_ReturnType ret = E_OK;
uint8 Rec_TC74_Temp_Val = 0;
uint8 str;
=======
#include "application.h"

uint8 ack = 0;
STD_ReturnType ret = E_OK;
RealTimeDS1307_t RealTimeDS1307;

uint8 U4Program = 0;
uint8 TC74_A7_TempVal = 0;
uint8 last_temp_sent = 0xFF;
>>>>>>> 22c14f3ef1956f6bdab906416641732c28e078a6

int main() {
    application_initialize();

<<<<<<< HEAD
    while (1) {
        if (Rec_TC74_Temp_Val >= 45) {
            motor_stop(&motor1);
            motor_stop(&motor2);
            relay_turn_on(&relay1);
            lcd_4bit_send_char_string_pos(&lcd_1, 1, 1, "ALERT!        ");
        } else if (Rec_TC74_Temp_Val > 35) {
            motor_move_forward(&motor1);
            motor_move_forward(&motor2);
            relay_turn_off(&relay1);
            lcd_4bit_send_char_string_pos(&lcd_1, 1, 1, "System Normal!");
        } else {
            motor_move_backward(&motor1);
            motor_move_backward(&motor2);
            relay_turn_off(&relay1);
            lcd_4bit_send_char_string_pos(&lcd_1, 1, 1, "System Normal!");
        }
        __delay_ms(100);
=======
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
>>>>>>> 22c14f3ef1956f6bdab906416641732c28e078a6
    }
}

void application_initialize(void) {
    ecu_layer_initialize();
<<<<<<< HEAD
    MSSP_I2C_Init(&mssp_i2c2);
}

void I2C_DefaultInterruptHandler(void) {
    if (SSPSTATbits.R_nW == 0) { // Check if master is writing data (not reading)
        if (SSPSTATbits.BF == 1) { // Check if buffer is full (data is available)
            Rec_TC74_Temp_Val = SSPBUF; // Read the received data into the variable
            SSPCON1bits.CKP = 1; // Release the clock line
        }
    }
}


=======
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
>>>>>>> 22c14f3ef1956f6bdab906416641732c28e078a6
