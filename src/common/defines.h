#ifndef DEFINES_H
#define DEFINES_H

/* LOGIC */
#define TRUE  1
#define FALSE 0

/* ASM INSTRUCTIONS */
#ifndef UTEST
#define ASM_BKPT __asm__("BKPT")
#define ASM_NOP  __asm__("NOP")
#else
#define ASM_BKPT
#define ASM_NOP
#endif

/* SYSTEM */
#define SYS_CLK  180 // in MHz
#define APB1_CLK 45
#define APB2_CLK 90

#endif
