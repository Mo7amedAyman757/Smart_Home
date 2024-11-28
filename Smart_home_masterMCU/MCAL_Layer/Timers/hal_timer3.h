/* 
 * File:   hal_timer3.h
 * Author: LEGION
 *
 * Created on October 10, 2024, 9:30 AM
 */

#ifndef HAL_TIMER3_H
#define	HAL_TIMER3_H

/* Section : Includes */
#include "../GPIO/hal_gpio.h"
#include "../interrupt/internal_interrupt.h"
/*Section : Macro Declaration*/
#define TIMER3_TIMER_MODE_CFG        0  // Timer3 operates in Timer mode.
#define TIMER3_COUNTER_MODE_CFG      1  // Timer3 operates in Counter mode.

#define TIMER3_RW_REG_8BIT_CFG       0  // Timer3 uses 8-bit read/write mode.
#define TIMER3_RW_REG_16BIT_CFG      1  // Timer3 uses 16-bit read/write mode.

#define TIMER3_SYNC_COUNTER_CFG      0  // Timer3 runs in Synchronized Counter mode.
#define TIMER3_ASYNC_COUNTER_CFG     1  // Timer3 runs in Asynchronous Counter mode.

/*Section : Macro Function Declaration*/
/*ENABLE TIMER3*/
#define TIMER3_ENABLE()            (T3CONbits.TMR3ON = 1)
/*DISABLE TIMER3*/
#define TIMER3_DISABLE()           (T3CONbits.TMR3ON = 0)
/*Configure Timer3 as timer */
#define TIMER3_TIMER_MODE()        (T3CONbits.TMR3CS = 0)
/*Configure Timer3 as COUNTER */
#define TIMER3_COUNTER_MODE()      (T3CONbits.TMR3CS = 1)
/*Timer3 synchronization with external clock*/
#define TIMER3_SYNC_COUNTER()      (T3CONbits.T3SYNC = 0)
/*Timer3 Asynchronize with external clock*/
#define TIMER3_ASYNC_COUNTER()     (T3CONbits.T3SYNC = 1)
/*Configure prescale value*/
#define TIMER3_PRESACALE_Val(_VAL) (T3CONbits.T3CKPS = _VAL)
/*Configure RW_REG as two 8-bit*/
#define TIMER3_RW_REG_8BIT()       (T3CONbits.RD16 = 0)
/*Configure RW_REG as two 16-bit*/
#define TIMER3_RW_REG_16BIT()      (T3CONbits.RD16 = 1)

/*Section : Data Type Declaration*/
typedef enum {
    TIMER3_PRESCALER_DIV_BY_1, // Prescaler divides the clock by 2.
    TIMER3_PRESCALER_DIV_BY_2, // Prescaler divides the clock by 4.
    TIMER3_PRESCALER_DIV_BY_4, // Prescaler divides the clock by 8.
    TIMER3_PRESCALER_DIV_BY_8, // Prescaler divides the clock by 16.
} timer3_prescaler_select_t;

typedef struct {
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void(* timer3_InterruptHandler)(void); // Function pointer to Timer1 interrupt service routine (ISR).
    priority_level_t priority; // Priority level for the Timer3 interrupt.
#endif
    uint16 preload_val; // Preload value to initialize Timer3 register.
    uint8 timer3_mode : 1; // Mode selection: 0 for Timer, 1 for Counter (1 bit)
    uint8 timer3_counter_cfg : 1; // Counter configuration: determines the Synchronization configuration for counting.
    timer3_prescaler_select_t timer3_prescaler; // Holds the selected prescaler division factor.
    uint8 timer3_reg : 1; // Register mode: 1 for 16-bit, 0 for 8-bit (1 bit).
} timer3_t;
/*Section : Function Declaration*/
STD_ReturnType Timer3_Init(const timer3_t *timer);
STD_ReturnType Timer3_DeInit(const timer3_t *timer);
STD_ReturnType Timer3_Write_value(const timer3_t *timer, uint16 value);
STD_ReturnType Timer3_Read_value(const timer3_t *timer, uint16 *value);
#endif	/* HAL_TIMER3_H */

