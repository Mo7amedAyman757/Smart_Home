/* 
 * File:   hal_timer3.c
 * Author: LEGION
 *
 * Created on October 10, 2024, 9:30 AM
 */

#include "hal_timer3.h"
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
void (* Timer3_InterruptHandler) (void) = NULL;
#endif
static STD_ReturnType Timer3_mode_config(const timer3_t *timer);
static STD_ReturnType Timer3_reg_config(const timer3_t *timer);
uint16 timer3_preload_val;

/**
 * @brief Initializes the Timer3 module with the specified configuration.
 * 
 * This function configures Timer3 based on the provided `timer3_t` structure. It sets the mode, prescaler, preload value, 
 * and other necessary settings such as interrupt configuration.
 * 
 * @param timer Pointer to a `timer3_t` structure that contains the configuration information for Timer3.
 * @return STD_ReturnType Returns E_OK if initialization is successful, otherwise E_NOK.
 */
STD_ReturnType Timer3_Init(const timer3_t *timer) {
    STD_ReturnType ret = E_NOK;
    if (NULL == timer) {
        ret = E_NOK;
    } else {
        /*Disable timer0*/
        TIMER3_DISABLE();
        /*configure prescaler*/
        TIMER3_PRESACALE_Val(timer->timer3_prescaler);
        /*configure timer 1 mode*/
        Timer3_mode_config(timer);
        /*configure register size*/
        Timer3_reg_config(timer);
        /*assign value*/
        TMR3H = (timer->preload_val) >> 8;
        TMR3L = (uint8) (timer->preload_val);
        timer3_preload_val = timer->preload_val;
        /*Configuration of Interrupt*/
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER3_INTERRUPT_ENABLE();
        TIMER3_INTERRUPT_CLEAR_FLAG();
#if  INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_Priority_level_Enable();
        if (timer->priority == INTERRUPT_HIGH_PRIORITY) {
            INTERRUPT_Global_InterruptHighEnable();
            TIMER3_HIGH_PRIORITY();
        } else if (timer->priority == INTERRUPT_LOW_PRIORITY) {
            INTERRUPT_Global_InterruptLowEnable();
            TIMER3_LOW_PRIORITY();
        } else {
        }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        Timer3_InterruptHandler = timer->timer3_InterruptHandler;
#endif
        /*Enable timer3*/
        TIMER3_ENABLE();
    }
    return ret;
}

/**
 * @brief Deinitializes Timer3, turning it off and clearing any configurations.
 * 
 * This function disables Timer3 and removes any configurations that were set during initialization.
 * It can also disable Timer1 interrupts if they were enabled.
 * 
 * @param timer Pointer to a `timer3_t` structure that contains the Timer3 configuration.
 * @return STD_ReturnType Returns E_OK if deinitialization is successful, otherwise E_NOK.
 */
STD_ReturnType Timer3_DeInit(const timer3_t *timer) {
    STD_ReturnType ret = E_NOK;
    if (NULL == timer) {
        ret = E_NOK;
    } else {
        /*Disable timer3*/
        TIMER3_DISABLE();
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER3_INTERRUPT_DISABLE();
#endif
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Writes a value to the Timer3 register.
 * 
 * This function writes a specific value to the Timer3 register, effectively setting the timer's count. 
 * The value is based on the provided `value` parameter.
 * 
 * @param timer Pointer to a `timer3_t` structure that contains the configuration information for Timer3.
 * @param value The value to be written to the Timer3 register.
 * @return STD_ReturnType Returns E_OK if the value is written successfully, otherwise E_NOK.
 */
STD_ReturnType Timer3_Write_value(const timer3_t *timer, uint16 value) {
    STD_ReturnType ret = E_NOK;
    if (NULL == timer) {
        ret = E_NOK;
    } else {
        TMR3H = (value) >> 8;
        TMR3L = (uint8) (value);
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Reads the current value from the Timer3 register.
 * 
 * This function retrieves the current value from Timer3 by reading its register.
 * The value is stored in the variable pointed to by the `value` parameter.
 * 
 * @param timer Pointer to a `timer3_t` structure that contains the configuration information for Timer3.
 * @param value Pointer to a variable where the Timer3 value will be stored.
 * @return STD_ReturnType Returns E_OK if the value is read successfully, otherwise E_NOK.
 */
STD_ReturnType Timer3_Read_value(const timer3_t *timer, uint16 *value) {
    STD_ReturnType ret = E_NOK;
    uint8 tmr3l = 0, tmr3h = 0;
    if ((NULL == timer) || (NULL == value)) {
        ret = E_NOK;
    } else {
        tmr3l = TMR1L;
        tmr3h = TMR1H;
        *value = (uint16) ((tmr3h << 8) + tmr3l);
    }
    return ret;
}

/**
 * @brief Configures Timer3 to operate in either timer or counter mode.
 * 
 * @param timer Pointer to a timer3_t structure that contains the mode configuration.
 * @return STD_ReturnType E_OK if the configuration is successful, otherwise E_NOK.
 */
static STD_ReturnType Timer3_mode_config(const timer3_t * timer) {
    STD_ReturnType ret = E_NOK;
    if (NULL == timer) {
        ret = E_NOK;
    } else {
        if (timer->timer3_mode == TIMER3_TIMER_MODE_CFG) {
            TIMER3_TIMER_MODE();
        } else if (timer->timer3_mode == TIMER3_COUNTER_MODE_CFG) {
            TIMER3_COUNTER_MODE();
            if (timer->timer3_counter_cfg == TIMER3_SYNC_COUNTER_CFG) {
                TIMER3_SYNC_COUNTER();
            } else if (timer->timer3_counter_cfg == TIMER3_ASYNC_COUNTER_CFG) {
                TIMER3_ASYNC_COUNTER();
            } else {
            }
        } else {
        }
    }
    return ret;
}

/**
 * @brief Configures Timer3 register size (8-bit or 16-bit mode).
 * 
 * @param timer Pointer to a timer3_t structure that contains the register configuration.
 * @return STD_ReturnType E_OK if the configuration is successful, otherwise E_NOK.
 */
static STD_ReturnType Timer3_reg_config(const timer3_t * timer) {
    STD_ReturnType ret = E_NOK;
    if (NULL == timer) {
        ret = E_NOK;
    } else {
        if (timer->timer3_reg == TIMER3_RW_REG_8BIT_CFG) {
            TIMER3_RW_REG_8BIT();
        } else if (timer->timer3_reg == TIMER3_RW_REG_16BIT_CFG) {
            TIMER3_RW_REG_16BIT();
        } else {
        }
    }
    return ret;
}

void TMR3_ISR(void) {
    TIMER3_INTERRUPT_CLEAR_FLAG();
    if (Timer3_InterruptHandler) {
        Timer3_InterruptHandler();
    } else {
    }
}
