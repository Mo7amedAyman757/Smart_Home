/* 
 * File:   hal_timer2.h
 * Author: LEGION
 *
 * Created on October 10, 2024, 8:54 AM
 */

#ifndef HAL_TIMER2_H
#define	HAL_TIMER2_H

/* Section : Includes */
#include "../GPIO/hal_gpio.h"
#include "../interrupt/internal_interrupt.h"
/*Section : Macro Declaration*/
/*TIMER2 INPUT CLOCK POSTSCALER*/
#define TIMER2_POSTSCALER_DIV_BY_1                 0
#define TIMER2_POSTSCALER_DIV_BY_2                 1
#define TIMER2_POSTSCALER_DIV_BY_3                 2
#define TIMER2_POSTSCALER_DIV_BY_4                 3
#define TIMER2_POSTSCALER_DIV_BY_5                 4
#define TIMER2_POSTSCALER_DIV_BY_6                 5
#define TIMER2_POSTSCALER_DIV_BY_7                 6 
#define TIMER2_POSTSCALER_DIV_BY_8                 7
#define TIMER2_POSTSCALER_DIV_BY_9                 8
#define TIMER2_POSTSCALER_DIV_BY_10                9
#define TIMER2_POSTSCALER_DIV_BY_11                10
#define TIMER2_POSTSCALER_DIV_BY_12                11
#define TIMER2_POSTSCALER_DIV_BY_13                12
#define TIMER2_POSTSCALER_DIV_BY_14                13
#define TIMER2_POSTSCALER_DIV_BY_15                14
#define TIMER2_POSTSCALER_DIV_BY_16                15

/*TIMER2 INPUT CLOCK PRESCALER*/
#define TIMER2_PRESCALER_DIV_BY_1                0
#define TIMER2_PRESCALER_DIV_BY_4                1
#define TIMER2_PRESCALER_DIV_BY_16               2

/*Section : Macro Function Declaration*/
/*ENABLE TIMER2*/
#define TIMER2_ENABLE()     (T2CONbits.TMR2ON = 1)
/*DISBLE TIMER2*/
#define TIMER2_DISABLE()     (T2CONbits.TMR2ON = 0)
/*Configure PostScaler*/
#define TIMER2_POSTSCALER_SELECT(_POSTSCALER) (T2CONbits.T2OUTPS = _POSTSCALER)
/*Configure PreScaler*/
#define TIMER2_PRESCALER_SELECT(_PRESCALER)   (T2CONbits.T2CKPS = _PRESCALER)

/*Section : Data Type Declaration*/
typedef struct {
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void(* timer2_InterruptHandler)(void); // Function pointer to Timer2 interrupt service routine (ISR).
    priority_level_t priority; // Priority level for the Timer1 interrupt.
#endif
    uint8 timer2_postscaler_val : 4; // Holds the selected postscaler division factor.
    uint8 timer2_prescaler_val : 2; // Holds the selected prescaler division factor.
    uint8 timer2_preload_val; // Preload value to initialize Timer2 register.
} timer2_t;
/*Section : Function Declaration*/
STD_ReturnType timer2_init(const timer2_t *timer);
STD_ReturnType timer2_Deinit(const timer2_t *timer);
STD_ReturnType timer2_write_value(const timer2_t *timer, uint8 value);
STD_ReturnType timer2_read_value(const timer2_t *timer, uint8 *value);

#endif	/* HAL_TIMER2_H */

