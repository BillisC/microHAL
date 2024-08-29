/** @file rcc.h
 *  @brief Function prototypes for the RCC driver.
 *
 *  This file contains all of the enums, macros, and
 *  function prototypes required for a functional RCC
 *  driver.
 *
 *  @author Vasileios Ch. (BillisC)
 *  @bug None, yet.
 */

#ifndef RCC_H
#define RCC_H

/* -- Includes -- */
#include <stdint.h>
#include "stm32f4xx.h"
#include "defines.h"

/* -- Structs -- */
/**
 *  @brief Contains RCC registers
 */
struct __attribute__((packed)) RCCRegs {
  REG32 CR;
  REG32 PLLCFGR;
  REG32 CFGR;
  REG32 CIR;
  REG32 AHB1RSTR;
  REG32 AHB2RSTR;
  REG32 AHB3RSTR;
  REG32 _reserved1;
  REG32 APB1RSTR;
  REG32 APB2RSTR;
  REG32 _reserved2[2];
  REG32 AHB1ENR;
  REG32 AHB2ENR;
  REG32 AHB3ENR;
  REG32 _reserved3;
  REG32 APB1ENR;
  REG32 APB2ENR;
  REG32 _reserved4[2];
  REG32 AHB1LPENR;
  REG32 AHB2LPENR;
  REG32 AHB3LPENR;
  REG32 _reserved5;
  REG32 APB1LPENR;
  REG32 APB2LPENR;
  REG32 _reserved6[2];
  REG32 BDCR;
  REG32 CSR;
  REG32 _reserved7[2];
  REG32 SSCGR;
  REG32 PLLI2SCFGR;
  REG32 PLLSAICFGR;
  REG32 DCKCFGR;
  REG32 CKGATENR;
  REG32 DCKCFGR2;
};

_Static_assert((sizeof(struct RCCRegs)) == (sizeof(uint32_t) * 38U),
               "RCC register struct size mismatch. Is it aligned?");

#define RCC_PTR (struct RCCRegs *)RCC_BASE

/**
 *  @brief Contains PLL configuration values
 */
struct __attribute__((packed)) RCCPLLConfig {
  uint8_t PLLM  : 6; /** Must be 2..63 */
  uint8_t PLLP  : 2; /** Must be 0..3 */
  uint8_t PLLQ  : 4; /** Must be 2..15 */
  uint8_t PLLR  : 3; /** Must be 2..7 */
  uint16_t PLLN : 9; /** Must be 50..432 */
  _Bool UseHSE  : 1;
};

_Static_assert((sizeof(struct RCCPLLConfig)) == (sizeof(uint8_t) * 4U),
               "RCC PLL configuration struct size mismatch. Is it aligned?");

/* -- Enums -- */
/**
 *  @brief Contains RCC oscillators
 */
typedef enum rcc_osc {
  RCC_OSC_HSI = 0x0,
  RCC_OSC_HSE = 0x1,
  RCC_OSC_LSI = 0x2,
  RCC_OSC_LSE = 0x3,
  RCC_OSC_PLL = 0x4,
  RCC_OSC_PLLSAI = 0x5,
  RCC_OSC_PLLI2S = 0x6,
} rcc_osc_t;

/**
 *  @brief Contains AHB/APB peripheral clocks
 */
typedef enum rcc_clk_periph {
  /* ---------- AHB1 ---------- */
  RCC_CLK_GPIOA = 0U,
  RCC_CLK_GPIOB,
  RCC_CLK_GPIOD,
  RCC_CLK_GPIOC,
  RCC_CLK_GPIOE,
  RCC_CLK_GPIOF,
  RCC_CLK_GPIOG,
  RCC_CLK_GPIOH,
  RCC_CLK_GPIOI,
  RCC_CLK_GPIOJ,
  RCC_CLK_GPIOK,
  RCC_CLK_CRC = 12U,
  RCC_CLK_BKPSRAM = 18U,
  RCC_CLK_CCMDATARAM = 20U,
  RCC_CLK_DMA1,
  RCC_CLK_DMA2,
  RCC_CLK_DMA2D,
  RCC_CLK_ETHMAC = 25U,
  RCC_CLK_ETHMACTX,
  RCC_CLK_ETHMACRX,
  RCC_CLK_ETHMACPTP,
  RCC_CLK_OTGHS,
  RCC_CLK_OTGHSULPI,

  /* ---------- AHB2 ---------- */
  RCC_CLK_DCMI = 32U,
  RCC_CLK_CRYP = 32U + 4U,
  RCC_CLK_HASH,
  RCC_CLK_RNG,
  RCC_CLK_OTGFS,

  /* ---------- AHB3 ---------- */
  RCC_CLK_FMC = 64U,
  RCC_CLK_QSPI,

  /* ---------- APB1 ---------- */
  RCC_CLK_TIM2 = 96U,
  RCC_CLK_TIM3,
  RCC_CLK_TIM4,
  RCC_CLK_TIM5,
  RCC_CLK_TIM6,
  RCC_CLK_TIM7,
  RCC_CLK_TIM12,
  RCC_CLK_TIM13,
  RCC_CLK_TIM14,
  RCC_CLK_WWDG = 96U + 11U,
  RCC_CLK_SPI2 = 96U + 14U,
  RCC_CLK_SPI3,
  RCC_CLK_SPDIFRX,
  RCC_CLK_USART2,
  RCC_CLK_USART3,
  RCC_CLK_UART4,
  RCC_CLK_UART5,
  RCC_CLK_I2C1,
  RCC_CLK_I2C2,
  RCC_CLK_I2C3,
  RCC_CLK_FMPI2C1,
  RCC_CLK_CAN1,
  RCC_CLK_CAN2,
  RCC_CLK_CEC,
  RCC_CLK_PWR,
  RCC_CLK_DAC,
  RCC_CLK_UART7,
  RCC_CLK_UART8,

  /* ---------- APB2 ---------- */
  RCC_CLK_TIM1 = 128U,
  RCC_CLK_TIM8,
  RCC_CLK_USART1 = 128U + 4U,
  RCC_CLK_USART6,
  RCC_CLK_ADC1 = 128U + 8U,
  RCC_CLK_ADC2,
  RCC_CLK_ADC3,
  RCC_CLK_SDIO,
  RCC_CLK_SPI1,
  RCC_CLK_SPI4,
  RCC_CLK_SYSCFG,
  RCC_CLK_TIM9 = 128U + 16U,
  RCC_CLK_TIM10,
  RCC_CLK_TIM11,
  RCC_CLK_SPI5 = 128U + 20U,
  RCC_CLK_SPI6,
  RCC_CLK_SAI1,
  RCC_CLK_SAI2,
  RCC_CLK_LTDC = 128U + 26U,
  RCC_CLK_DSI
} rcc_clk_periph_t;

/**
 *  @brief Contains RCC APBx prescaler dividers
 */
typedef enum rcc_apb_prescaler {
  RCC_APB_PRESCALER_DIV1 = 0x0,
  RCC_APB_PRESCALER_DIV2 = 0x4,
  RCC_APB_PRESCALER_DIV4 = 0x5,
  RCC_APB_PRESCALER_DIV8 = 0x6,
  RCC_APB_PRESCALER_DIV16 = 0x7,
} rcc_apb_prescaler_t;

/**
 *  @brief Contains RCC AHB prescaler dividers
 */
typedef enum rcc_ahb_prescaler {
  RCC_AHB_PRESCALER_DIV1 = 0x0,
  RCC_AHB_PRESCALER_DIV2 = 0x8,
  RCC_AHB_PRESCALER_DIV4 = 0x9,
  RCC_AHB_PRESCALER_DIV8 = 0xA,
  RCC_AHB_PRESCALER_DIV16 = 0xB,
  RCC_AHB_PRESCALER_DIV64 = 0xC,
  RCC_AHB_PRESCALER_DIV128 = 0xD,
  RCC_AHB_PRESCALER_DIV256 = 0xE,
  RCC_AHB_PRESCALER_DIV512 = 0xF,
} rcc_ahb_prescaler_t;

/**
 *  @brief Contains RCC system clock sources
 */
typedef enum rcc_systemclock_src {
  RCC_SYSTEMCLOCK_SRC_HSI = 0x0,
  RCC_SYSTEMCLOCK_SRC_HSE = 0x1,
  RCC_SYSTEMCLOCK_SRC_PLL = 0x2, /** PLL_P */
  RCC_SYSTEMCLOCK_SRC_PLR = 0x3, /** PLL_R */
} rcc_systemclock_src_t;

/**
 *  @brief Contains MCO1 clock sources
 */
typedef enum rcc_mco1_src {
  RCC_MCO1_SRC_HSI = 0x0,
  RCC_MCO1_SRC_LSE = 0x1,
  RCC_MCO1_SRC_HSE = 0x2,
  RCC_MCO1_SRC_PLL = 0x3,
} rcc_mco1_src_t;

/**
 *  @brief Contains MCO2 clock sources
 */
typedef enum rcc_mco2_src {
  RCC_MCO2_SRC_SYS = 0x0,
  RCC_MCO2_SRC_I2S = 0x1,
  RCC_MCO2_SRC_HSE = 0x2,
  RCC_MCO2_SRC_PLL = 0x3,
} rcc_mco2_src_t;

/**
 *  @brief Contains MCO prescaler dividers
 */
typedef enum rcc_mco_prescaler {
  RCC_MCO_PRESCALER_DIV1 = 0x0,
  RCC_MCO_PRESCALER_DIV2 = 0x4,
  RCC_MCO_PRESCALER_DIV3 = 0x5,
  RCC_MCO_PRESCALER_DIV4 = 0x6,
  RCC_MCO_PRESCALER_DIV5 = 0x7,
} rcc_mco_prescaler_t;

/**
 *  @brief Set AHB prescaler to the desired value
 *
 *  The available prescale dividers are available in
 *  the rcc_ahb_prescaler_t enum. Any other value will
 *  be ignored. A DSB instruction is inserted after each
 *  RCC register write as per errata.
 *
 *  @param value The prescaler divide value
 *  @return None
 */
void rcc_configure_ahb_prescaler(const rcc_ahb_prescaler_t value);

/**
 *  @brief Set APBx prescaler to the desired value
 *
 *  The available prescale dividers are available in
 *  the rcc_apb_prescaler_t enum. Any other value will
 *  be ignored. A DSB instruction is inserted after each
 *  RCC register write as per errata.
 *
 *  @param apb The selected APB (1..2)
 *  @param value The prescaler divide value
 *  @return None
 */
void rcc_configure_apb_prescaler(const uint8_t apb,
                                 const rcc_apb_prescaler_t value);

/**
 *  @brief Sets the PLL clocks according to config
 *
 *  The configuration values can be found in the
 *  RCCPLLConfig struct. Extra care must be taken with
 *  PLL values as their bits are not the same and
 *  wrapping may happen. A DSB instruction is inserted
 *  after each RCC register write as per errata.
 *
 *  @param peripheral The peripheral clock
 *  @return None
 */
void rcc_configure_pll_clk(const struct RCCPLLConfig config);

/**
 *  @brief Enable the specified oscillator
 *
 *  The available oscilattors are available in the
 *  rcc_osc_t enum. Any other value will be ignored.
 *  A DSB instruction is inserted after each RCC
 *  register write as per errata.
 *
 *  @param osc The selected oscillator
 *  @return None
 */
void rcc_enable_osc(const rcc_osc_t osc);

/**
 *  @brief Disable the specified oscillator
 *
 *  The available oscilattors are available in the
 *  rcc_osc_t enum. Any other value will be ignored.
 *  A DSB instruction is inserted after each RCC
 *  register write as per errata.
 *
 *  @param osc The selected oscillator
 *  @return None
 */
void rcc_disable_osc(const rcc_osc_t osc);

/**
 *  @brief Sets the system clock to the specified source
 *
 *  The available systemclock sources are located in
 *  the rcc_systemclock_src_t enum. Any other value
 *  will be ignored. A DSB instruction is inserted after
 *  each RCC register write as per errata.
 *
 *  @param source The selected clock source
 *  @return None
 */
void rcc_set_systemclock_src(const rcc_systemclock_src_t source);

/**
 *  @brief Enables the specified peripheral clock
 *
 *  The available peripherals can be found in the
 *  rcc_clk_periph_t enum. Any other value will be
 *  ignored. A DSB instruction is inserted after each
 *  RCC register write as per errata.
 *
 *  DISCLAIMER: Only enable peripherals that actually
 *  exist on hardware!
 *
 *  @param peripheral The peripheral clock
 *  @return None
 */
void rcc_enable_peripheral_clk(const rcc_clk_periph_t peripheral);

/**
 *  @brief Disables the specified peripheral clock
 *
 *  The available peripherals can be found in the
 *  rcc_clk_periph_t enum. Any other value will be
 *  ignored. A DSB instruction is inserted after each
 *  RCC register write as per errata.
 *
 *  @param peripheral The peripheral clock
 *  @return None
 */
void rcc_disable_peripheral_clk(const rcc_clk_periph_t peripheral);

/**
 *  @brief Set MCO1 to the specified clock source
 *
 *  The available source clocks are available in the
 *  rcc_mco1_src_t enum. Any other value will be ignored.
 *
 *  @param source The specified clock source
 *  @return None
 */
void rcc_set_mco1_src(const rcc_mco1_src_t source);

/**
 *  @brief Set MCO2 to the specified clock source
 *
 *  The available source clocks are available in the
 *  rcc_mco2_src_t enum. Any other value will be ignored.
 *
 *  @param source The specified clock source
 *  @return None
 */
void rcc_set_mco2_src(const rcc_mco2_src_t source);

/**
 *  @brief Set MCOx prescaler to the desired value
 *
 *  The available prescale dividers are available in
 *  the rcc_mco_prescaler_t enum. Any other value will
 *  be ignored.
 *
 *  @param mco The selected MCO (1..2)
 *  @param value The prescaler divide value
 *  @return None
 */
void rcc_configure_mco_prescaler(const uint8_t mco,
                                 const rcc_mco_prescaler_t value);

#endif
