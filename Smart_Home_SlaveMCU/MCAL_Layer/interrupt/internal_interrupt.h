/* 
 * File:   internal_interrupt.h
 * Author: LEGION
 *
 * Created on September 25, 2024, 10:37 PM
 */

#ifndef INTERNAL_INTERRUPT_H
#define	INTERNAL_INTERRUPT_H
/* Section : Includes */
#include "mcal_interrupt.h"

/*Section : Macro Function Declaration*/
/************ADC************/
#if ADC_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/*Enable ADC interrupt*/
#define ADC_INTERRUPT_ENABLE()     (PIE1bits.ADIE = 1)
/*Disable ADC interrupt*/
#define ADC_INTERRUPT_DISABLE()     (PIE1bits.ADIE = 0)
/*Clear flag of ADC interrupt*/
#define ADC_INTERRUPT_CLEAR_FLAG() (PIR1bits.ADIF = 0)
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This macro will enable high  priority of ADC module*/
#define ADC_HIGH_PRIORITY()         (IPR1bits.ADIP = 1)
/*This macro will enable low  priority of ADC module*/
#define ADC_LOW_PRIORITY()         (IPR1bits.ADIP = 0)
#endif
#endif
/************TIMER0************/
#if TIMER0_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/*Enable TIMER0 interrupt*/
#define TIMER0_INTERRUPT_ENABLE()      (INTCONbits.TMR0IE = 1)
/*Disable TIMER0 interrupt*/
#define TIMER0_INTERRUPT_DISABLE()     (INTCONbits.TMR0IE = 0)
/*Clear flag of TIMER0 interrupt*/
#define TIMER0_INTERRUPT_CLEAR_FLAG()  (INTCONbits.TMR0IF = 0)
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This macro will enable high  priority of TIMER0 module*/
#define TIMER0_HIGH_PRIORITY()        (INTCON2bits.TMR0IP = 1)
/*This macro will enable low  priority of TIMER0 module*/
#define TIMER0_LOW_PRIORITY()         (INTCON2bits.TMR0IP = 0)
#endif
#endif
/************TIMER1************/
#if TIMER1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/*Enable TIMER1 interrupt*/
#define TIMER1_INTERRUPT_ENABLE()      (PIE1bits.TMR1IE = 1)
/*Disable TIMER1 interrupt*/
#define TIMER1_INTERRUPT_DISABLE()     (PIE1bits.TMR1IE = 0)
/*Clear flag of TIMER1 interrupt*/
#define TIMER1_INTERRUPT_CLEAR_FLAG()  (PIR1bits.TMR1IF = 0)
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This macro will enable high  priority of TIMER1 module*/
#define TIMER1_HIGH_PRIORITY()        (IPR1bits.TMR1IP = 1)
/*This macro will enable low  priority of TIMER1 module*/
#define TIMER1_LOW_PRIORITY()         (IPR1bits.TMR1IP = 0)
#endif
#endif
/************TIMER2************/
#if TIMER2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/*Enable TIMER2 interrupt*/
#define TIMER2_INTERRUPT_ENABLE()      (PIE1bits.TMR2IE = 1)
/*Disable TIMER2 interrupt*/
#define TIMER2_INTERRUPT_DISABLE()     (PIE1bits.TMR2IE = 0)
/*Clear flag of TIMER2 interrupt*/
#define TIMER2_INTERRUPT_CLEAR_FLAG()  (PIR1bits.TMR2IF = 0)
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This macro will enable high  priority of TIMER2 module*/
#define TIMER2_HIGH_PRIORITY()        (IPR1bits.TMR2IP = 1)
/*This macro will enable low  priority of TIMER2 module*/
#define TIMER2_LOW_PRIORITY()         (IPR1bits.TMR2IP = 0)
#endif
#endif
/************TIMER3************/
#if TIMER3_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/*Enable TIMER3 interrupt*/
#define TIMER3_INTERRUPT_ENABLE()      (PIE2bits.TMR3IE = 1)
/*Disable TIMER3 interrupt*/
#define TIMER3_INTERRUPT_DISABLE()     (PIE2bits.TMR3IE= 0)
/*Clear flag of TIMER3 interrupt*/
#define TIMER3_INTERRUPT_CLEAR_FLAG()  (PIR2bits.TMR3IF = 0)
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This macro will enable high  priority of TIMER3 module*/
#define TIMER3_HIGH_PRIORITY()        (IPR2bits.TMR3IP = 1)
/*This macro will enable low  priority of TIMER3 module*/
#define TIMER3_LOW_PRIORITY()         (IPR2bits.TMR3IP = 0)
#endif
#endif
/************CCP1************/
#if CCP1_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/*Enable CCP1 interrupt*/
#define CCP1_INTERRUPT_ENABLE()      (PIE1bits.CCP1IE = 1)
/*Disable CCP1 interrupt*/
#define CCP1_INTERRUPT_DISABLE()     (PIE1bits.CCP1IE= 0)
/*Clear flag of CCP1 interrupt*/
#define CCP1_INTERRUPT_CLEAR_FLAG()  (PIR1bits.CCP1IF = 0)
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This macro will enable high  priority of CCP1 module*/
#define CCP1_HIGH_PRIORITY()        (IPR1bits.CCP1IP = 1)
/*This macro will enable low  priority of CCP1 module*/
#define CCP1_LOW_PRIORITY()         (IPR1bits.CCP1IP = 0)
#endif
#endif
/************CCP2************/
#if CCP2_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/*Enable CCP2 interrupt*/
#define CCP2_INTERRUPT_ENABLE()      (PIE2bits.CCP2IE = 1)
/*Disable CCP2 interrupt*/
#define CCP2_INTERRUPT_DISABLE()     (PIE2bits.CCP2IE= 0)
/*Clear flag of CCP2 interrupt*/
#define CCP2_INTERRUPT_CLEAR_FLAG()  (PIR2bits.CCP2IF = 0)
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This macro will enable high  priority of CCP2 module*/
#define CCP2_HIGH_PRIORITY()        (IPR2bits.CCP2IP = 1)
/*This macro will enable low  priority of CCP2 module*/
#define CCP2_LOW_PRIORITY()         (IPR2bits.CCP2IP = 0)
#endif
#endif
/************EUSART_TX************/
#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/*Enable EUSART_TX interrupt*/
#define EUSART_TX_INTERRUPT_ENABLE()      (PIE1bits.TXIE = 1)
/*Disable EUSART_TX interrupt*/
#define EUSART_TX_INTERRUPT_DISABLE()     (PIE1bits.TXIE= 0)
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This macro will enable high  priority of EUSART_TX module*/
#define EUSART_TX_HIGH_PRIORITY()        (IPR1bits.TXIP = 1)
/*This macro will enable low  priority of EUSART_TX module*/
#define EUSART_TX_LOW_PRIORITY()         (IPR1bits.TXIP = 0)
#endif
#endif
/************EUSART_RX************/
#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/*Enable EUSART_RX interrupt*/
#define EUSART_RX_INTERRUPT_ENABLE()      (PIE1bits.RCIE = 1)
/*Disable EUSART_RX interrupt*/
#define EUSART_RX_INTERRUPT_DISABLE()     (PIE1bits.RCIE= 0)
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This macro will enable high  priority of EUSART_RX module*/
#define EUSART_RX_HIGH_PRIORITY()        (IPR1bits.RCIP = 1)
/*This macro will enable low  priority of EUSART_RX module*/
#define EUSART_RX_LOW_PRIORITY()         (IPR1bits.RCIP = 0)
#endif
#endif
/************I2C************/
#if I2C_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
/*Enable I2C interrupt*/
#define MSSP_I2C_INTERRUPT_ENABLE()               (PIE1bits.SSPIE = 1)
/*Disable I2C interrupt*/
#define MSSP_I2C_INTERRUPT_DISABLE()              (PIE1bits.SSPIE= 0)
/*Clear flag of I2C interrupt*/
#define MSSP_I2C_INTERRUPT_CLEAR_FLAG()           (PIR1bits.SSPIF = 0)
/*Enable Bus Collision interrupt*/
#define MSSP_BUS_COLLISION_INTERRUPT_ENABLE()     (PIE2bits.BCLIE = 1)
/*Disable Bus Collision interrupt*/
#define MSSP_BUS_COLLISION_INTERRUPT_DISABLE()    (PIE2bits.BCLIE = 0)
/*Clear flag of Bus Collision interrupt*/
#define MSSP_BUS_COLLISION_INTERRUPT_CLEAR_FLAG() (PIR2bits.BCLIF = 0)
#if INTERRUPT_PRIORITY_LEVEL_ENABLE == INTERRUPT_FEATURE_ENABLE
/*This macro will enable high  priority of I2C module*/
#define MSSP_I2C_HIGH_PRIORITY()               (IPR1bits.SSPIP = 1)
/*This macro will enable low  priority of I2C module*/
#define MSSP_I2C_LOW_PRIORITY()                (IPR1bits.SSPIP = 0)
/*This macro will enable high  priority of Bus Collision module*/
#define MSSP_BUS_COLLISION_HIGH_PRIORITY()     (IPR2bits.BCLIP = 1)
/*This macro will enable low  priority of Bus Collision module*/
#define MSSP_BUS_COLLISION_LOW_PRIORITY()      (IPR2bits.BCLIP = 0)
#endif
#endif
/*Section : Macro Declaration*/


/*Section : Data Type Declaration*/


/*Section : Function Declaration*/


#endif	/* INTERNAL_INTERRUPT_H */

