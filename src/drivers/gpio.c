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
#include "gpio.h"
#include "defines.h"

void gp_set_direction(const char bank, const uint8_t pin, const gp_dir_t dir) {
  /* Check that the direction is valid */
  switch (dir) {
    case in:
    case ou:
    case al:
    case an: break;

    default: return;
  };

  /* Change the pin direction */
  struct gpio *regs = GPIO(bank);
  regs->MODER &= ~(3U << (pin * 2)); // Clear first
  regs->MODER |= ((3U & dir) << (pin * 2));
}

void gp_set_output_type(const char bank, const uint8_t pin, const gp_otype_t type) {
  /* Check that the type is valid */
  switch (type) {
    case pp:
    case od: break;

    default: return;
  };

  /* Change the pin output type */
  struct gpio *regs = GPIO(bank);
  regs->OTYPER &= ~(1U << pin); // Clear first
  regs->OTYPER |= ((1U & type) << pin);
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

  /* Change the pin output speed */
  struct gpio *regs = GPIO(bank);
  regs->OSPEEDR &= ~(3U << (pin * 2)); // Clear first
  regs->OSPEEDR |= ((3U & speed) << (pin * 2));
}

void gp_set_pupd(const char bank, const uint8_t pin, const gp_pupdr_t poopdr) {
  /* Check that the state value is valid */
  switch (poopdr) {
    case no:
    case pu:
    case pd: break;

    default: return;
  };

  /* Set pull-up / pull-down state of pin */
  struct gpio *regs = GPIO(bank);
  regs->PUPDR &= ~(3U << (pin * 2)); // Clear first
  regs->PUPDR |= ((3U & poopdr) << (pin * 2));
}

void gp_set_val(const char bank, const uint8_t pin, const uint8_t value) {
  /* Check that the value is valid */
  if ((value != TRUE) && (value != FALSE)) {
    return;
  } else {
    /* Set output pin state */
    struct gpio *regs = GPIO(bank);
    regs->BSSR = (1U << (pin + (16U * (1 - value))));
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
    /* Set the alternate function to the correct register */
    struct gpio *regs = GPIO(bank);
    uint8_t sel = (pin <= 7U) ? 0 : 1;
    regs->AFR[sel] &= ~(15U << ((pin - (8U * sel)) * 4)); // Clear first
    regs->AFR[sel] |= ((15U & af) << ((pin - (8U * sel)) * 4));
  }
}
