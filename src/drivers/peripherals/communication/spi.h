/** @file spi.h
 *  @brief Function prototypes for the SPI interface.
 *
 *  This file contains all of the enums, macros, and
 *  function prototypes required for a functional SPI
 *  interface.
 *
 *  Multi-slave switching is not available, so please
 *  handle GPIOs manually.
 *
 *  @author Vasileios Ch. (BillisC)
 *  @bug None, yet.
 */

/* -- Includes -- */
#include <stdint.h>
#include "stm32f4xx.h"
#include "defines.h"

/* -- Structs -- */
/**
 *  @brief Contains SPI/I2S registers
 */
struct __attribute__((packed)) SPIRegs {
  REG32 CR1;
  REG32 CR2;
  REG32 SR;
  REG32 DR;
  REG32 CRCPR;
  REG32 RXCRCR;
  REG32 TXCRCR;
  REG32 I2SCFGR;
  REG32 I2SPR;
};

_Static_assert((sizeof(struct SPIRegs)) == (sizeof(uint32_t) * 9U),
               "SPI Register struct size mismatch. Is it aligned?");

#define SPI(ADDR) (struct SPIRegs *)(ADDR);

/**
 *  @brief Contains SPI interrupt configuration
 */
struct __attribute__((packed)) SPIISR {
  _Bool ERR  : 1; /**< Error */
  _Bool RXNE : 1; /**< RX buffer not empty */
  _Bool TXE  : 1; /**< TX buffer empty */
};

_Static_assert((sizeof(struct SPIISR)) == (sizeof(uint8_t) * 1U),
               "SPI ISR struct size mismatch. Is it aligned?");

/**
 *  @brief Contains additional SPI configuration
 */
struct __attribute__((packed)) SPIConfig {
  _Bool UseCRC        : 1; /**< CRC checks */
  _Bool Use16Bits     : 1; /**< Otherwise 8 bits */
  _Bool LSBFirst      : 1; /**< Otherwise MSB */
  _Bool ClockPolarity : 1; /**< Idle clock state */
  _Bool ClockPhase    : 1; /**< Data capture at second phase when true */
  _Bool TIMode        : 1; /**< Otherwise Motorola */
};

_Static_assert((sizeof(struct SPIConfig)) == (sizeof(uint8_t) * 1U),
               "SPI Config struct size mismatch. Is it aligned?");

/* -- Enums -- */
/**
 *  @brief Available SPI peripherals
 */
typedef enum spi_peripheral {
#ifdef SPI1_BASE
  SPI_PERIPH_1 = 0x0,
#endif
#ifdef SPI2_BASE
  SPI_PERIPH_2,
#endif
#ifdef SPI3_BASE
  SPI_PERIPH_3,
#endif
#ifdef SPI4_BASE
  SPI_PERIPH_4,
#endif
#ifdef SPI5_BASE
  SPI_PERIPH_5,
#endif
#ifdef SPI6_BASE
  SPI_PERIPH_6,
#endif
  SPI_PERIPH_LEN
} spi_peripheral_t;

/**
 *  @brief Available SPI communication directions
 */
typedef enum spi_direction {
  SPI_DIR_FULL_DUPLEX = 0x0,
  SPI_DIR_HALF_DUPLEX_RX,
  SPI_DIR_HALF_DUPLEX_TX,
  SPI_DIR_SIMPLEX_RX,
  SPI_DIR_SIMPLEX_TX
} spi_direction_t;

/**
 *  @brief Available SPI NSS pin modes
 */
typedef enum spi_nss_mode {
  SPI_NSS_SOFT = 0x0,
  SPI_NSS_HARD_OE,
  SPI_NSS_HARD_OD
} spi_nss_mode_t;

/**
 *  @brief Available SPI prescaler dividers
 */
typedef enum spi_prescaler {
  SPI_PRESCALER_DIV_2 = 0x0,
  SPI_PRESCALER_DIV_4,
  SPI_PRESCALER_DIV_8,
  SPI_PRESCALER_DIV_16,
  SPI_PRESCALER_DIV_32,
  SPI_PRESCALER_DIV_64,
  SPI_PRESCALER_DIV_128,
  SPI_PRESCALER_DIV_256
} spi_prescaler_t;

/**
 *  @brief Enables specified SPI interrupts
 *
 *  The list of available SPI interrupts is located under
 *  the SPIISR struct.
 *
 *  @param spi The selected SPI
 *  @param config The interrupt config
 *  @return None
 */
void spi_set_interrupts(const spi_peripheral_t spi, const struct SPIISR config);

/**
 *  @brief Sets the SPI to the specified comm direction
 *
 *  The available directions can be located under the
 *  spi_direction_t enum. Any other value will be ignored.
 *
 *  @param spi The selected SPI
 *  @param dir The SPI direction
 *  @return None
 */
void spi_set_direction(const spi_peripheral_t spi, const spi_direction_t dir);

/**
 *  @brief Configures the SPI prescale divider
 *
 *  The available division values can be found in the
 *  spi_prescaler_t enum. Any other value will be ignored.
 *  Note that the prescaler will divide the clock speed of
 *  the bus of the peripheral and not the system clock. The
 *  resulting clock will be the baudrate of the SPI.
 *
 *  @param spi The selected SPI
 *  @param value The prescale divider
 *  @return None
 */
void spi_set_prescaler(const spi_peripheral_t spi, const spi_prescaler_t value);

/**
 *  @brief Sets the SPI NSS pin to the specified mode
 *
 *  The available NSS modes for the SPI are specified in
 *  the spi_nss_mode_t enum. Any other value will be ignored.
 *
 *  @param spi The selected SPI
 *  @param mode The NSS pin mode
 *  @return None
 */
void spi_set_nss_mode(const spi_peripheral_t spi, const spi_nss_mode_t mode);

/**
 *  @brief Enables DMA for SPI RX and/or TX
 *
 *  @param spi The selected SPI
 *  @param forTX Enable / disable DMA for TX
 *  @param forRX Enable / disable DMA for RX
 *  @return None
 */
void spi_set_dma(const spi_peripheral_t spi, const _Bool forTX,
                 const _Bool forRX);

/**
 *  @brief Set SPI options from specified config
 *
 *  The SPI configuration is located under the SPIConfig
 *  struct. Refer to the datasheet for the correct
 *  usage of these options.
 *
 *  @param spi The selected SPI
 *  @param config The SPI configuration
 *  @return None
 */
void spi_configure(const spi_peripheral_t spi, const struct SPIConfig config);

/**
 *  @brief Transmits specified SPI data
 *
 *  The data parameter is 16-bit but you may set the LSB
 *  for 8-bit transfers. The SPI loads the data in the
 *  shift register and transmits using the configured
 *  byte order.
 *
 *  @param spi The selected SPI
 *  @param data The data to transmit
 *  @return None
 */
void spi_tx_data(const spi_peripheral_t spi, const uint16_t data);

/**
 *  @brief Reads the received SPI data
 *
 *  The data can be read as soon as they are stored
 *  in the RX buffer from the shift register. You may pair
 *  this with an interrupt for better performance.
 *
 *  @param spi The selected SPI
 *  @return The received data
 */
uint16_t spi_rx_data(const spi_peripheral_t spi);

/**
 *  @brief Initiates the SPI peripheral with specified options.
 *
 *  @param spi The selected SPI
 *  @param master Use master configuration
 *  @return None
 */
void spi_start(const spi_peripheral_t spi, const _Bool master);

/**
 *  @brief Stops the SPI peripheral communication.
 *
 *  @param spi The selected SPI
 *  @return None
 */
void spi_stop(const spi_peripheral_t spi);