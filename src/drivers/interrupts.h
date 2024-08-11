/** @file interrupts.h
 *  @brief Function prototypes of the interrupt handlers.
 *
 *  This file contains all of the required externs and
 *  interrupt prototypes for a functional barebone MCU
 *  system.
 *
 *  @author Vasileios Ch. (BillisC)
 *  @bug None, yet.
 */

#ifndef INTERRUPTS_H
#define INTERRUPTS_H

/* -- Includes -- */
#include <stdint.h>

extern uint32_t ticks;
void SysTick_Handler(void);

#endif
