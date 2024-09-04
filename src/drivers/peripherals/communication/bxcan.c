/** @file bxcan.c
 *  @brief Function defines for the bxCAN driver.
 *
 *  This file contains all of the function definitions
 *  declared in bxcan.h.
 *
 *  @author Vasileios Ch. (BillisC)
 *  @bug None, yet.
 */

/* -- Includes -- */
#include "bxcan.h"
#include "stm32f446xx.h"

inline _Bool validateBXCAN(const bxcan_peripheral_t can) {
  /* Make sure peripheral exists */
  if (can < BXCAN_PERIPH_LEN) {
    return TRUE;
  } else {
    return FALSE;
  }
}

void bxcan_set_current_mode(const bxcan_peripheral_t can,
                            const bxcan_mode_t mode) {
  if (!validateBXCAN(can)) {
    return;
  } else {
    struct bxCANRegs *regs = CAN(can);

    /* Configure CAN mode bits */
    REG32 mcr = regs->MCR;
    mcr &= ~(CAN_MCR_SLEEP_Msk | CAN_MCR_INRQ_Msk); // clear first
    switch (mode) {
      case BXCAN_MODE_INIT:
        mcr |= CAN_MCR_INRQ_Msk;
        regs->MCR = mcr;
        while (!(CAN_MSR_INAK_Msk & regs->MSR)) { ASM_NOP; }
        break;
      case BXCAN_MODE_NORM:
        regs->MCR = mcr;
        while (CAN_MSR_INAK_Msk & regs->MSR) { ASM_NOP; }
        break;
      case BXCAN_MODE_LPOW:
        mcr |= CAN_MCR_SLEEP_Msk;
        regs->MCR = mcr;
        while (!(CAN_MSR_SLAK_Msk & regs->MSR)) { ASM_NOP; }
        break;
      default: return;
    }
  }
}

void bxcan_set_test_mode(const bxcan_peripheral_t can,
                         const bxcan_test_mode_t mode) {
  /* Make sure the modes are valid */
  switch (mode) {
    case BXCAN_TEST_MODE_NONE:
    case BXCAN_TEST_MODE_SLNT:
    case BXCAN_TEST_MODE_LOOP:
    case BXCAN_TEST_MODE_BOTH: break;
    default: return;
  }

  if (!validateBXCAN(can)) {
    return;
  } else {
    struct bxCANRegs *regs = CAN(can);

    /* Configure test mode bits */
    REG32 btr = regs->BTR;
    btr &= ~(CAN_BTR_SILM_Msk | CAN_BTR_LBKM_Msk); // clear first
    btr |= (mode << CAN_BTR_LBKM_Pos);

    regs->BTR = btr;
  }
}

void bxcan_set_time_triggered_mode(const bxcan_peripheral_t can,
                                   const _Bool state) {
  if (!validateBXCAN(can)) {
    return;
  } else {
    struct bxCANRegs *regs = CAN(can);

    /* Configure time triggered communication */
    if (state == TRUE) {
      regs->MCR |= CAN_MCR_TTCM_Msk;
    } else {
      regs->MCR &= ~(CAN_MCR_TTCM_Msk);
    }
  }
}

void bxcan_set_interrupts(const bxcan_peripheral_t can,
                          const struct bxCANISR config) {
  if (!validateBXCAN(can)) {
    return;
  } else {
    struct bxCANRegs *regs = CAN(can);

    /* Enable selected interrupt bits */
    REG32 ier = 0UL;
    ier |=
        ((config.TME << CAN_IER_TMEIE_Pos) |
         (config.FMP0 << CAN_IER_FMPIE0_Pos) |
         (config.FF0 << CAN_IER_FFIE0_Pos) |
         (config.FOV0 << CAN_IER_FOVIE0_Pos) |
         (config.FMP1 << CAN_IER_FMPIE1_Pos) |
         (config.FF1 << CAN_IER_FFIE1_Pos) |
         (config.FOV1 << CAN_IER_FOVIE1_Pos) |
         (config.EWG << CAN_IER_EWGIE_Pos) | (config.EPV << CAN_IER_EPVIE_Pos) |
         (config.BOF << CAN_IER_BOFIE_Pos) | (config.LEC << CAN_IER_LECIE_Pos) |
         (config.ERR << CAN_IER_ERRIE_Pos) | (config.WKU << CAN_IER_WKUIE_Pos) |
         (config.SLK << CAN_IER_SLKIE_Pos));

    regs->IER = ier;
  }
}

void bxcan_configure_bitrate(const bxcan_peripheral_t can,
                             const struct bxCANBitrateConfig config) {
  if (!validateBXCAN(can)) {
    return;
  } else {
    struct bxCANRegs *regs = CAN(can);

    /* Configure timing bits */
    REG32 btr = regs->BTR;
    btr &=
        ~(CAN_BTR_TS1_Msk | CAN_BTR_TS2_Msk | CAN_BTR_BRP_Msk); // clear first
    btr |= ((config.TimeSeg1 << CAN_BTR_TS1_Pos) |
            (config.TimeSeg2 << CAN_BTR_TS2_Pos) |
            (config.BaudPrescaler << CAN_BTR_BRP_Pos));

    regs->BTR = btr;
  }
}

void bxcan_configure_automation(const bxcan_peripheral_t can,
                                const struct bxCANAutomationConfig config) {
  if (!validateBXCAN(can)) {
    return;
  } else {
    struct bxCANRegs *regs = CAN(can);

    /* Configure automation */
    REG32 mcr = regs->MCR;
    mcr &= ~(CAN_MCR_ABOM_Msk | CAN_MCR_AWUM_Msk | CAN_MCR_NART_Msk);
    mcr |= ((config.AutoBusOff << CAN_MCR_ABOM_Pos) |
            (config.AutoWakeUp << CAN_MCR_AWUM_Pos) |
            ((1U - config.AutoReTx) << CAN_MCR_NART_Pos));

    regs->MCR = mcr;
  }
}

void bxcan_configure_fifo(const bxcan_peripheral_t can, const _Bool lock,
                          const bxcan_fifo_priority_t priority) {
  if (!validateBXCAN(can)) {
    return;
  } else {
    struct bxCANRegs *regs = CAN(can);

    /* Configure FIFO */
    REG32 mcr = regs->MCR;
    mcr &= ~(CAN_MCR_NART_Msk | CAN_MCR_RFLM_Msk);
    mcr |= ((priority << CAN_MCR_NART_Pos) | (lock << CAN_MCR_RFLM_Pos));

    regs->MCR = mcr;
  }
}

void bxcan_set_filter_start(const bxcan_peripheral_t can,
                            const uint8_t filters) {
  if (!validateBXCAN(can)) {
    return;
  } else if (filters > 0x3FU) {
    /* 6-bit limit */
    return;
  } else {
    /* Filter options are available in CAN1 only */
    struct bxCANRegs *regs = CAN(0U);

    /* Configure filter attribution bits */
    REG32 fmr = regs->FMR;
    fmr &= ~(CAN_FMR_CAN2SB_Msk); // clear first
    fmr |= (filters << CAN_FMR_CAN2SB_Pos);

    regs->FMR = fmr;
  }
}

void bxcan_configure_filter(const bxcan_peripheral_t can, const uint8_t filter,
                            const struct bxCANFilterConfig config) {
  if (!validateBXCAN(can)) {
    return;
  } else if (filter > 27U) {
    return;
  } else {
    /* Filter options are available in CAN1 only */
    struct bxCANRegs *regs = CAN(0U);

    /* Enter filter init mode */
    regs->FMR |= CAN_FMR_FINIT_Msk;

    /* The steps to configure a single filter are
     * as follows:
     * 1. Set masking / listing mode
     * 2. Set bit scaling
     * 3. Set FIFO
     * 4. Configure IDs
     * 5. Enable the filter
     */

    /* 1. Configure masking mode */
    REG32 fm1r = regs->FM1R;
    fm1r &= BIT(filter);
    fm1r |= (config.ListMode << filter);
    regs->FM1R = fm1r;

    /* 2. Configure scale bits */
    REG32 fs1r = regs->FS1R;
    fs1r &= BIT(filter);
    fs1r |= (config.SingleScale << filter);
    regs->FS1R = fs1r;

    /* 3. Configure filter FIFO */
    REG32 ffa1r = regs->FFA1R;
    ffa1r &= BIT(filter);
    ffa1r |= (config.FIFO << filter);
    regs->FFA1R = ffa1r;

    /* 4. Configure target IDs */
    regs->FilterBank[filter].FR1 =
        ((config.FilterID[1] << 16U) | config.FilterID[0]);
    regs->FilterBank[filter].FR2 =
        ((config.FilterIDMask[1] << 16U) | config.FilterIDMask[0]);

    /* 5. Enable filter */
    REG32 fa1r = regs->FA1R;
    fa1r &= BIT(filter);
    fa1r |= (config.Activate << filter);
    regs->FA1R = fa1r;

    /* Exit filter init mode */
    regs->FMR &= CAN_FMR_FINIT_Msk;
  }
}

void bxcan_tx_frame(const bxcan_peripheral_t can, const uint8_t mailbox,
                    struct bxCANFrame *frame) {
  if (!validateBXCAN(can)) {
    return;
  } else if (mailbox > 2U) {
    return;
  } else if (frame->DLC > 8U) {
    return;
  } else {
    struct bxCANRegs *regs = CAN(can);

    /* Wait until the mailbox becomes empty */
    while (!(regs->TxMailbox[mailbox].IR & CAN_TI0R_TXRQ_Msk)) { ASM_NOP; };

    /* Correct global time transmission */
    if ((frame->TGT) && (CAN_MCR_TTCM_Msk & regs->MCR)) {
      frame->DLC = 8U;
    } else {
      frame->TGT = FALSE;
    }

    /* Pass data in temp registers */
    REG32 lr = 0U;
    REG32 hr = 0U;
    for (uint8_t i = 0U; i < frame->DLC; i++) {
      if (i < 4U) {
        lr |= (frame->DATA[i] << (i * 8));
      } else {
        hr |= (frame->DATA[i] << ((i - 4) * 8));
      }
    }

    /* Configure frame and transmit it */
    regs->TxMailbox[mailbox].LR = lr;
    regs->TxMailbox[mailbox].HR = hr;
    regs->TxMailbox[mailbox].TR =
        ((frame->DLC) | (frame->TGT << CAN_TDT0R_TGT_Pos));
    regs->TxMailbox[mailbox].IR =
        ((frame->ID << ((frame->IDE) ? CAN_RI0R_EXID_Pos : CAN_RI0R_STID_Pos)) |
         (frame->IDE << CAN_TI0R_IDE_Pos) | CAN_TI0R_TXRQ_Msk);
  }
}

void bxcan_rx_frame(const bxcan_peripheral_t can, const _Bool FIFO,
                    struct bxCANFrame *frame) {
  if (!validateBXCAN(can)) {
    return;
  } else {
    struct bxCANRegs *regs = CAN(can);

    /* Information gathering */
    REG32 ir = regs->FIFOMailbox[FIFO].IR;
    frame->IDE = ((ir >> CAN_RI0R_IDE_Pos) & 1U);
    frame->ID = (ir >> ((frame->IDE) ? CAN_RI0R_EXID_Pos : CAN_RI0R_STID_Pos));
    REG32 tr = regs->FIFOMailbox[FIFO].TR;
    frame->DLC = (tr & 0xFU);
    frame->TIME = (tr >> CAN_RDT0R_TIME_Pos);

    /* Data gathering */
    REG32 lr = regs->FIFOMailbox[FIFO].LR;
    REG32 hr = regs->FIFOMailbox[FIFO].HR;
    for (uint8_t i = 0U; i < frame->DLC; i++) {
      if (i < 4U) {
        frame->DATA[i] = (lr >> (i * 8));
      } else {
        frame->DATA[i] = (hr >> ((i - 4) * 8));
      }
    }

    /* Release FIFO */
    regs->RFR[FIFO] |= CAN_RF0R_RFOM0_Msk;
  }
}

const struct bxCANErrorInfo bxcan_get_error_info(const bxcan_peripheral_t can) {
  struct bxCANErrorInfo info = {0};

  if (!validateBXCAN(can)) {
    return info;
  } else {
    struct bxCANRegs *regs = CAN(can);

    /* Retrieve errors from register */
    REG32 esr = regs->ESR;
    info.RxErrors = (esr >> CAN_ESR_REC_Pos);
    info.TxErrors = ((esr >> CAN_ESR_TEC_Pos) & 0xFFU);
    info.LastCode = ((esr >> CAN_ESR_LEC_Pos) & 0x07U);
    info.BusOff = ((esr >> CAN_ESR_BOFF_Pos) & 0x01U);
    info.Passive = ((esr >> CAN_ESR_EPVF_Pos) & 0x01U);
    info.Warning = ((esr >> CAN_ESR_EWGF_Pos) & 0x01U);

    return info;
  }
}
