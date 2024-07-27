/* Includes */
#include "stm32f4xx.h"
#include "common/defines.h"
#include "drivers/mcu_init.h"
#include "drivers/gpio.h"

int main() {
  mcu_init();
  ASM_BKPT;

  /* MAIN CODE GOES HERE */
  while (TRUE) { ASM_NOP; }

  return 0;
}
