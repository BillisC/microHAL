/** @file adc.h
 *  @brief Function prototypes for the ADC driver.
 *
 *  This file contains all of the enums, macros, and
 *  function prototypes required for a functional ADC
 *  driver.
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
struct __attribute__((packed)) adc {
  volatile uint32_t SR;
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t SMPR1;
  volatile uint32_t SMPR2;
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

/* -- Enums -- */
typedef enum adc_quality {
  b12 = 0x00, // >= 15 ADCCLK cycles
  b10 = 0x01, // >= 13 ADCCLK cycles
  b08 = 0x02, // >= 11 ADCCLK cycles
  b06 = 0x03  // >= 9 ADCCLK cycles
} adc_quality_t;

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

#endif
