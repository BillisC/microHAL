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
                const usart_mode_t mode) {
  /* Check that the USART exists */
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

  /* Power on USART interface */
  volatile uint8_t cr1 = regs->CR1;
  cr1 |= USART_CR1_UE_Msk;

  /* Setup communication modes */
  cr1 &= ~(USART_CR1_TE_Msk | USART_CR1_RE_Msk); // Clear first
  if (mode == tx) {
    cr1 |= USART_CR1_TE_Msk;
  } else if (mode == rx) {
    cr1 |= USART_CR1_RE_Msk;
  } else {
    cr1 |= (USART_CR1_TE_Msk | USART_CR1_RE_Msk);
  }

  /* Calculate USART div accurately */
  const uint8_t over8 = 0U; // No need for that
  float usartdiv_f =
      (((APB1_CLK * 1000000.0f) /
        (8.0f * (2.0f - (float)(1U & over8)) * (float)baudrate)) *
       16.0f);
  uint32_t usartdiv = (uint32_t)usartdiv_f;

  regs->BRR = usartdiv;
}

void usart_set_databits(const usart_sel_t usart,
                        const usart_stopbits_t stopbits,
                        const usart_databits_t databits) {
  /* Make sure the stopbits are valid */
  switch (stopbits) {
    case sb1:
    case sbh:
    case sb2:
    case sbo: break;

    default: return;
  }

  /* Check that the USART exists */
  switch (usart) {
    case usart1:
    case usart2:
    case usart3:
    case uart4:
    case uart5:
    case usart6: break;

    default: return;
  }

  /* Make sure the number of databits is valid */
  if ((databits != db8) && (databits != db9)) {
    return;
  } else {
    struct usart *regs = USART(usart);

    /* Set amount of databits */
    volatile uint32_t cr1 = regs->CR1;
    cr1 &= ~(USART_CR1_M_Msk);
    cr1 |= (databits << USART_CR1_M_Pos);

    regs->CR1 = cr1;

    /* Set amount of stopbits */
    volatile uint32_t cr2 = regs->CR2;
    cr2 &= ~(USART_CR2_STOP_Msk);
    cr2 |= (stopbits << USART_CR2_STOP_Pos);

    regs->CR2 = cr2;
  }
}

void usart_set_parity(const usart_sel_t usart, const usart_parity_t parity) {
  /* Check that the parity is valid */
  switch (parity) {
    case evn:
    case odd:
    case off: break;

    default: return;
  }

  /* Check that the USART exists */
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

  /* Set amount of databits */
  volatile uint32_t cr1 = regs->CR1;

  if (parity == evn) {
    cr1 &= ~(USART_CR1_PS_Msk);
    cr1 |= USART_CR1_PCE_Msk;
  } else if (parity == odd) {
    cr1 |= (USART_CR1_PS_Msk | USART_CR1_PCE_Msk);
  } else {
    cr1 &= ~(USART_CR1_PCE_Msk);
  }

  regs->CR1 = cr1;
}

void usart_write(const usart_sel_t usart, const char character) {
  /* Check that the USART exists */
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

  /* Wait for TXE and transmit data */
  while (!(regs->SR & USART_SR_TXE_Msk)) { ASM_NOP; };
  regs->DR = character;
}
