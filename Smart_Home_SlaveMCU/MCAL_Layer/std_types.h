/* 
 * File:   std_types.h
 * Author: LEGION
 *
 * Created on September 2, 2024, 2:28 PM
 */

#ifndef STD_TYPES_H
#define	STD_TYPES_H


/* Section : Includes */
#include "compiler.h"
#include "std_libraries.h"

/*Section : Macro Declaration*/
#define E_OK   (STD_ReturnType)0x01
#define E_NOK   (STD_ReturnType)0x00

/*Section : Macro Function Declaration*/

/*Section : Data Type Declaration*/
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;
typedef signed char sint8;
typedef signed short sint16;
typedef signed long sint32;

typedef uint8 STD_ReturnType; // from file of std_return_type of AUTOSAR

/*Section : Function Declaration*/

#endif	/* STD_TYPES_H */

