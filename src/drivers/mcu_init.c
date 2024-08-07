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
#include "mcu_init.h"
#include "stm32f4xx.h"
#include <stdint.h>

static void clock_init(void) {
  /* Enable 8 MHz HSE oscillator (Source: STLINK) */
  RCC->CR |= RCC_CR_HSEBYP_Msk | RCC_CR_HSEON_Msk;
  while (! (RCC->CR & RCC_CR_HSERDY_Msk)) { ASM_NOP; };

  /* Enable power controller */
  uint32_t apb1enr = RCC_APB1ENR_PWREN_Msk;
  RCC->APB1ENR |= apb1enr;
  /* Do some dummy reads */
  volatile uint32_t dummy_read;
  dummy_read = RCC->APB1ENR;
  dummy_read = RCC->APB1ENR;

  /* Set voltage regulator scaling to 1 */
  PWR->CR |= (3U << PWR_CR_VOS_Pos);

  /* Configure flash controller for 3V3 and 180 MHz
   * system clock (5 wait states). */
  FLASH->ACR |= FLASH_ACR_LATENCY_5WS;

  /* Clear PLL clock parameters */
  RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLM_Msk |
                    RCC_PLLCFGR_PLLN_Msk |
                    RCC_PLLCFGR_PLLP_Msk);

  /* Configure the PLL clock */
  RCC->PLLCFGR |= ((PLLM_VAL << RCC_PLLCFGR_PLLM_Pos) |
                   (PLLN_VAL << RCC_PLLCFGR_PLLN_Pos) |
                   (PLLSRC_VAL << RCC_PLLCFGR_PLLSRC_Pos));

  /* Enable PLL clock */
  RCC->CR |= RCC_CR_PLLON_Msk;
  while (! (RCC->CR & RCC_CR_PLLRDY_Msk)) { ASM_NOP; };

  #if EN_OVERDRIVE == TRUE
    /* Enable overdrive mode */
    PWR->CR |= (PWR_CR_ODEN_Msk);
    while (! (PWR->CSR & PWR_CSR_ODRDY)) { ASM_NOP; };

    /* Switch internal voltage regulator to
     * overdrive mode. */
    PWR->CR |= (PWR_CR_ODSWEN_Msk);
    while (! (PWR->CSR & PWR_CSR_ODSWRDY)) { ASM_NOP; };
  #endif

  /* Select PLL as the system clock source */
  RCC->CFGR |= (RCC_CFGR_SW_PLL << RCC_CFGR_SW_Pos);
  while (! (RCC->CFGR & RCC_CFGR_SWS_PLL)) { ASM_NOP; };

  /* Inform CMSIS about the system clock */
  SystemCoreClockUpdate();
}

static void ahb1_periph(void) {
  uint32_t ahb1enr = 0U;
  #if PWR_GPIO == TRUE
    ahb1enr |= RCC_AHB1ENR_GPIOAEN_Msk;
  #endif

  RCC->AHB1ENR |= ahb1enr;
}

static void apb2_periph(void) {
  uint32_t apb2enr = 0U;
  #if PWR_ADC1 == TRUE
    apb2enr |= RCC_APB2ENR_ADC1EN_Msk;
  #endif
  #if PWR_ADC2 == TRUE
    apb2enr |= RCC_APB2ENR_ADC2EN_Msk;
  #endif
  #if PWR_ADC3 == TRUE
    apb2enr |= RCC_APB2ENR_ADC3EN_Msk;
  #endif

  RCC->APB2ENR |= apb2enr;
}

static void peripheral_init(void) {
  /* Enable peripherals */
  ahb1_periph();
  apb2_periph();

  /* dummy reads */
  volatile uint32_t dummy_read;
  dummy_read = RCC->AHB1ENR;
}

void mcu_init(void) {
  clock_init();
  /* Set interrupt rate to 1 KHz (/180 MHZ) and enable interrupts */
  SysTick_Config(180000);
  __enable_irq();

  peripheral_init();
}
