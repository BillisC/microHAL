/** @file bxcan.h
 *  @brief Function prototypes for the bxCAN interface.
 *
 *  This file contains all of the enums, macros, and
 *  function prototypes required for a functional CAN
 *  interface.
 *
 *  @author Vasileios Ch. (BillisC)
 *  @bug None, yet.
 */

#ifndef BXCAN_H
#define BXCAN_H

/* -- Includes -- */
#include <stdint.h>
#include "stm32f4xx.h"
#include "defines.h"

/* -- Structs -- */
/**
 *  @brief Contains bxCAN Mailbox registers
 */
struct __attribute__((packed)) bxCANMailboxRegs {
  REG32 IR;
  REG32 TR;
  REG32 LR;
  REG32 HR;
};

_Static_assert((sizeof(struct bxCANMailboxRegs)) == (sizeof(uint32_t) * 4U),
               "bxCAN Mailbox register struct size mismatch. Is it aligned?");

/**
 *  @brief Contains bxCAN Filter registers
 */
struct __attribute__((packed)) bxCANFilterRegs {
  REG32 FR1;
  REG32 FR2;
};

_Static_assert((sizeof(struct bxCANFilterRegs)) == (sizeof(uint32_t) * 2U),
               "bxCAN Filter register struct size mismatch. Is it aligned?");

/**
 *  @brief Contains bxCAN registers
 */
struct __attribute__((packed)) bxCANRegs {
  REG32 MCR;
  REG32 MSR;
  REG32 TSR;
  REG32 RF0R;
  REG32 RF1R;
  REG32 IER;
  REG32 ESR;
  REG32 BTR;
  REG32 _reserved1[88];
  struct bxCANMailboxRegs TxMailbox[3];
  struct bxCANMailboxRegs FIFOMailbox[2];
  REG32 _reserved2[12];
  REG32 FMR;
  REG32 FM1R;
  REG32 FS1R;
  REG32 _reserved3;
  REG32 FFA1R;
  REG32 _reserved4;
  REG32 FA1R;
  REG32 _reserved5[8];
  struct bxCANFilterRegs FilterBank[28];
};

_Static_assert((sizeof(struct bxCANRegs)) == (sizeof(uint32_t) * 199U),
               "bxCAN register struct size mismatch. Is it aligned?");

#define CAN(NUM) (struct bxCANRegs *)(CAN1_BASE + (0x400UL * uint8_t(NUM)))

/**
 *  @brief Contains bxCAN baudrate configuration
 */
struct __attribute__((packed)) bxCANBitrateConfig {
  uint8_t TimeSeg1       : 4;  /**< tBS1 = tq x (TimeSeg1 + 1) */
  uint8_t TimeSeg2       : 3;  /**< tBS2 = tq x (TimeSeg2 + 1) */
  uint16_t BaudPrescaler : 10; /**< tq = (BaudPrescaler + 1) x tPCLK */
};

_Static_assert((sizeof(struct bxCANBitrateConfig)) == (sizeof(uint8_t) * 3U),
               "bxCAN Bitrate config struct size mismatch. Is it aligned?");

/* -- Enums -- */
/**
 *  @brief Available bxCAN operation modes
 */
typedef enum bxcan_peripheral {
#ifdef CAN1_BASE
  BXCAN_PERIPH_1 = 0x0,
#endif
#ifdef CAN2_BASE
  BXCAN_PERIPH_2 = 0x1,
#endif
  BXCAN_PERIPH_LEN
} bxcan_peripheral_t;

/**
 *  @brief Available bxCAN operation modes
 */
typedef enum bxcan_mode {
  BXCAN_MODE_INIT = 0x0,
  BXCAN_MODE_NORM,
  BXCAN_MODE_LPOW,
} bxcan_mode_t;

/**
 *  @brief Available bxCAN test modes
 */
typedef enum bxcan_test_mode {
  BXCAN_TEST_MODE_NONE = 0x0,
  BXCAN_TEST_MODE_SLNT,
  BXCAN_TEST_MODE_LOOP,
  BXCAN_TEST_MODE_BOTH
} bxcan_test_mode_t;

/**
 * @brief Sets the bxCAN to the specified mode.
 *
 * The available operation modes for CAN are specified
 * in the bxcan_mode_t enum. Any other value will be
 * ignored.
 *
 * @param mode The selected mode
 * @return None
 */
void bxcan_set_current_mode(const bxcan_mode_t mode);

/**
 * @brief Configures bxCAN test mode features
 *
 * The available test modes for CAN are specified
 * in the bxcan_test_mode_t enum. Any other value
 * will be ignored.
 *
 * @param mode The selected test mode
 * @return None
 */
void bxcan_set_test_mode(const bxcan_test_mode_t mode);

/**
 * @brief Configures the bxCAN bitrate according to config.
 *
 * The configuration options for the baudrate is
 * located in the bx for CAN are specified in the
 * bxCANBitrateConfig struct. Make sure to not exceed
 * the bit limit of the values and calculate the expected
 * outcome beforehand.
 *
 * @param config The baudrate configuration
 * @return None
 */
void bxcan_configure_bitrate(const struct bxCANBitrateConfig config);

#endif
