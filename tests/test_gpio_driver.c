/* -- Includes -- */
#include <stdint.h>
#include "unity.h"
#include "gpio.h"
#include "unity_internals.h"

#define BANK_NUM(bank) ((uint8_t)bank - (uint8_t)'A')

/* 8 banks + 1 arbitrary */
struct GPIORegs test_regs[9] = {0};
struct GPIORegs *GPIO(const uint8_t bank) {
  return &test_regs[BANK_NUM(bank)];
}

void direction_highest_set_valid(void) {
  test_regs[BANK_NUM('H')].MODER = 0x00000000UL;
  gp_set_direction('H', 15U, GP_DIR_AN);
  TEST_ASSERT_EQUAL_HEX32(0xC0000000UL, test_regs[BANK_NUM('H')].MODER);
}

void direction_arbitrary_set_invalid_dir(void) {
  test_regs[BANK_NUM('B')].MODER = 0x00000000UL;
  gp_set_direction('B', 3U, 0x4U);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM('B')].MODER);
}

void direction_arbitrary_set_invalid_bank(void) {
  test_regs[BANK_NUM('I')].MODER = 0x00000000UL;
  gp_set_direction('I', 0U, GP_DIR_OU);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM('I')].MODER);
}

void direction_arbitrary_set_invalid_pin(void) {
  test_regs[BANK_NUM('B')].MODER = 0x00000000UL;
  gp_set_direction('B', 16U, GP_DIR_OU);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM('B')].MODER);
}

void otype_highest_set_valid(void) {
  test_regs[BANK_NUM('H')].OTYPER = 0x00000000UL;
  gp_set_output_type('H', 15U, GP_OTYPE_OD);
  TEST_ASSERT_EQUAL_HEX32(0x00008000UL, test_regs[BANK_NUM('H')].OTYPER);
}

void otype_arbitrary_set_invalid_type(void) {
  test_regs[BANK_NUM('A')].OTYPER = 0x00000000UL;
  gp_set_output_type('A', 0U, 0x3U);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM('A')].OTYPER);
}

void otype_arbitrary_set_invalid_bank(void) {
  test_regs[BANK_NUM('I')].OTYPER = 0x00000000UL;
  gp_set_output_type('I', 0U, GP_OTYPE_OD);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM('I')].OTYPER);
}

void otype_arbitrary_set_invalid_pin(void) {
  test_regs[BANK_NUM('A')].OTYPER = 0x00000000UL;
  gp_set_output_type('A', 16U, GP_OTYPE_OD);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM('A')].OTYPER);
}

void speed_highest_set_valid(void) {
  test_regs[BANK_NUM('H')].OSPEEDR = 0x00000000UL;
  gp_set_speed('H', 15U, GP_SPEED_HIG);
  TEST_ASSERT_EQUAL_HEX32(0xC0000000UL, test_regs[BANK_NUM('H')].OSPEEDR);
}

void speed_arbitrary_set_invalid_speed(void) {
  test_regs[BANK_NUM('A')].OSPEEDR = 0x00000000UL;
  gp_set_speed('A', 0U, 0x4U);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM('A')].OSPEEDR);
}

void speed_arbitrary_set_invalid_bank(void) {
  test_regs[BANK_NUM('I')].OSPEEDR = 0x00000000UL;
  gp_set_speed('I', 0U, GP_SPEED_HIG);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM('I')].OSPEEDR);
}

void speed_arbitrary_set_invalid_pin(void) {
  test_regs[BANK_NUM('A')].OSPEEDR = 0x00000000UL;
  gp_set_speed('A', 16U, GP_SPEED_HIG);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM('A')].OSPEEDR);
}

void pupd_highest_set_valid(void) {
  test_regs[BANK_NUM('H')].PUPDR = 0x00000000UL;
  gp_set_pupd('H', 15U, GP_PUPD_PLDO);
  TEST_ASSERT_EQUAL_HEX32(0x80000000UL, test_regs[BANK_NUM('H')].PUPDR);
}

void pupd_arbitrary_set_invalid_pupd(void) {
  test_regs[BANK_NUM('A')].PUPDR = 0x00000000UL;
  gp_set_pupd('A', 0U, 0x3U);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM('A')].PUPDR);
}

void pupd_arbitrary_set_invalid_bank(void) {
  test_regs[BANK_NUM('I')].PUPDR = 0x00000000UL;
  gp_set_pupd('I', 0U, GP_PUPD_PLDO);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM('I')].PUPDR);
}

void pupd_arbitrary_set_invalid_pin(void) {
  test_regs[BANK_NUM('A')].PUPDR = 0x00000000UL;
  gp_set_pupd('A', 16U, GP_PUPD_PLDO);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM('A')].PUPDR);
}

void val_high_set_valid(void) {
  test_regs[BANK_NUM('H')].BSSR = 0x00000000UL;
  gp_set_val('H', 15U, 1U);
  TEST_ASSERT_EQUAL_HEX32(0x00008000UL, test_regs[BANK_NUM('H')].BSSR);
}

void val_arbitrary_set_invalid_bank(void) {
  test_regs[BANK_NUM('I')].BSSR = 0x00000000UL;
  gp_set_val('I', 0U, 1U);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM('I')].BSSR);
}

void val_arbitrary_set_invalid_pin(void) {
  test_regs[BANK_NUM('A')].BSSR = 0x00000000UL;
  gp_set_val('A', 16U, 1U);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM('A')].BSSR);
}

void read_high_get_valid(void) {
  test_regs[BANK_NUM('A')].IDR = 0x00000004UL;
  TEST_ASSERT_EQUAL_HEX8(0x01U, gp_read_val('A', 2U));
}

void read_arbitrary_get_invalid_bank(void) {
  test_regs[BANK_NUM('I')].IDR = 0x00000004UL;
  TEST_ASSERT_EQUAL_HEX8(0x00U, gp_read_val('I', 2U));
}

void read_arbitrary_get_invalid_pin(void) {
  test_regs[BANK_NUM('A')].IDR = 0x00010000UL;
  TEST_ASSERT_EQUAL_HEX8(0x00U, gp_read_val('A', 16U));
}

void af_highest_set_valid(void) {
  test_regs[BANK_NUM('H')].AFR[1] = 0x00000000UL;
  gp_set_af('H', 15U, 15U);
  TEST_ASSERT_EQUAL_HEX32(0xF0000000UL, test_regs[BANK_NUM('H')].AFR[1]);
}

void af_arbitrary_set_invalid_af(void) {
  test_regs[BANK_NUM('A')].AFR[0] = 0x00000000UL;
  gp_set_af('A', 0U, 16U);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM('A')].AFR[0]);
}

void af_arbitrary_set_invalid_bank(void) {
  test_regs[BANK_NUM('I')].AFR[0] = 0x00000000UL;
  gp_set_af('I', 0U, 1U);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM('I')].AFR[0]);
}

void af_arbitrary_set_invalid_pin(void) {
  test_regs[BANK_NUM('A')].AFR[1] = 0x00000000UL;
  gp_set_af('A', 16U, 1U);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM('A')].AFR[1]);
}

void setUp() {}

void tearDown() {}

int main(void) {
  UNITY_BEGIN();

  /* gp_set_direction() */
  RUN_TEST(direction_highest_set_valid);
  RUN_TEST(direction_arbitrary_set_invalid_dir);
  RUN_TEST(direction_arbitrary_set_invalid_bank);
  RUN_TEST(direction_arbitrary_set_invalid_pin);
  /* gp_set_output_type() */
  RUN_TEST(otype_highest_set_valid);
  RUN_TEST(otype_arbitrary_set_invalid_type);
  RUN_TEST(otype_arbitrary_set_invalid_bank);
  RUN_TEST(otype_arbitrary_set_invalid_pin);
  /* gp_set_speed() */
  RUN_TEST(speed_highest_set_valid);
  RUN_TEST(speed_arbitrary_set_invalid_speed);
  RUN_TEST(speed_arbitrary_set_invalid_bank);
  RUN_TEST(speed_arbitrary_set_invalid_pin);
  /* gp_set_pupd() */
  RUN_TEST(pupd_highest_set_valid);
  RUN_TEST(pupd_arbitrary_set_invalid_pupd);
  RUN_TEST(pupd_arbitrary_set_invalid_bank);
  RUN_TEST(pupd_arbitrary_set_invalid_pin);
  /* gp_set_val() */
  RUN_TEST(val_high_set_valid);
  RUN_TEST(val_arbitrary_set_invalid_bank);
  RUN_TEST(val_arbitrary_set_invalid_pin);
  /* gp_read_val() */
  RUN_TEST(read_high_get_valid);
  RUN_TEST(read_arbitrary_get_invalid_bank);
  RUN_TEST(read_arbitrary_get_invalid_pin);
  /* gp_set_af() */
  RUN_TEST(af_highest_set_valid);
  RUN_TEST(af_arbitrary_set_invalid_af);
  RUN_TEST(af_arbitrary_set_invalid_bank);
  RUN_TEST(af_arbitrary_set_invalid_pin);

  return UNITY_END();
}
