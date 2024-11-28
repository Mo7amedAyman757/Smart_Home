/* 
 * File:   hal_timer1.h
 * Author: LEGION
 *
 * Created on October 10, 2024, 7:23 AM
 */

#ifndef HAL_TIMER1_H
#define	HAL_TIMER1_H

/* Section : Includes */
#include "../GPIO/hal_gpio.h"
#include "../interrupt/internal_interrupt.h"
/*Section : Macro Declaration*/
#define TIMER1_TIMER_MODE_CFG        0  // Timer1 operates in Timer mode.
#define TIMER1_COUNTER_MODE_CFG      1  // Timer1 operates in Counter mode.

#define TIMER1_RW_REG_8BIT_CFG       0  // Timer1 uses 8-bit read/write mode.
#define TIMER1_RW_REG_16BIT_CFG      1  // Timer1 uses 16-bit read/write mode.

#define TIMER1_SYNC_COUNTER_CFG      0  // Timer1 runs in Synchronized Counter mode.
#define TIMER1_ASYNC_COUNTER_CFG     1  // Timer1 runs in Asynchronous Counter mode.

/*Section : Macro Function Declaration*/
/*ENABLE TIMER1*/
#define TIMER1_ENABLE()            (T1CONbits.TMR1ON = 1)
/*DISABLE TIMER1*/
#define TIMER1_DISABLE()           (T1CONbits.TMR1ON = 0)
/*Configure Timer1 as timer */
#define TIMER1_TIMER_MODE()        (T1CONbits.TMR1CS = 0)
/*Configure Timer1 as COUNTER */
#define TIMER1_COUNTER_MODE()      (T1CONbits.TMR1CS = 1)
/*Timer1 synchronization with external clock*/
#define TIMER1_SYNC_COUNTER()      (T1CONbits.T1SYNC = 0)
/*Timer1 Asynchronize with external clock*/
#define TIMER1_ASYNC_COUNTER()     (T1CONbits.T1SYNC = 1)
/*TIMER1 Oscillator enable*/
#define TIMER1_OSC_ENABLE()        (T1CONbits.T1OSCEN = 1)
/*TIMER1 Oscillator disable*/
#define TIMER1_OSC_DISABLE()       (T1CONbits.T1OSCEN = 0)
/*Configure prescale value*/
#define TIMER1_PRESACALE_Val(_VAL) (T1CONbits.T1CKPS = _VAL)
/*Configure RW_REG as two 8-bit*/
#define TIMER1_RW_REG_8BIT()       (T1CONbits.RD16 = 0)
/*Configure RW_REG as two 16-bit*/
#define TIMER1_RW_REG_16BIT()      (T1CONbits.RD16 = 1)
/*READ System Clock Status bit*/
#define TIMER2_CLOCK_STATUS()      (T1CONbits.T1RUN)

/*Section : Data Type Declaration*/
typedef enum {
    TIMER1_PRESCALER_DIV_BY_1, // Prescaler divides the clock by 2.
    TIMER1_PRESCALER_DIV_BY_2, // Prescaler divides the clock by 4.
    TIMER1_PRESCALER_DIV_BY_4, // Prescaler divides the clock by 8.
    TIMER1_PRESCALER_DIV_BY_8, // Prescaler divides the clock by 16.
} timer1_prescaler_select_t;

typedef struct {
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void(* timer1_InterruptHandler)(void); // Function pointer to Timer1 interrupt service routine (ISR).
    priority_level_t priority; // Priority level for the Timer1 interrupt.
#endif
    uint16 preload_val; // Preload value to initialize Timer1 register.
    uint8 timer1_mode : 1; // Mode selection: 0 for Timer, 1 for Counter (1 bit)
    uint8 timer1_counter_cfg : 1; // Counter configuration: determines the Synchronization configuration for counting.
    uint8 timer1_osc_cfg : 1; // Timer1 oscillator enable configuration.
    timer1_prescaler_select_t timer1_prescaler; // Holds the selected prescaler division factor.
    uint8 timer1_reg : 1; // Register mode: 1 for 16-bit, 0 for 8-bit (1 bit).
} timer1_t;
/*Section : Function Declaration*/
STD_ReturnType timer1_init(const timer1_t *timer);
STD_ReturnType timer1_Deinit(const timer1_t *timer);
STD_ReturnType timer1_write_value(const timer1_t *timer, uint16 value);
STD_ReturnType timer1_read_value(const timer1_t *timer, uint16 *value);

#endif	/* HAL_TIMER1_H */

