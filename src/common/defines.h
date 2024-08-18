#ifndef DEFINES_H
#define DEFINES_H

/* LOGIC */
#define TRUE  1
#define FALSE 0

/* ASM INSTRUCTIONS */
#ifndef UTEST
#define ASM_BKPT __asm volatile("BKPT")
#define ASM_NOP  __asm volatile("NOP")
#define ASM_DSB  __asm volatile("DSB")
#else
#define ASM_BKPT
#define ASM_NOP
#define ASM_DSB
#endif

/* SYSTEM */
#define HSE_CLK  8U // in MHz
#define SYS_CLK  180
#define APB1_CLK 45
#define APB2_CLK 90

#endif
