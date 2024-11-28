/* 
 * File:   hal_timer1.c
 * Author: LEGION
 *
 * Created on October 10, 2024, 7:23 AM
 */

#include "hal_timer1.h"


#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
void (* Timer1_InterruptHandler) (void) = NULL;
#endif
static STD_ReturnType Timer1_mode_config(const timer1_t *timer);
static STD_ReturnType Timer1_reg_config(const timer1_t *timer);
uint16 timer1_preload_val;

/**
 * @brief Initializes the Timer1 module with the specified configuration.
 * 
 * This function configures Timer1 based on the provided `timer1_t` structure. It sets the mode, prescaler, preload value, 
 * and other necessary settings such as interrupt configuration.
 * 
 * @param timer Pointer to a `timer1_t` structure that contains the configuration information for Timer1.
 * @return STD_ReturnType Returns E_OK if initialization is successful, otherwise E_NOK.
 */
STD_ReturnType timer1_init(const timer1_t *timer) {
    STD_ReturnType ret = E_NOK;
    if (NULL == timer) {
        ret = E_NOK;
    } else {
        /*Disable timer1*/
        TIMER1_DISABLE();
        /*configure prescaler*/
        TIMER1_PRESACALE_Val(timer->timer1_prescaler);
        /*configure timer 1 mode*/
        Timer1_mode_config(timer);
        /*configure register size*/
        Timer1_reg_config(timer);
        /*assign value*/
        TMR1H = (timer->preload_val) >> 8;
        TMR1L = (uint8) (timer->preload_val);
        timer1_preload_val = timer->preload_val;
        /*Configuration of Interrupt*/
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER1_INTERRUPT_ENABLE();
        TIMER1_INTERRUPT_CLEAR_FLAG();
#if  INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_Priority_level_Enable();
        if (timer->priority == INTERRUPT_HIGH_PRIORITY) {
            INTERRUPT_Global_InterruptHighEnable();
            TIMER1_HIGH_PRIORITY();
        } else if (timer->priority == INTERRUPT_LOW_PRIORITY) {
            INTERRUPT_Global_InterruptLowEnable();
            TIMER1_LOW_PRIORITY();
        } else {
        }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        Timer1_InterruptHandler = timer->timer1_InterruptHandler;
#endif
        /*Enable timer1*/
        TIMER1_ENABLE();
    }
    return ret;
}

/**
 * @brief Deinitializes Timer1, turning it off and clearing any configurations.
 * 
 * This function disables Timer1 and removes any configurations that were set during initialization.
 * It can also disable Timer1 interrupts if they were enabled.
 * 
 * @param timer Pointer to a `timer1_t` structure that contains the Timer1 configuration.
 * @return STD_ReturnType Returns E_OK if deinitialization is successful, otherwise E_NOK.
 */
STD_ReturnType timer1_Deinit(const timer1_t * timer) {
    STD_ReturnType ret = E_NOK;
    if (NULL == timer) {
        ret = E_NOK;
    } else {
        /*Disable timer1*/
        TIMER1_DISABLE();
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER1_INTERRUPT_DISABLE();
#endif
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Writes a value to the Timer1 register.
 * 
 * This function writes a specific value to the Timer1 register, effectively setting the timer's count. 
 * The value is based on the provided `value` parameter.
 * 
 * @param timer Pointer to a `timer1_t` structure that contains the configuration information for Timer1.
 * @param value The value to be written to the Timer1 register.
 * @return STD_ReturnType Returns E_OK if the value is written successfully, otherwise E_NOK.
 */
STD_ReturnType timer1_write_value(const timer1_t *timer, uint16 value) {
    STD_ReturnType ret = E_NOK;
    if (NULL == timer) {
        ret = E_NOK;
    } else {
        TMR1H = (value) >> 8;
        TMR1L = (uint8) (value);
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Reads the current value from the Timer1 register.
 * 
 * This function retrieves the current value from Timer1 by reading its register.
 * The value is stored in the variable pointed to by the `value` parameter.
 * 
 * @param timer Pointer to a `timer1_t` structure that contains the configuration information for Timer1.
 * @param value Pointer to a variable where the Timer1 value will be stored.
 * @return STD_ReturnType Returns E_OK if the value is read successfully, otherwise E_NOK.
 */
STD_ReturnType timer1_read_value(const timer1_t *timer, uint16 * value) {
    STD_ReturnType ret = E_NOK;
    uint8 tmr1l = 0, tmr1h = 0;
    if ((NULL == timer) || (NULL == value)) {
        ret = E_NOK;
    } else {
        tmr1l = TMR1L;
        tmr1h = TMR1H;
        *value = (uint16) ((tmr1h << 8) + tmr1l);
    }
    return ret;
}

/**
 * @brief Configures Timer1 to operate in either timer or counter mode.
 * 
 * @param timer Pointer to a timer1_t structure that contains the mode configuration.
 * @return STD_ReturnType E_OK if the configuration is successful, otherwise E_NOK.
 */
static STD_ReturnType Timer1_mode_config(const timer1_t * timer) {
    STD_ReturnType ret = E_NOK;
    if (NULL == timer) {
        ret = E_NOK;
    } else {
        if (timer->timer1_mode == TIMER1_TIMER_MODE_CFG) {
            TIMER1_TIMER_MODE();
        } else if (timer->timer1_mode == TIMER1_COUNTER_MODE_CFG) {
            TIMER1_COUNTER_MODE();
            if (timer->timer1_counter_cfg == TIMER1_SYNC_COUNTER_CFG) {
                TIMER1_SYNC_COUNTER();
            } else if (timer->timer1_counter_cfg == TIMER1_ASYNC_COUNTER_CFG) {
                TIMER1_ASYNC_COUNTER();
            } else {
            }
        } else {
        }
    }
    return ret;
}

/**
 * @brief Configures Timer1 register size (8-bit or 16-bit mode).
 * 
 * @param timer Pointer to a timer1_t structure that contains the register configuration.
 * @return STD_ReturnType E_OK if the configuration is successful, otherwise E_NOK.
 */
static STD_ReturnType Timer1_reg_config(const timer1_t * timer) {
    STD_ReturnType ret = E_NOK;
    if (NULL == timer) {
        ret = E_NOK;
    } else {
        if (timer->timer1_reg == TIMER1_RW_REG_8BIT_CFG) {
            TIMER1_RW_REG_8BIT();
        } else if (timer->timer1_reg == TIMER1_RW_REG_16BIT_CFG) {
            TIMER1_RW_REG_16BIT();
        } else {
        }
    }
    return ret;
}

void TMR1_ISR(void) {
    TIMER1_INTERRUPT_CLEAR_FLAG();
    if (Timer1_InterruptHandler) {
        Timer1_InterruptHandler();
    } else {
    }
}