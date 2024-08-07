/** @file adc.c
 *  @brief Function defines for the ADC driver.
 *
 *  This file contains all of the function definitions
 *  declared in adc.h.
 *
 *  @author Vasileios Ch. (BillisC)
 *  @bug None, yet.
 */

/* -- Includes -- */
#include "adc.h"
#include "defines.h"
#include "stm32f446xx.h"

void adc_set_prescaler(const adc_prescaler_t value) {
  /* Check that the divider is valid */
  switch (value) {
    case div2:
    case div4:
    case div6:
    case div8: break;

    default: return;
  }

  struct adc_common *regs = ADC_COMMON;

  /* Cautiously apply prescaler value */
  volatile uint32_t ccr = regs->CCR;
  ccr &= ~(ADC_CCR_ADCPRE_Msk); // Clear first
  ccr |= ((3UL & value) << ADC_CCR_ADCPRE_Pos);

  regs->CCR = ccr;
}

void adc_set_resolution(const uint8_t adc, const adc_res_t value) {
  /* Check that the resolution is valid */
  switch (value) {
    case b06:
    case b08:
    case b10:
    case b12: break;

    default: return;
  }

  /* Check that the ADC exists */
  if (adc > ADC_NUM) {
    return;
  } else {
    struct adc *regs = ADC_(adc);

    /* Cautiously change resolution */
    volatile uint32_t cr1 = regs->CR1;
    cr1 &= ~(ADC_CR1_RES_Msk); // Clear first
    cr1 |= ((3UL & value) << ADC_CR1_RES_Pos);

    regs->CR1 = cr1;
  }
}

void adc_set_samplerate(const uint8_t adc, const uint8_t channel, const adc_samplerate_t value) {
  /* Check that the cycle count is valid */
  switch (value) {
    case c003:
    case c015:
    case c028:
    case c056:
    case c084:
    case c112:
    case c144:
    case c480: break;

    default: return;
  }

  /* Check that the ADC and channel exist */
  if ((adc > ADC_NUM) || (channel > 18U)) {
    return;
  } else {
    struct adc *regs = ADC_(adc);

    /* Cautiously change samplerate */
    uint8_t sel = (channel <= 9U) ? 1U : 0U;
    volatile uint32_t smpr = regs->SMPR[sel];
    smpr &= ~(7UL << ((channel - (10UL * (1U-sel))) * 3U)); // Clear first
    smpr |= ((7UL & value) << ((channel - (10UL * (1U-sel))) * 3U));

    regs->SMPR[sel] = smpr;
  }
}

void adc_set_modes(const uint8_t adc, const struct adc_modes config) {
  /* Check that the ADC and channel exist */
  if (adc > ADC_NUM) {
    return;
  } else {
    struct adc *regs = ADC_(adc);

    /* Cautiously set modes on CR1 */
    volatile uint32_t cr1 = regs->CR1;
    cr1 &= ~(ADC_CR1_SCAN_Msk |
              ADC_CR1_DISCEN_Msk); // Clear first
    cr1 |= (((1UL & config.SCAN) << ADC_CR1_SCAN_Pos) |
             ((1UL & config.DISC) << ADC_CR1_DISCEN_Pos));

    regs->CR1 = cr1;

    /* Cautiously set modes on CR2 */
    volatile uint32_t cr2 = regs->CR2;
    cr2 &= ~(ADC_CR2_CONT_Msk |
              ADC_CR2_DMA_Msk |
              ADC_CR2_DDS_Msk); // Clear first
    cr2 |= (((1UL & config.CONT) << ADC_CR2_CONT_Pos) |
             ((1UL & config.DMA) << ADC_CR2_DMA_Pos) |
             ((1UL & config.DDS) << ADC_CR2_DDS_Pos));

    regs->CR2 = cr2;
  }
}

void adc_set_seq(const uint8_t adc, const uint8_t* seq, const uint8_t count) {
  /* Check that the ADC and channel exist */
  if (adc > ADC_NUM) {
    return;
  } else {
    struct adc *regs = ADC_(adc);

    /* Cautiously apply new sequence */
    volatile uint32_t sqr[3] = { 0 };

    sqr[0] |= (15UL & count) << ADC_SQR1_L_Pos;

    for (uint8_t i = 0U; i < 16U; i++) {
      uint8_t sel = (i < 6U) ? 2U : ((i < 12U) ? 1U : 0U);
      sqr[sel] |= ((31UL & seq[i]) << ((i - (6U * (2U-sel))) * 5U));
    }

    regs->SQR[0] = sqr[0];
    regs->SQR[1] = sqr[1];
    regs->SQR[2] = sqr[2];
  }
}

void adc_on(const uint8_t adc) {
  /* Check that the ADC and channel exist */
  if (adc > ADC_NUM) {
    return;
  } else {
    struct adc *regs = ADC_(adc);

    /* Power on */
    regs->CR2 |= ADC_CR2_ADON_Msk;

    /* Small delay */
    volatile uint32_t dummy_read;
    dummy_read = regs->CR2;
    dummy_read = regs->CR2;

    /* Start ADC conversion */
    regs->CR2 |= ADC_CR2_SWSTART_Msk;
  }
}

void adc_off(const uint8_t adc) {
  /* Check that the ADC and channel exist */
  if (adc > ADC_NUM) {
    return;
  } else {
    struct adc *regs = ADC_(adc);

    /* Power off */
    regs->CR2 &= ~(ADC_CR2_ADON_Msk);
  }
}

uint16_t adc_read(const uint8_t adc) {
  /* Check that the ADC and channel exist */
  if (adc > ADC_NUM) {
    return 0U;
  } else {
    struct adc *regs = ADC_(adc);

    /* Wait for conversion */
    while (! (1UL & (regs->SR >> ADC_SR_EOC_Pos)));
    uint16_t result = 65535U & regs->DR;

    regs->SR &= ~ADC_SR_EOC_Pos; // Clear EOC flag

    return result;
  }
}
