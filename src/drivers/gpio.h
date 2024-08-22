/** @file gpio.h
 *  @brief Function prototypes for the GPIO driver.
 *
 *  This file contains all of the enums, macros, and
 *  function prototypes required for a functional GPIO
 *  driver.
 *
 *  @author Vasileios Ch. (BillisC)
 *  @bug None, yet.
 */

#ifndef GPIO_H
#define GPIO_H

/* -- Includes -- */
#include <stdint.h>
#include "stm32f4xx.h"

/* -- Structs -- */
/**
 *  @brief Contains GPIO registers
 */
struct __attribute__((packed)) GPIORegs {
  volatile uint32_t MODER;
  volatile uint32_t OTYPER;
  volatile uint32_t OSPEEDR;
  volatile uint32_t PUPDR;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSSR;
  volatile uint32_t LCKR;
  volatile uint32_t AFR[2];
};

_Static_assert((sizeof(struct GPIORegs)) == (sizeof(uint32_t) * 10U),
               "GPIO register struct size mismatch. Is it aligned?");

#ifndef UTEST
#define GPIO(bank)                                                             \
  (struct GPIORegs *)(GPIOA_BASE + (0x400U * ((uint8_t)bank - (uint8_t)'A')))
#else
extern struct GPIORegs *GPIO(const uint8_t bank);
#endif

/* -- Enums -- */
typedef enum gp_bank {
#ifdef GPIOA_BASE
  GP_BANK_A = (uint8_t)'A',
#endif
#ifdef GPIOB_BASE
  GP_BANK_B = (uint8_t)'B',
#endif
#ifdef GPIOC_BASE
  GP_BANK_C = (uint8_t)'C',
#endif
#ifdef GPIOD_BASE
  GP_BANK_D = (uint8_t)'D',
#endif
#ifdef GPIOE_BASE
  GP_BANK_E = (uint8_t)'E',
#endif
#ifdef GPIOF_BASE
  GP_BANK_F = (uint8_t)'F',
#endif
#ifdef GPIOG_BASE
  GP_BANK_G = (uint8_t)'G',
#endif
#ifdef GPIOH_BASE
  GP_BANK_H = (uint8_t)'H',
#endif
#ifdef GPIOI_BASE
  GP_BANK_I = (uint8_t)'I',
#endif
#ifdef GPIOJ_BASE
  GP_BANK_J = (uint8_t)'J',
#endif
#ifdef GPIOK_BASE
  GP_BANK_K = (uint8_t)'K',
#endif
  GP_BANK_LEN // This should be substracted with 'A'
} gp_bank_t;

/**
 *  @brief Available GPIO modes
 */
typedef enum gp_dir {
  GP_DIR_IN = 0x00,
  GP_DIR_OU = 0x01,
  GP_DIR_AL = 0x02,
  GP_DIR_AN = 0x03
} gp_dir_t;

/**
 *  @brief Available GPIO output types
 */
typedef enum gp_otype {
  GP_OTYPE_PP = 0x00,
  GP_OTYPE_OD = 0x01
} gp_otype_t;

/**
 *  @brief Available GPIO output speeds
 */
typedef enum gp_speed {
  GP_SPEED_LOW = 0x00,
  GP_SPEED_MED = 0x01,
  GP_SPEED_FAS = 0x02,
  GP_SPEED_HIG = 0x03
} gp_speed_t;

/**
 *  @brief Available GPIO pull states
 */
typedef enum gp_pupd {
  GP_PUPD_NONE = 0x00,
  GP_PUPD_PLUP = 0x01,
  GP_PUPD_PLDO = 0x02,
} gp_pupd_t;

/**
 * @brief Sets the GPIO pin to the desired mode.
 *
 * The available directions for the GPIO pins are specified
 * in the gp_dir_t enum. Any other value will be ignored.
 *
 * @param bank The GPIO bank
 * @param pin The GPIO pin
 * @param dir The pin mode
 * @return None
 */
void gp_set_direction(const gp_bank_t bank, const uint8_t pin,
                      const gp_dir_t dir);

/**
 * @brief Sets the GPIO output pin to the desired type.
 *
 * The available output types for the GPIO pins are specified
 * in the gp_otype_t enum. Any other value will be ignored.
 *
 * @param bank The GPIO bank
 * @param pin The GPIO pin
 * @param type The pin type
 * @return None
 */
void gp_set_output_type(const gp_bank_t bank, const uint8_t pin,
                        const gp_otype_t type);

/**
 * @brief Sets the GPIO output pin to the desired speed.
 *
 * The available speeds for the GPIO output pins are specified
 * in the gp_speed_t enum. Any other value will be ignored.
 *
 * @param bank The GPIO bank
 * @param pin The GPIO pin
 * @param speed The pin speed
 * @return None
 */
void gp_set_speed(const gp_bank_t bank, const uint8_t pin,
                  const gp_speed_t speed);

/**
 * @brief Sets the GPIO input pin to the desired state.
 *
 * The available pull-up/pull-down states for the GPIO pins
 * are specified in the gp_pupdr_t enum. Any other value will
 * be ignored.
 *
 * @param bank The GPIO bank
 * @param pin The GPIO pin
 * @param poopdr The pin state
 * @return None
 */
void gp_set_pupd(const gp_bank_t bank, const uint8_t pin,
                 const gp_pupd_t poopdr);

/**
 * @brief Sets the GPIO output pin to the desired value.
 *
 * Allowed values are either TRUE(1) or FALSE(0). Any other
 * value will be ignored.
 *
 * @param bank The GPIO bank
 * @param pin The GPIO pin
 * @param value The pin value
 * @return None
 */
void gp_set_val(const gp_bank_t bank, const uint8_t pin, const _Bool value);

/**
 * @brief Reads the GPIO input pin value.
 *
 * @param bank The GPIO bank
 * @param pin The GPIO pin
 * @return The current state of the pin
 */
uint8_t gp_read_val(const gp_bank_t bank, const uint8_t pin);

/**
 * @brief Sets the alternate function of the GPIO pin
 *
 * @param bank The GPIO bank
 * @param pin The GPIO pin
 * @param The alternate function number
 * @return None
 */
void gp_set_af(const gp_bank_t bank, const uint8_t pin, const uint8_t af);

#endif /* GPIO_H */
