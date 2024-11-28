#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Smart_home_masterMCU.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/Smart_home_masterMCU.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=ECU_Layer/7_segment/ecu_seven_seg.c ECU_Layer/button/ecu_button.c ECU_Layer/chr_lcd/chr_lcd.c ECU_Layer/EEPROM_24C02C/EEPROM_24C02C.c ECU_Layer/keypad/ecu_keypad.c ECU_Layer/LED/ecu_led.c ECU_Layer/motor/ecu_motor.c ECU_Layer/RealTimeDS1307/RealTimeDS1307.c ECU_Layer/relay/ecu_relay.c ECU_Layer/TempSensor_TC74/TempSensor_TC74.c ECU_Layer/UARTLoggingDebugData/UART_LoggingDebugData.c ECU_Layer/ecu_layer_init.c MCAL_Layer/ADC/hal_adc.c MCAL_Layer/CCP/hal_ccp.c MCAL_Layer/eeprom/hal_eeprom.c MCAL_Layer/eusart/hal_eusart.c MCAL_Layer/GPIO/hal_gpio.c MCAL_Layer/I2C/hal_i2c.c MCAL_Layer/interrupt/external_interrupt.c MCAL_Layer/interrupt/interrupt_manager.c MCAL_Layer/interrupt/internal_interrupt.c MCAL_Layer/Timers/hal_timer0.c MCAL_Layer/Timers/hal_timer1.c MCAL_Layer/Timers/hal_timer2.c MCAL_Layer/Timers/hal_timer3.c MCAL_Layer/device_config.c application.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/ECU_Layer/7_segment/ecu_seven_seg.p1 ${OBJECTDIR}/ECU_Layer/button/ecu_button.p1 ${OBJECTDIR}/ECU_Layer/chr_lcd/chr_lcd.p1 ${OBJECTDIR}/ECU_Layer/EEPROM_24C02C/EEPROM_24C02C.p1 ${OBJECTDIR}/ECU_Layer/keypad/ecu_keypad.p1 ${OBJECTDIR}/ECU_Layer/LED/ecu_led.p1 ${OBJECTDIR}/ECU_Layer/motor/ecu_motor.p1 ${OBJECTDIR}/ECU_Layer/RealTimeDS1307/RealTimeDS1307.p1 ${OBJECTDIR}/ECU_Layer/relay/ecu_relay.p1 ${OBJECTDIR}/ECU_Layer/TempSensor_TC74/TempSensor_TC74.p1 ${OBJECTDIR}/ECU_Layer/UARTLoggingDebugData/UART_LoggingDebugData.p1 ${OBJECTDIR}/ECU_Layer/ecu_layer_init.p1 ${OBJECTDIR}/MCAL_Layer/ADC/hal_adc.p1 ${OBJECTDIR}/MCAL_Layer/CCP/hal_ccp.p1 ${OBJECTDIR}/MCAL_Layer/eeprom/hal_eeprom.p1 ${OBJECTDIR}/MCAL_Layer/eusart/hal_eusart.p1 ${OBJECTDIR}/MCAL_Layer/GPIO/hal_gpio.p1 ${OBJECTDIR}/MCAL_Layer/I2C/hal_i2c.p1 ${OBJECTDIR}/MCAL_Layer/interrupt/external_interrupt.p1 ${OBJECTDIR}/MCAL_Layer/interrupt/interrupt_manager.p1 ${OBJECTDIR}/MCAL_Layer/interrupt/internal_interrupt.p1 ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer0.p1 ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer1.p1 ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer2.p1 ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer3.p1 ${OBJECTDIR}/MCAL_Layer/device_config.p1 ${OBJECTDIR}/application.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/ECU_Layer/7_segment/ecu_seven_seg.p1.d ${OBJECTDIR}/ECU_Layer/button/ecu_button.p1.d ${OBJECTDIR}/ECU_Layer/chr_lcd/chr_lcd.p1.d ${OBJECTDIR}/ECU_Layer/EEPROM_24C02C/EEPROM_24C02C.p1.d ${OBJECTDIR}/ECU_Layer/keypad/ecu_keypad.p1.d ${OBJECTDIR}/ECU_Layer/LED/ecu_led.p1.d ${OBJECTDIR}/ECU_Layer/motor/ecu_motor.p1.d ${OBJECTDIR}/ECU_Layer/RealTimeDS1307/RealTimeDS1307.p1.d ${OBJECTDIR}/ECU_Layer/relay/ecu_relay.p1.d ${OBJECTDIR}/ECU_Layer/TempSensor_TC74/TempSensor_TC74.p1.d ${OBJECTDIR}/ECU_Layer/UARTLoggingDebugData/UART_LoggingDebugData.p1.d ${OBJECTDIR}/ECU_Layer/ecu_layer_init.p1.d ${OBJECTDIR}/MCAL_Layer/ADC/hal_adc.p1.d ${OBJECTDIR}/MCAL_Layer/CCP/hal_ccp.p1.d ${OBJECTDIR}/MCAL_Layer/eeprom/hal_eeprom.p1.d ${OBJECTDIR}/MCAL_Layer/eusart/hal_eusart.p1.d ${OBJECTDIR}/MCAL_Layer/GPIO/hal_gpio.p1.d ${OBJECTDIR}/MCAL_Layer/I2C/hal_i2c.p1.d ${OBJECTDIR}/MCAL_Layer/interrupt/external_interrupt.p1.d ${OBJECTDIR}/MCAL_Layer/interrupt/interrupt_manager.p1.d ${OBJECTDIR}/MCAL_Layer/interrupt/internal_interrupt.p1.d ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer0.p1.d ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer1.p1.d ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer2.p1.d ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer3.p1.d ${OBJECTDIR}/MCAL_Layer/device_config.p1.d ${OBJECTDIR}/application.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/ECU_Layer/7_segment/ecu_seven_seg.p1 ${OBJECTDIR}/ECU_Layer/button/ecu_button.p1 ${OBJECTDIR}/ECU_Layer/chr_lcd/chr_lcd.p1 ${OBJECTDIR}/ECU_Layer/EEPROM_24C02C/EEPROM_24C02C.p1 ${OBJECTDIR}/ECU_Layer/keypad/ecu_keypad.p1 ${OBJECTDIR}/ECU_Layer/LED/ecu_led.p1 ${OBJECTDIR}/ECU_Layer/motor/ecu_motor.p1 ${OBJECTDIR}/ECU_Layer/RealTimeDS1307/RealTimeDS1307.p1 ${OBJECTDIR}/ECU_Layer/relay/ecu_relay.p1 ${OBJECTDIR}/ECU_Layer/TempSensor_TC74/TempSensor_TC74.p1 ${OBJECTDIR}/ECU_Layer/UARTLoggingDebugData/UART_LoggingDebugData.p1 ${OBJECTDIR}/ECU_Layer/ecu_layer_init.p1 ${OBJECTDIR}/MCAL_Layer/ADC/hal_adc.p1 ${OBJECTDIR}/MCAL_Layer/CCP/hal_ccp.p1 ${OBJECTDIR}/MCAL_Layer/eeprom/hal_eeprom.p1 ${OBJECTDIR}/MCAL_Layer/eusart/hal_eusart.p1 ${OBJECTDIR}/MCAL_Layer/GPIO/hal_gpio.p1 ${OBJECTDIR}/MCAL_Layer/I2C/hal_i2c.p1 ${OBJECTDIR}/MCAL_Layer/interrupt/external_interrupt.p1 ${OBJECTDIR}/MCAL_Layer/interrupt/interrupt_manager.p1 ${OBJECTDIR}/MCAL_Layer/interrupt/internal_interrupt.p1 ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer0.p1 ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer1.p1 ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer2.p1 ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer3.p1 ${OBJECTDIR}/MCAL_Layer/device_config.p1 ${OBJECTDIR}/application.p1

# Source Files
SOURCEFILES=ECU_Layer/7_segment/ecu_seven_seg.c ECU_Layer/button/ecu_button.c ECU_Layer/chr_lcd/chr_lcd.c ECU_Layer/EEPROM_24C02C/EEPROM_24C02C.c ECU_Layer/keypad/ecu_keypad.c ECU_Layer/LED/ecu_led.c ECU_Layer/motor/ecu_motor.c ECU_Layer/RealTimeDS1307/RealTimeDS1307.c ECU_Layer/relay/ecu_relay.c ECU_Layer/TempSensor_TC74/TempSensor_TC74.c ECU_Layer/UARTLoggingDebugData/UART_LoggingDebugData.c ECU_Layer/ecu_layer_init.c MCAL_Layer/ADC/hal_adc.c MCAL_Layer/CCP/hal_ccp.c MCAL_Layer/eeprom/hal_eeprom.c MCAL_Layer/eusart/hal_eusart.c MCAL_Layer/GPIO/hal_gpio.c MCAL_Layer/I2C/hal_i2c.c MCAL_Layer/interrupt/external_interrupt.c MCAL_Layer/interrupt/interrupt_manager.c MCAL_Layer/interrupt/internal_interrupt.c MCAL_Layer/Timers/hal_timer0.c MCAL_Layer/Timers/hal_timer1.c MCAL_Layer/Timers/hal_timer2.c MCAL_Layer/Timers/hal_timer3.c MCAL_Layer/device_config.c application.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/Smart_home_masterMCU.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F46K20
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/ECU_Layer/7_segment/ecu_seven_seg.p1: ECU_Layer/7_segment/ecu_seven_seg.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_Layer/7_segment" 
	@${RM} ${OBJECTDIR}/ECU_Layer/7_segment/ecu_seven_seg.p1.d 
	@${RM} ${OBJECTDIR}/ECU_Layer/7_segment/ecu_seven_seg.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_Layer/7_segment/ecu_seven_seg.p1 ECU_Layer/7_segment/ecu_seven_seg.c 
	@-${MV} ${OBJECTDIR}/ECU_Layer/7_segment/ecu_seven_seg.d ${OBJECTDIR}/ECU_Layer/7_segment/ecu_seven_seg.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_Layer/7_segment/ecu_seven_seg.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_Layer/button/ecu_button.p1: ECU_Layer/button/ecu_button.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_Layer/button" 
	@${RM} ${OBJECTDIR}/ECU_Layer/button/ecu_button.p1.d 
	@${RM} ${OBJECTDIR}/ECU_Layer/button/ecu_button.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_Layer/button/ecu_button.p1 ECU_Layer/button/ecu_button.c 
	@-${MV} ${OBJECTDIR}/ECU_Layer/button/ecu_button.d ${OBJECTDIR}/ECU_Layer/button/ecu_button.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_Layer/button/ecu_button.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_Layer/chr_lcd/chr_lcd.p1: ECU_Layer/chr_lcd/chr_lcd.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_Layer/chr_lcd" 
	@${RM} ${OBJECTDIR}/ECU_Layer/chr_lcd/chr_lcd.p1.d 
	@${RM} ${OBJECTDIR}/ECU_Layer/chr_lcd/chr_lcd.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_Layer/chr_lcd/chr_lcd.p1 ECU_Layer/chr_lcd/chr_lcd.c 
	@-${MV} ${OBJECTDIR}/ECU_Layer/chr_lcd/chr_lcd.d ${OBJECTDIR}/ECU_Layer/chr_lcd/chr_lcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_Layer/chr_lcd/chr_lcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_Layer/EEPROM_24C02C/EEPROM_24C02C.p1: ECU_Layer/EEPROM_24C02C/EEPROM_24C02C.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_Layer/EEPROM_24C02C" 
	@${RM} ${OBJECTDIR}/ECU_Layer/EEPROM_24C02C/EEPROM_24C02C.p1.d 
	@${RM} ${OBJECTDIR}/ECU_Layer/EEPROM_24C02C/EEPROM_24C02C.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_Layer/EEPROM_24C02C/EEPROM_24C02C.p1 ECU_Layer/EEPROM_24C02C/EEPROM_24C02C.c 
	@-${MV} ${OBJECTDIR}/ECU_Layer/EEPROM_24C02C/EEPROM_24C02C.d ${OBJECTDIR}/ECU_Layer/EEPROM_24C02C/EEPROM_24C02C.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_Layer/EEPROM_24C02C/EEPROM_24C02C.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_Layer/keypad/ecu_keypad.p1: ECU_Layer/keypad/ecu_keypad.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_Layer/keypad" 
	@${RM} ${OBJECTDIR}/ECU_Layer/keypad/ecu_keypad.p1.d 
	@${RM} ${OBJECTDIR}/ECU_Layer/keypad/ecu_keypad.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_Layer/keypad/ecu_keypad.p1 ECU_Layer/keypad/ecu_keypad.c 
	@-${MV} ${OBJECTDIR}/ECU_Layer/keypad/ecu_keypad.d ${OBJECTDIR}/ECU_Layer/keypad/ecu_keypad.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_Layer/keypad/ecu_keypad.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_Layer/LED/ecu_led.p1: ECU_Layer/LED/ecu_led.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_Layer/LED" 
	@${RM} ${OBJECTDIR}/ECU_Layer/LED/ecu_led.p1.d 
	@${RM} ${OBJECTDIR}/ECU_Layer/LED/ecu_led.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_Layer/LED/ecu_led.p1 ECU_Layer/LED/ecu_led.c 
	@-${MV} ${OBJECTDIR}/ECU_Layer/LED/ecu_led.d ${OBJECTDIR}/ECU_Layer/LED/ecu_led.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_Layer/LED/ecu_led.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_Layer/motor/ecu_motor.p1: ECU_Layer/motor/ecu_motor.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_Layer/motor" 
	@${RM} ${OBJECTDIR}/ECU_Layer/motor/ecu_motor.p1.d 
	@${RM} ${OBJECTDIR}/ECU_Layer/motor/ecu_motor.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_Layer/motor/ecu_motor.p1 ECU_Layer/motor/ecu_motor.c 
	@-${MV} ${OBJECTDIR}/ECU_Layer/motor/ecu_motor.d ${OBJECTDIR}/ECU_Layer/motor/ecu_motor.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_Layer/motor/ecu_motor.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_Layer/RealTimeDS1307/RealTimeDS1307.p1: ECU_Layer/RealTimeDS1307/RealTimeDS1307.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_Layer/RealTimeDS1307" 
	@${RM} ${OBJECTDIR}/ECU_Layer/RealTimeDS1307/RealTimeDS1307.p1.d 
	@${RM} ${OBJECTDIR}/ECU_Layer/RealTimeDS1307/RealTimeDS1307.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_Layer/RealTimeDS1307/RealTimeDS1307.p1 ECU_Layer/RealTimeDS1307/RealTimeDS1307.c 
	@-${MV} ${OBJECTDIR}/ECU_Layer/RealTimeDS1307/RealTimeDS1307.d ${OBJECTDIR}/ECU_Layer/RealTimeDS1307/RealTimeDS1307.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_Layer/RealTimeDS1307/RealTimeDS1307.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_Layer/relay/ecu_relay.p1: ECU_Layer/relay/ecu_relay.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_Layer/relay" 
	@${RM} ${OBJECTDIR}/ECU_Layer/relay/ecu_relay.p1.d 
	@${RM} ${OBJECTDIR}/ECU_Layer/relay/ecu_relay.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_Layer/relay/ecu_relay.p1 ECU_Layer/relay/ecu_relay.c 
	@-${MV} ${OBJECTDIR}/ECU_Layer/relay/ecu_relay.d ${OBJECTDIR}/ECU_Layer/relay/ecu_relay.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_Layer/relay/ecu_relay.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_Layer/TempSensor_TC74/TempSensor_TC74.p1: ECU_Layer/TempSensor_TC74/TempSensor_TC74.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_Layer/TempSensor_TC74" 
	@${RM} ${OBJECTDIR}/ECU_Layer/TempSensor_TC74/TempSensor_TC74.p1.d 
	@${RM} ${OBJECTDIR}/ECU_Layer/TempSensor_TC74/TempSensor_TC74.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_Layer/TempSensor_TC74/TempSensor_TC74.p1 ECU_Layer/TempSensor_TC74/TempSensor_TC74.c 
	@-${MV} ${OBJECTDIR}/ECU_Layer/TempSensor_TC74/TempSensor_TC74.d ${OBJECTDIR}/ECU_Layer/TempSensor_TC74/TempSensor_TC74.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_Layer/TempSensor_TC74/TempSensor_TC74.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_Layer/UARTLoggingDebugData/UART_LoggingDebugData.p1: ECU_Layer/UARTLoggingDebugData/UART_LoggingDebugData.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_Layer/UARTLoggingDebugData" 
	@${RM} ${OBJECTDIR}/ECU_Layer/UARTLoggingDebugData/UART_LoggingDebugData.p1.d 
	@${RM} ${OBJECTDIR}/ECU_Layer/UARTLoggingDebugData/UART_LoggingDebugData.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_Layer/UARTLoggingDebugData/UART_LoggingDebugData.p1 ECU_Layer/UARTLoggingDebugData/UART_LoggingDebugData.c 
	@-${MV} ${OBJECTDIR}/ECU_Layer/UARTLoggingDebugData/UART_LoggingDebugData.d ${OBJECTDIR}/ECU_Layer/UARTLoggingDebugData/UART_LoggingDebugData.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_Layer/UARTLoggingDebugData/UART_LoggingDebugData.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_Layer/ecu_layer_init.p1: ECU_Layer/ecu_layer_init.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_Layer" 
	@${RM} ${OBJECTDIR}/ECU_Layer/ecu_layer_init.p1.d 
	@${RM} ${OBJECTDIR}/ECU_Layer/ecu_layer_init.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_Layer/ecu_layer_init.p1 ECU_Layer/ecu_layer_init.c 
	@-${MV} ${OBJECTDIR}/ECU_Layer/ecu_layer_init.d ${OBJECTDIR}/ECU_Layer/ecu_layer_init.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_Layer/ecu_layer_init.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_Layer/ADC/hal_adc.p1: MCAL_Layer/ADC/hal_adc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/ADC" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/ADC/hal_adc.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/ADC/hal_adc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_Layer/ADC/hal_adc.p1 MCAL_Layer/ADC/hal_adc.c 
	@-${MV} ${OBJECTDIR}/MCAL_Layer/ADC/hal_adc.d ${OBJECTDIR}/MCAL_Layer/ADC/hal_adc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_Layer/ADC/hal_adc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_Layer/CCP/hal_ccp.p1: MCAL_Layer/CCP/hal_ccp.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/CCP" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/CCP/hal_ccp.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/CCP/hal_ccp.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_Layer/CCP/hal_ccp.p1 MCAL_Layer/CCP/hal_ccp.c 
	@-${MV} ${OBJECTDIR}/MCAL_Layer/CCP/hal_ccp.d ${OBJECTDIR}/MCAL_Layer/CCP/hal_ccp.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_Layer/CCP/hal_ccp.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_Layer/eeprom/hal_eeprom.p1: MCAL_Layer/eeprom/hal_eeprom.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/eeprom" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/eeprom/hal_eeprom.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/eeprom/hal_eeprom.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_Layer/eeprom/hal_eeprom.p1 MCAL_Layer/eeprom/hal_eeprom.c 
	@-${MV} ${OBJECTDIR}/MCAL_Layer/eeprom/hal_eeprom.d ${OBJECTDIR}/MCAL_Layer/eeprom/hal_eeprom.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_Layer/eeprom/hal_eeprom.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_Layer/eusart/hal_eusart.p1: MCAL_Layer/eusart/hal_eusart.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/eusart" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/eusart/hal_eusart.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/eusart/hal_eusart.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_Layer/eusart/hal_eusart.p1 MCAL_Layer/eusart/hal_eusart.c 
	@-${MV} ${OBJECTDIR}/MCAL_Layer/eusart/hal_eusart.d ${OBJECTDIR}/MCAL_Layer/eusart/hal_eusart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_Layer/eusart/hal_eusart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_Layer/GPIO/hal_gpio.p1: MCAL_Layer/GPIO/hal_gpio.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/GPIO" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/GPIO/hal_gpio.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/GPIO/hal_gpio.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_Layer/GPIO/hal_gpio.p1 MCAL_Layer/GPIO/hal_gpio.c 
	@-${MV} ${OBJECTDIR}/MCAL_Layer/GPIO/hal_gpio.d ${OBJECTDIR}/MCAL_Layer/GPIO/hal_gpio.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_Layer/GPIO/hal_gpio.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_Layer/I2C/hal_i2c.p1: MCAL_Layer/I2C/hal_i2c.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/I2C" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/I2C/hal_i2c.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/I2C/hal_i2c.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_Layer/I2C/hal_i2c.p1 MCAL_Layer/I2C/hal_i2c.c 
	@-${MV} ${OBJECTDIR}/MCAL_Layer/I2C/hal_i2c.d ${OBJECTDIR}/MCAL_Layer/I2C/hal_i2c.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_Layer/I2C/hal_i2c.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_Layer/interrupt/external_interrupt.p1: MCAL_Layer/interrupt/external_interrupt.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/interrupt" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/interrupt/external_interrupt.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/interrupt/external_interrupt.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_Layer/interrupt/external_interrupt.p1 MCAL_Layer/interrupt/external_interrupt.c 
	@-${MV} ${OBJECTDIR}/MCAL_Layer/interrupt/external_interrupt.d ${OBJECTDIR}/MCAL_Layer/interrupt/external_interrupt.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_Layer/interrupt/external_interrupt.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_Layer/interrupt/interrupt_manager.p1: MCAL_Layer/interrupt/interrupt_manager.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/interrupt" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/interrupt/interrupt_manager.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/interrupt/interrupt_manager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_Layer/interrupt/interrupt_manager.p1 MCAL_Layer/interrupt/interrupt_manager.c 
	@-${MV} ${OBJECTDIR}/MCAL_Layer/interrupt/interrupt_manager.d ${OBJECTDIR}/MCAL_Layer/interrupt/interrupt_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_Layer/interrupt/interrupt_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_Layer/interrupt/internal_interrupt.p1: MCAL_Layer/interrupt/internal_interrupt.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/interrupt" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/interrupt/internal_interrupt.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/interrupt/internal_interrupt.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_Layer/interrupt/internal_interrupt.p1 MCAL_Layer/interrupt/internal_interrupt.c 
	@-${MV} ${OBJECTDIR}/MCAL_Layer/interrupt/internal_interrupt.d ${OBJECTDIR}/MCAL_Layer/interrupt/internal_interrupt.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_Layer/interrupt/internal_interrupt.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_Layer/Timers/hal_timer0.p1: MCAL_Layer/Timers/hal_timer0.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/Timers" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer0.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer0.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer0.p1 MCAL_Layer/Timers/hal_timer0.c 
	@-${MV} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer0.d ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer0.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer0.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_Layer/Timers/hal_timer1.p1: MCAL_Layer/Timers/hal_timer1.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/Timers" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer1.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer1.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer1.p1 MCAL_Layer/Timers/hal_timer1.c 
	@-${MV} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer1.d ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_Layer/Timers/hal_timer2.p1: MCAL_Layer/Timers/hal_timer2.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/Timers" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer2.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer2.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer2.p1 MCAL_Layer/Timers/hal_timer2.c 
	@-${MV} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer2.d ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_Layer/Timers/hal_timer3.p1: MCAL_Layer/Timers/hal_timer3.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/Timers" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer3.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer3.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer3.p1 MCAL_Layer/Timers/hal_timer3.c 
	@-${MV} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer3.d ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer3.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer3.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_Layer/device_config.p1: MCAL_Layer/device_config.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/device_config.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/device_config.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_Layer/device_config.p1 MCAL_Layer/device_config.c 
	@-${MV} ${OBJECTDIR}/MCAL_Layer/device_config.d ${OBJECTDIR}/MCAL_Layer/device_config.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_Layer/device_config.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/application.p1: application.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/application.p1.d 
	@${RM} ${OBJECTDIR}/application.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1  -mdebugger=none   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/application.p1 application.c 
	@-${MV} ${OBJECTDIR}/application.d ${OBJECTDIR}/application.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/application.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/ECU_Layer/7_segment/ecu_seven_seg.p1: ECU_Layer/7_segment/ecu_seven_seg.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_Layer/7_segment" 
	@${RM} ${OBJECTDIR}/ECU_Layer/7_segment/ecu_seven_seg.p1.d 
	@${RM} ${OBJECTDIR}/ECU_Layer/7_segment/ecu_seven_seg.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_Layer/7_segment/ecu_seven_seg.p1 ECU_Layer/7_segment/ecu_seven_seg.c 
	@-${MV} ${OBJECTDIR}/ECU_Layer/7_segment/ecu_seven_seg.d ${OBJECTDIR}/ECU_Layer/7_segment/ecu_seven_seg.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_Layer/7_segment/ecu_seven_seg.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_Layer/button/ecu_button.p1: ECU_Layer/button/ecu_button.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_Layer/button" 
	@${RM} ${OBJECTDIR}/ECU_Layer/button/ecu_button.p1.d 
	@${RM} ${OBJECTDIR}/ECU_Layer/button/ecu_button.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_Layer/button/ecu_button.p1 ECU_Layer/button/ecu_button.c 
	@-${MV} ${OBJECTDIR}/ECU_Layer/button/ecu_button.d ${OBJECTDIR}/ECU_Layer/button/ecu_button.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_Layer/button/ecu_button.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_Layer/chr_lcd/chr_lcd.p1: ECU_Layer/chr_lcd/chr_lcd.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_Layer/chr_lcd" 
	@${RM} ${OBJECTDIR}/ECU_Layer/chr_lcd/chr_lcd.p1.d 
	@${RM} ${OBJECTDIR}/ECU_Layer/chr_lcd/chr_lcd.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_Layer/chr_lcd/chr_lcd.p1 ECU_Layer/chr_lcd/chr_lcd.c 
	@-${MV} ${OBJECTDIR}/ECU_Layer/chr_lcd/chr_lcd.d ${OBJECTDIR}/ECU_Layer/chr_lcd/chr_lcd.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_Layer/chr_lcd/chr_lcd.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_Layer/EEPROM_24C02C/EEPROM_24C02C.p1: ECU_Layer/EEPROM_24C02C/EEPROM_24C02C.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_Layer/EEPROM_24C02C" 
	@${RM} ${OBJECTDIR}/ECU_Layer/EEPROM_24C02C/EEPROM_24C02C.p1.d 
	@${RM} ${OBJECTDIR}/ECU_Layer/EEPROM_24C02C/EEPROM_24C02C.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_Layer/EEPROM_24C02C/EEPROM_24C02C.p1 ECU_Layer/EEPROM_24C02C/EEPROM_24C02C.c 
	@-${MV} ${OBJECTDIR}/ECU_Layer/EEPROM_24C02C/EEPROM_24C02C.d ${OBJECTDIR}/ECU_Layer/EEPROM_24C02C/EEPROM_24C02C.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_Layer/EEPROM_24C02C/EEPROM_24C02C.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_Layer/keypad/ecu_keypad.p1: ECU_Layer/keypad/ecu_keypad.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_Layer/keypad" 
	@${RM} ${OBJECTDIR}/ECU_Layer/keypad/ecu_keypad.p1.d 
	@${RM} ${OBJECTDIR}/ECU_Layer/keypad/ecu_keypad.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_Layer/keypad/ecu_keypad.p1 ECU_Layer/keypad/ecu_keypad.c 
	@-${MV} ${OBJECTDIR}/ECU_Layer/keypad/ecu_keypad.d ${OBJECTDIR}/ECU_Layer/keypad/ecu_keypad.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_Layer/keypad/ecu_keypad.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_Layer/LED/ecu_led.p1: ECU_Layer/LED/ecu_led.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_Layer/LED" 
	@${RM} ${OBJECTDIR}/ECU_Layer/LED/ecu_led.p1.d 
	@${RM} ${OBJECTDIR}/ECU_Layer/LED/ecu_led.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_Layer/LED/ecu_led.p1 ECU_Layer/LED/ecu_led.c 
	@-${MV} ${OBJECTDIR}/ECU_Layer/LED/ecu_led.d ${OBJECTDIR}/ECU_Layer/LED/ecu_led.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_Layer/LED/ecu_led.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_Layer/motor/ecu_motor.p1: ECU_Layer/motor/ecu_motor.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_Layer/motor" 
	@${RM} ${OBJECTDIR}/ECU_Layer/motor/ecu_motor.p1.d 
	@${RM} ${OBJECTDIR}/ECU_Layer/motor/ecu_motor.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_Layer/motor/ecu_motor.p1 ECU_Layer/motor/ecu_motor.c 
	@-${MV} ${OBJECTDIR}/ECU_Layer/motor/ecu_motor.d ${OBJECTDIR}/ECU_Layer/motor/ecu_motor.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_Layer/motor/ecu_motor.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_Layer/RealTimeDS1307/RealTimeDS1307.p1: ECU_Layer/RealTimeDS1307/RealTimeDS1307.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_Layer/RealTimeDS1307" 
	@${RM} ${OBJECTDIR}/ECU_Layer/RealTimeDS1307/RealTimeDS1307.p1.d 
	@${RM} ${OBJECTDIR}/ECU_Layer/RealTimeDS1307/RealTimeDS1307.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_Layer/RealTimeDS1307/RealTimeDS1307.p1 ECU_Layer/RealTimeDS1307/RealTimeDS1307.c 
	@-${MV} ${OBJECTDIR}/ECU_Layer/RealTimeDS1307/RealTimeDS1307.d ${OBJECTDIR}/ECU_Layer/RealTimeDS1307/RealTimeDS1307.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_Layer/RealTimeDS1307/RealTimeDS1307.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_Layer/relay/ecu_relay.p1: ECU_Layer/relay/ecu_relay.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_Layer/relay" 
	@${RM} ${OBJECTDIR}/ECU_Layer/relay/ecu_relay.p1.d 
	@${RM} ${OBJECTDIR}/ECU_Layer/relay/ecu_relay.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_Layer/relay/ecu_relay.p1 ECU_Layer/relay/ecu_relay.c 
	@-${MV} ${OBJECTDIR}/ECU_Layer/relay/ecu_relay.d ${OBJECTDIR}/ECU_Layer/relay/ecu_relay.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_Layer/relay/ecu_relay.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_Layer/TempSensor_TC74/TempSensor_TC74.p1: ECU_Layer/TempSensor_TC74/TempSensor_TC74.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_Layer/TempSensor_TC74" 
	@${RM} ${OBJECTDIR}/ECU_Layer/TempSensor_TC74/TempSensor_TC74.p1.d 
	@${RM} ${OBJECTDIR}/ECU_Layer/TempSensor_TC74/TempSensor_TC74.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_Layer/TempSensor_TC74/TempSensor_TC74.p1 ECU_Layer/TempSensor_TC74/TempSensor_TC74.c 
	@-${MV} ${OBJECTDIR}/ECU_Layer/TempSensor_TC74/TempSensor_TC74.d ${OBJECTDIR}/ECU_Layer/TempSensor_TC74/TempSensor_TC74.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_Layer/TempSensor_TC74/TempSensor_TC74.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_Layer/UARTLoggingDebugData/UART_LoggingDebugData.p1: ECU_Layer/UARTLoggingDebugData/UART_LoggingDebugData.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_Layer/UARTLoggingDebugData" 
	@${RM} ${OBJECTDIR}/ECU_Layer/UARTLoggingDebugData/UART_LoggingDebugData.p1.d 
	@${RM} ${OBJECTDIR}/ECU_Layer/UARTLoggingDebugData/UART_LoggingDebugData.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_Layer/UARTLoggingDebugData/UART_LoggingDebugData.p1 ECU_Layer/UARTLoggingDebugData/UART_LoggingDebugData.c 
	@-${MV} ${OBJECTDIR}/ECU_Layer/UARTLoggingDebugData/UART_LoggingDebugData.d ${OBJECTDIR}/ECU_Layer/UARTLoggingDebugData/UART_LoggingDebugData.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_Layer/UARTLoggingDebugData/UART_LoggingDebugData.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/ECU_Layer/ecu_layer_init.p1: ECU_Layer/ecu_layer_init.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/ECU_Layer" 
	@${RM} ${OBJECTDIR}/ECU_Layer/ecu_layer_init.p1.d 
	@${RM} ${OBJECTDIR}/ECU_Layer/ecu_layer_init.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/ECU_Layer/ecu_layer_init.p1 ECU_Layer/ecu_layer_init.c 
	@-${MV} ${OBJECTDIR}/ECU_Layer/ecu_layer_init.d ${OBJECTDIR}/ECU_Layer/ecu_layer_init.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/ECU_Layer/ecu_layer_init.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_Layer/ADC/hal_adc.p1: MCAL_Layer/ADC/hal_adc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/ADC" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/ADC/hal_adc.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/ADC/hal_adc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_Layer/ADC/hal_adc.p1 MCAL_Layer/ADC/hal_adc.c 
	@-${MV} ${OBJECTDIR}/MCAL_Layer/ADC/hal_adc.d ${OBJECTDIR}/MCAL_Layer/ADC/hal_adc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_Layer/ADC/hal_adc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_Layer/CCP/hal_ccp.p1: MCAL_Layer/CCP/hal_ccp.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/CCP" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/CCP/hal_ccp.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/CCP/hal_ccp.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_Layer/CCP/hal_ccp.p1 MCAL_Layer/CCP/hal_ccp.c 
	@-${MV} ${OBJECTDIR}/MCAL_Layer/CCP/hal_ccp.d ${OBJECTDIR}/MCAL_Layer/CCP/hal_ccp.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_Layer/CCP/hal_ccp.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_Layer/eeprom/hal_eeprom.p1: MCAL_Layer/eeprom/hal_eeprom.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/eeprom" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/eeprom/hal_eeprom.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/eeprom/hal_eeprom.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_Layer/eeprom/hal_eeprom.p1 MCAL_Layer/eeprom/hal_eeprom.c 
	@-${MV} ${OBJECTDIR}/MCAL_Layer/eeprom/hal_eeprom.d ${OBJECTDIR}/MCAL_Layer/eeprom/hal_eeprom.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_Layer/eeprom/hal_eeprom.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_Layer/eusart/hal_eusart.p1: MCAL_Layer/eusart/hal_eusart.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/eusart" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/eusart/hal_eusart.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/eusart/hal_eusart.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_Layer/eusart/hal_eusart.p1 MCAL_Layer/eusart/hal_eusart.c 
	@-${MV} ${OBJECTDIR}/MCAL_Layer/eusart/hal_eusart.d ${OBJECTDIR}/MCAL_Layer/eusart/hal_eusart.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_Layer/eusart/hal_eusart.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_Layer/GPIO/hal_gpio.p1: MCAL_Layer/GPIO/hal_gpio.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/GPIO" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/GPIO/hal_gpio.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/GPIO/hal_gpio.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_Layer/GPIO/hal_gpio.p1 MCAL_Layer/GPIO/hal_gpio.c 
	@-${MV} ${OBJECTDIR}/MCAL_Layer/GPIO/hal_gpio.d ${OBJECTDIR}/MCAL_Layer/GPIO/hal_gpio.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_Layer/GPIO/hal_gpio.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_Layer/I2C/hal_i2c.p1: MCAL_Layer/I2C/hal_i2c.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/I2C" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/I2C/hal_i2c.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/I2C/hal_i2c.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_Layer/I2C/hal_i2c.p1 MCAL_Layer/I2C/hal_i2c.c 
	@-${MV} ${OBJECTDIR}/MCAL_Layer/I2C/hal_i2c.d ${OBJECTDIR}/MCAL_Layer/I2C/hal_i2c.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_Layer/I2C/hal_i2c.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_Layer/interrupt/external_interrupt.p1: MCAL_Layer/interrupt/external_interrupt.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/interrupt" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/interrupt/external_interrupt.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/interrupt/external_interrupt.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_Layer/interrupt/external_interrupt.p1 MCAL_Layer/interrupt/external_interrupt.c 
	@-${MV} ${OBJECTDIR}/MCAL_Layer/interrupt/external_interrupt.d ${OBJECTDIR}/MCAL_Layer/interrupt/external_interrupt.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_Layer/interrupt/external_interrupt.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_Layer/interrupt/interrupt_manager.p1: MCAL_Layer/interrupt/interrupt_manager.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/interrupt" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/interrupt/interrupt_manager.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/interrupt/interrupt_manager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_Layer/interrupt/interrupt_manager.p1 MCAL_Layer/interrupt/interrupt_manager.c 
	@-${MV} ${OBJECTDIR}/MCAL_Layer/interrupt/interrupt_manager.d ${OBJECTDIR}/MCAL_Layer/interrupt/interrupt_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_Layer/interrupt/interrupt_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_Layer/interrupt/internal_interrupt.p1: MCAL_Layer/interrupt/internal_interrupt.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/interrupt" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/interrupt/internal_interrupt.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/interrupt/internal_interrupt.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_Layer/interrupt/internal_interrupt.p1 MCAL_Layer/interrupt/internal_interrupt.c 
	@-${MV} ${OBJECTDIR}/MCAL_Layer/interrupt/internal_interrupt.d ${OBJECTDIR}/MCAL_Layer/interrupt/internal_interrupt.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_Layer/interrupt/internal_interrupt.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_Layer/Timers/hal_timer0.p1: MCAL_Layer/Timers/hal_timer0.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/Timers" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer0.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer0.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer0.p1 MCAL_Layer/Timers/hal_timer0.c 
	@-${MV} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer0.d ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer0.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer0.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_Layer/Timers/hal_timer1.p1: MCAL_Layer/Timers/hal_timer1.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/Timers" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer1.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer1.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer1.p1 MCAL_Layer/Timers/hal_timer1.c 
	@-${MV} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer1.d ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_Layer/Timers/hal_timer2.p1: MCAL_Layer/Timers/hal_timer2.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/Timers" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer2.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer2.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer2.p1 MCAL_Layer/Timers/hal_timer2.c 
	@-${MV} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer2.d ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_Layer/Timers/hal_timer3.p1: MCAL_Layer/Timers/hal_timer3.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer/Timers" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer3.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer3.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer3.p1 MCAL_Layer/Timers/hal_timer3.c 
	@-${MV} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer3.d ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer3.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_Layer/Timers/hal_timer3.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/MCAL_Layer/device_config.p1: MCAL_Layer/device_config.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/MCAL_Layer" 
	@${RM} ${OBJECTDIR}/MCAL_Layer/device_config.p1.d 
	@${RM} ${OBJECTDIR}/MCAL_Layer/device_config.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/MCAL_Layer/device_config.p1 MCAL_Layer/device_config.c 
	@-${MV} ${OBJECTDIR}/MCAL_Layer/device_config.d ${OBJECTDIR}/MCAL_Layer/device_config.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/MCAL_Layer/device_config.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/application.p1: application.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/application.p1.d 
	@${RM} ${OBJECTDIR}/application.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits $(COMPARISON_BUILD)  -std=c99 -gcoff -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/application.p1 application.c 
	@-${MV} ${OBJECTDIR}/application.d ${OBJECTDIR}/application.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/application.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/Smart_home_masterMCU.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/Smart_home_masterMCU.${IMAGE_TYPE}.map  -D__DEBUG=1  -mdebugger=none  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits -std=c99 -gcoff -mstack=compiled:auto:auto:auto        $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/Smart_home_masterMCU.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} ${DISTDIR}/Smart_home_masterMCU.${IMAGE_TYPE}.hex 
	
	
else
${DISTDIR}/Smart_home_masterMCU.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/Smart_home_masterMCU.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -mwarn=-3 -Wa,-a -msummary=-psect,-class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mno-default-config-bits -std=c99 -gcoff -mstack=compiled:auto:auto:auto     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/Smart_home_masterMCU.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
