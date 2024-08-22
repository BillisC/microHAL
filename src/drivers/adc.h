/** @file adc.h
 *  @brief Function prototypes for the ADC driver.
 *
 *  This file contains all of the enums, macros, and
 *  function prototypes required for a functional ADC
 *  driver.
 *
 *  DISCLAIMER: Only for regular channels in single /
 *  continuous / discontinuous modes. Injected channels
 *  may be implemented later.
 *
 *  @author Vasileios Ch. (BillisC)
 *  @bug None, yet.
 */

#ifndef ADC_H
#define ADC_H

/* -- Includes -- */
#include <stdint.h>
#include "stm32f4xx.h"

/* -- Structs -- */
/**
 *  @brief Contains ADC registers
 */
struct __attribute__((packed)) ADCRegs {
  volatile uint32_t SR;
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t SMPR[2];
  volatile uint32_t JOFR[4];
  volatile uint32_t HTR;
  volatile uint32_t LTR;
  volatile uint32_t SQR[3];
  volatile uint32_t JSQR;
  volatile uint32_t JDR[4];
  volatile uint32_t DR;
};

_Static_assert((sizeof(struct ADCRegs)) == (sizeof(uint32_t) * 20U),
               "ADC register struct size mismatch. Is it aligned?");

/**
 *  @brief Contains ADC common registers
 */
struct __attribute__((packed)) ADCCommonRegs {
  volatile uint32_t CSR;
  volatile uint32_t CCR;
  volatile uint32_t CDR;
};

_Static_assert((sizeof(struct ADCCommonRegs)) == (sizeof(uint32_t) * 3U),
               "ADC Common register struct size mismatch. Is it aligned?");

#ifndef UTEST
#define ADC_(NUM)  (struct ADCRegs *)(ADC1_BASE + (0x100UL * ((uint8_t)NUM)))
#define ADC_COMMON (struct ADCCommonRegs *)(ADC123_COMMON_BASE)
#else
extern struct ADCRegs *ADC_(const uint8_t number);
extern struct ADCCommonRegs *ADC_COMMON;
#endif

/**
 *  @brief Contains ADC conversion modes
 */
struct __attribute__((packed)) ADCModes {
  volatile _Bool DMA  : 1;
  volatile _Bool DDS  : 1;
  volatile _Bool CONT : 1;
  volatile _Bool DISC : 1; // One stop per conversion
  volatile _Bool SCAN : 1;
};

_Static_assert((sizeof(struct ADCModes)) == (sizeof(uint8_t) * 1U),
               "ADC Configuration struct size mismatch. Is it aligned?");

/* -- Enums -- */
typedef enum adc_peripheral {
#ifdef ADC1_BASE
  ADC_PERIPH_1 = 0x00,
#endif
#ifdef ADC2_BASE
  ADC_PERIPH_2 = 0x01,
#endif
#ifdef ADC3_BASE
  ADC_PERIPH_3 = 0x02,
#endif
  ADC_PERIPH_LEN
} adc_peripheral_t;

typedef enum adc_res {
  ADC_RES_B12 = 0x00, // >= 15 ADCCLK cycles
  ADC_RES_B10 = 0x01, // >= 13 ADCCLK cycles
  ADC_RES_B08 = 0x02, // >= 11 ADCCLK cycles
  ADC_RES_B06 = 0x03  // >= 9 ADCCLK cycles
} adc_res_t;

typedef enum adc_trigger {
  ADC_TRIGGER_NONE = 0x00,
  ADC_TRIGGER_RISE = 0x01,
  ADC_TRIGGER_FALL = 0x02,
  ADC_TRIGGER_BOTH = 0x03
} adc_trigger_t;

typedef enum adc_samplerate {
  ADC_SAMPLERATE_C003 = 0x00,
  ADC_SAMPLERATE_C015 = 0x01,
  ADC_SAMPLERATE_C028 = 0x02,
  ADC_SAMPLERATE_C056 = 0x03,
  ADC_SAMPLERATE_C084 = 0x04,
  ADC_SAMPLERATE_C112 = 0x05,
  ADC_SAMPLERATE_C144 = 0x06,
  ADC_SAMPLERATE_C480 = 0x07
} adc_samplerate_t;

typedef enum adc_prescaler {
  ADC_PRESCALER_DIV2 = 0x00,
  ADC_PRESCALER_DIV4 = 0x01,
  ADC_PRESCALER_DIV6 = 0x02,
  ADC_PRESCALER_DIV8 = 0x03,
} adc_prescaler_t;

/**
 * @brief Sets the ADC Prescaler divider to the specified value.
 *
 * The available dividers for the ADC Prescaler are specified in
 * the adc_prescaler_t enum. Any other value will be ignored.
 *
 * @param value The prescaler divider value
 * @return None
 */
void adc_set_prescaler(const adc_prescaler_t value);

/**
 * @brief Sets the ADC resolution to the specified value.
 *
 * The available resolutions for the ADC channel reads are
 * specified in the adc_res_t enum. Any other value will be
 * ignored.
 *
 * @param adc The selected ADC
 * @param value The resolution of the ADC conversions
 * @return None
 */
void adc_set_resolution(const adc_peripheral_t adc, const adc_res_t value);

/**
 * @brief Sets the ADC sampling rate to the specified value.
 *
 * The available sampling rates for the ADC channel reads are
 * specified in the adc_res_t enum (in clock cycles). Any other
 * value will be ignored.
 *
 * @param adc The selected ADC
 * @param channel The selected channel (0..19)
 * @param value The clock cycles of the ADC conversions
 * @return None
 */
void adc_set_samplerate(const adc_peripheral_t adc, const uint8_t channel,
                        const adc_samplerate_t value);

/**
 * @brief Sets the ADC modes according to the configuration.
 *
 * The configuration values are specified within the adc_config
 * struct. Some modes may not work as expected yet.
 *
 * @param adc The selected ADC
 * @param config The ADC configuration
 * @return None
 */
void adc_set_modes(const adc_peripheral_t adc, const struct ADCModes config);

/**
 * @brief Sets the ADC conversion sequence to the specified order.
 *
 * The sequence consists of 16 5-bit elements. Bits 6..8 will be
 * ignored.
 *
 * @param adc The selected ADC
 * @param seq Pointer to channel conversion sequence array
 * @param count The total amount of conversions
 * @return None
 */
void adc_set_seq(const adc_peripheral_t adc, const uint8_t *seq,
                 const uint8_t count);

/**
 * @brief Starts the ADC conversion.
 *
 * The ADC will be powered on upon calling this command and
 * start the conversion procedure as configured. Dummy
 * reads are included.
 *
 * @param adc The selected ADC
 * @return None
 */
void adc_on(const adc_peripheral_t adc);

/**
 * @brief Stops the ADC conversion.
 *
 * The ADC will be powered off upon calling this command
 * and instantly stop the conversion procedure.
 *
 * @param adc The selected ADC
 * @return None
 */
void adc_off(const adc_peripheral_t adc);

/**
 * @brief Reads the last ADC conversion result.
 *
 * @param adc The selected ADC
 * @return The conversion result
 */
uint16_t adc_read(const adc_peripheral_t adc);

#endif
