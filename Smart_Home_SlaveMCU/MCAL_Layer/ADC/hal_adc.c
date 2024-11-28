/* 
 * File:   hal_adc.c
 * Author: LEGION
 *
 * Created on September 29, 2024, 1:02 PM
 */

#include "hal_adc.h"

static inline void adc_input_channel_port_configure(ADC_Channel_Select_t channel);
static inline void select_result_format(const ADC_config_t *adc);
static inline void select_voltage_reference(const ADC_config_t *adc);


#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
void (* ADC_Interrupt_Handler)(void) = NULL;
#endif

STD_ReturnType ADC_init(const ADC_config_t *adc) {
    STD_ReturnType ret = E_NOK;
    if (NULL == adc) {
        ret = E_NOK;
    } else {
        /*Disable ADC*/
        ADC_CONVERSION_DISABLE();
        /*Configure Acquisition time*/
        ADCON2bits.ACQT = adc->Aquisition_time;
        /*Configure Conversion time*/
        ADCON2bits.ADCS = adc->Conversion_Clock;
        /*Select channel*/
        ADCON0bits.CHS = adc->Channel_Select;
        adc_input_channel_port_configure(adc->Channel_Select);
        /*Configure Interrupt*/
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        ADC_INTERRUPT_ENABLE();
        ADC_INTERRUPT_CLEAR_FLAG();
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
        INTERRUPT_Priority_level_Enable();
        if (adc->priority == INTERRUPT_HIGH_PRIORITY) {
            INTERRUPT_Global_InterruptHighEnable();
            ADC_HIGH_PRIORITY();
        } else if (adc->priority == INTERRUPT_LOW_PRIORITY) {
            INTERRUPT_Global_InterruptLowEnable();
            ADC_LOW_PRIORITY();
        } else {
        }
#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
        ADC_Interrupt_Handler = adc->InterruptHandler;
#endif
        /*Select result format*/
        select_result_format(adc);
        /*Configure voltage reference*/
        select_voltage_reference(adc);
        /*Enable ADC*/
        ADC_CONVERSION_ENABLE();
        ret = E_OK;
    }
    return ret;
}

STD_ReturnType ADC_DeInit(const ADC_config_t *adc) {
    STD_ReturnType ret = E_NOK;
    if (NULL == adc) {
        ret = E_NOK;
    } else {
        ADC_CONVERSION_DISABLE();
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
        ADC_INTERRUPT_DISABLE();
#endif
        ret = E_OK;
    }
    return ret;
}

STD_ReturnType ADC_SelectChannel(const ADC_config_t *adc, ADC_Channel_Select_t channel) {
    STD_ReturnType ret = E_NOK;
    if (NULL == adc) {
        ret = E_NOK;
    } else {
        ADCON0bits.CHS = channel;
        adc_input_channel_port_configure(channel);
    }
    return ret;
}

STD_ReturnType ADC_StartConversion(const ADC_config_t *adc) {
    STD_ReturnType ret = E_NOK;
    if (NULL == adc) {
        ret = E_NOK;
    } else {
        ADC_CONVERSION_START();
    }
    return ret;
}

/**
 * 
 * @param adc
 * @param conversion_status
 *        true  - if conversion is complete
 *        false - if conversion is not complete 
 * @return 
 */
STD_ReturnType ADC_IsConversionDone(const ADC_config_t *adc, uint8 *conversion_status) {
    STD_ReturnType ret = E_NOK;
    if ((NULL == adc) || (NULL == conversion_status)) {
        ret = E_NOK;
    } else {
        *conversion_status = (uint8) (!(ADCON0bits.GO_nDONE));
    }
    return ret;
}

STD_ReturnType ADC_GetConversionResult(const ADC_config_t *adc, uint16 *conversion_result) {
    STD_ReturnType ret = E_NOK;
    if ((NULL == adc) || (NULL == conversion_result)) {
        ret = E_NOK;
    } else {
        if (ADC_RESULT_RIGHT == adc->result_format) {
            *conversion_result = (uint16) ((ADRESH << 8) + ADRESL);
        } else if (ADC_RESULT_LEFT == adc->result_format) {
            *conversion_result = (uint16) (((ADRESH << 8) + ADRESL) << 6);
        } else {
            /*Default*/
            *conversion_result = (uint16) ((ADRESH << 8) + ADRESL);
        }
    }
    return ret;
}

STD_ReturnType ADC_GetConversion_Blocking(const ADC_config_t *adc, ADC_Channel_Select_t channel, uint16 *conversion_result) {
    STD_ReturnType ret = E_NOK;
    if ((NULL == adc) || (NULL == conversion_result)) {
        ret = E_NOK;
    } else {
        /*Select channel */
        ret = ADC_SelectChannel(adc, channel);
        /*Start Conversion*/
        ret = ADC_StartConversion(adc);
        /*check if conversion is completed*/
        while (ADCON0bits.GO_nDONE);
        /* Get result */
        ret = ADC_GetConversionResult(adc, conversion_result);
        ret = E_OK;
    }
    return ret;
}

STD_ReturnType ADC_StartConversion_Interrupt(const ADC_config_t *adc, ADC_Channel_Select_t channel) {
    STD_ReturnType ret = E_NOK;
    if (NULL == adc) {
        ret = E_NOK;
    } else {
        /*Select channel */
        ret = ADC_SelectChannel(adc, channel);
        /*Start Conversion*/
        ret = ADC_StartConversion(adc);
    }
    return ret;
}

static inline void adc_input_channel_port_configure(ADC_Channel_Select_t channel) {
    switch (channel) {
        case ADC_CHANNEL_AN0:
            ADC_AN0_ANALOG_ENABLE();
            SETBIT(TRISA, _TRISA_RA0_POSN);
            break;
        case ADC_CHANNEL_AN1:
            ADC_AN1_ANALOG_ENABLE();
            SETBIT(TRISA, _TRISA_RA1_POSN);
            break;
        case ADC_CHANNEL_AN2:
            ADC_AN2_ANALOG_ENABLE();
            SETBIT(TRISA, _TRISA_RA2_POSN);
            break;
        case ADC_CHANNEL_AN3:
            ADC_AN3_ANALOG_ENABLE();
            SETBIT(TRISA, _TRISA_RA3_POSN);
            break;
        case ADC_CHANNEL_AN4:
            ADC_AN4_ANALOG_ENABLE();
            SETBIT(TRISA, _TRISA_RA5_POSN);
            break;
        case ADC_CHANNEL_AN5:
            ADC_AN5_ANALOG_ENABLE();
            SETBIT(TRISE, _TRISE_RE0_POSN);
            break;
        case ADC_CHANNEL_AN6:
            ADC_AN6_ANALOG_ENABLE();
            SETBIT(TRISE, _TRISE_RE1_POSN);
            break;
        case ADC_CHANNEL_AN7:
            ADC_AN7_ANALOG_ENABLE();
            SETBIT(TRISE, _TRISE_RE2_POSN);
            break;
        case ADC_CHANNEL_AN8:
            ADC_AN8_ANALOG_ENABLE();
            SETBIT(TRISB, _TRISB_RB2_POSN);
            break;
        case ADC_CHANNEL_AN9:
            ADC_AN9_ANALOG_ENABLE();
            SETBIT(TRISB, _TRISB_RB3_POSN);
            break;
        case ADC_CHANNEL_AN10:
            ADC_AN10_ANALOG_ENABLE();
            SETBIT(TRISB, _TRISB_RB1_POSN);
            break;
        case ADC_CHANNEL_AN11:
            ADC_AN11_ANALOG_ENABLE();
            SETBIT(TRISB, _TRISB_RB4_POSN);
            break;
        case ADC_CHANNEL_AN12:
            ADC_AN12_ANALOG_ENABLE();
            SETBIT(TRISB, _TRISB_RB0_POSN);
            break;
    }
}

static inline void select_result_format(const ADC_config_t *adc) {
    STD_ReturnType ret = E_NOK;
    if (NULL == adc) {
        ret = E_NOK;
    } else {
        if (ADC_RESULT_RIGHT == adc->result_format) {
            ADC_RESULT_RIGHT_FORMAT();
        } else if (ADC_RESULT_LEFT == adc->result_format) {
            ADC_RESULT_LEFT_FORMAT();
        } else {
            /*Default*/
            ADC_RESULT_RIGHT_FORMAT();
        }
    }
}

static inline void select_voltage_reference(const ADC_config_t *adc) {
    STD_ReturnType ret = E_NOK;
    if (NULL == adc) {
        ret = E_NOK;
    } else {
        if (ADC_VOLTAGE_REFERENCE_ENABLE == adc->voltage_reference) {
            ADC_ENABLE_VOLTAGE_REFERENCE();
        } else if (ADC_VOLTAGE_REFERENCE_DISABLE == adc->voltage_reference) {
            ADC_DISABLE_VOLTAGE_REFERENCE();
        } else {
            /*Default*/
            ADC_DISABLE_VOLTAGE_REFERENCE();
        }
    }
}

void ADC_ISR(void) {
    ADC_INTERRUPT_CLEAR_FLAG();
    if (ADC_Interrupt_Handler) {
        ADC_Interrupt_Handler();
    } else {
    }
}