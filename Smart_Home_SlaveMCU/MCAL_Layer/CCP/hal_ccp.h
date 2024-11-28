/* 
 * File:   hal_ccp.h
 * Author: LEGION
 *
 * Created on October 11, 2024, 4:25 PM
 */

#ifndef HAL_CCP_H
#define	HAL_CCP_H

/* Section : Includes */
#include "hal_ccp_cfg.h"
#include "../GPIO/hal_gpio.h"
#include "../interrupt/internal_interrupt.h"
/*Section : Macro Declaration*/
// Disables the CCP module.
#define CCP_MODULE_DISABLE                  0x00

// Captures on every falling edge.
#define CCP_CAPTURE_MODE_FALLING_EDGE       0x04

// Captures on every rising edge.
#define CCP_CAPTURE_MODE_1_RISING_EDGE      0x05

// Captures on every 4th rising edge.
#define CCP_CAPTURE_MODE_4_RISING_EDGE      0x06

// Captures on every 16th rising edge.
#define CCP_CAPTURE_MODE_16_RISING_EDGE     0x07

// Toggles the output on compare match.
#define CCP_COMPARE_MODE_TOGGLE_OUTPUT      0x02

// Sets the output high on compare match.
#define CCP_COMPARE_MODE_SET_HIGH_OUTPUT    0x08

// Sets the output low on compare match.
#define CCP_COMPARE_MODE_SET_LOW_OUTPUT     0x09

// Generates a software interrupt on compare match.
#define CCP_COMPARE_MODE_GEN_SW_INTERRUPT   0x0A

// Triggers a special event on compare match.
#define CCP_COMPARE_MODE_GEN_SPECIAL_EVENT  0x0B

// Enables PWM mode.
#define CCP_PWM_MODE                        0x0C

/* Macro for checking capture readiness */
#define CCP_CAPTURE_NOT_READY              0x00
#define CCP_CAPTURE_READY                  0x01

/* Macro for checking compare readiness */
#define CCP_COMPARE_NOT_READY              0x00
#define CCP_COMPARE_READY                  0x01

/* Postscaler options for CCP2 using Timer2
 * These define the division ratio applied to Timer2 after counting up to a specified value.
 * Postscaling allows Timer2 to slow down its output frequency to the CCP2 module.
 */
#define CCP_TIMER2_POSTSCALER_DIV_BY_1                 1   // No postscaler, direct Timer2 output
#define CCP_TIMER2_POSTSCALER_DIV_BY_2                 2   // Timer2 output divided by 2
#define CCP_TIMER2_POSTSCALER_DIV_BY_3                 3   // Timer2 output divided by 3
#define CCP_TIMER2_POSTSCALER_DIV_BY_4                 4   // Timer2 output divided by 4
#define CCP_TIMER2_POSTSCALER_DIV_BY_5                 5   // Timer2 output divided by 5
#define CCP_TIMER2_POSTSCALER_DIV_BY_6                 6   // Timer2 output divided by 6
#define CCP_TIMER2_POSTSCALER_DIV_BY_7                 7   // Timer2 output divided by 7
#define CCP_TIMER2_POSTSCALER_DIV_BY_8                 8   // Timer2 output divided by 8
#define CCP_TIMER2_POSTSCALER_DIV_BY_9                 9   // Timer2 output divided by 9
#define CCP_TIMER2_POSTSCALER_DIV_BY_10                10   // Timer2 output divided by 10
#define CCP_TIMER2_POSTSCALER_DIV_BY_11                11  // Timer2 output divided by 11
#define CCP_TIMER2_POSTSCALER_DIV_BY_12                12  // Timer2 output divided by 12
#define CCP_TIMER2_POSTSCALER_DIV_BY_13                13  // Timer2 output divided by 13
#define CCP_TIMER2_POSTSCALER_DIV_BY_14                14  // Timer2 output divided by 14
#define CCP_TIMER2_POSTSCALER_DIV_BY_15                15  // Timer2 output divided by 15
#define CCP_TIMER2_POSTSCALER_DIV_BY_16                16  // Timer2 output divided by 16

/* Prescaler options for CCP2 using Timer2
 * These define the division ratio applied to the input clock of Timer2 before it begins counting.
 * Prescaling allows Timer2 to slow down its counting speed relative to the clock.
 */
#define CCP_TIMER2_PRESCALER_DIV_BY_1                1   // No prescaler, direct clock input to Timer2
#define CCP_TIMER2_PRESCALER_DIV_BY_4                2   // Timer2 clock input divided by 4
#define CCP_TIMER2_PRESCALER_DIV_BY_16               3   // Timer2 clock input divided by 16

/*Section : Macro Function Declaration*/
// Sets the mode of CCP1 by assigning the provided value to the CCP1M bits in the CCP1CON register.
#define CCP1_MODE_SELECT(_CCP1)        (CCP1CONbits.CCP1M = _CCP1)

// Sets the mode of CCP2 by assigning the provided value to the CCP2M bits in the CCP2CON register.
#define CCP2_MODE_SELECT(_CCP2)        (CCP2CONbits.CCP2M = _CCP2)


/*Section : Data Type Declaration*/

/* Enumeration for selecting between Capture, Compare, and PWM modes for CCP1 */
typedef enum {
    CCP_CAPTURE_SELECT,
    CCP_COMPARE_SELECT,
    CCP_PWM_SELECT
} ccp_mode_t;

typedef enum {
    CCP1_CCP2_TIMER1, // Both CCP1 and CCP2 use Timer1 for capture or compare.
    CCP1_TIMER1_CCP2_TIMER3, // CCP1 uses Timer1 and CCP2 uses Timer3 for capture or compare.
    CCP1_CCP2_TIMER3 // Both CCP1 and CCP2 use Timer3 for capture or compare.
} ccp_capture_compare_timer3_t;

typedef union {

    struct {
        uint8 ccpr_low; /* 8-bit low part of the CCP register */
        uint8 ccpr_high; /* 8-bit high part of the CCP1 register */
    };

    struct {
        uint16 ccpr_16bit; /* 16-bit value of the CCP register */
    };

} CCP_REG_T;

// Defines the CCP instance selection for use in code, either CCP1 or CCP2.

typedef enum {
    CCP1_INST, // Refers to the CCP1 instance.
    CCP2_INST // Refers to the CCP2 instance.
} ccp_inst_t;

typedef struct {
    ccp_inst_t ccp_inst; // Specifies the CCP instance (either CCP1 or CCP2).
    ccp_mode_t ccp_mode; // Specifies the mode for CCP (capture, compare, or PWM).
    pin_config_t pin_cfg; // Configuration of the CCP pin (input/output, etc.).
    uint8 ccp_mode_variant; // Stores a variant for the selected CCP mode, such as rising or falling edge for capture mode.
    ccp_capture_compare_timer3_t ccp_capture_compare_timer3; // Specifies the timer selection when using capture mode (Timer1 or Timer3).
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE 
    void(* CCP1_InterruptHandler)(void); // Pointer to the interrupt handler function for CCP1.
    priority_level_t ccp1_priority; // Specifies the priority level for CCP1 interrupts.
#endif

#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void(* CCP2_InterruptHandler)(void); // Pointer to the interrupt handler function for CCP2.
    priority_level_t ccp2_priority; // Specifies the priority level for CCP2 interrupts.
#endif

#if (CCP1_CONFIG_MODE_SELECT == CCP_PWM_MODE_SELECTED) || (CCP2_CONFIG_MODE_SELECT == CCP_PWM_MODE_SELECTED)
    uint32 PWM_frequency; // Specifies the PWM frequency when using PWM mode.
    uint8 timer2_postscaler_val : 4; // Postscaler value for Timer2, used in PWM mode (4-bit field).
    uint8 timer2_prescaler_val : 2; // Prescaler value for Timer2, used in PWM mode (2-bit field).
#endif 
} ccp_t;

/*Section : Function Declaration*/
/* Function to initialize CCP1 module */
STD_ReturnType CCP_Init(const ccp_t * ccp);
/* Function to de_initialize CCP1 module */
STD_ReturnType CCP_DeInit(const ccp_t * ccp);

#if (CCP1_CONFIG_MODE_SELECT == CCP_CAPTURE_MODE_SELECTED) || (CCP2_CONFIG_MODE_SELECT == CCP_CAPTURE_MODE_SELECTED)
/* Function to check if capture data is ready */
STD_ReturnType CCP_IsCaptureDataReady(uint8 *capture_status);
/* Function to read captured data */
STD_ReturnType CCP_CaptureDataRead(const ccp_t * ccp, uint16 *capture_value);
#endif

#if (CCP1_CONFIG_MODE_SELECT == CCP_COMPARE_MODE_SELECTED) || (CCP2_CONFIG_MODE_SELECT == CCP_COMPARE_MODE_SELECTED)
/* Function to check if comparison is complete */
STD_ReturnType CCP_IsCompareComplete(uint8 *compare_status);
/* Function to set comparison value */
STD_ReturnType CCP_CompareSetValue(const ccp_t * ccp, uint16 compare_value);
#endif

#if (CCP1_CONFIG_MODE_SELECT == CCP_PWM_MODE_SELECTED) || (CCP2_CONFIG_MODE_SELECT == CCP_PWM_MODE_SELECTED)
/* Function to set PWM duty cycle */
STD_ReturnType CCP_PWM_Set_Duty(const ccp_t * ccp, const uint8 duty);
/* Function to start PWM mode */
STD_ReturnType CCP_PWM_Start(const ccp_t * ccp1);
/* Function to stop PWM mode */
STD_ReturnType CCP_PWM_Stop(const ccp_t * ccp);
#endif
#endif	/* HAL_CCP_H */

