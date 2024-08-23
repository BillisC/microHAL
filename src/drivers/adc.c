/** @file adc.c
 *  @brief Function defines for the ADC_ driver.
 *
 *  This file contains all of the function definitions
 *  declared in adc.h.
 *
 *  @author Vasileios Ch. (BillisC)
 *  @bug None, yet.
 */

/* -- Includes -- */
#include "adc.h"

static inline _Bool verifyADC(const adc_peripheral_t adc) {
  /* Check that the ADC_ exists */
  if ((adc >= 0U) && (adc < ADC_PERIPH_LEN)) {
    return TRUE;
  } else {
    return FALSE;
  }
}

void adc_set_prescaler(const adc_prescaler_t value) {
  /* Check that the divider is valid */
  switch (value) {
    case ADC_PRESCALER_DIV2:
    case ADC_PRESCALER_DIV4:
    case ADC_PRESCALER_DIV6:
    case ADC_PRESCALER_DIV8: break;

    default: return;
  }

  struct ADCCommonRegs *regs = ADC_COMMON;

  /* Apply prescaler value */
  REG32 ccr = regs->CCR;
  ccr &= ~(ADC_CCR_ADCPRE_Msk); // Clear first
  ccr |= ((3UL & value) << ADC_CCR_ADCPRE_Pos);

  regs->CCR = ccr;
}

void adc_set_resolution(const adc_peripheral_t adc, const adc_res_t value) {
  /* Check that the resolution is valid */
  switch (value) {
    case ADC_RES_B06:
    case ADC_RES_B08:
    case ADC_RES_B10:
    case ADC_RES_B12: break;

    default: return;
  }

  if (!verifyADC(adc)) {
    return;
  } else {
    struct ADCRegs *regs = ADC_(adc);

    /* Change resolution */
    REG32 cr1 = regs->CR1;
    cr1 &= ~(ADC_CR1_RES_Msk); // Clear first
    cr1 |= ((3UL & value) << ADC_CR1_RES_Pos);

    regs->CR1 = cr1;
  }
}

void adc_set_samplerate(const adc_peripheral_t adc, const uint8_t channel,
                        const adc_samplerate_t value) {
  /* Check that the cycle count is valid */
  switch (value) {
    case ADC_SAMPLERATE_C003:
    case ADC_SAMPLERATE_C015:
    case ADC_SAMPLERATE_C028:
    case ADC_SAMPLERATE_C056:
    case ADC_SAMPLERATE_C084:
    case ADC_SAMPLERATE_C112:
    case ADC_SAMPLERATE_C144:
    case ADC_SAMPLERATE_C480: break;

    default: return;
  }

  if (!verifyADC(adc)) {
    return;
  } else if (channel > 18U) {
    return;
  } else {
    struct ADCRegs *regs = ADC_(adc);

    /* Change samplerate */
    uint8_t sel = (channel <= 9U) ? 1U : 0U;
    REG32 smpr = regs->SMPR[sel];
    smpr &= ~(7UL << ((channel - (10UL * (1U - sel))) * 3U)); // Clear first
    smpr |= ((7UL & value) << ((channel - (10UL * (1U - sel))) * 3U));

    regs->SMPR[sel] = smpr;
  }
}

void adc_set_modes(const adc_peripheral_t adc, const struct ADCModes config) {
  if (!verifyADC(adc)) {
    return;
  } else {
    struct ADCRegs *regs = ADC_(adc);

    /* Set modes on CR1 */
    REG32 cr1 = regs->CR1;
    cr1 &= ~(ADC_CR1_SCAN_Msk | ADC_CR1_DISCEN_Msk); // Clear first
    cr1 |= ((config.SCAN << ADC_CR1_SCAN_Pos) |
            (config.DISC << ADC_CR1_DISCEN_Pos));

    regs->CR1 = cr1;

    /* Set modes on CR2 */
    REG32 cr2 = regs->CR2;
    cr2 &= ~(ADC_CR2_CONT_Msk | ADC_CR2_DMA_Msk | ADC_CR2_DDS_Msk);
    cr2 |= ((config.CONT << ADC_CR2_CONT_Pos) |
            (config.DMA << ADC_CR2_DMA_Pos) | (config.DDS << ADC_CR2_DDS_Pos));

    regs->CR2 = cr2;
  }
}

void adc_set_seq(const adc_peripheral_t adc, const uint8_t *seq,
                 const uint8_t count) {
  if (!verifyADC(adc)) {
    return;
  } else {
    struct ADCRegs *regs = ADC_(adc);

    /* Apply new sequence */
    REG32 sqr[3] = {0};

    sqr[0] |= (15UL & ((count < 16U) ? count : 0U)) << ADC_SQR1_L_Pos;

    for (uint8_t i = 0U; i < 16U; i++) {
      if (seq[i] > 18U) {
        continue;
      } else {
        uint8_t sel = (i < 6U) ? 2U : ((i < 12U) ? 1U : 0U);
        sqr[sel] |= ((31UL & seq[i]) << ((i - (6U * (2U - sel))) * 5U));
      }
    }

    regs->SQR[0] = sqr[0];
    regs->SQR[1] = sqr[1];
    regs->SQR[2] = sqr[2];
  }
}

void adc_on(const adc_peripheral_t adc) {
  if (!verifyADC(adc)) {
    return;
  } else {
    struct ADCRegs *regs = ADC_(adc);

    /* Power on */
    regs->CR2 |= ADC_CR2_ADON_Msk;

    /* Small delay */
    REG32 dummy_read;
    dummy_read = regs->CR2;
    dummy_read = regs->CR2;

    /* Start ADC_ conversion */
    regs->CR2 |= ADC_CR2_SWSTART_Msk;
  }
}

void adc_off(const adc_peripheral_t adc) {
  if (!verifyADC(adc)) {
    return;
  } else {
    struct ADCRegs *regs = ADC_(adc);

    /* Power off */
    regs->CR2 &= ~(ADC_CR2_ADON_Msk);
  }
}

uint16_t adc_read(const adc_peripheral_t adc) {
  if (!verifyADC(adc)) {
    return 0U;
  } else {
    struct ADCRegs *regs = ADC_(adc);

    /* Wait for conversion */
    while (!(1UL & (regs->SR >> ADC_SR_EOC_Pos))) {};
    uint16_t result = 65535U & regs->DR;

    regs->SR &= ~ADC_SR_EOC_Pos; // Clear EOC flag

    return result;
  }
}
