/* 
 * File:   hal_eeprom.c
 * Author: LEGION
 *
 * Created on September 26, 2024, 11:12 PM
 */

#include "hal_eeprom.h"

/**
 * @brief Write a byte of data to a specified EEPROM address.
 * 
 * This function writes a single byte to the EEPROM at the address
 * specified by the `data_loc`. The operation's success or failure
 * is returned as a `STD_ReturnType` value.
 * 
 * @param data_loc The address in EEPROM (16-bit) where the byte will be written.
 *                 Since EEPROM can have more than 256 addresses, a 16-bit integer is used.
 * @param data     The byte (8-bit) to be written to the EEPROM at the specified address.
 *                 EEPROM stores data as 8-bit values.
 * 
 * @return STD_ReturnType The return status of the function. Typically, a custom return
 *         type that indicates success (e.g., `E_OK`) or failure (e.g., `E_NOT_OK`).
 */
STD_ReturnType data_EEPROM_WriteByte(uint16 data_loc, uint8 data) {
    STD_ReturnType ret = E_OK;
    /*Read Interrupt status*/
    uint8 GlobalInterruptStatus = INTCONbits.GIE;
    /*Write Address to EEADRH & EEADR*/
    EEADRH = (uint8) ((data_loc >> 8)& 0x03);
    EEADR = (uint8) (data_loc & 0xFF);
    /*Write data to EEDATA*/
    EEDATA = data;
    /*clear EEPGD & CFGS to access EEPROM*/
    EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
    CFGS = ACCESS_FLASH_EEPROM_MEMORY;
    /*Set Write Enable cycle*/
    EECON1bits.WREN = ENABLE_EEPROM_WRITE_CYCLE;
    /*Disable Interrupt*/
    INTERRUPT_GlobalInterruptDisable();
    /*Write required sequence 0x55 --> 0xAA*/
    EECON2 = 0x55;
    EECON2 = 0xAA;
    /*Set write control bit*/
    EECON1bits.WR = INITIATES_DATA_EEPROM_WRITE_ERASE;
    /*wait for complete write cycle*/
    while (EECON1bits.WR);
    /*Inhibits write cycle*/
    EECON1bits.WREN = INHIBITS_EEPROM_WRITE_CYCLE;
    /*Restore Interrupt Status*/
    INTCONbits.GIE = GlobalInterruptStatus;
    return ret;
}

/**
 * @brief Read a byte of data from a specified EEPROM address.
 * 
 * This function reads a single byte from the EEPROM at the address
 * specified by the `data_loc`. The byte is stored in the variable
 * pointed to by `data`. The operation's success or failure is
 * returned as a `STD_ReturnType` value.
 * 
 * @param data_loc The address in EEPROM (16-bit) from which the byte will be read.
 *                 Since EEPROM can have more than 256 addresses, a 16-bit integer is used.
 * @param data     A pointer to an 8-bit variable where the read byte will be stored.
 *                 The function writes the byte from EEPROM into the variable that 
 *                 `data` points to.
 * 
 * @return STD_ReturnType The return status of the function. Typically, a custom return
 *         type that indicates success (e.g., `E_OK`) or failure (e.g., `E_NOT_OK`).
 */
STD_ReturnType data_EEPROM_ReadByte(uint16 data_loc, uint8 *data) {
    STD_ReturnType ret = E_NOK;
    if (NULL == data) {
        ret = E_NOK;
    } else {
        /*Write Address to EEADRH & EEADR*/
        EEADRH = (uint8) ((data_loc >> 8)& 0x03);
        EEADR = (uint8) (data_loc & 0xFF);
        /*clear EEPGD & CFGS to access EEPROM*/
        EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
        CFGS = ACCESS_FLASH_EEPROM_MEMORY;
        /*initiates data EEPROM Read cycle*/
        EECON1bits.RD = INITIATES_DATA_EEPROM_READ;
        /*Wait at least 2 NOPS*/
        NOP();
        NOP();
        *data = EEDATA;
    }
    return ret;
}
