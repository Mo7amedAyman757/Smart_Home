/* 
 * File:   interrrupt_manager.h
 * Author: LEGION
 *
 * Created on September 25, 2024, 10:37 PM
 */

#ifndef INTERRRUPT_MANAGER_H
#define	INTERRRUPT_MANAGER_H

/* Section : Includes */
#include "mcal_interrupt.h"

/*Section : Macro Function Declaration*/

/*Section : Macro Declaration*/

/*Section : Data Type Declaration*/

/*Section : Function Declaration*/
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(uint8 source);
void RB5_ISR(uint8 source);
void RB6_ISR(uint8 source);
void RB7_ISR(uint8 source);
void ADC_ISR(void);
void TMR0_ISR(void);
void TMR1_ISR(void);
void TMR2_ISR(void);
void TMR3_ISR(void);
void CCP1_ISR(void);
void CCP2_ISR(void);
void EUSART_TX_ISR(void);
void EUSART_RX_ISR(void);
void MSSP_I2C_ISR(void);
void MSSP_I2C_BC_ISR(void);
#endif	/* INTERRRUPT_MANAGER_H */

