/* 
 * File:   hal_timer0.c
 * Author: LEGION
 *
 * Created on October 10, 2024, 6:18 AM
 */

#include"hal_timer0.h"

#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
void (* Timer0_InterruptHandler) (void) = NULL;
#endif

static STD_ReturnType Timer0_prescaler_config(const timer0_t *timer);
static STD_ReturnType Timer0_mode_config(const timer0_t *timer);
static STD_ReturnType Timer0_reg_config(const timer0_t *timer);
uint16 timer0_preload_val = 0;

/**
 * @brief Initializes the Timer0 module with the specified configuration.
 * 
 * @param timer Pointer to a timer0_t structure that contains the configuration information.
 * @return STD_ReturnType E_OK if initialization is successful, otherwise E_NOK.
 */
STD_ReturnType timer0_init(const timer0_t *timer) {
    STD_ReturnType ret = E_NOK;
    if (NULL == timer) {
        ret = E_NOK;
    } else {
        /*Disable timer0*/
        TIMER0_DISABLE();
        /*configure prescaler*/
        ret = Timer0_prescaler_config(timer);
        /*configure timer 0 mode*/
        ret = Timer0_mode_config(timer);
        /*configure register size*/
        ret = Timer0_reg_config(timer);
        /*assign value*/
        TMR0H = (timer->preload_value) >> 8;
        TMR0L = (uint8) (timer->preload_value);
        timer0_preload_val = timer->preload_value;
        /*Configuration of Interrupt*/
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER0_INTERRUPT_ENABLE();
        TIMER0_INTERRUPT_CLEAR_FLAG();
#if  INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_Priority_level_Enable();
        if (timer->priority == INTERRUPT_HIGH_PRIORITY) {
            INTERRUPT_Global_InterruptHighEnable();
            TIMER0_HIGH_PRIORITY();
        } else if (timer->priority == INTERRUPT_LOW_PRIORITY) {
            INTERRUPT_Global_InterruptLowEnable();
            TIMER0_LOW_PRIORITY();
        } else {
        }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        Timer0_InterruptHandler = timer->timer0_InterruptHandler;
#endif
        /*Enable timer0*/
        TIMER0_ENABLE();
    }
    return ret;
}

/**
 * @brief Deinitializes the Timer0 module, turning it off and clearing any configurations.
 * 
 * @param timer Pointer to a timer0_t structure that contains the configuration information.
 * @return STD_ReturnType E_OK if deinitialization is successful, otherwise E_NOK.
 */
STD_ReturnType timer0_Deinit(const timer0_t *timer) {
    STD_ReturnType ret = E_NOK;
    if (NULL == timer) {
        ret = E_NOK;
    } else {
        /*Disable timer0*/
        TIMER0_DISABLE();
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        TIMER0_INTERRUPT_DISABLE();
#endif        
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Writes a value to the Timer0 register to set the initial timer count.
 * 
 * @param timer Pointer to a timer0_t structure that contains the configuration information.
 * @param value The value to be written to the Timer0 register.
 * @return STD_ReturnType E_OK if the value is written successfully, otherwise E_NOK.
 */
STD_ReturnType timer0_write_value(const timer0_t *timer, uint16 value) {
    STD_ReturnType ret = E_NOK;
    if (NULL == timer) {
        ret = E_NOK;
    } else {
        TMR0H = (value) >> 8;
        TMR0L = (uint8) (value);
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Reads the current value from the Timer0 register.
 * 
 * @param timer Pointer to a timer0_t structure that contains the configuration information.
 * @param value Pointer to a variable where the Timer0 value will be stored.
 * @return STD_ReturnType E_OK if the value is read successfully, otherwise E_NOK.
 */
STD_ReturnType timer0_read_value(const timer0_t *timer, uint16 *value) {
    STD_ReturnType ret = E_NOK;
    uint8 tmr0h, tmr0l;
    if ((NULL == timer) || (NULL == value)) {
        ret = E_NOK;
    } else {
        tmr0h = TMR0H;
        tmr0l = TMR0L;
        *value = (uint16) ((tmr0h << 8) + tmr0l);
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Configures the prescaler for Timer0 based on the timer configuration.
 * 
 * @param timer Pointer to a timer0_t structure that contains the prescaler configuration.
 * @return STD_ReturnType E_OK if the configuration is successful, otherwise E_NOK.
 */
static STD_ReturnType Timer0_prescaler_config(const timer0_t *timer) {
    STD_ReturnType ret = E_NOK;
    if (NULL == timer) {
        ret = E_NOK;
    } else {
        if (timer->prescaler_enable == prescaler_enable_cfg) {
            TIMER0_PRESACLER_ENABLE();
            T0CONbits.T0PS = timer->prescaler_value;
        } else if (timer->prescaler_enable == prescaler_disable_cfg) {
            TIMER0_PRESACLER_DISABLE();
        } else {
        }
    }
    return ret;
}

/**
 * @brief Configures Timer0 to operate in either timer or counter mode.
 * 
 * @param timer Pointer to a timer0_t structure that contains the mode configuration.
 * @return STD_ReturnType E_OK if the configuration is successful, otherwise E_NOK.
 */
static STD_ReturnType Timer0_mode_config(const timer0_t *timer) {
    STD_ReturnType ret = E_NOK;
    if (NULL == timer) {
        ret = E_NOK;
    } else {
        if (timer->timer0_mode == timer0_timer_cfg) {
            TIMER0_TIMER_MODE();
        } else if (timer->timer0_mode == timer0_counter_cfg) {
            TIMER0_COUTNER_MODE();
            if (timer->timer0_source_edge == timer0_rising_edge) {
                TIMER0_INC_RISING_EDGE();
            } else if (timer->timer0_source_edge == timer0_falling_edge) {
                TIMER0_INC_FALLING_EDGE();
            } else {
            }
        } else {
        }
    }
    return ret;
}

/**
 * @brief Configures Timer0 register size (8-bit or 16-bit mode).
 * 
 * @param timer Pointer to a timer0_t structure that contains the register configuration.
 * @return STD_ReturnType E_OK if the configuration is successful, otherwise E_NOK.
 */
static STD_ReturnType Timer0_reg_config(const timer0_t *timer) {
    STD_ReturnType ret = E_NOK;
    if (NULL == timer) {
        ret = E_NOK;
    } else {
        if (timer->timer0_reg == timer0_8_bit_reg) {
            TIMER0_8BIT_REG();
        } else if (timer->timer0_reg == timer0_16_bit_reg) {
            TIMER0_16BIT_REG();
        } else {
        }
    }
    return ret;
}

void TMR0_ISR(void) {
    TIMER0_INTERRUPT_CLEAR_FLAG();
    if (Timer0_InterruptHandler) {
        Timer0_InterruptHandler();
    } else {
    }
}