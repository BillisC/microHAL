/* Includes */
#include "defines.h"
#include "interrupts.h"
#include "mcu_init.h"
#include "dma.h"
#include "gpio.h"
#include "usart.h"

void delay_ms(const uint32_t milliseconds);

volatile const char *MESSAGE = "Hello, USART!\r\n";

int main(void) {
  ASM_BKPT;
  mcu_init();

  /* Setup GPIO for USART TX communication */
  gp_set_direction('A', 2, GP_DIR_AL);
  gp_set_af('A', 2, 7U);
  gp_set_speed('A', 2, GP_SPEED_HIG);

  /* Setup DMA for USART communication */
  // *(uint32_t*)(0x40026010 + (24*6)) -> CR
  dma_set_addresses(1, 6, (uint32_t)&USART2->DR, (uint32_t)MESSAGE, 0UL);
  dma_set_direction(1, 6, DMA_DIR_MEM2PER);
  dma_configure_data(1, 6, 15U, DMA_DATASIZE_BYTE, DMA_DATASIZE_BYTE);
  struct DMAStreamConfig d_config = {TRUE, FALSE, FALSE, TRUE, FALSE};
  dma_configure_stream(1, 6, d_config);
  dma_set_channel(1, 6, 4, DMA_PRIORITY_VHI);
  dma_enable(1, 6);

  /* Setup USART */
  usart_set_dma(USART_SEL_2, TRUE, FALSE);
  usart_set_databits(USART_SEL_2, USART_STOPBITS_SB1, USART_DATABITS_DB8);
  usart_start(USART_SEL_2, 115200, USART_MODE_TX);

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
