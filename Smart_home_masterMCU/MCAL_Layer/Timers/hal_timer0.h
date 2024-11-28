/* 
 * File:   hal_timer0.h
 * Author: LEGION
 *
 * Created on October 10, 2024, 6:18 AM
 */

#ifndef HAL_TIMER0_H
#define	HAL_TIMER0_H

/* Section : Includes */
#include "../GPIO/hal_gpio.h"
#include "../interrupt/internal_interrupt.h"
/*Section : Macro Declaration*/
#define timer0_8_bit_reg        1   // Configure Timer0 to operate in 8-bit mode.
#define timer0_16_bit_reg       0   // Configure Timer0 to operate in 16-bit mode.

#define timer0_timer_cfg        0   // Set Timer0 to work as a timer.
#define timer0_counter_cfg      1   // Set Timer0 to work as a counter.

#define timer0_rising_edge      0   // Capture on rising edge of the external signal (incorrect duplicate macro, should be fixed).
#define timer0_falling_edge     1   // Capture on falling edge of the external signal.

#define prescaler_enable_cfg    0   // Enable the prescaler for Timer0.
#define prescaler_disable_cfg   1   // Disable the prescaler for Timer0 (fixed typo: 'disnable' to 'disable').

/*Section : Macro Function Declaration*/
/*ENABLE Timer 0*/
#define TIMER0_ENABLE()           (T0CONbits.TMR0ON = 1)
/*DISABLE Timer 0*/
#define TIMER0_DISABLE()          (T0CONbits.TMR0ON = 0)
/*configure timer0 as 8-bit*/
#define TIMER0_8BIT_REG()         (T0CONbits.T08BIT = 1)
/*configure timer0 as 16-bit*/
#define TIMER0_16BIT_REG()        (T0CONbits.T08BIT = 0)
/*Configure timer as counter*/
#define TIMER0_COUTNER_MODE()     (T0CONbits.T0CS = 1)
/*Configure timer as timer*/
#define TIMER0_TIMER_MODE()       (T0CONbits.T0CS = 0)
/*configure timer to increment on rising edge*/
#define TIMER0_INC_RISING_EDGE()  (T0CONbits.T0SE = 0)
/*configure timer to increment on rising edge*/
#define TIMER0_INC_FALLING_EDGE() (T0CONbits.T0SE = 1)
/*Enable Prescaler*/
#define TIMER0_PRESACLER_ENABLE() (T0CONbits.PSA = 0)
/*Disable Prescaler*/
#define TIMER0_PRESACLER_DISABLE() (T0CONbits.PSA = 1)

/*Section : Data Type Declaration*/
typedef enum {
    PRESCALER_DIV_BY_2, // Prescaler divides the clock by 2.
    TIMER0_PRESCALER_DIV_BY_4, // Prescaler divides the clock by 4.
    TIMER0_PRESCALER_DIV_BY_8, // Prescaler divides the clock by 8.
    TIMER0_PRESCALER_DIV_BY_16, // Prescaler divides the clock by 16.
    TIMER0_PRESCALER_DIV_BY_32, // Prescaler divides the clock by 32.
    TIMER0_PRESCALER_DIV_BY_64, // Prescaler divides the clock by 64.
    TIMER0_PRESCALER_DIV_BY_128, // Prescaler divides the clock by 128.
    TIMER0_PRESCALER_DIV_BY_256, // Prescaler divides the clock by 256.
} timer0_prescaler_select_t; // Enum to select the prescaler division factor for Timer0.

typedef struct {
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void(* timer0_InterruptHandler)(void); // Function pointer to Timer0 interrupt service routine (ISR).
    priority_level_t priority; // Priority level for the Timer0 interrupt.
#endif
    timer0_prescaler_select_t prescaler_value; // Holds the selected prescaler division factor.
    uint16 preload_value; // Preload value to initialize Timer0 register.
    uint8 prescaler_enable : 1; // Enable or disable the prescaler (1 bit).
    uint8 timer0_mode : 1; // Mode selection: 0 for Timer, 1 for Counter (1 bit).
    uint8 timer0_source_edge : 1; // Source edge selection: 0 for rising, 1 for falling (1 bit).
    uint8 timer0_reg : 1; // Register mode: 0 for 16-bit, 1 for 8-bit (1 bit).
} timer0_t; // Struct that contains the configuration for Timer0.


/*Section : Function Declaration*/
STD_ReturnType timer0_init(const timer0_t *timer);
STD_ReturnType timer0_Deinit(const timer0_t *timer);
STD_ReturnType timer0_write_value(const timer0_t *timer, uint16 value);
STD_ReturnType timer0_read_value(const timer0_t *timer, uint16 *value);
#endif	/* HAL_TIMER0_H */

