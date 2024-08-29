/** @file isr.c
 *  @brief Function defines of the interrupt handlers.
 *
 *  This file contains all of the function definitions
 *  declared in interrupts.h.
 *
 *  @author Vasileios Ch. (BillisC)
 *  @bug None, yet.
 */

/* -- Includes -- */
#include "isr.h"

/* SysTick interrupt routine override */
volatile uint32_t ticks = 0UL;
void SysTick_Handler(void) { ticks++; }
