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

#include "control.h"

/**
  * @brief Inits L9110's operation, in the direction specified (0/1)
  * @param  int Direction
  * @retval None
  */
void InitOperation(int direction)
{
  int i;
  
  // Reset finish signal
  GPIO_WriteLow(REQ_FINISHED_PORT, REQ_FINISHED_PIN);
  
  // Reset counters
  for (i = 0; i < 3; i++) {
    ADCZeroDraw[i] = 0;
    ADCAboveThreshDraw[i] = 0;
  }
  
  if (direction) {
    // U3
    GPIO_WriteHigh(L9110_U3_PORT, L9110_U3_IA);
    GPIO_WriteLow(L9110_U3_PORT, L9110_U3_IB);
    
    // U4
    GPIO_WriteHigh(L9110_U4_PORT, L9110_U4_IA);
    GPIO_WriteLow(L9110_U4_PORT, L9110_U4_IB);
    
    // U5
    GPIO_WriteHigh(L9110_U5_PORT, L9110_U5_IA);
    GPIO_WriteLow(L9110_U5_PORT, L9110_U5_IB);
  } else {
    // U3
    GPIO_WriteLow(L9110_U3_PORT, L9110_U3_IA);
    GPIO_WriteHigh(L9110_U3_PORT, L9110_U3_IB);
    
    // U4
    GPIO_WriteLow(L9110_U4_PORT, L9110_U4_IA);
    GPIO_WriteHigh(L9110_U4_PORT, L9110_U4_IB);
    
    // U5
    GPIO_WriteLow(L9110_U5_PORT, L9110_U5_IA);
    GPIO_WriteHigh(L9110_U5_PORT, L9110_U5_IB);
  }
  
  WorkStatus = L9110_WORKING_STATUS_U3 | L9110_WORKING_STATUS_U4 | L9110_WORKING_STATUS_U5;
}

/**
  * @brief Commands L9110 to cut off power to motors
  * @param  GPIO_TypeDef* GPIO Port
  * @param  GPIO_Pin_TypeDef GPIO Pins
  * @param  int Work status position
  * @retval None
  */
void CutOperation(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins)
{
  GPIO_WriteLow(GPIOx, PortPins);
}

/*
    Configure ADC1 Continuous Conversion with End Of Conversion interrupt enabled .
  */
void InitADC()
{
  /* De-Init ADC1 peripheral */
  ADC1_DeInit();
    
  /* Enable EOC interrupt */
  ADC1_ITConfig(ADC1_IT_EOCIE, ENABLE);
    
  /* Enable conversion data buffering */
  ADC1_DataBufferCmd(ENABLE);
    
  /* Enable scan mode conversion */
  ADC1_ScanModeCmd(ENABLE);

  /* Init ADC1 peripheral */
  /* ADC1 Channel 3 */
  ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS, REF_2V5_ANALOG, ADC1_PRESSEL_FCPU_D4, \
            ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL3,\
            DISABLE);
                        
  /* ADC1 Channel 4 */
  ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS, L9110_U3_DRAW, ADC1_PRESSEL_FCPU_D4, \
            ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL4,\
            DISABLE);
                        
  /* ADC1 Channel 5 */
  ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS, L9110_U4_DRAW, ADC1_PRESSEL_FCPU_D4, \
            ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL5,\
            DISABLE);
                        
  /* ADC1 Channel 6 */
  ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS, L9110_U5_DRAW, ADC1_PRESSEL_FCPU_D4, \
            ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL6,\
            DISABLE);
  
  ADC1_Cmd(ENABLE);
}

/*
    Configure TIM2 to interrupt every 10ms
  */
void InitTimer()
{
  TIM2_DeInit();
  TIM2_TimeBaseInit(TIM2_PRESCALER_32768,      // Interrupt every 32768 clock pulses.
                    5);                        // 16Mhz / 32768 = 488 -> every 2ms -> ARR=5 -> every 10ms
  TIM2_ITConfig(TIM2_IT_UPDATE, ENABLE);
  TIM2_Cmd(ENABLE);
}

/*
    Handles voltage readings from ADC, reacts to thresholds defined in globals.
  */
void HandleVoltage(int Array_Index, int WorkStatus_Bit, GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins)
{
  bool continue_operation = TRUE;

  /* Check if L9110 should still be working */
  if ((WorkStatus & WorkStatus_Bit) != 0x00) {
    /* Check for zero draw */
    if (ADCReadings[Array_Index + 1] == 0x00) {
      ADCZeroDraw[Array_Index]++;

      // Voltage is zero, reset the above v. threshold counter
      ADCAboveThreshDraw[Array_Index] = 0;
    }
    
    /* Inspect values against zero threshold */
    if (ADCZeroDraw[Array_Index] > L9110_ZERO_DRAW_THRESH) {
      continue_operation = FALSE;
    }

    /* Inspect values against voltage threshold */
    if (ADCReadings[Array_Index + 1] >= L9110_CUTOFF_VOLTAGE) {
      if (ADCAboveThreshDraw[Array_Index] > L9110_ABOVE_THRESH_DRAW) {
        continue_operation = FALSE;
      } else {
        ADCAboveThreshDraw[Array_Index]++;
      }
    }

    /* Check if we got a conclusion to turn off L9110 */
    if (!continue_operation) {
      // Cut off U3 voltage and set finish flag
      CutOperation(GPIOx, PortPins);
      WorkStatus = WorkStatus ^ WorkStatus_Bit;
    }
  }
}