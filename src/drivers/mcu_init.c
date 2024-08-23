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
  RCC->CR |= (RCC_CR_HSEBYP_Msk | RCC_CR_HSEON_Msk);
  while (!(RCC->CR & RCC_CR_HSERDY_Msk)) { ASM_NOP; };

  /* Enable power controller */
  RCC->APB1ENR |= RCC_APB1ENR_PWREN_Msk;
  ASM_DSB;

  /* Set voltage regulator scaling to 1 */
  PWR->CR |= (3UL << PWR_CR_VOS_Pos);

  /* Configure flash controller for 3V3 and 180 MHz
   * system clock (5 wait states). */
  FLASH->ACR |= FLASH_ACR_LATENCY_5WS;

  /* Configure the PLL clock */
#ifndef CPPCHECK // To avoid bitmask error
  RCC->PLLCFGR &=
      ~(RCC_PLLCFGR_PLLM_Msk | RCC_PLLCFGR_PLLN_Msk | RCC_PLLCFGR_PLLSRC_Msk |
        RCC_PLLCFGR_PLLP_Msk); // Clear first
  RCC->PLLCFGR |=
      ((PLLM_VAL << RCC_PLLCFGR_PLLM_Pos) | (PLLN_VAL << RCC_PLLCFGR_PLLN_Pos) |
       (PLLP_VAL << RCC_PLLCFGR_PLLP_Pos) |
       (PLLSRC_VAL << RCC_PLLCFGR_PLLSRC_Pos));
  ASM_DSB;
#endif

  /* Configure the APB clocks */
  RCC->CFGR |=
      ((APB1_CLK << RCC_CFGR_PPRE1_Pos) | (APB2_CLK << RCC_CFGR_PPRE2_Pos));
  ASM_DSB;

  /* Enable PLL clock */
  RCC->CR |= RCC_CR_PLLON_Msk;
  while (!(RCC->CR & RCC_CR_PLLRDY_Msk)) { ASM_NOP; };

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
  RCC->CFGR |= (RCC_CFGR_SW_PLL << RCC_CFGR_SW_Pos);
  while (!(RCC->CFGR & RCC_CFGR_SWS_PLL)) { ASM_NOP; };

  /* Inform CMSIS about the system clock */
  SystemCoreClockUpdate();
}

static void ahb1_periph(void) {
  uint32_t ahb1enr = 0UL;
#if PWR_GPIOA == TRUE
  ahb1enr |= RCC_AHB1ENR_GPIOAEN_Msk;
#endif
#if PWR_GPIOB == TRUE
  ahb1enr |= RCC_AHB1ENR_GPIOBEN_Msk;
#endif
#if PWR_GPIOC == TRUE
  ahb1enr |= RCC_AHB1ENR_GPIOCEN_Msk;
#endif
#if PWR_GPIOD == TRUE
  ahb1enr |= RCC_AHB1ENR_GPIODEN_Msk;
#endif
#if PWR_GPIOE == TRUE
  ahb1enr |= RCC_AHB1ENR_GPIOEEN_Msk;
#endif
#if PWR_GPIOF == TRUE
  ahb1enr |= RCC_AHB1ENR_GPIOFEN_Msk;
#endif
#if PWR_GPIOG == TRUE
  ahb1enr |= RCC_AHB1ENR_GPIOGEN_Msk;
#endif
#if PWR_GPIOH == TRUE
  ahb1enr |= RCC_AHB1ENR_GPIOHEN_Msk;
#endif
#if PWR_DMA1 == TRUE
  ahb1enr |= RCC_AHB1ENR_DMA1EN_Msk;
#endif
#if PWR_DMA2 == TRUE
  ahb1enr |= RCC_AHB1ENR_DMA2EN_Msk;
#endif

  RCC->AHB1ENR |= ahb1enr;
  ASM_DSB;
}

static void apb1_periph(void) {
  uint32_t apb1enr = 0UL;
#if PWR_USART2 == TRUE
  apb1enr |= RCC_APB1ENR_USART2EN_Msk;
#endif
#if PWR_USART3 == TRUE
  apb1enr |= RCC_APB1ENR_USART3EN_Msk;
#endif
#if PWR_UART4 == TRUE
  apb1enr |= RCC_APB1ENR_UART4EN_Msk;
#endif
#if PWR_UART5 == TRUE
  apb1enr |= RCC_APB1ENR_UART5EN_Msk;
#endif

  RCC->APB1ENR |= apb1enr;
  ASM_DSB;
}

static void apb2_periph(void) {
  uint32_t apb2enr = 0UL;
#if PWR_ADC1 == TRUE
  apb2enr |= RCC_APB2ENR_ADC1EN_Msk;
#endif
#if PWR_ADC2 == TRUE
  apb2enr |= RCC_APB2ENR_ADC2EN_Msk;
#endif
#if PWR_ADC3 == TRUE
  apb2enr |= RCC_APB2ENR_ADC3EN_Msk;
#endif
#if PWR_USART1 == TRUE
  apb2enr |= RCC_APB2ENR_USART1EN_Msk;
#endif
#if PWR_USART6 == TRUE
  apb2enr |= RCC_APB2ENR_USART6EN_Msk;
#endif

  RCC->APB2ENR |= apb2enr;
  ASM_DSB;
}

static void peripheral_init(void) {
  /* Enable peripherals */
  ahb1_periph();
  apb1_periph();
  apb2_periph();
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
