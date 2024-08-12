/** @file dma.c
 *  @brief Function defines the DMA driver.
 *
 *  This file contains all of the function definitions
 *  declared in dma.h.
 *
 *  @author Vasileios Ch. (BillisC)
 *  @bug There is a case where DMA1 clears EN SxCR bit
 *  when the peripheral address is USART2 DR. There is no
 *  workaround at the moment (is it errata?).
 */

/* -- Includes -- */
#include "dma.h"
#include "defines.h"

void dma_set_addresses(const uint8_t dma, const uint8_t stream,
                       const uint32_t PA, const uint32_t M0A,
                       const uint32_t M1A) {
  /* Make sure that the stream exists */
  if (!(stream < 8)) {
    return;
  } else {
    struct DMARegs *regs = DMA(dma);

    /* Set memory addresses */
    regs->S[stream].PAR |= PA;
    regs->S[stream].M0AR |= M0A;
    regs->S[stream].M1AR |= M1A;
  }
}

void dma_configure_data(const uint8_t dma, const uint8_t stream,
                        const uint16_t count, const dma_datasize_t msize,
                        const dma_datasize_t psize) {
  /* Check that datasizes are correct */
  switch (msize) {
    case DMA_DATASIZE_BYTE:
    case DMA_DATASIZE_HWRD:
    case DMA_DATASIZE_WORD: break;

    default: return;
  }

  switch (psize) {
    case DMA_DATASIZE_BYTE:
    case DMA_DATASIZE_HWRD:
    case DMA_DATASIZE_WORD: break;

    default: return;
  }

  /* Make sure that the stream exists */
  if (!(stream < 8)) {
    return;
  } else {
    struct DMARegs *regs = DMA(dma);

    /* Set the DMA datasizes */
    volatile uint32_t cr = regs->S[stream].CR;
    cr &= ~(DMA_SxCR_MSIZE_Msk | DMA_SxCR_PSIZE_Msk); // Clear first
    cr |= (((3UL & msize) << DMA_SxCR_MSIZE_Pos) |
           ((3UL & psize) << DMA_SxCR_PSIZE_Pos));

    regs->S[stream].CR = cr;

    /* Set transfer count */
    regs->S[stream].NDTR = (uint32_t)(0xFFFFUL & count);
  }
}

void dma_set_direction(const uint8_t dma, const uint8_t stream,
                       const dma_dir_t direction) {
  switch (direction) {
    case DMA_DIR_PER2MEM:
    case DMA_DIR_MEM2PER:
    case DMA_DIR_MEM2MEM: break;

    default: return;
  };

  /* Make sure that the stream exists */
  if (!(stream < 8)) {
    return;
  } else {
    struct DMARegs *regs = DMA(dma);

    /* Set the stream to the specified direction */
    volatile uint32_t cr = regs->S[stream].CR;
    cr &= ~(DMA_SxCR_DIR_Msk); // Clear first
    cr |= ((3UL & direction) << DMA_SxCR_DIR_Pos);

    regs->S[stream].CR = cr;
  }
}

void dma_configure_stream(const uint8_t dma, const uint8_t stream,
                          const struct DMAStreamConfig config) {
  /* Make sure that the stream exists */
  if (!(stream < 8)) {
    return;
  } else {
    struct DMARegs *regs = DMA(dma);

    /* Configure DMA stream modes in CR */
    volatile uint32_t cr = regs->S[stream].CR;
    cr &= ~(DMA_SxCR_CIRC_Msk | DMA_SxCR_DBM_Msk | DMA_SxCR_PINC_Msk |
            DMA_SxCR_MINC_Msk | DMA_SxCR_PFCTRL_Msk); // Clear first
    cr |= (((1UL & config.Circular) << DMA_SxCR_CIRC_Pos) |
           ((1UL & config.MemIncrement) << DMA_SxCR_MINC_Pos) |
           ((1UL & config.PerIncrement) << DMA_SxCR_PINC_Pos) |
           ((1UL & config.DoubleBuffer) << DMA_SxCR_DBM_Pos) |
           ((1UL & config.PerFlowCtrl) << DMA_SxCR_PFCTRL_Pos));

    regs->S[stream].CR = cr;
  }
}

void dma_set_channel(const uint8_t dma, const uint8_t stream,
                     const uint8_t channel, const dma_priority_t priority) {
  /* Make sure the priority is correct */
  switch (priority) {
    case DMA_PRIORITY_LOW:
    case DMA_PRIORITY_MED:
    case DMA_PRIORITY_HIG:
    case DMA_PRIORITY_VHI: break;

    default: return;
  };

  /* Make sure that the stream exists */
  if (!(stream < 8)) {
    return;
  } else {
    /* Make sure that the channel exists */
    if (!(channel < 8)) {
      return;
    } else {
      struct DMARegs *regs = DMA(dma);

      /* Select channel and specify priority */
      volatile uint32_t cr = regs->S[stream].CR;
      cr &= ~(DMA_SxCR_CHSEL_Msk | DMA_SxCR_PL_Msk); // Clear first
      cr |= (((7UL & channel) << DMA_SxCR_CHSEL_Pos) |
             ((3UL & priority) << DMA_SxCR_PL_Pos));

      regs->S[stream].CR = cr;
    }
  }
}

void dma_set_interrupts(const uint8_t dma, const uint8_t stream,
                        const struct DMAStreamISR config) {
  /* Make sure that the stream exists */
  if (!(stream < 8)) {
    return;
  } else {
    struct DMARegs *regs = DMA(dma);

    /* Configure DMA stream interrupts in CR */
    volatile uint32_t cr = regs->S[stream].CR;
    cr &= ~(DMA_SxCR_DMEIE_Msk | DMA_SxCR_HTIE_Msk | DMA_SxCR_TCIE_Msk |
            DMA_SxCR_TEIE_Msk);
    cr |= (((1UL & config.DMEI) << DMA_SxCR_DMEIE_Pos) |
           ((1UL & config.HTI) << DMA_SxCR_HTIE_Pos) |
           ((1UL & config.TCI) << DMA_SxCR_TCIE_Pos) |
           ((1UL & config.TEI) << DMA_SxCR_TEIE_Pos));

    regs->S[stream].CR = cr;

    /* Configure DMA stream interrupts in FCR */
    volatile uint32_t fcr = regs->S[stream].FCR;
    fcr &= ~(DMA_SxFCR_FEIE_Msk);
    fcr |= ((1UL & config.FEI) << DMA_SxFCR_FEIE_Pos);

    regs->S[stream].FCR = fcr;
  }
}

void dma_enable(const uint8_t dma, const uint8_t stream) {
  /* Make sure that the stream exists */
  if (!(stream < 8)) {
    return;
  } else {
    struct DMARegs *regs = DMA(dma);

    /* Enable the specified stream */
    regs->S[stream].CR |= DMA_SxCR_EN_Msk;
  }
}

void dma_disable(const uint8_t dma, const uint8_t stream) {
  /* Make sure that the stream exists */
  if (!(stream < 8)) {
    return;
  } else {
    struct DMARegs *regs = DMA(dma);

    /* Disable the specified stream */
    regs->S[stream].CR &= ~(DMA_SxCR_EN_Msk);
    while (regs->S[stream].CR & DMA_SxCR_EN_Msk) {};
  }
}
