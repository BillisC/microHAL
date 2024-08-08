/** @file gpio.c
 *  @brief Function defines for the GPIO driver.
 *
 *  This file contains all of the function definitions
 *  declared in gpio.h.
 *
 *  @author Vasileios Ch. (BillisC)
 *  @bug None, yet.
 */

/* -- Includes -- */
#include "defines.h"
#include "gpio.h"

void gp_set_direction(const char bank, const uint8_t pin, const gp_dir_t dir) {
  /* Check that the direction is valid */
  switch (dir) {
    case in:
    case ou:
    case al:
    case an: break;

    default: return;
  };

  struct gpio *regs = GPIO(bank);

  /* Change the pin direction */
  volatile uint32_t moder = regs->MODER;
  moder &= ~(3UL << (pin * 2U)); // Clear first
  moder |= ((3UL & dir) << (pin * 2U));

  regs->MODER = moder;
}

void gp_set_output_type(const char bank, const uint8_t pin,
                        const gp_otype_t type) {
  /* Check that the type is valid */
  if ((type != pp) && (type != od)) {
    return;
  } else {
    struct gpio *regs = GPIO(bank);

    /* Change the pin output type */
    volatile uint32_t otyper = regs->OTYPER;
    otyper &= ~(1UL << pin); // Clear first
    otyper |= ((1UL & type) << pin);

    regs->OTYPER = otyper;
  }
}

void gp_set_speed(const char bank, const uint8_t pin, const gp_speed_t speed) {
  /* Check that the speed is valid */
  switch (speed) {
    case low:
    case med:
    case fas:
    case hig: break;

    default: return;
  };

  struct gpio *regs = GPIO(bank);

  /* Change the pin output speed */
  volatile uint32_t ospeedr = regs->OSPEEDR;
  ospeedr &= ~(3UL << (pin * 2U)); // Clear first
  ospeedr |= ((3UL & speed) << (pin * 2U));

  regs->OSPEEDR = ospeedr;
}

void gp_set_pupd(const char bank, const uint8_t pin, const gp_pupdr_t poopdr) {
  /* Check that the state value is valid */
  switch (poopdr) {
    case no:
    case pu:
    case pd: break;

    default: return;
  };

  struct gpio *regs = GPIO(bank);

  /* Set pull-up / pull-down state of pin */
  volatile uint32_t pupdr = regs->PUPDR;
  pupdr &= ~(3UL << (pin * 2U)); // Clear first
  pupdr |= ((3UL & poopdr) << (pin * 2U));

  regs->PUPDR = pupdr;
}

void gp_set_val(const char bank, const uint8_t pin, const uint8_t value) {
  /* Check that the value is valid */
  if ((value != TRUE) && (value != FALSE)) {
    return;
  } else {
    struct gpio *regs = GPIO(bank);

    /* Set output pin state */
    regs->BSSR = (1UL << (pin + (16U * (1 - value))));
  }
}

uint8_t gp_read_val(const char bank, const uint8_t pin) {
  struct gpio *regs = GPIO(bank);
  return (1U & (regs->IDR >> pin));
}

void gp_set_af(const char bank, const uint8_t pin, const uint8_t af) {
  /* Check that the value is valid */
  if (!(af <= 15U)) {
    return;
  } else {
    struct gpio *regs = GPIO(bank);

    /* Set the alternate function to the correct register */
    uint8_t sel = (pin <= 7U) ? 0U : 1U;
    volatile uint32_t afr = regs->AFR[sel];
    afr &= ~(15U << ((pin - (8U * sel)) * 4U)); // Clear first
    afr |= ((15U & af) << ((pin - (8U * sel)) * 4U));

    regs->AFR[sel] = afr;
  }
}
