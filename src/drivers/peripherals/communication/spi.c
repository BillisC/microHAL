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