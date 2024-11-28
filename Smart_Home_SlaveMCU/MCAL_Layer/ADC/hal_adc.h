/* 
 * File:   hal_adc.h
 * Author: LEGION
 *
 * Created on September 29, 2024, 1:02 PM
 */

#ifndef HAL_ADC_H
#define	HAL_ADC_H

/* Section : Includes */
#include "../GPIO/hal_gpio.h"
#include "hal_adc_cfg.h"
#include "../interrupt/internal_interrupt.h"

/*Section : Macro Function Declaration*/
/****************ADCON0****************/
/*A/D conversion status--> conversion in progress(1) / idle state(0) */
#define ADC_CONVERSION_STATUS()   (ADCON0bits.GO_nDONE)  
/*start conversion of A/D */
#define ADC_CONVERSION_START()    (ADCON0bits.GO_nDONE = 1)
/*enable ADC*/
#define ADC_CONVERSION_ENABLE()   (ADCON0bits.ADON = 1)
/*Disable ADC*/
#define ADC_CONVERSION_DISABLE()   (ADCON0bits.ADON = 0)
/****************ADCON1****************/
#define ADC_ENABLE_VOLTAGE_REFERENCE() do{ \
    ADCON1bits.VCFG1 = 1; /* VREF- from external pin */ \
    ADCON1bits.VCFG0 = 1; /* VREF- from external pin */ \
} while(0)

#define ADC_DISABLE_VOLTAGE_REFERENCE() do{ \
    ADCON1bits.VCFG1 = 0; /* VREF- from VSS (ground) */ \
    ADCON1bits.VCFG0 = 0; /*  VREF+ from VDD (power supply) */ \
} while(0)
/****************ADCON2****************/
#define ADC_RESULT_RIGHT_FORMAT()    (ADCON2bits.ADFM = 1)
#define ADC_RESULT_LEFT_FORMAT()    (ADCON2bits.ADFM = 0)
/*-----------------ANSEL & ANSELH-----------------*/
/* Enable or disable configuration of AN0*/
#define ADC_AN0_ANALOG_ENABLE()    (ANSELbits.ANS0 = 1)
#define ADC_AN0_ANALOG_DISABLE()   (ANSELbits.ANS0 = 0)
/* Enable or disable configuration of AN1*/
#define ADC_AN1_ANALOG_ENABLE()    (ANSELbits.ANS1 = 1)
#define ADC_AN1_ANALOG_DISABLE()   (ANSELbits.ANS1 = 0)
/* Enable or disable configuration of AN2*/
#define ADC_AN2_ANALOG_ENABLE()    (ANSELbits.ANS2 = 1)
#define ADC_AN2_ANALOG_DISABLE()   (ANSELbits.ANS2 = 0)
/* Enable or disable configuration of AN3*/
#define ADC_AN3_ANALOG_ENABLE()    (ANSELbits.ANS3 = 1)
#define ADC_AN3_ANALOG_DISABLE()   (ANSELbits.ANS3 = 0)
/* Enable or disable configuration of AN4*/
#define ADC_AN4_ANALOG_ENABLE()    (ANSELbits.ANS4 = 1)
#define ADC_AN4_ANALOG_DISABLE()   (ANSELbits.ANS4 = 0)
/* Enable or disable configuration of AN5*/
#define ADC_AN5_ANALOG_ENABLE()    (ANSELbits.ANS5 = 1)
#define ADC_AN5_ANALOG_DISABLE()   (ANSELbits.ANS5 = 0)
/* Enable or disable configuration of AN6*/
#define ADC_AN6_ANALOG_ENABLE()    (ANSELbits.ANS6 = 1)
#define ADC_AN6_ANALOG_DISABLE()   (ANSELbits.ANS6 = 0)
/* Enable or disable configuration of AN7*/
#define ADC_AN7_ANALOG_ENABLE()    (ANSELbits.ANS7 = 1)
#define ADC_AN7_ANALOG_DISABLE()   (ANSELbits.ANS7 = 0)
/* Enable or disable configuration of AN8*/
#define ADC_AN8_ANALOG_ENABLE()    (ANSELHbits.ANS8 = 1)
#define ADC_AN8_ANALOG_DISABLE()   (ANSELHbits.ANS8 = 0)
/* Enable or disable configuration of AN9*/
#define ADC_AN9_ANALOG_ENABLE()    (ANSELHbits.ANS9 = 1)
#define ADC_AN9_ANALOG_DISABLE()   (ANSELHbits.ANS9 = 0)
/* Enable or disable configuration of AN10*/
#define ADC_AN10_ANALOG_ENABLE()    (ANSELHbits.ANS10 = 1)
#define ADC_AN10_ANALOG_DISABLE()   (ANSELHbits.ANS10 = 0)
/* Enable or disable configuration of AN11*/
#define ADC_AN11_ANALOG_ENABLE()    (ANSELHbits.ANS11 = 1)
#define ADC_AN11_ANALOG_DISABLE()   (ANSELHbits.ANS11 = 0)
/* Enable or disable configuration of AN12*/
#define ADC_AN12_ANALOG_ENABLE()    (ANSELHbits.ANS12 = 1)
#define ADC_AN12_ANALOG_DISABLE()   (ANSELHbits.ANS12 = 0)
/*Section : Macro Declaration*/
#define ADC_RESULT_RIGHT 0x01U
#define ADC_RESULT_LEFT  0x00U

#define ADC_VOLTAGE_REFERENCE_ENABLE  0x01U
#define ADC_VOLTAGE_REFERENCE_DISABLE 0x00U

#define ADC_CONVERSION_COMPLETED   1
#define ADC_CONVERSION_IN_PORGRESS 0

/*Section : Data Type Declaration*/
typedef enum {
    ADC_CHANNEL_AN0 = 0,
    ADC_CHANNEL_AN1,
    ADC_CHANNEL_AN2,
    ADC_CHANNEL_AN3,
    ADC_CHANNEL_AN4,
    ADC_CHANNEL_AN5,
    ADC_CHANNEL_AN6,
    ADC_CHANNEL_AN7,
    ADC_CHANNEL_AN8,
    ADC_CHANNEL_AN9,
    ADC_CHANNEL_AN10,
    ADC_CHANNEL_AN11,
    ADC_CHANNEL_AN12,
} ADC_Channel_Select_t;

typedef enum {
    ADC_0_TAD = 0,
    ADC_2_TAD,
    ADC_4_TAD,
    ADC_6_TAD,
    ADC_8_TAD,
    ADC_12_TAD,
    ADC_16_TAD,
    ADC_20_TAD,
} ADC_Aquisition_time_t;

typedef enum {
    ADC_CONVERSION_CLOCK_FOSC_DIV_2 = 0,
    ADC_CONVERSION_CLOCK_FOSC_DIV_8,
    ADC_CONVERSION_CLOCK_FOSC_DIV_32,
    ADC_CONVERSION_CLOCK_FOSC_DIV_FRC,
    ADC_CONVERSION_CLOCK_FOSC_DIV_4,
    ADC_CONVERSION_CLOCK_FOSC_DIV_16,
    ADC_CONVERSION_CLOCK_FOSC_DIV_64,
} ADC_Conversion_Clock_t;

typedef struct {
#if ADC_INTERRUPT_FEATURE_ENABLE ==  INTERRUPT_FEATURE_ENABLE
    void (* InterruptHandler) (void);
    priority_level_t priority;
#endif
    ADC_Aquisition_time_t Aquisition_time;
    ADC_Conversion_Clock_t Conversion_Clock;
    ADC_Channel_Select_t Channel_Select;
    uint8 voltage_reference;
    uint8 result_format;
} ADC_config_t;

/*Section : Function Declaration*/
STD_ReturnType ADC_init(const ADC_config_t *adc);
STD_ReturnType ADC_deinit(const ADC_config_t *adc);

STD_ReturnType ADC_SelectChannel(const ADC_config_t *adc, ADC_Channel_Select_t channel);

STD_ReturnType ADC_StartConversion(const ADC_config_t *adc);

STD_ReturnType ADC_IsConversionDone(const ADC_config_t *adc, uint8 *convetsion_status);

STD_ReturnType ADC_GetConversionResult(const ADC_config_t *adc, uint16 *conversion_result);

STD_ReturnType ADC_GetConversion_Blocking(const ADC_config_t *adc, ADC_Channel_Select_t channel, uint16 *conversion_result);

STD_ReturnType ADC_StartConversion_Interrupt(const ADC_config_t *adc, ADC_Channel_Select_t channel);
#endif	/* HAL_ADC_H */

