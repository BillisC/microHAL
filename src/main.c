/* Includes */
#include "defines.h"
#include "mcu_init.h"
#include "gpio.h"
#include "adc.h"
#include "usart.h"

volatile uint16_t read = 0U;

int main(void) {
  mcu_init();

  /* GPIO test */
  // gp_set_direction('A', 5U, (gp_dir_t)ou);
  // gp_set_val('A', 5U, TRUE);
  //// ASM_BKPT;
  // gp_set_val('A', 5U, FALSE);
  //
  ///* ADC test */
  // gp_set_direction('A', 0U, (gp_dir_t)an);
  // struct adc_modes config = {FALSE, FALSE, FALSE, FALSE, FALSE};
  // adc_set_modes(1, config);
  // adc_set_prescaler((adc_prescaler_t)div4);
  // adc_set_samplerate(1, 0U, (adc_samplerate_t)c084);
  // adc_on(1);
  // read = adc_read(1);
  //// ASM_BKPT;

  /* USART test  */
  gp_set_direction('A', 2U, (gp_dir_t)al);
  gp_set_direction('A', 3U, (gp_dir_t)al);
  gp_set_af('A', 2U, 7U);
  gp_set_af('A', 3U, 7U);

  usart_init((usart_sel_t)usart2, 115200);

  char *message = "Hello, USART!";
  while (*message != '\0') {
    usart_write((usart_sel_t)usart2, *message++); // Send data
  }

  /* MAIN CODE GOES HERE */
  while (TRUE) { ASM_NOP; }

  return 0;
}
