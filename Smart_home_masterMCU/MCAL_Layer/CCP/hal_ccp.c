/* 
 * File:   hal_ccp.c
 * Author: LEGION
 *
 * Created on October 11, 2024, 4:25 PM
 */

#include "hal_ccp.h"

#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void(* CCP1_Interrupt_Handler)(void) = NULL;
#endif
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
static void(* CCP2_Interrupt_Handler)(void) = NULL;
#endif

static STD_ReturnType CCP_capture_set_mode_variant(const ccp_t * ccp);
static STD_ReturnType CCP_compare_set_mode_variant(const ccp_t * ccp);
static STD_ReturnType CCP_PWM_set_mode_variant(const ccp_t * ccp);
static void CCP_interrupt_config(const ccp_t * ccp);
static void CCP_capture_compare_mode_timer_select(const ccp_t * ccp);

/**
 * @brief Initializes the CCP module with the specified configuration.
 * 
 * This function configures the CCP module (either CCP1 or CCP2) based on the provided 
 * configuration structure. The initialization may include setting the mode, configuring 
 * timers, interrupts, PWM frequency, and other parameters specific to the CCP instance.
 * 
 * @param ccp Pointer to the CCP configuration structure containing the settings 
 *            for the CCP module (ccp_inst, ccp_mode, pin_cfg, etc.).
 * 
 * @return STD_ReturnType Return status indicating the success or failure of the 
 *         initialization process. 
 */
STD_ReturnType CCP_Init(const ccp_t * ccp) {
    STD_ReturnType ret = E_NOK;
    if (NULL == ccp) {
        ret = E_NOK;
    } else {
        /*Disable CCPX*/
        if (ccp->ccp_inst == CCP1_INST) {
            CCP1_MODE_SELECT(CCP_MODULE_DISABLE);
        } else if (ccp->ccp_inst == CCP2_INST) {
            CCP2_MODE_SELECT(CCP_MODULE_DISABLE);
        }
        if (ccp->ccp_mode == CCP_CAPTURE_SELECT) {
            CCP_capture_set_mode_variant(ccp);
        } else if (ccp->ccp_mode == CCP_COMPARE_SELECT) {
            CCP_compare_set_mode_variant(ccp);
        }
#if (CCP1_CONFIG_MODE_SELECT == CCP_PWM_MODE_SELECTED) || (CCP2_CONFIG_MODE_SELECT == CCP_PWM_MODE_SELECTED)
        else if (ccp->ccp_mode == CCP_PWM_SELECT) {
            CCP_PWM_set_mode_variant(ccp);
        }
#endif
        else {
            /*Nothing*/
        }
        /*PIN Configuration*/
        ret = gpio_pin_initialization(&(ccp->pin_cfg));
        /*Interrupt Configuration*/
        CCP_interrupt_config(ccp);
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief De-initializes the CCP module, restoring it to a default state.
 * 
 * This function disables or resets the CCP module (either CCP1 or CCP2) based on the
 * configuration provided. It ensures that the CCP module is no longer active and can 
 * safely be reinitialized or used for other purposes.
 * 
 * @param ccp Pointer to the CCP configuration structure containing the settings 
 *            for the CCP module (ccp_inst, ccp_mode, etc.).
 * 
 * @return STD_ReturnType Return status indicating the success or failure of the 
 *         de-initialization process. 
 */
STD_ReturnType CCP_DeInit(const ccp_t * ccp) {
    STD_ReturnType ret = E_NOK;
    if (NULL == ccp) {
        ret = E_NOK;
    } else {
        if (ccp->ccp_inst == CCP1_INST) {
            CCP1_MODE_SELECT(CCP_MODULE_DISABLE);
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            CCP1_INTERRUPT_DISABLE();
#endif
        } else if (ccp->ccp_inst == CCP2_INST) {
            CCP2_MODE_SELECT(CCP_MODULE_DISABLE);
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            CCP2_INTERRUPT_DISABLE();
#endif
        }
    }
    return ret;
}

#if (CCP1_CONFIG_MODE_SELECT == CCP_CAPTURE_MODE_SELECTED) || (CCP2_CONFIG_MODE_SELECT == CCP_CAPTURE_MODE_SELECTED)

/**
 * @brief Checks if the capture data is ready.
 * 
 * This function checks whether a capture event has occurred by verifying the CCP1 interrupt flag.
 * If the capture event has occurred, it clears the interrupt flag and sets the capture status to ready.
 * If the capture event has not occurred, it sets the capture status to not ready.
 *
 * @param capture_status Pointer to a variable that will store the status of the capture event (ready or not ready).
 * @return STD_ReturnType Returns E_OK if the status was successfully updated, or E_NOK if the pointer is NULL.
 */
STD_ReturnType CCP_IsCaptureDataReady(uint8 *capture_status) {
    STD_ReturnType ret = E_NOK;
    if (NULL == capture_status) {
        ret = E_NOK;
    } else {
        if (CCP_CAPTURE_READY == PIR1bits.CCP1IF) {
            *capture_status = CCP_CAPTURE_READY;
            CCP1_INTERRUPT_CLEAR_FLAG();
        } else {
            *capture_status = CCP_CAPTURE_NOT_READY;
        }
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Reads the captured value from the CCP module.
 * 
 * This function reads the 16-bit captured value from the selected CCP module (CCP1 or CCP2).
 * It retrieves the value from the CCPR registers, combines the low and high bytes, and stores
 * it in the `capture_value` pointer provided.
 *
 * @param ccp Pointer to a structure that holds the CCP instance information (CCP1 or CCP2).
 * @param capture_value Pointer to store the 16-bit captured value.
 * @return STD_ReturnType Returns E_OK if the capture value was successfully read, or E_NOK if either pointer is NULL.
 */
STD_ReturnType CCP_CaptureDataRead(const ccp_t * ccp, uint16 *capture_value) {
    STD_ReturnType ret = E_NOK;
    CCP_REG_T capture_time_val = {.ccpr_low = 0, .ccpr_high = 0};
    if ((NULL == ccp) || (NULL == capture_value)) {
        ret = E_NOK;
    } else {
        if (ccp->ccp_inst == CCP1_INST) {
            capture_time_val.ccpr_low = CCPR1L;
            capture_time_val.ccpr_high = CCPR1H;
            *capture_value = capture_time_val.ccpr_16bit;
        } else if (ccp->ccp_inst == CCP2_INST) {
            capture_time_val.ccpr_low = CCPR2L;
            capture_time_val.ccpr_high = CCPR2H;
            *capture_value = capture_time_val.ccpr_16bit;
        }
        ret = E_OK;
    }
    return ret;
}
#endif

#if (CCP1_CONFIG_MODE_SELECT == CCP_COMPARE_MODE_SELECTED) || (CCP2_CONFIG_MODE_SELECT == CCP_COMPARE_MODE_SELECTED)

/**
 * @brief Checks if the compare event has completed.
 * 
 * This function verifies if a compare event has occurred by checking the CCP1 interrupt flag.
 * If the event has occurred, the function clears the interrupt flag and sets the compare status to ready.
 * If the compare event has not occurred, it sets the compare status to not ready.
 *
 * @param compare_status Pointer to a variable that will store the status of the compare event (ready or not ready).
 * @return STD_ReturnType Returns E_OK if the status was successfully updated, or E_NOK if the pointer is NULL.
 */
STD_ReturnType CCP_IsCompareComplete(uint8 *compare_status) {
    STD_ReturnType ret = E_NOK;
    if (NULL == compare_status) {
        ret = E_NOK;
    } else {
        if (CCP_CAPTURE_READY == PIR1bits.CCP1IF) {
            *compare_status = CCP_CAPTURE_READY;
            CCP1_INTERRUPT_CLEAR_FLAG();
        } else {
            *compare_status = CCP_CAPTURE_NOT_READY;
        }
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Sets the compare value for a CCP module.
 * 
 * This function sets a comparison value for either CCP1 or CCP2 module based on the instance in the `ccp` structure.
 * It updates the appropriate compare registers with the 16-bit comparison value provided.
 *
 * @param ccp Pointer to a structure that holds the CCP instance information (CCP1 or CCP2).
 * @param compare_value The 16-bit value to be compared by the CCP module.
 * @return STD_ReturnType Returns E_OK if the value was successfully set, or E_NOK if the pointer is NULL.
 */
STD_ReturnType CCP_CompareSetValue(const ccp_t * ccp, uint16 compare_value) {
    STD_ReturnType ret = E_NOK;
    CCP_REG_T compare_time_val = {.ccpr_low = 0, .ccpr_high = 0};
    compare_time_val.ccpr_16bit = compare_value;
    if (NULL == ccp) {
        ret = E_NOK;
    } else {
        if (ccp->ccp_inst == CCP1_INST) {
            CCPR1L = compare_time_val.ccpr_low;
            CCPR1H = compare_time_val.ccpr_high;
        } else if (ccp->ccp_inst == CCP2_INST) {
            CCPR2L = compare_time_val.ccpr_low;
            CCPR2H = compare_time_val.ccpr_high;
        }
        ret = E_OK;
    }
    return ret;
}
#endif

#if (CCP1_CONFIG_MODE_SELECT == CCP_PWM_MODE_SELECTED) || (CCP2_CONFIG_MODE_SELECT == CCP_PWM_MODE_SELECTED)

/**
 * @brief Sets the duty cycle for a CCP PWM module.
 * 
 * This function calculates the duty cycle for a CCP PWM module based on the percentage value provided.
 * It updates the low and high parts of the duty cycle register for either CCP1 or CCP2.
 * 
 * @param ccp Pointer to a structure that holds the CCP instance information (CCP1 or CCP2).
 * @param duty The duty cycle percentage (0-100%) to set for the PWM signal.
 * @return STD_ReturnType Returns E_OK if the duty cycle was successfully set, or E_NOK if the pointer is NULL.
 */
STD_ReturnType CCP_PWM_Set_Duty(const ccp_t * ccp, const uint8 duty) {
    STD_ReturnType ret = E_NOK;
    uint16 duty_temp = 0;
    if (NULL == ccp) {
        ret = E_NOK;
    } else {
        duty_temp = (uint16) ((PR2 + 1) * ((float) duty / 100.0) *4);
        if (ccp->ccp_inst == CCP1_INST) {
            CCP1CONbits.DC1B = (uint8) (duty_temp & 0x0003);
            CCPR1L = (uint8) (duty_temp >> 2);
        } else if (ccp->ccp_inst == CCP2_INST) {
            CCP2CONbits.DC2B = (uint8) (duty_temp & 0x0003);
            CCPR2L = (uint8) (duty_temp >> 2);
        } else {
            /*Nothing*/
        }
        ret = E_OK;
    }
    return ret;
}

/**
 * @brief Starts the PWM operation for a CCP module.
 * 
 * This function enables PWM mode for the specified CCP module (CCP1 or CCP2)
 * by configuring the CCP mode bits to start generating PWM output.
 *
 * @param ccp Pointer to a structure that holds the CCP instance information (CCP1 or CCP2).
 * @return STD_ReturnType Returns E_OK if the PWM mode was successfully started, or E_NOK if the pointer is NULL.
 */
STD_ReturnType CCP_PWM_Start(const ccp_t * ccp) {
    STD_ReturnType ret = E_NOK;
    if (NULL == ccp) {
        ret = E_NOK;
    } else {
        if (CCP1_INST == ccp->ccp_inst) {
            CCP1CONbits.CCP1M = CCP_PWM_MODE;
        } else if (CCP2_INST == ccp->ccp_inst) {
            CCP2CONbits.CCP2M = CCP_PWM_MODE;
        } else {
        }
    }
    return ret;
}

/**
 * @brief Stops the PWM operation for a CCP module.
 * 
 * This function disables the PWM mode for the specified CCP module (CCP1 or CCP2),
 * stopping the PWM signal generation.
 *
 * @param ccp Pointer to a structure that holds the CCP instance information (CCP1 or CCP2).
 * @return STD_ReturnType Returns E_OK if the PWM mode was successfully stopped, or E_NOK if the pointer is NULL.
 */
STD_ReturnType CCP_PWM_Stop(const ccp_t * ccp) {
    STD_ReturnType ret = E_NOK;
    if (NULL == ccp) {
        ret = E_NOK;
    } else {
        if (CCP1_INST == ccp->ccp_inst) {
            CCP1CONbits.CCP1M = CCP_MODULE_DISABLE;
        } else if (CCP2_INST == ccp->ccp_inst) {
            CCP2CONbits.CCP2M = CCP_MODULE_DISABLE;
        } else {
        }
    }
    return ret;
}
#endif

/**
 * @brief Configures the capture mode for the specified CCP instance.
 *
 * This function sets the capture mode for the CCP1 or CCP2 instance based on 
 * the `ccp_mode_variant` specified in the `ccp` structure. It configures 
 * the capture mode for either CCP1 or CCP2 to one of the predefined modes:
 * falling edge, rising edge (1, 4, or 16 times).
 *
 * @param ccp Pointer to the `ccp_t` structure that contains the configuration.
 * @return STD_ReturnType - `E_OK` if the mode is set successfully, `E_NOK` if the pointer is `NULL` or an invalid mode is selected.
 */
static STD_ReturnType CCP_capture_set_mode_variant(const ccp_t * ccp) {
    STD_ReturnType ret = E_OK;
    if (NULL == ccp) {
        ret = E_NOK;
    } else {
        if (ccp->ccp_inst == CCP1_INST) {
            switch (ccp->ccp_mode_variant) {
                case CCP_CAPTURE_MODE_FALLING_EDGE:
                    CCP1_MODE_SELECT(CCP_CAPTURE_MODE_FALLING_EDGE);
                    break;
                case CCP_CAPTURE_MODE_1_RISING_EDGE:
                    CCP1_MODE_SELECT(CCP_CAPTURE_MODE_1_RISING_EDGE);
                    break;
                case CCP_CAPTURE_MODE_4_RISING_EDGE:
                    CCP1_MODE_SELECT(CCP_CAPTURE_MODE_4_RISING_EDGE);
                    break;
                case CCP_CAPTURE_MODE_16_RISING_EDGE:
                    CCP1_MODE_SELECT(CCP_CAPTURE_MODE_16_RISING_EDGE);
                    break;
                default: ret = E_NOK;
            }
        } else if (ccp->ccp_inst == CCP2_INST) {
            switch (ccp->ccp_mode_variant) {
                case CCP_CAPTURE_MODE_FALLING_EDGE:
                    CCP2_MODE_SELECT(CCP_CAPTURE_MODE_FALLING_EDGE);
                    break;
                case CCP_CAPTURE_MODE_1_RISING_EDGE:
                    CCP2_MODE_SELECT(CCP_CAPTURE_MODE_1_RISING_EDGE);
                    break;
                case CCP_CAPTURE_MODE_4_RISING_EDGE:
                    CCP2_MODE_SELECT(CCP_CAPTURE_MODE_4_RISING_EDGE);
                    break;
                case CCP_CAPTURE_MODE_16_RISING_EDGE:
                    CCP2_MODE_SELECT(CCP_CAPTURE_MODE_16_RISING_EDGE);
                    break;
                default: ret = E_NOK;
            }
        }
        CCP_capture_compare_mode_timer_select(ccp);
    }
    return ret;
}

/**
 * @brief Configures the timer selection for CCP capture mode.
 *
 * This function selects the timer (Timer1 or Timer3) for CCP1 and CCP2 capture mode based on the 
 * configuration provided in the `ccp` structure. Depending on the value of `ccp_capture_timer3`, 
 * the appropriate bits in `T3CON` are set to direct the timers for CCP1 and CCP2 operations.
 *
 * - `CCP1_CCP2_TIMER1`: Both CCP1 and CCP2 use Timer1.
 * - `CCP1_CCP2_TIMER3`: Both CCP1 and CCP2 use Timer3.
 * - `CCP1_TIMER1_CCP2_TIMER3`: CCP1 uses Timer1 and CCP2 uses Timer3.
 *
 * @param ccp Pointer to the `ccp_t` structure that contains the timer selection configuration.
 */
#if (CCP1_CONFIG_MODE_SELECT == CCP_CAPTURE_MODE_SELECTED) || (CCP2_CONFIG_MODE_SELECT == CCP_CAPTURE_MODE_SELECTED)

static void CCP_capture_compare_mode_timer_select(const ccp_t * ccp) {
    if (CCP1_CCP2_TIMER1 == ccp->ccp_capture_compare_timer3) {
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 0;
    } else if (CCP1_CCP2_TIMER3 == ccp->ccp_capture_compare_timer3) {
        T3CONbits.T3CCP1 = 0;
        T3CONbits.T3CCP2 = 1;
    } else if (CCP1_TIMER1_CCP2_TIMER3 == ccp->ccp_capture_compare_timer3) {
        T3CONbits.T3CCP1 = 1;
        T3CONbits.T3CCP2 = 0;
    } else {
        /*Nothing*/
    }
}
#endif

/**
 * @brief Configures the compare mode for the specified CCP instance.
 *
 * This function sets the compare mode for the CCP1 or CCP2 instance based on 
 * the `ccp_mode_variant` specified in the `ccp` structure. It configures 
 * the compare mode to one of the predefined options, such as toggling output 
 * or generating special events or software interrupts.
 *
 * @param ccp Pointer to the `ccp_t` structure that contains the configuration.
 * @return STD_ReturnType - `E_OK` if the mode is set successfully, `E_NOK` if the pointer is `NULL` or an invalid mode is selected.
 */
static STD_ReturnType CCP_compare_set_mode_variant(const ccp_t * ccp) {
    STD_ReturnType ret = E_OK;
    if (NULL == ccp) {
        ret = E_NOK;
    } else {
        if (ccp->ccp_inst == CCP1_INST) {
            switch (ccp->ccp_mode_variant) {
                case CCP_COMPARE_MODE_TOGGLE_OUTPUT:
                    CCP1_MODE_SELECT(CCP_COMPARE_MODE_TOGGLE_OUTPUT);
                    break;
                case CCP_COMPARE_MODE_SET_LOW_OUTPUT:
                    CCP1_MODE_SELECT(CCP_COMPARE_MODE_SET_LOW_OUTPUT);
                    break;
                case CCP_COMPARE_MODE_SET_HIGH_OUTPUT:
                    CCP1_MODE_SELECT(CCP_COMPARE_MODE_SET_HIGH_OUTPUT);
                    break;
                case CCP_COMPARE_MODE_GEN_SW_INTERRUPT:
                    CCP1_MODE_SELECT(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);
                    break;
                case CCP_COMPARE_MODE_GEN_SPECIAL_EVENT:
                    CCP1_MODE_SELECT(CCP_COMPARE_MODE_GEN_SPECIAL_EVENT);
                    break;
                default: ret = E_NOK;
            }
        } else if (ccp->ccp_inst == CCP2_INST) {
            switch (ccp->ccp_mode_variant) {
                case CCP_COMPARE_MODE_TOGGLE_OUTPUT:
                    CCP2_MODE_SELECT(CCP_COMPARE_MODE_TOGGLE_OUTPUT);
                    break;
                case CCP_COMPARE_MODE_SET_LOW_OUTPUT:
                    CCP2_MODE_SELECT(CCP_COMPARE_MODE_SET_LOW_OUTPUT);
                    break;
                case CCP_COMPARE_MODE_SET_HIGH_OUTPUT:
                    CCP2_MODE_SELECT(CCP_COMPARE_MODE_SET_HIGH_OUTPUT);
                    break;
                case CCP_COMPARE_MODE_GEN_SW_INTERRUPT:
                    CCP2_MODE_SELECT(CCP_COMPARE_MODE_GEN_SW_INTERRUPT);
                    break;
                case CCP_COMPARE_MODE_GEN_SPECIAL_EVENT:
                    CCP2_MODE_SELECT(CCP_COMPARE_MODE_GEN_SPECIAL_EVENT);
                    break;
                default: ret = E_NOK;
            }
        }
        CCP_capture_compare_mode_timer_select(ccp);
    }
    return ret;
}
#if (CCP1_CONFIG_MODE_SELECT == CCP_PWM_MODE_SELECTED) || (CCP2_CONFIG_MODE_SELECT == CCP_PWM_MODE_SELECTED)

/**
 * @brief Configures the PWM mode for the specified CCP instance.
 *
 * This function sets the PWM mode for the CCP1 or CCP2 instance based on 
 * the `ccp_mode_variant` specified in the `ccp` structure. It configures 
 * the PWM mode if the mode is selected, and also sets the PWM frequency 
 * using the values in the `ccp` structure.
 *
 * @param ccp Pointer to the `ccp_t` structure that contains the configuration.
 * @return STD_ReturnType - `E_OK` if the mode is set successfully, `E_NOK` if the pointer is `NULL`.
 */
static STD_ReturnType CCP_PWM_set_mode_variant(const ccp_t * ccp) {
    STD_ReturnType ret = E_OK;
    if (NULL == ccp) {
        ret = E_NOK;
    } else {
        if (ccp->ccp_inst == CCP1_INST) {
            if (ccp->ccp_mode_variant == CCP_PWM_MODE) {
                CCP1_MODE_SELECT(CCP_PWM_MODE);
            } else {
                /*Nothing*/
            }
        } else if (ccp->ccp_inst == CCP2_INST) {
            if (ccp->ccp_mode_variant == CCP_PWM_MODE) {
                CCP2_MODE_SELECT(CCP_PWM_MODE);
            } else {
                /*Nothing*/
            }
        } else {
            /*Nothing*/
        }
        PR2 = (uint8) ((_XTAL_FREQ / (ccp->PWM_frequency * 4.0 * ccp->timer2_postscaler_val * ccp->timer2_prescaler_val)) - 1);
    }
    return ret;
}
#endif

/**
 * @brief Configures the interrupt settings for the specified CCP instance.
 *
 * This function configures the interrupt settings for the CCP1 or CCP2 instance. 
 * It enables the corresponding interrupt, clears the interrupt flag, and 
 * configures the interrupt priority (if enabled). The interrupt handler is also 
 * set according to the configuration.
 *
 * @param ccp Pointer to the `ccp_t` structure that contains the interrupt configuration.
 */
static void CCP_interrupt_config(const ccp_t * ccp) {
    if (ccp->ccp_inst == CCP1_INST) {
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        CCP1_INTERRUPT_ENABLE();
        CCP1_INTERRUPT_CLEAR_FLAG();
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_Priority_level_Enable();
        if (ccp->ccp1_priority == INTERRUPT_HIGH_PRIORITY) {
            INTERRUPT_Global_InterruptHighEnable();
            CCP1_HIGH_PRIORITY()
        } else if (ccp->ccp1_priority == INTERRUPT_LOW_PRIORITY) {
            INTERRUPT_Global_InterruptLowEnable();
            CCP1_LOW_PRIORITY();
        } else {
        }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        CCP1_Interrupt_Handler = ccp->CCP1_InterruptHandler;
#endif
    } else if (ccp->ccp_inst == CCP2_INST) {
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        CCP2_INTERRUPT_ENABLE();
        CCP2_INTERRUPT_CLEAR_FLAG();
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_Priority_level_Enable();
        if (ccp->ccp2_priority == INTERRUPT_HIGH_PRIORITY) {
            INTERRUPT_Global_InterruptHighEnable();
            CCP2_HIGH_PRIORITY()
        } else if (ccp->ccp2_priority == INTERRUPT_LOW_PRIORITY) {
            INTERRUPT_Global_InterruptLowEnable();
            CCP2_LOW_PRIORITY();
        } else {
        }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        CCP2_Interrupt_Handler = ccp->CCP2_InterruptHandler;
#endif
    }
}

void CCP1_ISR(void) {
    CCP1_INTERRUPT_CLEAR_FLAG();
    if (CCP1_Interrupt_Handler) {
        CCP1_Interrupt_Handler();
    } else {
    }
}

void CCP2_ISR(void) {
    CCP2_INTERRUPT_CLEAR_FLAG();
    if (CCP2_Interrupt_Handler) {
        CCP2_Interrupt_Handler();
    } else {
    }
}