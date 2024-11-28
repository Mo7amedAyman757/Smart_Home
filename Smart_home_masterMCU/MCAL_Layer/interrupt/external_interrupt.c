/* 
 * File:   external_interrupt.c
 * Author: LEGION
 *
 * Created on September 25, 2024, 10:37 PM
 */

#include"external_interrupt.h"

static void(*INT0_InterruptHandler)(void) = NULL;
static void(*INT1_InterruptHandler)(void) = NULL;
static void(*INT2_InterruptHandler)(void) = NULL;

static void(*RB4_InterruptHandlerLow)(void) = NULL;
static void(*RB4_InterruptHandlerHigh)(void) = NULL;
static void(*RB5_InterruptHandlerLow)(void) = NULL;
static void(*RB5_InterruptHandlerHigh)(void) = NULL;
static void(*RB6_InterruptHandlerLow)(void) = NULL;
static void(*RB6_InterruptHandlerHigh)(void) = NULL;
static void(*RB7_InterruptHandlerLow)(void) = NULL;
static void(*RB7_InterruptHandlerHigh)(void) = NULL;

static STD_ReturnType interrupt_intx_enable(const interrupt_INTx_t * int_obj);
static STD_ReturnType interrupt_intx_disable(const interrupt_INTx_t * int_obj);
static STD_ReturnType interrupt_intx_priority_init(const interrupt_INTx_t * int_obj);
static STD_ReturnType interrupt_intx_edge_init(const interrupt_INTx_t * int_obj);
static STD_ReturnType interrupt_intx_pin_init(const interrupt_INTx_t * int_obj);
static STD_ReturnType interrupt_intx_clear_flag(const interrupt_INTx_t * int_obj);

static STD_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void));
static STD_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void));
static STD_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void));
static STD_ReturnType interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj);


static STD_ReturnType interrupt_RBx_enable(const interrupt_RBx_t * int_obj);
static STD_ReturnType interrupt_RBx_disable(const interrupt_RBx_t * int_obj);
static STD_ReturnType interrupt_RBx_priority_init(const interrupt_RBx_t * int_obj);
static STD_ReturnType interrupt_RBx_pin_init(const interrupt_RBx_t * int_obj);
static STD_ReturnType interrupt_RBx_clear_flag(const interrupt_RBx_t * int_obj);

static STD_ReturnType interrupt_RBx_SetInterruptHandler(const interrupt_RBx_t *int_obj);

/**
 * @brief Initializes the external interrupt for the specified INTx pin.
 * @param int_obj Pointer to a structure that holds the configuration settings for the INTx interrupt.
 * @return STD_ReturnType Returns the success or error status of the initialization. 
 */
STD_ReturnType interrupt_INTx_init(const interrupt_INTx_t * int_obj) {
    STD_ReturnType ret = E_NOK;
    if (NULL == int_obj) {
        ret = E_NOK;
    } else {
        /*Disabe Interrupt*/
        ret = interrupt_intx_disable(int_obj);
        /*Clear interrupt flag*/
        ret = interrupt_intx_clear_flag(int_obj);
        /*Configure interrupt edge*/
        ret = interrupt_intx_edge_init(int_obj);
        /*Configure interrupt priority*/
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
        ret = interrupt_intx_priority_init(int_obj);
#endif
        /*Configure interrupt I/O pin*/
        ret = interrupt_intx_pin_init(int_obj);
        /*Configure callback function*/
        ret = interrupt_INTx_SetInterruptHandler(int_obj);
        /*Enable Interrupt*/
        ret = interrupt_intx_enable(int_obj);
    }
    return ret;
}

/**
 * @brief Deinitializes the external interrupt for the specified INTx pin.
 * @param int_obj  Pointer to a structure that holds the configuration settings for the INTx interrupt.
 * @return STD_ReturnType Returns the success or error status of the initialization.  
 */
STD_ReturnType interrupt_INTx_deinit(const interrupt_INTx_t * int_obj) {
    STD_ReturnType ret = E_NOK;
    if (NULL == int_obj) {
        ret = E_NOK;
    } else {
        /*Disabe Interrupt*/
        ret = interrupt_intx_disable(int_obj);
        /*Clear interrupt flag*/
        ret = interrupt_intx_clear_flag(int_obj);
    }
    return ret;
}

/**
 * @brief Initializes the interrupt for the specified RBx pin (RB4 to RB7).
 * @param int_obj  Pointer to a structure that holds the configuration settings for the INTx interrupt.
 * @return STD_ReturnType Returns the success or error status of the initialization.  
 */
STD_ReturnType interrupt_RBx_init(const interrupt_RBx_t * int_obj) {
    STD_ReturnType ret = E_NOK;
    if (NULL == int_obj) {
        ret = E_NOK;
    } else {
        /*Disabe Interrupt*/
        interrupt_RBx_disable(int_obj);
        /*Clear interrupt flag*/
        interrupt_RBx_clear_flag(int_obj);
        /*Configure interrupt priority*/
#if INTERRUPT_PORIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
        interrupt_RBx_priority_init(int_obj);
#endif
        /*Configure interrupt I/O pin*/
        interrupt_RBx_pin_init(int_obj);
        /*Configure callback function*/
        interrupt_RBx_SetInterruptHandler(int_obj);
        /*Enable Interrupt*/
        interrupt_RBx_enable(int_obj);
    }
    return ret;
}

/**
 * @brief Deinitializes the interrupt for the specified RBx pin (RB4 to RB7).
 * @param int_obj  Pointer to a structure that holds the configuration settings for the RBx interrupt.
 * @return STD_ReturnType Returns the success or error status of the initialization.  
 */
STD_ReturnType interrupt_RBx_deinit(const interrupt_RBx_t * int_obj) {
    STD_ReturnType ret = E_NOK;
    if (NULL == int_obj) {
        ret = E_NOK;
    } else {
        /*Disabe Interrupt*/
        interrupt_RBx_disable(int_obj);
        /*Clear interrupt flag*/
        interrupt_RBx_clear_flag(int_obj);
    }
    return ret;
}

/************procedure for External interrupt INTx************/
static STD_ReturnType interrupt_intx_enable(const interrupt_INTx_t * int_obj) {
    STD_ReturnType ret = E_NOK;
    if (NULL == int_obj) {
        ret = E_NOK;
    } else {
        switch (int_obj->source) {
            case INTERRUPT_EXTERNAL_INT0:
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_Global_InterruptHighEnable();
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT0_INTERRUPT_ENABLE();
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT1:
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_Priority_level_Enable();
                if (INTERRUPT_LOW_PRIORITY == int_obj->priority) {
                    INTERRUPT_Global_InterruptLowEnable();
                } else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority) {
                    INTERRUPT_Global_InterruptHighEnable();
                } else {
                    /*Nothing*/
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT1_INTERRUPT_ENABLE();
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT2:
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_Priority_level_Enable();
                if (INTERRUPT_LOW_PRIORITY == int_obj->priority) {
                    INTERRUPT_Global_InterruptLowEnable();
                } else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority) {
                    INTERRUPT_Global_InterruptHighEnable();
                } else {
                    /*Nothing*/
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_INT2_INTERRUPT_ENABLE();
                ret = E_OK;
                break;
            default: ret = E_NOK;
        }

    }
    return ret;
}

static STD_ReturnType interrupt_intx_disable(const interrupt_INTx_t * int_obj) {
    STD_ReturnType ret = E_NOK;
    if (NULL == int_obj) {
        ret = E_NOK;
    } else {
        switch (int_obj->source) {
            case INTERRUPT_EXTERNAL_INT0:
                EXT_INT0_INTERRUPT_DISABLE();
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT1:
                EXT_INT1_INTERRUPT_DISABLE();
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT2:
                EXT_INT2_INTERRUPT_DISABLE();
                ret = E_OK;
                break;
            default: ret = E_NOK;
        }
    }
    return ret;
}
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE

static STD_ReturnType interrupt_intx_priority_init(const interrupt_INTx_t *int_obj) {
    STD_ReturnType ret = E_NOK;
    if (NULL == int_obj) {
        ret = E_NOK;
    } else {
        switch (int_obj->source) {
            case INTERRUPT_EXTERNAL_INT1:
                if (INTERRUPT_LOW_PRIORITY == int_obj->priority) {
                    EXT_INT1_LOW_PRIORITY_SET();
                } else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority) {
                    EXT_INT1_HIGH_PRIORITY_SET();
                } else {
                    /*Nothing*/
                }
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT2:
                if (INTERRUPT_LOW_PRIORITY == int_obj->priority) {
                    EXT_INT2_LOW_PRIORITY_SET();
                } else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority) {
                    EXT_INT2_HIGH_PRIORITY_SET();
                } else {
                    /*Nothing*/
                }
                ret = E_OK;
                break;
            default: ret = E_NOK;
        }
    }
    return ret;
}
#endif

static STD_ReturnType interrupt_intx_edge_init(const interrupt_INTx_t * int_obj) {
    STD_ReturnType ret = E_NOK;
    if (NULL == int_obj) {
        ret = E_NOK;
    } else {
        switch (int_obj->source) {
            case INTERRUPT_EXTERNAL_INT0:
                if (INTERRUPT_RISING_EDGE == int_obj->edge) {
                    EXT_INT0_INTERRUPT_RISING_EDGE();
                } else if (INTERRUPT_FALLING_EDGE == int_obj->edge) {
                    EXT_INT0_INTERRUPT_FALLING_EDGE();
                } else {
                    /*Nothing*/
                }
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT1:
                if (INTERRUPT_RISING_EDGE == int_obj->edge) {
                    EXT_INT1_INTERRUPT_RISING_EDGE();
                } else if (INTERRUPT_FALLING_EDGE == int_obj->edge) {
                    EXT_INT1_INTERRUPT_FALLING_EDGE();
                } else {
                    /*Nothing*/
                }
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT2:
                if (INTERRUPT_RISING_EDGE == int_obj->edge) {
                    EXT_INT2_INTERRUPT_RISING_EDGE();
                } else if (INTERRUPT_FALLING_EDGE == int_obj->edge) {
                    EXT_INT2_INTERRUPT_FALLING_EDGE();
                } else {
                    /*Nothing*/
                }
                ret = E_OK;
                break;
            default: ret = E_NOK;
        }
    }
    return ret;
}

static STD_ReturnType interrupt_intx_pin_init(const interrupt_INTx_t * int_obj) {
    STD_ReturnType ret = E_NOK;
    if (NULL == int_obj) {
        ret = E_NOK;
    } else {
        ret = gpio_pin_direction_initializion(&(int_obj->mcu_pin));
    }
    return ret;
}

static STD_ReturnType interrupt_intx_clear_flag(const interrupt_INTx_t * int_obj) {
    STD_ReturnType ret = E_NOK;
    if (NULL == int_obj) {
        ret = E_NOK;
    } else {
        switch (int_obj->source) {
            case INTERRUPT_EXTERNAL_INT0:
                EXT_INT0_INTERRUPT_CLEAR_FLAG();
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT1:
                EXT_INT1_INTERRUPT_CLEAR_FLAG();
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT2:
                EXT_INT2_INTERRUPT_CLEAR_FLAG();
                ret = E_OK;
                break;
            default: ret = E_NOK;
        }
    }
    return ret;
}

static STD_ReturnType INT0_SetInterruptHandler(void (*InterruptHandler)(void)) {
    STD_ReturnType ret = E_NOK;
    if (NULL == InterruptHandler) {
        ret = E_NOK;
    } else {
        INT0_InterruptHandler = InterruptHandler;
    }
    return ret;
}

static STD_ReturnType INT1_SetInterruptHandler(void (*InterruptHandler)(void)) {
    STD_ReturnType ret = E_NOK;
    if (NULL == InterruptHandler) {
        ret = E_NOK;
    } else {
        INT1_InterruptHandler = InterruptHandler;
    }
    return ret;
}

static STD_ReturnType INT2_SetInterruptHandler(void (*InterruptHandler)(void)) {
    STD_ReturnType ret = E_NOK;
    if (NULL == InterruptHandler) {
        ret = E_NOK;
    } else {
        INT2_InterruptHandler = InterruptHandler;
    }
    return ret;
}

static STD_ReturnType interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj) {
    STD_ReturnType ret = E_NOK;
    if (NULL == int_obj) {
        ret = E_NOK;
    } else {
        switch (int_obj->source) {
            case INTERRUPT_EXTERNAL_INT0:
                INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT1:
                INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_INT2:
                INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);
                ret = E_OK;
                break;
            default: ret = E_NOK;
        }
    }
    return ret;
}

void INT0_ISR(void) {

    if (INT0_InterruptHandler) {
        INT0_InterruptHandler();
    } else {
    }
    EXT_INT0_INTERRUPT_CLEAR_FLAG();
}

void INT1_ISR(void) {
    EXT_INT1_INTERRUPT_CLEAR_FLAG();

    if (INT1_InterruptHandler) {
        INT1_InterruptHandler();
    } else {
    }
}

void INT2_ISR(void) {
    EXT_INT2_INTERRUPT_CLEAR_FLAG();

    if (INT2_InterruptHandler) {
        INT2_InterruptHandler();
    } else {
    }
}

/***********procedure for interrupt on change***********/

static STD_ReturnType interrupt_RBx_enable(const interrupt_RBx_t * int_obj) {
    STD_ReturnType ret = E_NOK;
    if (NULL == int_obj) {
        ret = E_NOK;
    } else {
        switch (int_obj->source) {
            case INTERRUPT_EXTERNAL_RB4:
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_Priority_level_Enable();
                if (INTERRUPT_LOW_PRIORITY == int_obj->priority) {
                    INTERRUPT_Global_InterruptLowEnable();
                } else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority) {
                    INTERRUPT_Global_InterruptHighEnable();
                } else {
                    /*Nothing*/
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_RB4_INTERRUPT_IOCB_ENABLE();
                EXT_RBX_INTERRUPT_ENABLE();
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_RB5:
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_Priority_level_Enable();
                if (INTERRUPT_LOW_PRIORITY == int_obj->priority) {
                    INTERRUPT_Global_InterruptLowEnable();
                } else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority) {
                    INTERRUPT_Global_InterruptHighEnable();
                } else {
                    /*Nothing*/
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_RB5_INTERRUPT_IOCB_ENABLE();
                EXT_RBX_INTERRUPT_ENABLE();
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_RB6:
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_Priority_level_Enable();
                if (INTERRUPT_LOW_PRIORITY == int_obj->priority) {
                    INTERRUPT_Global_InterruptLowEnable();
                } else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority) {
                    INTERRUPT_Global_InterruptHighEnable();
                } else {
                    /*Nothing*/
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_RB6_INTERRUPT_IOCB_ENABLE();
                EXT_RBX_INTERRUPT_ENABLE();
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_RB7:
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
                INTERRUPT_Priority_level_Enable();
                if (INTERRUPT_LOW_PRIORITY == int_obj->priority) {
                    INTERRUPT_Global_InterruptLowEnable();
                } else if (INTERRUPT_HIGH_PRIORITY == int_obj->priority) {
                    INTERRUPT_Global_InterruptHighEnable();
                } else {
                    /*Nothing*/
                }
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif
                EXT_RB7_INTERRUPT_IOCB_ENABLE();
                EXT_RBX_INTERRUPT_ENABLE();
                ret = E_OK;
                break;
            default: ret = E_NOK;
        }
    }
    return ret;
}

static STD_ReturnType interrupt_RBx_disable(const interrupt_RBx_t * int_obj) {
    STD_ReturnType ret = E_NOK;
    if (NULL == int_obj) {
        ret = E_NOK;
    } else {
        EXT_RBX_INTERRUPT_DISABLE();
        EXT_RBX_INTERRUPT_CLEAR_FLAG();
        ret = E_OK;
    }
    return ret;
}
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE

static STD_ReturnType interrupt_RBx_priority_init(const interrupt_RBx_t * int_obj) {
    STD_ReturnType ret = E_NOK;
    if (NULL == int_obj) {
        ret = E_NOK;
    } else {
        switch (int_obj->source) {
            case INTERRUPT_EXTERNAL_RB4:
            case INTERRUPT_EXTERNAL_RB5:
            case INTERRUPT_EXTERNAL_RB6:
            case INTERRUPT_EXTERNAL_RB7:
                if (int_obj->priority == INTERRUPT_HIGH_PRIORITY) {
                    EXT_RBX_HIGH_PRIORITY_SET();
                } else if (int_obj->priority == INTERRUPT_LOW_PRIORITY) {
                    EXT_RBX_LOW_PRIORITY_SET();
                } else {
                    /*Nothing*/
                }
                ret = E_OK;
                break;
            default: ret = E_NOK;
        }
    }
    return ret;
}
#endif

static STD_ReturnType interrupt_RBx_pin_init(const interrupt_RBx_t * int_obj) {
    STD_ReturnType ret = E_NOK;
    if (NULL == int_obj) {
        ret = E_NOK;
    } else {
        ret = gpio_pin_direction_initializion(&(int_obj->mcu_pin));
    }
    return ret;
}

static STD_ReturnType interrupt_RBx_clear_flag(const interrupt_RBx_t * int_obj) {
    STD_ReturnType ret = E_NOK;
    if (NULL == int_obj) {
        ret = E_NOK;
    } else {
        EXT_RBX_INTERRUPT_CLEAR_FLAG();
    }
    return ret;
}

static STD_ReturnType interrupt_RBx_SetInterruptHandler(const interrupt_RBx_t *int_obj) {
    STD_ReturnType ret = E_NOK;
    if (NULL == int_obj) {
        ret = E_NOK;
    } else {
        switch (int_obj->source) {
            case INTERRUPT_EXTERNAL_RB4:
                RB4_InterruptHandlerHigh = int_obj->EXT_InterruptHandler_high;
                RB4_InterruptHandlerLow = int_obj->EXT_InterruptHandler_low;
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_RB5:
                RB5_InterruptHandlerHigh = int_obj->EXT_InterruptHandler_high;
                RB5_InterruptHandlerLow = int_obj->EXT_InterruptHandler_low;
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_RB6:
                RB6_InterruptHandlerHigh = int_obj->EXT_InterruptHandler_high;
                RB6_InterruptHandlerLow = int_obj->EXT_InterruptHandler_low;
                ret = E_OK;
                break;
            case INTERRUPT_EXTERNAL_RB7:
                RB7_InterruptHandlerHigh = int_obj->EXT_InterruptHandler_high;
                RB7_InterruptHandlerLow = int_obj->EXT_InterruptHandler_low;
                ret = E_OK;
                break;
            default:ret = E_NOK;
        }
    }
    return ret;
}

void RB4_ISR(uint8 source) {
    EXT_RBX_INTERRUPT_CLEAR_FLAG();
    if (source == 1) {
        if (RB4_InterruptHandlerHigh) {
            RB4_InterruptHandlerHigh();
        } else {
        }
    } else if (source == 0) {
        if (RB4_InterruptHandlerLow) {
            RB4_InterruptHandlerLow();
        } else {
        }
    } else {
    }
}

void RB5_ISR(uint8 source) {
    EXT_RBX_INTERRUPT_CLEAR_FLAG();
    if (source == 1) {
        if (RB5_InterruptHandlerHigh) {
            RB5_InterruptHandlerHigh();
        } else {
        }
    } else if (source == 0) {
        if (RB5_InterruptHandlerLow) {
            RB5_InterruptHandlerLow();
        } else {
        }
    } else {
    }
}

void RB6_ISR(uint8 source) {
    EXT_RBX_INTERRUPT_CLEAR_FLAG();
    if (source == 1) {
        if (RB6_InterruptHandlerHigh) {
            RB6_InterruptHandlerHigh();
        } else {
        }
    } else if (source == 0) {
        if (RB6_InterruptHandlerLow) {
            RB6_InterruptHandlerLow();
        } else {
        }
    } else {
    }
}

void RB7_ISR(uint8 source) {
    EXT_RBX_INTERRUPT_CLEAR_FLAG();
    if (source == 1) {
        if (RB7_InterruptHandlerHigh) {
            RB7_InterruptHandlerHigh();
        } else {
        }
    } else if (source == 0) {
        if (RB7_InterruptHandlerLow) {
            RB7_InterruptHandlerLow();
        } else {
        }
    } else {
    }
}
