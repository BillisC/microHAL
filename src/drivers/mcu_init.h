/** @file mcu_init.h
 *  @brief Function prototypes for the MCU initializer.
 *
 *  This file contains all of the enums, macros, and
 *  function prototypes required for a proper peripheral
 *  and clock initialization.
 *
 *  @author Vasileios Ch. (BillisC)
 *  @bug None, yet.
 */

#ifndef MCU_INIT_H
#define MCU_INIT_H

/* Includes */
#include "defines.h"

/* Peripherals */
#define PWR_GPIO TRUE
#define PWR_ADC1 TRUE
#define PWR_ADC2 FALSE
#define PWR_ADC3 FALSE

/* Clock Configuration
 * 8MHz (HSE) / 4 (PLLM) = 2MHz
 * 2MHz * 180 (PLLN) = 360MHz
 * 360MHz / 2 (PLLSRC) = 180MHz */
#define PLLM_VAL   4
#define PLLN_VAL   180
#define PLLSRC_VAL 1

/* Power Regulation */
#define EN_OVERDRIVE TRUE

/**
 * @brief MCU initialization function.
 *
 * @return None
 */
void mcu_init(void);

#endif
