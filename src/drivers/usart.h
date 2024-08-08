/** @file usart.h
 *  @brief Function prototypes for the USART interface.
 *
 *  This file contains all of the enums, macros, and
 *  function prototypes required for a functional usart
 *  driver.
 *
 *  @author Vasileios Ch. (BillisC)
 *  @bug None, yet.
 */

#ifndef USART_H
#define USART_H

/* Includes */
#include <stdint.h>
#include "stm32f4xx.h"

/* Structs */
struct __attribute__((packed)) usart {
  volatile uint32_t SR;
  volatile uint32_t DR;
  volatile uint32_t BRR;
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t CR3;
  volatile uint32_t GTPR;
};

_Static_assert((sizeof(struct usart)) == (sizeof(uint32_t) * 7U),
               "GPIO register struct size mismatch. Is it aligned?");

/* Enums  */
typedef enum usart_sel {
  usart1 = USART1_BASE,
  usart2 = USART2_BASE,
  usart3 = USART3_BASE,
  usart6 = USART6_BASE,
  uart4 = UART4_BASE,
  uart5 = UART5_BASE,
} usart_sel_t;

#define USART(sel) (struct usart *)((usart_sel_t)sel)

typedef enum usart_oversampling {
  ovr16 = 0x00,
  ovr08 = 0x01
} usart_oversampling_t;

typedef enum usart_databits {
  s1d8 = 0x00,
  s1d9 = 0x01
} usart_wlength_t;

typedef enum usart_stopbits {
  stop_one = 0x00,
  stop_hlf = 0x01,
  stop_two = 0x02,
  stop_ohl = 0x03
} usart_stopbits_t;

void usart_init(const usart_sel_t usart, const uint32_t baudrate);

void usart_write(const usart_sel_t usart, const char character);

#endif
