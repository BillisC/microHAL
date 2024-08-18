#ifndef DEFINES_H
#define DEFINES_H

/* LOGIC */
#define TRUE  1
#define FALSE 0

/* ASM INSTRUCTIONS */
#ifndef UTEST
#define ASM_BKPT volatile __asm__("BKPT")
#define ASM_NOP  volatile __asm__("NOP")
#define ASM_DSB  volatile __asm__("DSB")
#else
#define ASM_BKPT
#define ASM_NOP
#define ASM_DSB
#endif

/* SYSTEM */
#define SYS_CLK  180 // in MHz
#define APB1_CLK 45
#define APB2_CLK 90

#endif
