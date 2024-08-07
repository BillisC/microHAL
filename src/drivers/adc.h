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

#define ADC_NUM 3U

/* -- Includes -- */
#include <stdint.h>
#include "stm32f4xx.h"

/* -- Structs -- */
struct __attribute__((packed)) adc {
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

_Static_assert((sizeof(struct adc)) == (sizeof(uint32_t) * 20U),
               "ADC register struct size mismatch. Is it aligned?");

struct __attribute__((packed)) adc_common {
  volatile uint32_t CSR;
  volatile uint32_t CCR;
  volatile uint32_t CDR;
};

_Static_assert((sizeof(struct adc_common)) == (sizeof(uint32_t) * 3U),
               "ADC Common register struct size mismatch. Is it aligned?");

#define ADC_(number) (struct adc*) (ADC1_BASE + (0x100U * ((uint8_t)number - 1U)))
#define ADC_COMMON (struct adc_common*) (ADC123_COMMON_BASE)

struct __attribute__((packed)) adc_modes {
  volatile uint8_t DMA : 1;
  volatile uint8_t DDS : 1;
  volatile uint8_t CONT: 1;
  volatile uint8_t DISC: 1; // One stop per conversion
  volatile uint8_t SCAN: 1;
};

_Static_assert((sizeof(struct adc_modes)) == (sizeof(uint8_t) * 1U),
               "ADC Configuration struct size mismatch. Is it aligned?");

/* -- Enums -- */
typedef enum adc_res {
  b12 = 0x00, // >= 15 ADCCLK cycles
  b10 = 0x01, // >= 13 ADCCLK cycles
  b08 = 0x02, // >= 11 ADCCLK cycles
  b06 = 0x03  // >= 9 ADCCLK cycles
} adc_res_t;

typedef enum adc_trigger {
  none = 0x00,
  rise = 0x01,
  fall = 0x02,
  both = 0x03
} adc_trigger_t;

typedef enum adc_samplerate {
  c003 = 0x00,
  c015 = 0x01,
  c028 = 0x02,
  c056 = 0x03,
  c084 = 0x04,
  c112 = 0x05,
  c144 = 0x06,
  c480 = 0x07
} adc_samplerate_t;

typedef enum adc_prescaler {
  div2 = 0x00,
  div4 = 0x01,
  div6 = 0x02,
  div8 = 0x03,
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
  * @param adc The selected ADC (1..ADC_NUM)
  * @param value The resolution of the ADC conversions
  * @return None
  */
void adc_set_resolution(const uint8_t adc, const adc_res_t value);

/**
  * @brief Sets the ADC sampling rate to the specified value.
  *
  * The available sampling rates for the ADC channel reads are
  * specified in the adc_res_t enum (in clock cycles). Any other
  * value will be ignored.
  *
  * @param adc The selected ADC (1..ADC_NUM)
  * @param channel The selected channel (0..19)
  * @param value The clock cycles of the ADC conversions
  * @return None
  */
void adc_set_samplerate(const uint8_t adc, const uint8_t channel, const adc_samplerate_t value);

/**
  * @brief Sets the ADC modes according to the configuration.
  *
  * The configuration values are specified within the adc_config
  * struct. Some modes may not work as expected yet.
  *
  * @param adc The selected ADC (1..ADC_NUM)
  * @param config The ADC configuration
  * @return None
  */
void adc_set_modes(const uint8_t adc, const struct adc_modes config);

/**
  * @brief Sets the ADC conversion sequence to the specified order.
  *
  * The sequence consists of 16 5-bit elements. Bits 6..8 will be
  * ignored.
  *
  * @param adc The selected ADC (1..ADC_NUM)
  * @param seq Pointer to channel conversion sequence array
  * @param count The total amount of conversions
  * @return None
  */
void adc_set_seq(const uint8_t adc, const uint8_t* seq, const uint8_t count);

/**
  * @brief Starts the ADC conversion.
  *
  * The ADC will be powered on upon calling this command and
  * start the conversion procedure as configured. Dummy
  * reads are included.
  *
  * @param adc The selected ADC (1..ADC_NUM)
  * @return None
  */
void adc_on(const uint8_t adc);

/**
  * @brief Stops the ADC conversion.
  *
  * The ADC will be powered off upon calling this command
  * and instantly stop the conversion procedure.
  *
  * @param adc The selected ADC (1..ADC_NUM)
  * @return None
  */
void adc_off(const uint8_t adc);

/**
  * @brief Reads the last ADC conversion result.
  *
  * @param adc The selected ADC (1..ADC_NUM)
  * @return The conversion result
  */
uint16_t adc_read(const uint8_t adc);

#endif
