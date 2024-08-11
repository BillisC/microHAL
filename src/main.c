/* Includes */
#include "defines.h"
#include "interrupts.h"
#include "dma.h"
#include "mcu_init.h"
#include "gpio.h"
#include "usart.h"

void delay_ms(const uint32_t milliseconds);

int main(void) {
  mcu_init();

  const char *message = "Hello, USART!\t\n";

  /* Setup GPIO for USART communication */
  gp_set_direction('A', 2U, GP_DIR_AL);
  gp_set_direction('A', 3U, GP_DIR_AL);
  gp_set_af('A', 2U, 7U);
  gp_set_af('A', 3U, 7U);
  gp_set_speed('A', 2U, GP_SPEED_HIG);
  gp_set_speed('A', 3U, GP_SPEED_HIG);

  /* Setup DMA for USART communication */
  dma_set_addresses(1U, 6U, (uint32_t)&message, (uint32_t)&USART2->DR, 0U);
  dma_configure_data(1U, 6U, 1U, DMA_DATASIZE_BYTE, DMA_DATASIZE_BYTE);
  dma_set_direction(1U, 6U, DMA_DIR_MEM2PER);
  struct DMAStreamConfig d_config = {TRUE, FALSE, FALSE, FALSE, FALSE};
  dma_configure_stream(1U, 6U, d_config);
  dma_set_channel(1U, 6U, 4U, DMA_PRIORITY_VHI);

  /* Setup USART */
  usart_set_databits(USART_SEL_2, USART_STOPBITS_SB1, USART_DATABITS_DB8);
  usart_start(USART_SEL_2, 115200, USART_MODE_TX);
  usart_tx_message(USART_SEL_2, "Hello, USART!\t\n");

  /* MAIN CODE GOES HERE */
  while (TRUE) { ASM_NOP; }

  return 0;
}

/* Simple delay function in milliseconds */
void delay_ms(const uint32_t milliseconds) {
  uint32_t start = ticks;
  uint32_t end = start + milliseconds;

  if (end < start) {
    while (ticks > start) { ASM_NOP; };
  }

  while (ticks < end) { ASM_NOP; };
}
