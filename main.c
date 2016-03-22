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

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "globs.h"

/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void InitClock()
{
  //
  //  Initialise the clock
  //
  CLK_DeInit();
  CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);                // CPU Prescaler = 1.
  CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);                // Prescaler = 1, 16 MHz.
  CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO,              // Automatically switch
                        CLK_SOURCE_HSI,                   // Switch to internal timer.
                        DISABLE,                          // Disable the clock switch interrupt.
                        CLK_CURRENTCLOCKSTATE_DISABLE);   // Disable the previous clock.
}

void InitInputs()
{
  // Init GPIO Inputs
  GPIO_DeInit(RETRACT_SIN_PORT);
  GPIO_DeInit(EXTEND_SIN_PORT);
  GPIO_Init(RETRACT_SIN_PORT,RETRACT_SIN_PIN,GPIO_MODE_IN_FL_IT);
  GPIO_Init(EXTEND_SIN_PORT,EXTEND_SIN_PIN,GPIO_MODE_IN_FL_IT);
  
  // Init GPIO Outputs
  GPIO_Init(L9110_U3_PORT, (GPIO_Pin_TypeDef)(L9110_U3_IA | L9110_U3_IB),
            GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(L9110_U4_PORT, (GPIO_Pin_TypeDef)(L9110_U4_IA | L9110_U4_IB),
          GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(L9110_U5_PORT, (GPIO_Pin_TypeDef)(L9110_U5_IA | L9110_U5_IB),
        GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(REQ_FINISHED_PORT, REQ_FINISHED_PIN,
          GPIO_MODE_OUT_PP_HIGH_FAST);
  
  // Init GPIO Inrerrupts
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC, 
                            EXTI_SENSITIVITY_RISE_ONLY);
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOB, 
                            EXTI_SENSITIVITY_RISE_ONLY);
  EXTI_SetTLISensitivity(EXTI_TLISENSITIVITY_RISE_ONLY);
}

void main(void)
{
  InitClock();
  InitInputs();
  //InitADC();

  /* Infinite loop */
  enableInterrupts();
  while (1)
  {
  }
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif