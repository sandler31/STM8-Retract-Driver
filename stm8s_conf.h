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
#ifndef __STM8S_CONF_H
#define __STM8S_CONF_H

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

/* Uncomment the line below to enable peripheral header file inclusion */
#include "stm8s_clk.h"
#include "stm8s_exti.h"
#include "stm8s_gpio.h"
#include "stm8s_adc1.h"
#include "stm8s_tim2.h"

/* Uncomment the line below to expanse the "assert_param" macro in the
   Standard Peripheral Library drivers code */
#define USE_FULL_ASSERT    (1) 

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param expr: If expr is false, it calls assert_failed function
  *   which reports the name of the source file and the source
  *   line number of the call that failed.
  *   If expr is true, it returns no value.
  * @retval : None
  */
#define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
void assert_failed(uint8_t* file, uint32_t line);
#else
#define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#endif /* __STM8S_CONF_H */

