/** @file spi.c
 *  @brief Function defines for the SPI driver.
 *
 *  This file contains all of the function definitions
 *  declared in spi.h.
 *
 *  @author Vasileios Ch. (BillisC)
 *  @bug None, yet.
 */

/* -- Includes -- */
#include "spi.h"

/**
 *  @brief SPI address look up table
 *
 *  It was necessary once more.
 */
static uint32_t SPI_LUT[] = {
#ifdef SPI1_BASE
    SPI1_BASE,
#endif
#ifdef SPI2_BASE
    SPI2_BASE,
#endif
#ifdef SPI3_BASE
    SPI3_BASE,
#endif
#ifdef SPI4_BASE
    SPI4_BASE,
#endif
#ifdef SPI5_BASE
    SPI5_BASE,
#endif
#ifdef SPI6_BASE
    SPI6_BASE,
#endif
    0UL, // Safety value
};

static inline _Bool validateSPI(const spi_peripheral_t spi) {
  if (spi < SPI_PERIPH_LEN && spi >= 0U) {
    return TRUE;
  } else {
    return FALSE;
  }
}

void spi_set_interrupts(const spi_peripheral_t spi,
                        const struct SPIISR config) {
  if (!validateSPI(spi)) {
    return;
  } else {
    struct SPIRegs *regs = SPI(SPI_LUT[spi]);

    /* Set interrupt bits */
    REG32 cr2 = regs->CR2;
    cr2 &= ~(SPI_CR2_ERRIE_Msk | SPI_CR2_RXNEIE_Msk | SPI_CR2_TXEIE_Msk);
    cr2 |= ((config.ERR << SPI_CR2_ERRIE_Pos) |
            (config.RXNE << SPI_CR2_RXNEIE_Pos) |
            (config.TXE << SPI_CR2_TXEIE_Pos));

    regs->CR2 = cr2;
  }
}

void spi_set_direction(const spi_peripheral_t spi, const spi_direction_t dir) {
  if (!validateSPI(spi)) {
    return;
  } else {
    struct SPIRegs *regs = SPI(SPI_LUT[spi]);

    /* Configure communication way */
    REG32 cr1 = regs->CR1;
    cr1 &= ~(SPI_CR1_BIDIMODE_Msk | SPI_CR1_BIDIOE_Msk | SPI_CR1_RXONLY_Msk);
    switch (dir) {
      case SPI_DIR_FULL_DUPLEX: break;
      case SPI_DIR_HALF_DUPLEX_RX: cr1 |= (SPI_CR1_BIDIMODE_Msk); break;
      case SPI_DIR_HALF_DUPLEX_TX:
        cr1 |= (SPI_CR1_BIDIMODE_Msk | SPI_CR1_BIDIOE_Msk);
        break;
      case SPI_DIR_SIMPLEX_RX: cr1 |= (SPI_CR1_RXONLY_Msk); break;
      case SPI_DIR_SIMPLEX_TX: break;
      default: return;
    }

    regs->CR1 = cr1;
  }
}

void spi_set_prescaler(const spi_peripheral_t spi,
                       const spi_prescaler_t value) {
  /* Make sure the divide value is valid */
  switch (value) {
    case SPI_PRESCALER_DIV_2:
    case SPI_PRESCALER_DIV_4:
    case SPI_PRESCALER_DIV_8:
    case SPI_PRESCALER_DIV_16:
    case SPI_PRESCALER_DIV_32:
    case SPI_PRESCALER_DIV_64:
    case SPI_PRESCALER_DIV_128:
    case SPI_PRESCALER_DIV_256: break;
    default: return;
  }

  if (!validateSPI(spi)) {
    return;
  } else {
    struct SPIRegs *regs = SPI(SPI_LUT[spi]);

    /* Write the new divider value */
    REG32 cr1 = regs->CR1;
    cr1 &= ~(SPI_CR1_BR_Msk);
    cr1 |= (value << SPI_CR1_BR_Pos);

    regs->CR1 = cr1;
  }
}

void spi_set_nss_mode(const spi_peripheral_t spi, const spi_nss_mode_t mode) {
  if (!validateSPI(spi)) {
    return;
  } else {
    struct SPIRegs *regs = SPI(SPI_LUT[spi]);

    /* Configure NSS mode */
    REG32 cr1 = regs->CR1;
    REG32 cr2 = regs->CR2;
    cr1 &= ~(SPI_CR1_SSM_Msk);
    cr2 &= ~(SPI_CR2_SSOE_Msk);
    switch (mode) {
      case SPI_NSS_SOFT: cr1 |= (SPI_CR1_SSM_Msk); break;
      case SPI_NSS_HARD_OD: break;
      case SPI_NSS_HARD_OE: cr2 |= (SPI_CR2_SSOE_Msk); break;
      default: return;
    }

    regs->CR1 = cr1;
    regs->CR2 = cr2;
  }
}

void spi_set_dma(const spi_peripheral_t spi, const _Bool forTX,
                 const _Bool forRX) {
  if (!validateSPI(spi)) {
    return;
  } else {
    struct SPIRegs *regs = SPI(SPI_LUT[spi]);

    /* Set DMA bits */
    REG32 cr2 = regs->CR2;
    cr2 &= ~(SPI_CR2_TXDMAEN_Msk | SPI_CR2_RXDMAEN_Msk);
    cr2 |= ((forTX << SPI_CR2_TXDMAEN_Pos) | (forRX << SPI_CR2_RXDMAEN_Pos));

    regs->CR2 = cr2;
  }
}

void spi_configure(const spi_peripheral_t spi, const struct SPIConfig config) {
  if (!validateSPI(spi)) {
    return;
  } else {
    struct SPIRegs *regs = SPI(SPI_LUT[spi]);

    /* Configuration in CR1  */
    REG32 cr1 = regs->CR1;
    cr1 &= ~(SPI_CR1_CRCEN_Msk | SPI_CR1_DFF_Msk | SPI_CR1_LSBFIRST_Msk |
             SPI_CR1_CPOL_Msk | SPI_CR1_CPHA_Msk);
    cr1 |= ((config.UseCRC << SPI_CR1_CRCEN_Pos) |
            (config.Use16Bits << SPI_CR1_DFF_Pos) |
            (config.LSBFirst << SPI_CR1_LSBFIRST_Pos) |
            (config.ClockPolarity << SPI_CR1_CPOL_Pos) |
            (config.ClockPhase << SPI_CR1_CPHA_Pos));

    regs->CR1 = cr1;

    /* Configure TI mode in CR2*/
    REG32 cr2 = regs->CR2;
    cr2 &= ~(SPI_CR2_FRF_Msk);
    cr2 |= (config.TIMode << SPI_CR2_FRF_Pos);

    regs->CR2 = cr2;
  }
}

void spi_tx_data(const spi_peripheral_t spi, const uint16_t data) {
  if (!validateSPI(spi)) {
    return;
  } else {
    struct SPIRegs *regs = SPI(SPI_LUT[spi]);

    /* Wait for available TX buffer */
    while (!(regs->SR & SPI_SR_TXE_Msk)) { ASM_NOP; }
    regs->DR = data;
  }
}

uint16_t spi_rx_data(const spi_peripheral_t spi) {
  if (!validateSPI(spi)) {
    return 0UL;
  } else {
    struct SPIRegs *regs = SPI(SPI_LUT[spi]);

    /* Wait for available data in RX buffer */
    while (!(regs->SR & SPI_SR_RXNE_Msk)) { ASM_NOP; }
    return (regs->DR & 0xFFFFUL);
  }
}

void spi_start(const spi_peripheral_t spi, const _Bool master) {
  if (!validateSPI(spi)) {
    return;
  } else {
    struct SPIRegs *regs = SPI(SPI_LUT[spi]);

    /* Procedure to enable SPI */
    REG32 cr1 = regs->CR1;
    cr1 &= ~(SPI_CR1_MSTR_Msk);
    cr1 |= (SPI_CR1_SPE_Msk | (master << SPI_CR1_MSTR_Pos));

    regs->CR1 = cr1;
  }
}

void spi_stop(const spi_peripheral_t spi) {
  if (!validateSPI(spi)) {
    return;
  } else {
    struct SPIRegs *regs = SPI(SPI_LUT[spi]);

    REG32 cr1 = regs->CR1;
    if (((cr1 & SPI_CR1_BIDIMODE_Msk) && !(cr1 & SPI_CR1_BIDIOE_Msk)) ||
        (cr1 & SPI_CR1_RXONLY_Msk)) {
      /* If receive only mode is detected */
      cr1 &= ~(SPI_CR1_SPE_Msk);
      regs->CR1 = cr1;
      while (regs->SR & SPI_SR_BSY_Msk) { ASM_NOP; }
    } else {
      while (!(regs->SR & SPI_SR_RXNE_Msk)) { ASM_NOP; } // Retrieve last data
      while (!(regs->SR & SPI_SR_TXE_Msk)) { ASM_NOP; }  // Send last data
      while (regs->SR & SPI_SR_BSY_Msk) { ASM_NOP; }
      cr1 &= ~(SPI_CR1_SPE_Msk);
      regs->CR1 = cr1;
    }

    uint16_t last_data = (regs->DR & 0xFFFFUL);
    (void)last_data;
  }
}