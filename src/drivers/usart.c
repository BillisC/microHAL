/** @file usart.c
 *  @brief Function defines for the USART driver.
 *
 *  This file contains all of the function definitions
 *  declared in usart.h.
 *
 *  @author Vasileios Ch. (BillisC)
 *  @bug None, yet.
 */

/* -- Includes -- */
#include "defines.h"
#include "usart.h"

void usart_init(const usart_sel_t usart, const uint32_t baudrate,
                const uint8_t over8) {
  switch (usart) {
    case usart1:
    case usart2:
    case usart3:
    case uart4:
    case uart5:
    case usart6: break;

    default: return;
  }

  struct usart *regs = USART(usart);

  /* Power on usart interface */
  regs->CR1 |= (USART_CR1_UE_Msk | USART_CR1_TE_Msk);
  regs->CR1 |= (over8 << USART_CR1_OVER8_Pos);

  /* Calculate USART div accurately */
  float usartdiv_f =
      (((APB1_CLK * 1000000.0f) /
        (8.0f * (2.0f - (float)(1U & over8)) * (float)baudrate)) *
       16.0f);
  uint32_t usartdiv = (uint32_t)usartdiv_f;

  regs->BRR = usartdiv;
}

void usart_set_config(const usart_sel_t usart,
                      const struct usart_config config) {
  switch (usart) {
    case usart1:
    case usart2:
    case usart3:
    case uart4:
    case uart5:
    case usart6: break;

    default: return;
  }

  struct usart *regs = USART(usart);

  /* Configure USART */
  regs->CR1 |= (config.DATABITS << USART_CR1_M_Pos);    // 8b word length (7+1)
  regs->CR2 |= (config.STOPBITS << USART_CR2_STOP_Pos); // 1 stop bit
}

void usart_write(const usart_sel_t usart, const char character) {
  switch (usart) {
    case usart1:
    case usart2:
    case usart3:
    case uart4:
    case uart5:
    case usart6: break;

    default: return;
  }

  struct usart *regs = USART(usart);

  while (!(regs->SR & USART_SR_TXE_Msk)) { ASM_NOP; };
  regs->DR = character;
}
