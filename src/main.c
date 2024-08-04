/* Includes */
#include "common/defines.h"
#include "drivers/mcu_init.h"
#include "drivers/gpio.h"

int main(void) {
  mcu_init();

  /* GPIO test */
  gp_set_direction('A', 5U, (gp_dir_t)ou);
  gp_set_val('A', 5U, TRUE);
  ASM_BKPT;
  gp_set_val('A', 5U, FALSE);

  /* MAIN CODE GOES HERE */
  while (TRUE) { ASM_NOP; }

  return 0;
}
