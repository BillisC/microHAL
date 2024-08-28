/** @file mcu_init.c
 *  @brief Function definitions for the MCU initializer.
 *
 *  This file contains all of the function definitions
 *  declared in mcu_init.h.
 *
 *  @author Vasileios Ch. (BillisC)
 *  @bug None, yet.
 */

/* Includes */
#include <stdint.h>
#include "stm32f4xx.h"
#include "mcu_init.h"

static void clock_init(void) {
  /* Enable 8 MHz HSE oscillator (Source: STLINK) */
  rcc_enable_osc(RCC_OSC_HSE);

  /* Enable power controller */
  rcc_enable_peripheral_clk(RCC_CLK_PWR);

  /* Set voltage regulator scaling to 1 */
  PWR->CR |= (3UL << PWR_CR_VOS_Pos);

  /* Configure flash controller for 3V3 and 180 MHz
   * system clock (5 wait states). */
  FLASH->ACR |= FLASH_ACR_LATENCY_5WS;

  /* Configure the PLL clock */
  struct RCCPLLConfig pll = {0};
  pll.PLLM = PLLM_VAL;
  pll.PLLP = PLLP_VAL;
  pll.PLLN = PLLN_VAL;
  pll.UseHSE = PLLSRC_VAL;
  rcc_configure_pll_clk(pll);

  /* Configure the APB clocks */
  rcc_configure_apb_prescaler(1, PPRE1_VAL);
  rcc_configure_apb_prescaler(2, PPRE2_VAL);

  /* Enable PLL clock */
  rcc_enable_osc(RCC_OSC_PLL);

#if EN_OVERDRIVE == TRUE
  /* Enable overdrive mode */
  PWR->CR |= (PWR_CR_ODEN_Msk);
  while (!(PWR->CSR & PWR_CSR_ODRDY_Msk)) { ASM_NOP; };

  /* Switch internal voltage regulator to
   * overdrive mode. */
  PWR->CR |= (PWR_CR_ODSWEN_Msk);
  while (!(PWR->CSR & PWR_CSR_ODSWRDY_Msk)) { ASM_NOP; };
#endif

  /* Select PLL as the system clock source */
  rcc_set_systemclock_src(RCC_SYSTEMCLOCK_SRC_PLL);

  /* Inform CMSIS about the system clock */
  SystemCoreClockUpdate();
}

static void peripheral_init(void) {
  /* Enable peripherals */
  rcc_enable_peripheral_clk(RCC_CLK_GPIOA);
  rcc_enable_peripheral_clk(RCC_CLK_USART2);
}

void mcu_init(void) {
  clock_init();

  /* Set interrupt rate to 1 KHz and enable interrupts */
  SysTick_Config(SYS_CLK * 1000U);
  __enable_irq();

#if EN_FPU == TRUE
  SCB->CPACR |= ((3UL << 20U) | (3UL << 22U));
#endif

  peripheral_init();
}
