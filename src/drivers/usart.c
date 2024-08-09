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
                const usart_mode_t mode, const _Bool x8_oversample) {
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
  cr1 &= ~(USART_CR1_TE_Msk | USART_CR1_RE_Msk |
           USART_CR1_OVER8_Msk); // Clear first
  cr1 |= (x8_oversample << USART_CR1_OVER8_Pos);
  if (mode == tx) {
    cr1 |= USART_CR1_TE_Msk;
  } else if (mode == rx) {
    cr1 |= USART_CR1_RE_Msk;
  } else {
    cr1 |= (USART_CR1_TE_Msk | USART_CR1_RE_Msk);
  }

  regs->CR1 = cr1;

  /* Calculate USART div accurately */
  float usartdiv =
      ((APB1_CLK * 1000000.0f) / ((8 * (2 - x8_oversample) * baudrate)));
  uint16_t mantissa = (uint16_t)usartdiv;
  uint8_t fraction =
      (uint8_t)((float)(usartdiv - mantissa) * (16 - (8 * x8_oversample)));

  regs->BRR = ((4095UL & mantissa) << 4) | (15UL & fraction);
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
