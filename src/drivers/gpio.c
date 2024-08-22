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

static inline _Bool verifyGPIO(const gp_bank_t bank, const uint8_t pin) {
  switch (bank) {
#ifdef GPIOA_BASE
    case GP_BANK_A:
#endif
#ifdef GPIOB_BASE
    case GP_BANK_B:
#endif
#ifdef GPIOC_BASE
    case GP_BANK_C:
#endif
#ifdef GPIOD_BASE
    case GP_BANK_D:
#endif
#ifdef GPIOE_BASE
    case GP_BANK_E:
#endif
#ifdef GPIOF_BASE
    case GP_BANK_F:
#endif
#ifdef GPIOG_BASE
    case GP_BANK_G:
#endif
#ifdef GPIOH_BASE
    case GP_BANK_H:
#endif
#ifdef GPIOI_BASE
    case GP_BANK_I:
#endif
#ifdef GPIOJ_BASE
    case GP_BANK_J:
#endif
#ifdef GPIOK_BASE
    case GP_BANK_K:
#endif
      break;

    default: return FALSE;
  };

  if (pin > 15U) {
    return FALSE;
  } else {
    return TRUE;
  }
}

void gp_set_direction(const gp_bank_t bank, const uint8_t pin,
                      const gp_dir_t dir) {
  /* Check that the direction is valid */
  switch (dir) {
    case GP_DIR_IN:
    case GP_DIR_OU:
    case GP_DIR_AL:
    case GP_DIR_AN: break;

    default: return;
  };

  if (!verifyGPIO(bank, pin)) {
    return;
  } else {
    struct GPIORegs *regs = GPIO(bank);

    /* Change the pin direction */
    volatile uint32_t moder = regs->MODER;
    moder &= ~(3UL << (pin * 2U)); // Clear first
    moder |= ((3UL & dir) << (pin * 2U));

    regs->MODER = moder;
  }
}

void gp_set_output_type(const gp_bank_t bank, const uint8_t pin,
                        const gp_otype_t type) {
  /* Check that the type exists */
  if ((type != GP_OTYPE_PP) && (type != GP_OTYPE_OD)) {
    return;
  } else if (!verifyGPIO(bank, pin)) {
    return;
  } else {
    struct GPIORegs *regs = GPIO(bank);

    /* Change the pin output type */
    volatile uint32_t otyper = regs->OTYPER;
    otyper &= ~(1UL << pin); // Clear first
    otyper |= ((1UL & type) << pin);

    regs->OTYPER = otyper;
  }
}

void gp_set_speed(const gp_bank_t bank, const uint8_t pin,
                  const gp_speed_t speed) {
  /* Check that the speed is valid */
  switch (speed) {
    case GP_SPEED_LOW:
    case GP_SPEED_MED:
    case GP_SPEED_FAS:
    case GP_SPEED_HIG: break;

    default: return;
  };

  if (!verifyGPIO(bank, pin)) {
    return;
  } else {
    struct GPIORegs *regs = GPIO(bank);

    /* Change the pin output speed */
    volatile uint32_t ospeedr = regs->OSPEEDR;
    ospeedr &= ~(3UL << (pin * 2U)); // Clear first
    ospeedr |= ((3UL & speed) << (pin * 2U));

    regs->OSPEEDR = ospeedr;
  }
}

void gp_set_pupd(const gp_bank_t bank, const uint8_t pin,
                 const gp_pupd_t poopdr) {
  /* Check that the state value is valid */
  switch (poopdr) {
    case GP_PUPD_NONE:
    case GP_PUPD_PLUP:
    case GP_PUPD_PLDO: break;

    default: return;
  };

  if (!verifyGPIO(bank, pin)) {
    return;
  } else {
    struct GPIORegs *regs = GPIO(bank);

    /* Set pull-up / pull-down state of pin */
    volatile uint32_t pupdr = regs->PUPDR;
    pupdr &= ~(3UL << (pin * 2U)); // Clear first
    pupdr |= ((3UL & poopdr) << (pin * 2U));

    regs->PUPDR = pupdr;
  }
}

void gp_set_val(const gp_bank_t bank, const uint8_t pin, const _Bool value) {
  if (!verifyGPIO(bank, pin)) {
    return;
  } else {
    /* Check that the value is valid */
    struct GPIORegs *regs = GPIO(bank);

    /* Set output pin state */
    regs->BSSR = (1UL << (pin + (16U * (1 - value))));
  }
}

uint8_t gp_read_val(const gp_bank_t bank, const uint8_t pin) {
  if (!verifyGPIO(bank, pin)) {
    return 0U;
  } else {
    struct GPIORegs *regs = GPIO(bank);
    return (1U & (regs->IDR >> pin));
  }
}

void gp_set_af(const gp_bank_t bank, const uint8_t pin, const uint8_t af) {
  /* Check that the AF value is valid */
  if (!(af <= 15U)) {
    return;
  } else if (!verifyGPIO(bank, pin)) {
    return;
  } else {
    struct GPIORegs *regs = GPIO(bank);

    /* Set the alternate function to the correct register */
    uint8_t sel = (pin <= 7U) ? 0U : 1U;
    volatile uint32_t afr = regs->AFR[sel];
    afr &= ~(15U << ((pin - (8U * sel)) * 4U)); // Clear first
    afr |= ((15U & af) << ((pin - (8U * sel)) * 4U));

    regs->AFR[sel] = afr;
  }
}
