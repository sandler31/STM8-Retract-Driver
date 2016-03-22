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
#ifndef __STM8S_IT_H
#define __STM8S_IT_H

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "globs.h"
#include "control.h"

/* Exported functions ------------------------------------------------------- */
INTERRUPT void EXTI_PORTB_IRQHandler(void); /* EXTI PORTB */
INTERRUPT void EXTI_PORTC_IRQHandler(void); /* EXTI PORTC */
INTERRUPT void TIM2_UPD_OVF_BRK_IRQHandler(void); /* TIM2 Interrupt */
INTERRUPT void ADC1_IRQHandler(void); /* ADC1 End of Scan Interrupt */

#endif /* __STM8S_IT_H */