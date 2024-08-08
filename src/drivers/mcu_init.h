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

/* -- Includes -- */
#include "defines.h"

/* -- Coprocessors -- */
#define EN_FPU TRUE

/* -- Peripherals -- */
#define PWR_GPIO   TRUE
#define PWR_ADC1   TRUE
#define PWR_ADC2   FALSE
#define PWR_ADC3   FALSE
#define PWR_USART1 FALSE
#define PWR_USART2 TRUE
#define PWR_USART3 FALSE
#define PWR_USART6 FALSE
#define PWR_UART4  FALSE
#define PWR_UART5  FALSE

/** Clock Configuration
 * 8MHz (HSE) / 4 (PLLM) = 2MHz
 * 2MHz * 180 (PLLN) = 360MHz
 * 360MHz / 2 (PLLSRC) = 180MHz
 * -- WIP --
 * 180MHz / 4 (PPRE1) = 45MHz (APB1)
 * 180MHz / 2 (PPRE2) = 90MHz (APB2)
 */
#define PLLM_VAL   4U
#define PLLN_VAL   180U
#define PLLSRC_VAL 1U // == 2
#define PPRE1_VAL  5U // == 4
#define PPRE2_VAL  4U // == 2

_Static_assert((((8 / 4) * 180) / 2) == (SYS_CLK),
               "System clock calculation mismatch. Did you update SYS_CLK?");

_Static_assert((SYS_CLK / 4) == (APB1_CLK),
               "APB1 clock calculation mismatch. Did you update APB1_CLK?");

_Static_assert((SYS_CLK / 2) == (APB2_CLK),
               "APB2 clock calculation mismatch. Did you update APB2_CLK?");

/* Power Regulation */
#define EN_OVERDRIVE TRUE

/**
 * @brief MCU initialization function.
 *
 * @return None
 */
void mcu_init(void);

#endif
