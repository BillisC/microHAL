/** @file stm32f4xx.h
 *  @brief CMSIS device header stubs
 *
 *  This file contains stubs that make unit testing
 *  possible natively. This is a necessary step as CMSIS
 *  has function definitions in their headers.
 *
 *  @author Vasileios Ch. (BillisC)
 */

#ifndef STM32F4XX_STUBS
#define STM32F4XX_STUBS

/* -- Includes -- */
#include <stdint.h>
#include "system_stm32f4xx.h"

/* GPIO */
#define GPIOA_BASE (0UL)

/* ADC */
#define ADC1_BASE           (0UL)
#define ADC123_COMMON_BASE  (0UL)
#define ADC_SR_EOC_Pos      (1U)
#define ADC_CCR_ADCPRE_Pos  (16U)
#define ADC_CCR_ADCPRE_Msk  (0x3UL << ADC_CCR_ADCPRE_Pos)
#define ADC_CR1_RES_Pos     (24U)
#define ADC_CR1_RES_Msk     (0x3UL << ADC_CR1_RES_Pos)
#define ADC_CR1_SCAN_Pos    (8U)
#define ADC_CR1_SCAN_Msk    (0x1UL << ADC_CR1_SCAN_Pos)
#define ADC_CR1_DISCEN_Pos  (11U)
#define ADC_CR1_DISCEN_Msk  (0x1UL << ADC_CR1_DISCEN_Pos)
#define ADC_CR2_CONT_Pos    (1U)
#define ADC_CR2_CONT_Msk    (0x1UL << ADC_CR2_CONT_Pos)
#define ADC_CR2_DMA_Pos     (8U)
#define ADC_CR2_DMA_Msk     (0x1UL << ADC_CR2_DMA_Pos)
#define ADC_CR2_DDS_Pos     (9U)
#define ADC_CR2_DDS_Msk     (0x1UL << ADC_CR2_DDS_Pos)
#define ADC_CR2_SWSTART_Msk (0x1UL << (30U))
#define ADC_CR2_ADON_Msk    (0x1UL << (0U))
#define ADC_SQR1_L_Pos      (20U)

/* DMA */
#define DMA1_BASE           (0U)
#define DMA_SxCR_EN_Msk     (0x1UL << (0UL))
#define DMA_SxCR_MSIZE_Pos  (13U)
#define DMA_SxCR_MSIZE_Msk  (0x3UL << DMA_SxCR_MSIZE_Pos)
#define DMA_SxCR_PSIZE_Pos  (11U)
#define DMA_SxCR_PSIZE_Msk  (0x3UL << DMA_SxCR_PSIZE_Pos)
#define DMA_SxCR_DIR_Pos    (6U)
#define DMA_SxCR_DIR_Msk    (0x3UL << DMA_SxCR_DIR_Pos)
#define DMA_SxCR_CIRC_Pos   (8U)
#define DMA_SxCR_CIRC_Msk   (0x1UL << DMA_SxCR_CIRC_Pos)
#define DMA_SxCR_MINC_Pos   (10U)
#define DMA_SxCR_MINC_Msk   (0x1UL << DMA_SxCR_MINC_Pos)
#define DMA_SxCR_PINC_Pos   (9U)
#define DMA_SxCR_PINC_Msk   (0x1UL << DMA_SxCR_PINC_Pos)
#define DMA_SxCR_DBM_Pos    (18U)
#define DMA_SxCR_DBM_Msk    (0x1UL << DMA_SxCR_DBM_Pos)
#define DMA_SxCR_PFCTRL_Pos (5U)
#define DMA_SxCR_PFCTRL_Msk (0x1UL << DMA_SxCR_PFCTRL_Pos)
#define DMA_SxCR_CHSEL_Pos  (25U)
#define DMA_SxCR_CHSEL_Msk  (0x7UL << DMA_SxCR_CHSEL_Pos)
#define DMA_SxCR_PL_Pos     (16U)
#define DMA_SxCR_PL_Msk     (0x3UL << DMA_SxCR_PL_Pos)
#define DMA_SxCR_DMEIE_Pos  (1U)
#define DMA_SxCR_DMEIE_Msk  (0x1UL << DMA_SxCR_DMEIE_Pos)
#define DMA_SxCR_HTIE_Pos   (3U)
#define DMA_SxCR_HTIE_Msk   (0x1UL << DMA_SxCR_HTIE_Pos)
#define DMA_SxCR_TCIE_Pos   (4U)
#define DMA_SxCR_TCIE_Msk   (0x1UL << DMA_SxCR_TCIE_Pos)
#define DMA_SxCR_TEIE_Pos   (2U)
#define DMA_SxCR_TEIE_Msk   (0x1UL << DMA_SxCR_TEIE_Pos)
#define DMA_SxFCR_FEIE_Pos  (7U)
#define DMA_SxFCR_FEIE_Msk  (0x1UL << DMA_SxFCR_FEIE_Pos)

/* U(S)ART */
#define USART1_BASE          (0UL)
#define USART2_BASE          (1UL)
#define USART3_BASE          (2UL)
#define UART4_BASE           (3UL)
#define UART5_BASE           (4UL)
#define USART6_BASE          (5UL)
#define USART_CR1_TE_Pos     (3U)
#define USART_CR1_TE_Msk     (0x1UL << USART_CR1_TE_Pos)
#define USART_CR1_RE_Pos     (2U)
#define USART_CR1_RE_Msk     (0x1UL << USART_CR1_RE_Pos)
#define USART_CR1_UE_Pos     (13U)
#define USART_CR1_UE_Msk     (0x1UL << USART_CR1_UE_Pos)
#define USART_CR1_PEIE_Pos   (8U)
#define USART_CR1_PEIE_Msk   (0x1UL << USART_CR1_PEIE_Pos)
#define USART_CR1_TXEIE_Pos  (7U)
#define USART_CR1_TXEIE_Msk  (0x1UL << USART_CR1_TXEIE_Pos)
#define USART_CR1_TCIE_Pos   (6U)
#define USART_CR1_TCIE_Msk   (0x1UL << USART_CR1_TCIE_Pos)
#define USART_CR1_RXNEIE_Pos (5U)
#define USART_CR1_RXNEIE_Msk (0x1UL << USART_CR1_RXNEIE_Pos)
#define USART_CR1_IDLEIE_Pos (4U)
#define USART_CR1_IDLEIE_Msk (0x1UL << USART_CR1_IDLEIE_Pos)
#define USART_CR1_M_Pos      (12U)
#define USART_CR1_M_Msk      (0x1UL << USART_CR1_M_Pos)
#define USART_CR1_PS_Msk     (0x1UL << (9U))
#define USART_CR1_PCE_Msk    (0x1UL << (10U))
#define USART_CR2_LBDIE_Pos  (6U)
#define USART_CR2_LBDIE_Msk  (0x1UL << USART_CR2_LBDIE_Pos)
#define USART_CR2_STOP_Pos   (12U)
#define USART_CR2_STOP_Msk   (0x3UL << USART_CR2_STOP_Pos)
#define USART_CR3_CTSIE_Pos  (10U)
#define USART_CR3_CTSIE_Msk  (0x1UL << USART_CR3_CTSIE_Pos)
#define USART_CR3_EIE_Pos    (0U)
#define USART_CR3_EIE_Msk    (0x1UL << USART_CR3_EIE_Pos)
#define USART_CR3_DMAT_Pos   (7U)
#define USART_CR3_DMAT_Msk   (0x1UL << USART_CR3_DMAT_Pos)
#define USART_CR3_DMAR_Pos   (6U)
#define USART_CR3_DMAR_Msk   (0x1UL << USART_CR3_DMAR_Pos)
#define USART_SR_TXE_Msk     (0x1UL << (7U))
#define USART_SR_TC_Msk      (0x1UL << (6U))
#define USART_SR_RXNE_Msk    (0x1UL << (5U))

/* bxCAN */
#define CAN1_BASE          (0UL)
#define CAN_MCR_INRQ_Msk   (0x1UL << (0U))
#define CAN_MCR_SLEEP_Msk  (0x1UL << (1U))
#define CAN_MCR_TXFP_Pos   (2U)
#define CAN_MCR_TXFP_Msk   (0x1UL << CAN_MCR_TXFP_Pos)
#define CAN_MCR_RFLM_Pos   (3U)
#define CAN_MCR_RFLM_Msk   (0x1UL << CAN_MCR_RFLM_Pos)
#define CAN_MCR_NART_Pos   (4U)
#define CAN_MCR_NART_Msk   (0x1UL << CAN_MCR_NART_Pos)
#define CAN_MCR_AWUM_Pos   (5U)
#define CAN_MCR_AWUM_Msk   (0x1UL << CAN_MCR_AWUM_Pos)
#define CAN_MCR_ABOM_Pos   (6U)
#define CAN_MCR_ABOM_Msk   (0x1UL << CAN_MCR_ABOM_Pos)
#define CAN_MCR_TTCM_Msk   (0x1UL << (7U))
#define CAN_MSR_SLAK_Msk   (0x1UL << (1U))
#define CAN_MSR_INAK_Msk   (0x1UL << (0U))
#define CAN_BTR_BRP_Pos    (0U)
#define CAN_BTR_BRP_Msk    (0x3FFUL << CAN_BTR_BRP_Pos)
#define CAN_BTR_TS1_Pos    (16U)
#define CAN_BTR_TS1_Msk    (0xFUL << CAN_BTR_TS1_Pos)
#define CAN_BTR_TS2_Pos    (20U)
#define CAN_BTR_TS2_Msk    (0x7UL << CAN_BTR_TS2_Pos)
#define CAN_BTR_SJW_Msk    (0x3UL << (24U))
#define CAN_BTR_LBKM_Pos   (30U)
#define CAN_BTR_LBKM_Msk   (0x1UL << CAN_BTR_LBKM_Pos)
#define CAN_BTR_SILM_Msk   (0x1UL << (31U))
#define CAN_IER_TMEIE_Pos  (0U)
#define CAN_IER_FMPIE0_Pos (1U)
#define CAN_IER_FFIE0_Pos  (2U)
#define CAN_IER_FOVIE0_Pos (3U)
#define CAN_IER_FMPIE1_Pos (4U)
#define CAN_IER_FFIE1_Pos  (5U)
#define CAN_IER_FOVIE1_Pos (6U)
#define CAN_IER_EWGIE_Pos  (8U)
#define CAN_IER_EPVIE_Pos  (9U)
#define CAN_IER_BOFIE_Pos  (10U)
#define CAN_IER_LECIE_Pos  (11U)
#define CAN_IER_ERRIE_Pos  (15U)
#define CAN_IER_WKUIE_Pos  (16U)
#define CAN_IER_SLKIE_Pos  (17U)
#define CAN_FMR_FINIT_Msk  (0x1UL << (0U))
#define CAN_FMR_CAN2SB_Pos (8U)
#define CAN_FMR_CAN2SB_Msk (0x3FUL << CAN_FMR_CAN2SB_Pos)
#define CAN_TSR_TME0_Msk   (0x1UL << (26U))
#define CAN_TSR_TME1_Msk   (0x1UL << (27U))
#define CAN_TSR_TME2_Msk   (0x1UL << (28U))
#define CAN_TI0R_TXRQ_Msk  (0x1UL << (0U))
#define CAN_TDT0R_TGT_Pos  (8U)
#define CAN_RI0R_IDE_Pos   (2U)
#define CAN_RI0R_EXID_Pos  (3U)
#define CAN_RI0R_STID_Pos  (21U)
#define CAN_RF0R_RFOM0_Msk (0x1UL << (5U))
#define CAN_RDT0R_TIME_Pos (16U)
#define CAN_ESR_EWGF_Pos   (0U)
#define CAN_ESR_EPVF_Pos   (1U)
#define CAN_ESR_BOFF_Pos   (2U)
#define CAN_ESR_LEC_Pos    (4U)
#define CAN_ESR_TEC_Pos    (16U)
#define CAN_ESR_REC_Pos    (24U)

/* SPI */
#define SPI1_BASE            (0UL)
#define SPI_CR1_CPHA_Pos     (0U)
#define SPI_CR1_CPHA_Msk     (0x1UL << SPI_CR1_CPHA_Pos)
#define SPI_CR1_CPOL_Pos     (1U)
#define SPI_CR1_CPOL_Msk     (0x1UL << SPI_CR1_CPOL_Pos)
#define SPI_CR1_MSTR_Pos     (2U)
#define SPI_CR1_MSTR_Msk     (0x1UL << SPI_CR1_MSTR_Pos)
#define SPI_CR1_BR_Pos       (3U)
#define SPI_CR1_SPE_Msk      (0x1UL << (6U))
#define SPI_CR1_BR_Msk       (0x7UL << SPI_CR1_BR_Pos)
#define SPI_CR1_LSBFIRST_Pos (7U)
#define SPI_CR1_LSBFIRST_Msk (0x1UL << SPI_CR1_LSBFIRST_Pos)
#define SPI_CR1_SSI_Msk      (0x1UL << (8U))
#define SPI_CR1_SSM_Msk      (0x1UL << (9U))
#define SPI_CR1_RXONLY_Msk   (0x1UL << (10U))
#define SPI_CR1_DFF_Pos      (11U)
#define SPI_CR1_DFF_Msk      (0x1UL << SPI_CR1_DFF_Pos)
#define SPI_CR1_CRCEN_Pos    (13U)
#define SPI_CR1_CRCEN_Msk    (0x1UL << SPI_CR1_CRCEN_Pos)
#define SPI_CR1_BIDIOE_Msk   (0x1UL << (14U))
#define SPI_CR1_BIDIMODE_Msk (0x1UL << (15U))
#define SPI_CR2_RXDMAEN_Pos  (0U)
#define SPI_CR2_RXDMAEN_Msk  (0x1UL << SPI_CR2_RXDMAEN_Pos)
#define SPI_CR2_TXDMAEN_Pos  (1U)
#define SPI_CR2_TXDMAEN_Msk  (0x1UL << SPI_CR2_TXDMAEN_Pos)
#define SPI_CR2_SSOE_Msk     (0x1UL << (2U))
#define SPI_CR2_FRF_Pos      (4U)
#define SPI_CR2_FRF_Msk      (0x1UL << SPI_CR2_FRF_Pos)
#define SPI_CR2_ERRIE_Pos    (5U)
#define SPI_CR2_ERRIE_Msk    (0x1UL << SPI_CR2_ERRIE_Pos)
#define SPI_CR2_RXNEIE_Pos   (6U)
#define SPI_CR2_RXNEIE_Msk   (0x1UL << SPI_CR2_RXNEIE_Pos)
#define SPI_CR2_TXEIE_Pos    (7U)
#define SPI_CR2_TXEIE_Msk    (0x1UL << SPI_CR2_TXEIE_Pos)
#define SPI_SR_TXE_Msk       (0x1UL << (1U))
#define SPI_SR_RXNE_Msk      (0x1UL << (0U))
#define SPI_SR_BSY_Msk       (0x1UL << (7U))

/* RCC */
#define RCC_BASE            (0UL)
#define RCC_CR_HSEBYP_Msk   (0x1UL << (18U))
#define RCC_CR_HSERDY_Msk   (0x1UL << (17U))
#define RCC_CR_HSEON_Msk    (0x1UL << (16U))
#define RCC_CR_HSION_Msk    (0x1UL << (0U))
#define RCC_CR_HSIRDY_Msk   (0x1UL << (1U))
#define RCC_CSR_LSION_Msk   (0x1UL << (0U))
#define RCC_CSR_LSIRDY_Msk  (0x1UL << (1U))
#define RCC_BDCR_LSEON_Msk  (0x1UL << (0U))
#define RCC_BDCR_LSERDY_Msk (0x1UL << (1U))
#define RCC_BDCR_LSEBYP_Msk (0x1UL << (2U))
#define RCC_BDCR_RTCSEL_Pos (8U)
#define RCC_BDCR_RTCSEL_Msk (0x3UL << RCC_BDCR_RTCSEL_Pos)
#define RCC_BDCR_RTCEN_Pos  (15U)
#define RCC_BDCR_RTCEN_Msk  (0x1UL << RCC_BDCR_RTCEN_Pos)

#define RCC_CR_PLLSAION_Msk      (0x1UL << (28U))
#define RCC_CR_PLLSAIRDY_Msk     (0x1UL << (29U))
#define RCC_CR_PLLI2SON_Msk      (0x1UL << (26U))
#define RCC_CR_PLLI2SRDY_Msk     (0x1UL << (27U))
#define RCC_CR_PLLON_Msk         (0x1UL << (24U))
#define RCC_CR_PLLRDY_Msk        (0x1UL << (25U))
#define RCC_CFGR_HPRE_Pos        (4U)
#define RCC_CFGR_HPRE_Msk        (0xFUL << RCC_CFGR_HPRE_Pos)
#define RCC_CFGR_PPRE1_Pos       (10U)
#define RCC_CFGR_PPRE1_Msk       (0x3UL << RCC_CFGR_PPRE1_Pos)
#define RCC_CFGR_PPRE2_Pos       (13U)
#define RCC_CFGR_PPRE2_Msk       (0x3UL << RCC_CFGR_PPRE2_Pos)
#define RCC_CFGR_SW_Pos          (0U)
#define RCC_CFGR_SW_Msk          (0x3UL << RCC_CFGR_SW_Pos)
#define RCC_CFGR_SW_PLL          (0x00000002U)
#define RCC_CFGR_SWS_PLL         (0x00000008U)
#define RCC_CFGR_MCO1_Pos        (21U)
#define RCC_CFGR_MCO1_Msk        (0x3UL << RCC_CFGR_MCO1_Pos)
#define RCC_CFGR_MCO2_Pos        (30U)
#define RCC_CFGR_MCO2_Msk        (0x3UL << RCC_CFGR_MCO2_Pos)
#define RCC_CFGR_MCO1PRE_Pos     (24U)
#define RCC_CFGR_MCO1PRE_Msk     (0x7UL << RCC_CFGR_MCO1PRE_Pos)
#define RCC_CFGR_MCO2PRE_Pos     (27U)
#define RCC_CFGR_MCO2PRE_Msk     (0x7UL << RCC_CFGR_MCO2PRE_Pos)
#define RCC_CFGR_RTCPRE_Pos      (16U)
#define RCC_CFGR_RTCPRE_Msk      (0x1FUL << RCC_CFGR_RTCPRE_Pos)
#define RCC_PLLCFGR_PLLM_Pos     (0U)
#define RCC_PLLCFGR_PLLM_Msk     (0x3FUL << RCC_PLLCFGR_PLLM_Pos)
#define RCC_PLLCFGR_PLLN_Pos     (6U)
#define RCC_PLLCFGR_PLLN_Msk     (0x1FFUL << RCC_PLLCFGR_PLLN_Pos)
#define RCC_PLLCFGR_PLLP_Pos     (16U)
#define RCC_PLLCFGR_PLLP_Msk     (0x3UL << RCC_PLLCFGR_PLLP_Pos)
#define RCC_PLLCFGR_PLLR_Pos     (28U)
#define RCC_PLLCFGR_PLLR_Msk     (0x7UL << RCC_PLLCFGR_PLLR_Pos)
#define RCC_PLLCFGR_PLLQ_Pos     (24U)
#define RCC_PLLCFGR_PLLQ_Msk     (0xFUL << RCC_PLLCFGR_PLLQ_Pos)
#define RCC_PLLCFGR_PLLSRC_Pos   (22U)
#define RCC_PLLCFGR_PLLSRC_Msk   (0x1UL << RCC_PLLCFGR_PLLSRC_Pos)
#define RCC_AHB1ENR_GPIOAEN_Msk  (0x1UL << (0U))
#define RCC_AHB1ENR_GPIOBEN_Msk  (0x1UL << (1U))
#define RCC_AHB1ENR_GPIOCEN_Msk  (0x1UL << (2U))
#define RCC_AHB1ENR_GPIODEN_Msk  (0x1UL << (3U))
#define RCC_AHB1ENR_GPIOEEN_Msk  (0x1UL << (4U))
#define RCC_AHB1ENR_GPIOFEN_Msk  (0x1UL << (5U))
#define RCC_AHB1ENR_GPIOGEN_Msk  (0x1UL << (6U))
#define RCC_AHB1ENR_GPIOHEN_Msk  (0x1UL << (7U))
#define RCC_AHB1ENR_DMA1EN_Msk   (0x1UL << (21U))
#define RCC_AHB1ENR_DMA2EN_Msk   (0x1UL << (22U))
#define RCC_APB1ENR_PWREN_Msk    (0x1UL << (28U))
#define RCC_APB1ENR_USART2EN_Msk (0x1UL << (17U))
#define RCC_APB1ENR_USART3EN_Msk (0x1UL << (18U))
#define RCC_APB1ENR_UART4EN_Msk  (0x1UL << (19U))
#define RCC_APB1ENR_UART5EN_Msk  (0x1UL << (20U))
#define RCC_APB2ENR_ADC1EN_Msk   (0x1UL << (8U))
#define RCC_APB2ENR_ADC2EN_Msk   (0x1UL << (9U))
#define RCC_APB2ENR_ADC3EN_Msk   (0x1UL << (10U))
#define RCC_APB2ENR_USART1EN_Msk (0x1UL << (4U))
#define RCC_APB2ENR_USART6EN_Msk (0x1UL << (5U))

/* PWR */
/**
 * @brief Contains stubbed PWR registers.
 */
typedef struct {
  volatile uint32_t CR;
  volatile uint32_t CSR;
} PWR_TypeDef;

#define PWR                 ((PWR_TypeDef *)(0UL))
#define PWR_CR_VOS_Pos      (14U)
#define PWR_CR_ODEN_Msk     (0x1UL << (16U))
#define PWR_CR_ODSWEN_Msk   (0x1UL << (17U))
#define PWR_CSR_ODRDY_Msk   (0x1UL << (16U))
#define PWR_CSR_ODSWRDY_Msk (0x1UL << (17U))

/* FLASH */
/**
 * @brief Contains stubbed FLASH registers.
 */
typedef struct {
  volatile uint32_t ACR;
} FLASH_TypeDef;

#define FLASH                 ((FLASH_TypeDef *)(0UL))
#define FLASH_ACR_LATENCY_5WS 0x00000005U
#define FLASH_ACR_ICEN_Msk    (0x1UL << (9U))
#define FLASH_ACR_PRFTEN_Msk  (0x1UL << (8U))

/* SCB */
/**
 * @brief Contains stubbed SCB registers.
 */
typedef struct {
  volatile uint32_t CPACR;
} SCB_TypeDef;

#define SCB ((SCB_TypeDef *)(0UL))

/* CMSIS GCC */
__attribute__((always_inline)) static inline void __enable_irq(void) { return; }

/* CMSIS CM4 */
__attribute__((always_inline)) static inline uint32_t
SysTick_Config(uint32_t ticks) {
  (void)ticks;
  return 0UL;
}

#endif
