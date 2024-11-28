/* 
 * File:   hal_eeprom.h
 * Author: LEGION
 *
 * Created on September 26, 2024, 11:12 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H


/* Section : Includes */
#include "../interrupt/internal_interrupt.h"
#include "../GPIO/hal_gpio.h"

/*Section : Macro Declaration*/
/*Flash program or Data EEPROM memory select*/
#define  ACCESS_EEPROM_PROGRAM_MEMORY 0
#define  ACCESS_FLASH_PROGRAM_MEMORY  1

/*Flash program/Data EEPROM or configuration select*/
#define ACCESS_FLASH_EEPROM_MEMORY  0
#define ACCESS_CONFIG_REGISTERS     1

/*Flash program/Data EEPROM write enable*/
#define ENABLE_EEPROM_WRITE_CYCLE    1
#define INHIBITS_EEPROM_WRITE_CYCLE  0
/*Write control*/
#define INITIATES_DATA_EEPROM_WRITE_ERASE 1
#define DATA_EEPROM_WRITE_ERASE_COMPLETED 0
/*Read Control*/
#define INITIATES_DATA_EEPROM_READ 1
/*Section : Macro Function Declaration*/


/*Section : Data Type Declaration*/


/*Section : Function Declaration*/
STD_ReturnType data_EEPROM_WriteByte(uint16 data_loc, uint8 data);
STD_ReturnType data_EEPROM_ReadByte(uint16 data_loc, uint8 *data);

#endif	/* HAL_EEPROM_H */

