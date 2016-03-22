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

#include "interrupts.h"

/* Define global variables */
volatile uint16_t ADCReadings[4];
volatile uint16_t ADCZeroDraw[3];
volatile uint16_t ADCAboveThreshDraw[3];
volatile unsigned int WorkStatus;

/**
  * @brief External Interrupt PORTB Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI_PORTB_IRQHandler, 4)
{
  if ((GPIO_ReadInputData(EXTEND_SIN_PORT) & EXTEND_SIN_PIN) == EXTEND_SIN_PIN) { // Additional SIN (free cable)
    // Check that we are not in the middle of retracting/extending job
    if (WorkStatus == 0) {
      InitOperation(0);
      
      // Enable ADC to watch the consumption, and TIM2 to cut off when necessary
      InitADC();
      InitTimer();
    }
  }
}

/**
  * @brief External Interrupt PORTC Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI_PORTC_IRQHandler, 5)
{
  if ((GPIO_ReadInputData(RETRACT_SIN_PORT) & RETRACT_SIN_PIN) == RETRACT_SIN_PIN) { // SIN - On board
    // Check that we are not in the middle of retracting/extending job
    if (WorkStatus == 0) {
      InitOperation(1);
      
      // Enable ADC to watch the consumption, and TIM2 to cut off when necessary
      InitADC();
      InitTimer();
    }
  }
}

/**
  * @brief  Timer2 Update/Overflow/Break Interrupt routine
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM2_UPD_OVF_BRK_IRQHandler, 13)
{
  if (TIM2_GetFlagStatus(TIM2_FLAG_UPDATE))
  {
    HandleVoltage(0, L9110_WORKING_STATUS_U3, L9110_U3_PORT, (GPIO_Pin_TypeDef)(L9110_U3_IA | L9110_U3_IB));
    HandleVoltage(1, L9110_WORKING_STATUS_U4, L9110_U4_PORT, (GPIO_Pin_TypeDef)(L9110_U4_IA | L9110_U4_IB));
    HandleVoltage(2, L9110_WORKING_STATUS_U5, L9110_U5_PORT, (GPIO_Pin_TypeDef)(L9110_U5_IA | L9110_U5_IB));

    if (WorkStatus == 0x00) {
      ADC1_Cmd(DISABLE);
      TIM2_Cmd(DISABLE);
      /* Disable EOC and TIM2 interrupts */
      ADC1_ITConfig(ADC1_IT_EOCIE, DISABLE);
      TIM2_ITConfig(TIM2_IT_UPDATE, DISABLE);
      
      // Signal the owner that we finished!
      GPIO_WriteHigh(REQ_FINISHED_PORT, REQ_FINISHED_PIN);
    }

    TIM2_ClearFlag(TIM2_FLAG_UPDATE);
  }
}

/**
* @brief ADC1 interrupt routine.
* @par Parameters:
* None
* @retval
* None
*/
INTERRUPT_HANDLER(ADC1_IRQHandler, 22)
{
  /* Get buffered conversion results */
  ADCReadings[0] = ADC1_GetBufferValue(REF_2V5_ANALOG);
  ADCReadings[1] = ADC1_GetBufferValue(L9110_U3_DRAW);
  ADCReadings[2] = ADC1_GetBufferValue(L9110_U4_DRAW);
  ADCReadings[3] = ADC1_GetBufferValue(L9110_U5_DRAW);
}