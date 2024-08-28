/** @file rcc.c
 *  @brief Function defines for the RCC driver.
 *
 *  This file contains all of the function definitions
 *  declared in rcc.h.
 *
 *  @author Vasileios Ch. (BillisC)
 *  @bug None, yet.W
 */

/* Includes */
#include "defines.h"
#include "rcc.h"

void rcc_configure_ahb_prescaler(const rcc_ahb_prescaler_t value) {
  /* Make sure the prescaler value is valid */
  switch (value) {
    case RCC_AHB_PRESCALER_DIV1:
    case RCC_AHB_PRESCALER_DIV2:
    case RCC_AHB_PRESCALER_DIV4:
    case RCC_AHB_PRESCALER_DIV8:
    case RCC_AHB_PRESCALER_DIV16:
    case RCC_AHB_PRESCALER_DIV64:
    case RCC_AHB_PRESCALER_DIV128:
    case RCC_AHB_PRESCALER_DIV256:
    case RCC_AHB_PRESCALER_DIV512: break;
    default: return;
  }

  /* Change the AHB prescaler */
  struct RCCRegs *regs = RCC_PTR;
  REG32 cfgr = regs->CFGR;
  cfgr &= ~(RCC_CFGR_HPRE_Msk); // clear first
  cfgr |= (value << RCC_CFGR_HPRE_Pos);

  regs->CFGR = cfgr;
  ASM_DSB;
}

void rcc_configure_apb_prescaler(const uint8_t apb,
                                 const rcc_apb_prescaler_t value) {
  /* Make sure the prescaler value is valid */
  switch (value) {
    case RCC_APB_PRESCALER_DIV1:
    case RCC_APB_PRESCALER_DIV2:
    case RCC_APB_PRESCALER_DIV4:
    case RCC_APB_PRESCALER_DIV8:
    case RCC_APB_PRESCALER_DIV16: break;
    default: return;
  }

  /* Change the APB prescaler */
  struct RCCRegs *regs = RCC_PTR;
  REG32 cfgr = regs->CFGR;
  if (apb == 1) {
    cfgr &= ~(RCC_CFGR_PPRE1_Msk); // clear first
    cfgr |= (value << RCC_CFGR_PPRE1_Pos);
  } else if (apb == 2) {
    cfgr &= ~(RCC_CFGR_PPRE2_Msk); // clear first
    cfgr |= (value << RCC_CFGR_PPRE2_Pos);
  } else {
    return;
  }

  regs->CFGR = cfgr;
  ASM_DSB;
}

void rcc_configure_pll_clk(const struct RCCPLLConfig config) {
  /* Check if the configuration is valid, and if it's not,
   * ignore the bad values. This is done because the user
   * may want to leave some values untouched (by leaving
   * them zeroed). */
  const uint32_t good_pllr = (config.PLLR >= 2) ? RCC_PLLCFGR_PLLR_Msk : 0U;
  const uint32_t good_pllq = (config.PLLQ >= 2) ? RCC_PLLCFGR_PLLQ_Msk : 0U;
  const uint32_t good_plln = (config.PLLN >= 50) ? RCC_PLLCFGR_PLLN_Msk : 0U;
  const uint32_t good_pllm = (config.PLLM >= 2) ? RCC_PLLCFGR_PLLM_Msk : 0U;

  /* Configure the PLL clock */
  struct RCCRegs *regs = RCC_PTR;
  REG32 pllcfgr = regs->PLLCFGR;
  pllcfgr &= ~(good_pllr | good_pllq | good_plln | good_pllm |
               RCC_PLLCFGR_PLLP_Msk | RCC_PLLCFGR_PLLSRC_Msk); // clear first
  pllcfgr |= (((config.PLLR << RCC_PLLCFGR_PLLR_Pos) & good_pllr) |
              ((config.PLLQ << RCC_PLLCFGR_PLLQ_Pos) & good_pllq) |
              ((config.PLLN << RCC_PLLCFGR_PLLN_Pos) & good_plln) |
              ((config.PLLM << RCC_PLLCFGR_PLLM_Pos) & good_pllm) |
              (config.PLLP << RCC_PLLCFGR_PLLP_Pos) |
              (config.UseHSE << RCC_PLLCFGR_PLLSRC_Pos));

  regs->PLLCFGR = pllcfgr;
  ASM_DSB;
}

void rcc_enable_osc(const rcc_osc_t osc) {
  struct RCCRegs *regs = RCC_PTR;
  switch (osc) {
    case RCC_OSC_HSI:
      regs->CR |= RCC_CR_HSION_Msk;
      while (!(regs->CR & RCC_CR_HSIRDY_Msk)) { ASM_NOP; };
      break;
    case RCC_OSC_HSE:
      regs->CR |= (RCC_CR_HSEBYP_Msk | RCC_CR_HSEON_Msk);
      while (!(regs->CR & RCC_CR_HSERDY_Msk)) { ASM_NOP; };
      break;
    case RCC_OSC_LSI:
      regs->CSR |= RCC_CSR_LSION_Msk;
      while (!(regs->CSR & RCC_CSR_LSIRDY_Msk)) { ASM_NOP; };
      break;
    case RCC_OSC_LSE:
      regs->BDCR |= RCC_BDCR_LSEON_Msk;
      while (!(regs->BDCR & RCC_BDCR_LSERDY_Msk)) { ASM_NOP; };
      break;
    case RCC_OSC_PLL:
      regs->CR |= RCC_CR_PLLON_Msk;
      while (!(regs->CR & RCC_CR_PLLRDY_Msk)) { ASM_NOP; }
      break;
    case RCC_OSC_PLLSAI:
      regs->CR |= RCC_CR_PLLSAION_Msk;
      while (!(regs->CR & RCC_CR_PLLSAIRDY_Msk)) { ASM_NOP; };
      break;
    case RCC_OSC_PLLI2S:
      regs->CR |= RCC_CR_PLLI2SON_Msk;
      while (!(regs->CR & RCC_CR_PLLI2SRDY_Msk)) { ASM_NOP; }
      break;
    default: return;
  }
}

void rcc_disable_osc(const rcc_osc_t osc) {
  struct RCCRegs *regs = RCC_PTR;
  switch (osc) {
    case RCC_OSC_HSI: regs->CR &= ~(RCC_CR_HSION_Msk); break;
    case RCC_OSC_HSE: regs->CR &= ~(RCC_CR_HSEON_Msk); break;
    case RCC_OSC_LSI: regs->CSR &= ~(RCC_CSR_LSION_Msk); break;
    case RCC_OSC_LSE: regs->BDCR &= ~(RCC_BDCR_LSEON_Msk); break;
    case RCC_OSC_PLL: regs->CR &= ~(RCC_CR_PLLON_Msk); break;
    case RCC_OSC_PLLSAI: regs->CR &= ~(RCC_CR_PLLSAION_Msk); break;
    case RCC_OSC_PLLI2S: regs->CR &= ~(RCC_CR_PLLI2SON_Msk); break;
    default: return;
  }
  ASM_DSB;
}

void rcc_set_systemclock_src(const rcc_systemclock_src_t source) {
  /* Check that the source is correct */
  switch (source) {
    case RCC_SYSTEMCLOCK_SRC_HSI:
    case RCC_SYSTEMCLOCK_SRC_HSE:
    case RCC_SYSTEMCLOCK_SRC_PLL:
    case RCC_SYSTEMCLOCK_SRC_PLR: break;
    default: return;
  }

  /* Set system clock source */
  struct RCCRegs *regs = RCC_PTR;
  REG32 cfgr = regs->CFGR;
  cfgr &= ~(RCC_CFGR_SW_Msk);
  cfgr |= (source << RCC_CFGR_SW_Pos);

  regs->CFGR = cfgr;
  ASM_DSB;
}

void rcc_enable_peripheral_clk(const rcc_clk_periph_t peripheral) {
  /* Set peripheral clock bit */
  struct RCCRegs *regs = RCC_PTR;
  if (peripheral < BIT(5)) {
    regs->AHB1ENR |= BIT(peripheral);
  } else if (peripheral < BIT(6)) {
    regs->AHB2ENR |= BIT(peripheral - BIT(5));
  } else if (peripheral < BIT(7)) {
    regs->AHB3ENR |= BIT(peripheral - BIT(6));
  } else if (peripheral < BIT(8)) {
    regs->APB1ENR |= BIT(peripheral - BIT(7));
  } else if (peripheral < BIT(9)) {
    regs->APB2ENR |= BIT(peripheral - BIT(8));
  } else {
    return;
  }
  ASM_DSB;
}

void rcc_disable_peripheral_clk(const rcc_clk_periph_t peripheral) {
  /* Clear peripheral clock bit */
  struct RCCRegs *regs = RCC_PTR;
  if (peripheral < BIT(5)) {
    regs->AHB1RSTR &= ~BIT(peripheral);
  } else if (peripheral < BIT(6)) {
    regs->AHB2RSTR &= ~BIT(peripheral - BIT(5));
  } else if (peripheral < BIT(7)) {
    regs->AHB3RSTR &= ~BIT(peripheral - BIT(6));
  } else if (peripheral < BIT(8)) {
    regs->APB1RSTR &= ~BIT(peripheral - BIT(7));
  } else if (peripheral < BIT(9)) {
    regs->APB2RSTR &= ~BIT(peripheral - BIT(8));
  } else {
    return;
  }
  ASM_DSB;
}
