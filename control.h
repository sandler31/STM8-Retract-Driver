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
#ifndef __RETRACT_CONTROL_H
#define __RETRACT_CONTROL_H

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "globs.h"

/* Exported functions ------------------------------------------------------- */
void InitADC();
void InitTimer();
void CutOperation(GPIO_TypeDef*, GPIO_Pin_TypeDef);
void InitOperation(int);
void HandleVoltage(int, int, GPIO_TypeDef*, GPIO_Pin_TypeDef);

#endif /* __RETRACT_CONTROL_H */