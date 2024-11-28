/* 
 * File:   hal_timer2.c
 * Author: LEGION
 *
 * Created on October 10, 2024, 8:54 AM
 */

#include "hal_timer2.h"

#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
void (* Timer2_InterruptHandler) (void) = NULL;
#endif
uint8 timer2_preload_val;

/**
 * @brief Initializes the Timer2 module with the specified configuration.
 * 
 * This function configures Timer2 based on the provided `timer2_t` structure. It sets the mode, prescaler, preload value, 
 * and other necessary settings such as interrupt configuration.
 * 
 * @param timer Pointer to a `timer2_t` structure that contains the configuration information for Timer2.
 * @return STD_ReturnType Returns E_OK if initialization is successful, otherwise E_NOK.
 */
STD_ReturnType timer2_init(const timer2_t *timer) {
    STD_ReturnType ret = E_NOK;
    if (NULL == timer) {
        ret = E_NOK;
    } else {
        /*Disable timer0*/
        TIMER2_DISABLE();
        /*configure prescaler*/
        TIMER2_PRESCALER_SELECT(timer->timer2_prescaler_val);
        /*configure postscaler*/
        TIMER2_POSTSCALER_SELECT(timer->timer2_postscaler_val);
        /*assign value*/
        TMR2 = timer->timer2_preload_val;
        timer2_preload_val = timer->timer2_preload_val;
        /*Configuration of Interrupt*/
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER2_INTERRUPT_ENABLE();
        TIMER2_INTERRUPT_CLEAR_FLAG();
#if  INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_Priority_level_Enable();
        if (timer->priority == INTERRUPT_HIGH_PRIORITY) {
            INTERRUPT_Global_InterruptHighEnable();
            TIMER2_HIGH_PRIORITY();
        } else if (timer->priority == INTERRUPT_LOW_PRIORITY) {
            INTERRUPT_Global_InterruptLowEnable();
            TIMER2_LOW_PRIORITY();
        } else {
        }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        Timer2_InterruptHandler = timer->timer2_InterruptHandler;
#endif
        /*Enable timer0*/
        TIMER2_ENABLE();
    }
    return ret;
}

/**
 * @brief Deinitializes Timer2, turning it off and clearing any configurations.
 * 
 * This function disables Timer2 and removes any configurations that were set during initialization.
 * It can also disable Timer2 interrupts if they were enabled.
 * 
 * @param timer Pointer to a `timer2_t` structure that contains the Timer1 configuration.
 * @return STD_ReturnType Returns E_OK if deinitialization is successful, otherwise E_NOK.
 */
STD_ReturnType timer2_Deinit(const timer2_t *timer) {
    STD_ReturnType ret = E_NOK;
    if (NULL == timer) {
        ret = E_NOK;
    } else {
        /*Disable timer0*/
        TIMER2_DISABLE();
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER2_INTERRUPT_DISABLE();
#endif
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Writes a value to the Timer2 register.
 * 
 * This function writes a specific value to the Timer2 register, effectively setting the timer's count. 
 * The value is based on the provided `value` parameter.
 * 
 * @param timer Pointer to a `timer2_t` structure that contains the configuration information for Timer2.
 * @param value The value to be written to the Timer2 register.
 * @return STD_ReturnType Returns E_OK if the value is written successfully, otherwise E_NOK.
 */
STD_ReturnType timer2_write_value(const timer2_t *timer, uint8 value) {
    STD_ReturnType ret = E_NOK;
    if (NULL == timer) {
        ret = E_NOK;
    } else {
        TMR2 = value;
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Reads the current value from the Timer2 register.
 * 
 * This function retrieves the current value from Timer2 by reading its register.
 * The value is stored in the variable pointed to by the `value` parameter.
 * 
 * @param timer Pointer to a `timer2_t` structure that contains the configuration information for Timer2.
 * @param value Pointer to a variable where the Timer2 value will be stored.
 * @return STD_ReturnType Returns E_OK if the value is read successfully, otherwise E_NOK.
 */
STD_ReturnType timer2_read_value(const timer2_t *timer, uint8 *value) {
    STD_ReturnType ret = E_NOK;
    if ((NULL == timer) || (NULL == value)) {
        ret = E_NOK;
    } else {
        *value = TMR2;
        ret = E_OK;
    }
    return ret;
}

void TMR2_ISR(void) {
    TIMER2_INTERRUPT_CLEAR_FLAG();
    if (Timer2_InterruptHandler) {
        Timer2_InterruptHandler();
    } else {
    }
}