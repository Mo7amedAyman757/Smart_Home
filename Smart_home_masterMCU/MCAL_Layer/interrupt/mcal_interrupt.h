/* 
 * File:   mcal_interrupt.h
 * Author: LEGION
 *
 * Created on September 25, 2024, 10:36 PM
 */

#ifndef MCAL_INTERRUPT_H
#define	MCAL_INTERRUPT_H

/* Section : Includes */
#include"mcal_interrupt_cfg.h"

/*Section : Macro Declaration*/
#define INTERRUPT_ENABLE               1
#define INTERRUPT_DISABLE              0
#define INTERRUPT_OCCUR                1
#define INTERRUPT_NOT_OCCUR            0
#define INTERRUPT_PRIORITY_ENABLE      1
#define INTERRUPT_PRIORITY_DISABLE     0




/*Section : Macro Function Declaration*/
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This macro Interrupt Enable priority level on interrupt*/
#define INTERRUPT_Priority_level_Enable()      (RCONbits.IPEN = 1)
/*This macro Interrupt Disable priority level on interrupt*/
#define INTERRUPT_Priority_level_Disable()     (RCONbits.IPEN = 0)
/*This macro enable all global high priority interrupt*/
#define INTERRUPT_Global_InterruptHighEnable() (INTCONbits.GIEH = 1)
/*This macro disable all global high priority interrupt*/
#define INTERRUPT_Global_InterruptHighDisable() (INTCONbits.GIEH = 0)
/*This macro enable all global low priority interrupt*/
#define INTERRUPT_Global_InterruptLowEnable()  (INTCONbits.GIEL = 1)
/*This macro disable all global low priority interrupt*/
#define INTERRUPT_Global_InterruptLowDisable() (INTCONbits.GIEL = 0)
#else
/*This macro enable  global interrupt*/
#define INTERRUPT_GlobalInterruptEnable()        (INTCONbits.GIE = 1)
/*This macro disable  global interrupt*/
#define INTERRUPT_GlobalInterruptDisable()       (INTCONbits.GIE = 0)
/*This macro enable peripheral interrupt*/
#define INTERRUPT_PeripheralInterruptEnable()    (INTCONbits.PEIE = 1)
/*This macro disable peripheral interrupt*/
#define INTERRUPT_PeripheralInterruptDisable()   (INTCONbits.PEIE = 0)
#endif

/*Section : Data Type Declaration*/
typedef enum {
    INTERRUPT_LOW_PRIORITY,
    INTERRUPT_HIGH_PRIORITY
} priority_level_t;

/*Section : Function Declaration*/

#endif	/* MCAL_INTERRUPT_H */

