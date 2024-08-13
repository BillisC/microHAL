#include <stdint.h>
#include "unity.h"
#include "gpio.h"

#define BANK_NUM(bank) ((uint8_t)bank - (uint8_t)'A')

struct GPIORegs test_regs[8] = {0};
struct GPIORegs *GPIO(const uint8_t bank) {
  return &test_regs[BANK_NUM(bank)];
}

void test_direction_functionality(void) {
  uint8_t bank_to_test = 'A';

  /* INPUT MODE */
  gp_set_direction(bank_to_test, 5U, GP_DIR_IN);
  TEST_ASSERT_EQUAL(0xA8000000UL, test_regs[BANK_NUM(bank_to_test)].MODER);
  /* OUTPUT MODE */
  gp_set_direction(bank_to_test, 0U, GP_DIR_OU);
  TEST_ASSERT_EQUAL(0xA8000001UL, test_regs[BANK_NUM(bank_to_test)].MODER);
  /* ALTERNATE MODE */
  gp_set_direction(bank_to_test, 2U, GP_DIR_AL);
  TEST_ASSERT_EQUAL(0xA8000021UL, test_regs[BANK_NUM(bank_to_test)].MODER);
  /* ANALOG MODE */
  gp_set_direction(bank_to_test, 6U, GP_DIR_AN);
  TEST_ASSERT_EQUAL(0xA8003021UL, test_regs[BANK_NUM(bank_to_test)].MODER);
}

void setUp() {
  /* Initialize moder registers */
  test_regs[0U].MODER = 0xA8000000UL;
  test_regs[1U].MODER = 0x00000280UL;
  /* Initialize ospeedr registers */
  test_regs[1U].OSPEEDR = 0x000000C0UL;
  /* Initialize pupdr registers */
  test_regs[0U].PUPDR = 0x64000000UL;
  test_regs[1U].PUPDR = 0x00000100UL;
}

void tearDown() {}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_direction_functionality);
  return UNITY_END();
}
