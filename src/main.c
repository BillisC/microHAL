/* Includes */
#include "defines.h"
#include "interrupts.h"
#include "mcu_init.h"
#include "usart.h"
#include "gpio.h"

void delay_ms(const uint32_t milliseconds);

int main(void) {
  mcu_init();

  /* Setup GPIO for USART TX communication */
  gp_set_direction('A', 2, GP_DIR_AL);
  gp_set_af('A', 2, 7U);
  gp_set_speed('A', 2, GP_SPEED_HIG);

  /* Setup USART */
  usart_set_dma(USART_SEL_2, TRUE, FALSE);
  usart_set_databits(USART_SEL_2, USART_STOPBITS_SB1, USART_DATABITS_DB8);
  usart_start(USART_SEL_2, 115200, USART_MODE_TX);

  /* Send message */
  const char *message = "Hello, USART!\r\n";
  usart_tx_message(USART_SEL_2, message);

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
