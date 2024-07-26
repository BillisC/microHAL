// Common
#include "common/defines.h"

// Drivers
#include "stm32f4xx.h"
#include "drivers/mcu_init.h"

int main() {
  mcu_init();
  ASM_BKPT;

  /* MAIN CODE GOES HERE */
  while (TRUE) { ASM_NOP; }

  return 0;
}
