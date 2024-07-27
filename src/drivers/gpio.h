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

/* -- Structs -- */
struct __attribute__((packed)) gpio {
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

_Static_assert((sizeof(struct gpio)) == (sizeof(uint32_t) * 10U), 
               "GPIO struct size mismatch. Is it aligned?");

#define GPIO(bank) (struct gpio*) (0x40020000U + (0x400U * ((uint8_t)bank - (uint8_t)'A')))

/* -- Enums -- */
typedef enum gp_dir {
  in  = 0x00,
  ou  = 0x01,
  al  = 0x02,
  an  = 0x03
} gp_dir_t;

typedef enum gp_otype {
  pp  = 0x00,
  od  = 0x01
} gp_otype_t;

typedef enum gp_speed {
  low = 0x00,
  med = 0x01,
  fas = 0x02,
  hig = 0x03
} gp_speed_t;

typedef enum gp_pupdr {
  no  = 0x00,
  pu  = 0x01,
  pd  = 0x02,
} gp_pupdr_t;

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
void gp_set_direction(const char bank, const uint8_t pin, const gp_dir_t dir);

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
void gp_set_output_type(const char bank, const uint8_t pin, const gp_otype_t type);

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
void gp_set_speed(const char bank, const uint8_t pin, const gp_speed_t speed);

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
void gp_set_pupd(const char bank, const uint8_t pin, const gp_pupdr_t poopdr);

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
void gp_set_val(const char bank, const uint8_t pin, const uint8_t value);

/**
  * @brief Reads the GPIO input pin value.
  *
  * @param bank The GPIO bank
  * @param pin The GPIO pin
  * @return The current state of the pin
  */
uint8_t gp_read_val(const char bank, const uint8_t pin);

#endif /* GPIO_H */
