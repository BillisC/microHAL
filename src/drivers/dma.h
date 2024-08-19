/** @file dma.h
 *  @brief Function prototypes for the DMA driver.
 *
 *  This file contains all of the enums, macros, and
 *  function prototypes required for a functional DMA
 *  driver.
 *
 *  DISCLAIMER: No burst or FIFO for the time being!
 *
 *  @author Vasileios Ch. (BillisC)
 *  @bug There is a case where DMA1 clears EN SxCR bit
 *  when the peripheral address is USART2 DR. There is no
 *  workaround at the moment (is it errata?).
 */

#ifndef DMA_H
#define DMA_H

/* -- Includes -- */
#include <stdint.h>
#include "stm32f4xx.h"

/* -- Structs -- */
/**
 *  @brief Contains DMA stream registers
 */
struct __attribute__((packed)) DMAStreamRegs {
  volatile uint32_t CR;
  volatile uint32_t NDTR;
  volatile uint32_t PAR;
  volatile uint32_t M0AR;
  volatile uint32_t M1AR;
  volatile uint32_t FCR;
};

_Static_assert((sizeof(struct DMAStreamRegs)) == (sizeof(uint32_t) * 6U),
               "DMA Sx register struct size mismatch. Is it aligned?");

/**
 *  @brief Contains DMA registers
 */
struct __attribute__((packed)) DMARegs {
  volatile uint32_t LISR;
  volatile uint32_t HISR;
  volatile uint32_t LIFCR;
  volatile uint32_t HIFCR;
  volatile struct DMAStreamRegs S[8];
};

_Static_assert((sizeof(struct DMARegs)) ==
                   (sizeof(uint32_t) * (4U + (6U * 8U))),
               "DMA register struct size mismatch. Is it aligned?");

#define DMA(x) (struct DMARegs *)(DMA1_BASE + ((x - 1) * 0x400UL))

/**
 *  @brief Contains DMA stream options
 */
struct __attribute__((packed)) DMAStreamConfig {
  volatile _Bool Circular     : 1;
  volatile _Bool DoubleBuffer : 1;
  volatile _Bool PerIncrement : 1;
  volatile _Bool MemIncrement : 1;
  volatile _Bool PerFlowCtrl  : 1;
};

_Static_assert((sizeof(struct DMAStreamConfig)) == (sizeof(uint8_t) * 1U),
               "DMA Stream config struct size mismatch. Is it aligned?");

/**
 *  @brief Contains DMA stream interrupt configuration
 */
struct __attribute__((packed)) DMAStreamISR {
  volatile _Bool HTI  : 1;
  volatile _Bool TCI  : 1;
  volatile _Bool TEI  : 1;
  volatile _Bool FEI  : 1;
  volatile _Bool DMEI : 1;
};

_Static_assert((sizeof(struct DMAStreamISR)) == (sizeof(uint8_t) * 1U),
               "DMA Stream Interrupt struct size mismatch. Is it aligned?");

/* -- Enums -- */
/**
 *  @brief Available DMA directions
 */
typedef enum dma_dir {
  DMA_DIR_PER2MEM = 0x00,
  DMA_DIR_MEM2PER = 0x01,
  DMA_DIR_MEM2MEM = 0x02
} dma_dir_t;

/**
 *  @brief Available DMA data sizes
 */
typedef enum dma_datasize {
  DMA_DATASIZE_BYTE = 0x00,
  DMA_DATASIZE_HWRD = 0x01,
  DMA_DATASIZE_WORD = 0x02
} dma_datasize_t;

/**
 *  @brief Available DMA priorities
 */
typedef enum dma_priority {
  DMA_PRIORITY_LOW = 0x00,
  DMA_PRIORITY_MED = 0x01,
  DMA_PRIORITY_HIG = 0x02,
  DMA_PRIORITY_VHI = 0x03
} dma_priority_t;

/**
 * @brief Set the DMA source and destination addresses.
 *
 * Usually only the peripheral and M0 addresses are needed.
 * In that case you shall set M1A to zero.
 *
 * @param dma The selected DMA
 * @param stream The selected stream (0..7)
 * @param PA The peripheral address
 * @param M0A The memory 0 address
 * @param M1A The memory 1 address
 * @return None
 */
void dma_set_addresses(const uint8_t dma, const uint8_t stream,
                       const uint32_t PA, const uint32_t M0A,
                       const uint32_t M1A);

/**
 * @brief Set DMA transfers to specified configuration.
 *
 * The DMA datasizes are specified in the dma_datasize_t enum.
 * Any other value will be ignored.
 *
 * @param dma The selected DMA (1..2)
 * @param stream The selected stream (0..7)
 * @param count The total number of data items
 * @param msize The size of data stored in memory
 * @param psize The size of data stored in the peripheral
 * @return None
 */
void dma_configure_data(const uint8_t dma, const uint8_t stream,
                        const uint16_t count, const dma_datasize_t msize,
                        const dma_datasize_t psize);

/**
 * @brief Set DMA transfers to the desired direction.
 *
 * The DMA directions are specified in the dma_dir_t enum.
 * Any other value will be ignored. After that set the
 * addresses according to the chip's manual.
 *
 * @param dma The selected DMA (1..2)
 * @param stream The selected stream (0..7)
 * @param direction The transfer direction
 * @return None
 */
void dma_set_direction(const uint8_t dma, const uint8_t stream,
                       const dma_dir_t direction);

/**
 * @brief Set DMA stream to the specified configuration.
 *
 * The DMA stream options are specified in the DMAStreamConfig
 * struct.
 *
 * @param dma The selected DMA (1..2)
 * @param stream The selected stream (0..7)
 * @param config The stream configuration
 * @return None
 */
void dma_configure_stream(const uint8_t dma, const uint8_t stream,
                          const struct DMAStreamConfig config);

/**
 * @brief Set the DMA stream channel and priority.
 *
 * The DMA priority levels are specified in the dma_priority_t
 * enum. Any other value will be ignored. Refer to the chip's
 * manual for the channel function matrix.
 *
 * @param dma The selected DMA (1..2)
 * @param stream The selected stream (0..7)
 * @param channel The selected channel (0..7)
 * @param priority The stream priority level
 * @return None
 */
void dma_set_channel(const uint8_t dma, const uint8_t stream,
                     const uint8_t channel, const dma_priority_t priority);

/**
 * @brief Enabled the specified DMA stream interrupts.
 *
 * The available DMA interrupts are located in the DMAStreamISR
 * struct.
 *
 * @param dma The selected DMA (1..2)
 * @param stream The selected stream (0..7)
 * @param config The interrupt configuration
 * @return None
 */
void dma_set_interrupts(const uint8_t dma, const uint8_t stream,
                        const struct DMAStreamISR config);

/**
 * @brief Enables DMA stream transfers.
 *
 * @param dma The selected DMA (1..2)
 * @param stream The selected stream (0..7)
 * @return None
 */
void dma_enable(const uint8_t dma, const uint8_t stream);

/**
 * @brief Disables DMA stream transfers.
 *
 * @param dma The selected DMA (1..2)
 * @param stream The selected stream (0..7)
 * @return None
 */
void dma_disable(const uint8_t dma, const uint8_t stream);

#endif
