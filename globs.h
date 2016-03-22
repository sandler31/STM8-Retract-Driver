/**
 *  STM8 Retract Driver
 *  Author: Michael Sandler
 *   Email: mich at <FAMILYNAME> dot in
 *     Web: http://sandler.in/
 * License: GPL
 *
 * Copyright 2016 by Michael Sandler
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GLOBS_H__
#define __GLOBS_H__

/* I/O configuration */
/* GPIO Related */
#define RETRACT_SIN_PORT (GPIOC)
#define RETRACT_SIN_PIN (GPIO_PIN_6)
#define EXTEND_SIN_PORT (GPIOB)
#define EXTEND_SIN_PIN (GPIO_PIN_4)
#define REQ_FINISHED_PORT (GPIOB)
#define REQ_FINISHED_PIN (GPIO_PIN_5)
#define L9110_U3_PORT (GPIOC)
#define L9110_U3_IA (GPIO_PIN_7)
#define L9110_U3_IB (GPIO_PIN_5)
#define L9110_U4_PORT (GPIOA)
#define L9110_U4_IA (GPIO_PIN_2)
#define L9110_U4_IB (GPIO_PIN_3)
#define L9110_U5_PORT (GPIOC)
#define L9110_U5_IA (GPIO_PIN_4)
#define L9110_U5_IB (GPIO_PIN_3)

/* ADC Related */
#define REF_2V5_ANALOG (ADC1_CHANNEL_3)
#define L9110_U3_DRAW (ADC1_CHANNEL_4)
#define L9110_U4_DRAW (ADC1_CHANNEL_5)
#define L9110_U5_DRAW (ADC1_CHANNEL_6)


/* Constants */
/* 8 out of 1023 with reference 5.0Vdd is roughly 40mV on the 0.1Ohm measurment resistor
   (meaning 400mA draw, which is ~half of what the L9110 can withstand)
   Retracts themselves are drawing around 300mA while working. (note that they have peak when starting)
*/
#define L9110_CUTOFF_VOLTAGE (uint8_t)0x9           // ADC Level (0-1023)
#define L9110_ZERO_DRAW_THRESH (uint16_t)0xFF       // Timer ticks
#define L9110_ABOVE_THRESH_DRAW (uint16_t)0x40       // Timer ticks
#define L9110_WORKING_STATUS_U3 (uint8_t)0x1
#define L9110_WORKING_STATUS_U4 (uint8_t)0x2
#define L9110_WORKING_STATUS_U5 (uint8_t)0x4


/* Global Variables */
extern volatile uint16_t ADCReadings[4];
extern volatile uint16_t ADCZeroDraw[3];
extern volatile uint16_t ADCAboveThreshDraw[3];
extern volatile unsigned int WorkStatus;

#endif /* __GLOBS_H__ */