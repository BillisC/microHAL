/** @file main.c
 *  @brief Simple main function with example
 *
 *  @author Vasileios Ch. (BillisC)
 *  @bug None, yet.
 */

/* Includes */
#include "defines.h"
#include "_init.h"
#include "usart.h"
#include "gpio.h"
#include "spi.h"

void delay_ms(const uint32_t milliseconds);

int main(void) {
  mcu_init();

  /* Setup SPI Slave */
  /* NSS */
  gp_set_direction(GP_BANK_B, 12, GP_DIR_AL);
  gp_set_af(GP_BANK_B, 12, 5U);
  gp_set_speed(GP_BANK_B, 12, GP_SPEED_HIG);
  /* CK */
  gp_set_direction(GP_BANK_B, 13, GP_DIR_AL);
  gp_set_af(GP_BANK_B, 13, 5U);
  gp_set_speed(GP_BANK_B, 13, GP_SPEED_HIG);
  /* MISO */
  gp_set_direction(GP_BANK_B, 14, GP_DIR_AL);
  gp_set_af(GP_BANK_B, 14, 5U);
  gp_set_speed(GP_BANK_B, 14, GP_SPEED_HIG);
  /* MOSI */
  gp_set_direction(GP_BANK_B, 15, GP_DIR_AL);
  gp_set_af(GP_BANK_B, 15, 5U);
  gp_set_speed(GP_BANK_B, 15, GP_SPEED_HIG);

  spi_set_direction(SPI_PERIPH_2, SPI_DIR_FULL_DUPLEX);
  spi_set_nss_mode(SPI_PERIPH_2, SPI_NSS_SOFT_LO);
  spi_start(SPI_PERIPH_2, FALSE);

  /* Setup SPI Master */
  /* NSS */
  gp_set_direction(GP_BANK_A, 4, GP_DIR_OU);
  gp_set_val(GP_BANK_A, 4, FALSE);
  /* CK */
  gp_set_direction(GP_BANK_A, 5, GP_DIR_AL);
  gp_set_af(GP_BANK_A, 5, 5U);
  gp_set_speed(GP_BANK_A, 5, GP_SPEED_HIG);
  /* MISO */
  gp_set_direction(GP_BANK_A, 6, GP_DIR_AL);
  gp_set_af(GP_BANK_A, 6, 5U);
  gp_set_speed(GP_BANK_A, 6, GP_SPEED_HIG);
  /* MOSI */
  gp_set_direction(GP_BANK_A, 7, GP_DIR_AL);
  gp_set_af(GP_BANK_A, 7, 5U);
  gp_set_speed(GP_BANK_A, 7, GP_SPEED_HIG);

  spi_set_direction(SPI_PERIPH_1, SPI_DIR_FULL_DUPLEX);
  spi_set_prescaler(SPI_PERIPH_1, SPI_PRESCALER_DIV_4); // 22.5MHz
  spi_set_nss_mode(SPI_PERIPH_1, SPI_NSS_SOFT_HI);
  spi_start(SPI_PERIPH_1, TRUE);

  spi_tx_data(SPI_PERIPH_1, 0);
  uint16_t data = spi_rx_data(SPI_PERIPH_2);
  ASM_BKPT;

  /* MAIN CODE GOES HERE */
  while (TRUE) {
    // usart_tx_message(USART_PERIPH_2, message);
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
