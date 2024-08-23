/** @file main.c
 *  @brief Simple main function with example
 *
 *  @author Vasileios Ch. (BillisC)
 *  @bug None, yet.
 */

/* Includes */
#include "defines.h"
#include "interrupts.h"
#include "mcu_init.h"
#include "usart.h"
#include "gpio.h"

void delay_ms(const uint32_t milliseconds);

/* Message to send */
const char *message = "Just a test message!\r\n";

int main(void) {
  mcu_init();

  /* Setup GPIO for USART TX communication */
  gp_set_direction(GP_BANK_A, 2, GP_DIR_AL);
  gp_set_af(GP_BANK_A, 2, 7U);
  gp_set_speed(GP_BANK_A, 2, GP_SPEED_HIG);

  /* Setup USART */
  usart_set_dma(USART_PERIPH_2, TRUE, FALSE);
  usart_set_databits(USART_PERIPH_2, USART_STOPBITS_SB1, USART_DATABITS_DB8);
  usart_start(USART_PERIPH_2, 115200, USART_MODE_TX);

  /* MAIN CODE GOES HERE */
  while (TRUE) {
    usart_tx_message(USART_PERIPH_2, message);
    delay_ms(1000U);
  }

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
