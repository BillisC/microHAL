/** @file defines.h
 *  @brief Defines used commonly in most files
 *
 *  @author Vasileios Ch. (BillisC)
 *  @bug None, yet.
 */

#ifndef DEFINES_H
#define DEFINES_H

/* LOGIC */
#define TRUE  1
#define FALSE 0

/* ASM INSTRUCTIONS */
#ifndef UTEST
#define ASM_INSTR(x) __asm volatile(#x)
#else
#define ASM_INSTR(x)
#endif
#define ASM_BKPT ASM_INSTR(BKPT)
#define ASM_NOP  ASM_INSTR(NOP)
#define ASM_DSB  ASM_INSTR(DSB)

/* SYSTEM */
#define HSE_CLK  8 // in MHz
#define SYS_CLK  180
#define APB1_CLK 45
#define APB2_CLK 90

/* TYPES */
#define REG32 volatile uint32_t

#endif
