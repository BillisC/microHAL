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
               "USART register struct size mismatch. Is it aligned?");

/* Refer to datasheet */
struct __attribute__((packed)) usart_config {
  volatile uint8_t STOPBITS : 2;
  volatile uint8_t DATABITS : 1;
};

_Static_assert((sizeof(struct usart_config)) == (sizeof(uint8_t) * 1U),
               "USART configuration struct size mismatch. Is it aligned?");

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

void usart_init(const usart_sel_t usart, const uint32_t baudrate,
                const uint8_t over8);

void usart_set_config(const usart_sel_t usart,
                      const struct usart_config config);

void usart_write(const usart_sel_t usart, const char character);

#endif
