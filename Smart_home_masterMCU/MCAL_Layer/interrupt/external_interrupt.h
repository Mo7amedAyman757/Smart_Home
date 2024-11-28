/* 
 * File:   external_interrupt.h
 * Author: LEGION
 *
 * Created on September 25, 2024, 10:37 PM
 */

#ifndef EXTERNAL_INTERRUPT_H
#define	EXTERNAL_INTERRUPT_H

/* Section : Includes */
#include"mcal_interrupt.h"



/*Section : Macro Function Declaration*/
#if EXTERNAL_INTERRUPT_INTX_ENABLE == INTERRUPT_FEATURE_ENABLE
/**************INT0**************/
/*This macro enable external interrupt for INT0*/
#define EXT_INT0_INTERRUPT_ENABLE()            (INTCONbits.INT0IE = 1)
/*This macro disable external interrupt for INT0*/
#define EXT_INT0_INTERRUPT_DISABLE()           (INTCONbits.INT0IE = 0)
/*This macr clear interrupt flag for INT0*/
#define EXT_INT0_INTERRUPT_CLEAR_FLAG()        (INTCONbits.INT0IF = 0)
/*This macr set interrupt on rising edge for INT0*/
#define EXT_INT0_INTERRUPT_RISING_EDGE()     (INTCON2bits.INTEDG0 = 1)
/*This macr set interrupt on falling edge for INT0*/
#define EXT_INT0_INTERRUPT_FALLING_EDGE()    (INTCON2bits.INTEDG0 = 0)

/**************INT1**************/
/*This macro enable external interrupt for INT1*/
#define EXT_INT1_INTERRUPT_ENABLE()            (INTCON3bits.INT1IE = 1)
/*This macro disable external interrupt for INT1*/
#define EXT_INT1_INTERRUPT_DISABLE()           (INTCON3bits.INT1IE = 0)
/*This macr clear interrupt flag for INT1*/
#define EXT_INT1_INTERRUPT_CLEAR_FLAG()        (INTCON3bits.INT1IF = 0)
/*This macr set interrupt on rising edge for INT1*/
#define EXT_INT1_INTERRUPT_RISING_EDGE()      (INTCON2bits.INTEDG1 = 1)
/*This macr set interrupt on falling edge for INT1*/
#define EXT_INT1_INTERRUPT_FALLING_EDGE()     (INTCON2bits.INTEDG1 = 0)

/**************INT2**************/
/*This macro enable external interrupt for INT2*/
#define EXT_INT2_INTERRUPT_ENABLE()            (INTCON3bits.INT2IE = 1)
/*This macro disable external interrupt for INT2*/
#define EXT_INT2_INTERRUPT_DISABLE()           (INTCON3bits.INT2IE = 0)
/*This macr clear interrupt flag for INT2*/
#define EXT_INT2_INTERRUPT_CLEAR_FLAG()        (INTCON3bits.INT2IF = 0)
/*This macr set interrupt on rising edge for INT2*/
#define EXT_INT2_INTERRUPT_RISING_EDGE()      (INTCON2bits.INTEDG2 = 1)
/*This macr set interrupt on falling edge for INT2*/
#define EXT_INT2_INTERRUPT_FALLING_EDGE()     (INTCON2bits.INTEDG2 = 0)

/*******Set priority for INT1 or INT2*******/
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
/*this routine set the external interrupt priority to high,INT1*/
#define EXT_INT1_HIGH_PRIORITY_SET()   (INTCON3bits.INT1IP = 1)
/*this routine set the external interrupt priority to low,INT1*/
#define EXT_INT1_LOW_PRIORITY_SET()    (INTCON3bits.INT1IP = 0)
/*this routine set the external interrupt priority to high,INT2*/
#define EXT_INT2_HIGH_PRIORITY_SET()   (INTCON3bits.INT2IP = 1)
/*this routine set the external interrupt priority to low,INT2*/
#define EXT_INT2_LOW_PRIORITY_SET()    (INTCON3bits.INT2IP = 0)
#endif
#endif

#if EXTERNAL_INTERRUPT_ONCHANGE_ENABLE == INTERRUPT_FEATURE_ENABLE
/**************RBX**************/
/*This macro enable interrupt on change for RBX*/
#define EXT_RBX_INTERRUPT_ENABLE()           (INTCONbits.RBIE = 1)
/*This macro disable interrupt on change for RBX*/
#define EXT_RBX_INTERRUPT_DISABLE()          (INTCONbits.RBIE = 0)
/*This macro clear interrupt on change flag for RBX*/
#define EXT_RBX_INTERRUPT_CLEAR_FLAG()       (INTCONbits.RBIF = 0)
/* Enable interrupt-on-change for pin RB4 by setting the corresponding IOCB bit.*/
#define EXT_RB4_INTERRUPT_IOCB_ENABLE()      (IOCBbits.IOCB4 = 1)
/* Enable interrupt-on-change for pin RB5 by setting the corresponding IOCB bit.*/
#define EXT_RB5_INTERRUPT_IOCB_ENABLE()      (IOCBbits.IOCB5 = 1)
/* Enable interrupt-on-change for pin RB6 by setting the corresponding IOCB bit.*/
#define EXT_RB6_INTERRUPT_IOCB_ENABLE()      (IOCBbits.IOCB6 = 1)
/* Enable interrupt-on-change for pin RB7 by setting the corresponding IOCB bit.*/
#define EXT_RB7_INTERRUPT_IOCB_ENABLE()      (IOCBbits.IOCB7 = 1)

#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
/*this routine set the external interrupt priority to high,RBX*/
#define EXT_RBX_HIGH_PRIORITY_SET()   (INTCON2bits.RBIP = 1)
/*this routine set the external interrupt priority to low,RBX*/
#define EXT_RBX_LOW_PRIORITY_SET()   (INTCON2bits.RBIP = 0)
#endif
#endif

/*Section : Macro Declaration*/

/*Section : Data Type Declaration*/
typedef enum {
    INTERRUPT_FALLING_EDGE, // Falling edge trigger.
    INTERRUPT_RISING_EDGE, // Rising edge trigger.
} interrupt_INTx_edge;

typedef enum {
    INTERRUPT_EXTERNAL_INT0, // Interrupt source is INT0.
    INTERRUPT_EXTERNAL_INT1, // Interrupt source is INT1.
    INTERRUPT_EXTERNAL_INT2, // Interrupt source is INT2.
} interrupt_INTx_src;

typedef enum {
    INTERRUPT_EXTERNAL_RB4, // Interrupt source is RB4.
    INTERRUPT_EXTERNAL_RB5, // Interrupt source is RB5.
    INTERRUPT_EXTERNAL_RB6, // Interrupt source is RB6.
    INTERRUPT_EXTERNAL_RB7, // Interrupt source is RB7.
} interrupt_RBx_src;

typedef struct {
    void(* EXT_InterruptHandler)(void); // Function pointer for external interrupt handler.
    pin_config_t mcu_pin; // MCU pin configuration.
    interrupt_INTx_edge edge; // Interrupt edge (rising/falling).
    interrupt_INTx_src source; // Interrupt source (INT0/INT1/INT2).
    priority_level_t priority; // Priority level of the interrupt.
} interrupt_INTx_t;

typedef struct {
    void(* EXT_InterruptHandler_high)(void); // Function pointer for high-priority handler.
    void(* EXT_InterruptHandler_low)(void); // Function pointer for low-priority handler.
    pin_config_t mcu_pin; // MCU pin configuration.
    interrupt_RBx_src source; // Interrupt source (RB4/RB5/RB6/RB7).
    priority_level_t priority; // Priority level of the interrupt.
} interrupt_RBx_t;

/*Section : Function Declaration*/
STD_ReturnType interrupt_INTx_init(const interrupt_INTx_t * int_obj);
STD_ReturnType interrupt_INTx_deinit(const interrupt_INTx_t * int_obj);
STD_ReturnType interrupt_RBx_init(const interrupt_RBx_t * int_obj);
STD_ReturnType interrupt_RBx_deinit(const interrupt_RBx_t * int_obj);
/* EXTERNAL_INTERRUPT_H */

#endif