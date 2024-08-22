/** @file test_gpio_driver.c
 *  @brief Unit tests for the GPIO driver
 *
 *  The unit tests defined in this file handle
 *  mostly invalid parameter and edge cases in a
 *  stubbed environment. The purpose of these tests
 *  is logic checking and does not reflect the
 *  actual behaviour of registers in real MCUs.
 *
 *  @author Vasileios Ch. (BillisC)
 */

/* -- Includes -- */
#include <stdint.h>
#include "unity.h"
#include "gpio.h"

#define BANK_NUM(bank) ((uint8_t)bank - (uint8_t)'A')

/* 8 banks + 1 arbitrary
 * GP_BANK_LEN is the letter after the last bank
 * and when substracted with 'A' it returns the
 * number of banks!
 */
struct GPIORegs test_regs[(GP_BANK_LEN - 'A') + 1] = {0};
struct GPIORegs *GPIO(const uint8_t bank) {
  return &test_regs[BANK_NUM(bank)];
}

void Test_GPIOSetDirection_EdgeCase_ShouldSetRegisterProperly(void) {
  test_regs[BANK_NUM(GP_BANK_LEN - 1)].MODER = 0x00000000UL;
  gp_set_direction(GP_BANK_LEN - 1, 15U, GP_DIR_AN);
  TEST_ASSERT_EQUAL_HEX32(0xC0000000UL,
                          test_regs[BANK_NUM(GP_BANK_LEN - 1)].MODER);
}

void Test_GPIOSetDirection_DirectionIsInvalid_ShouldNotSetRegister(void) {
  test_regs[BANK_NUM('A')].MODER = 0x00000000UL;
  gp_set_direction('A', 3U, 0x4U);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM('A')].MODER);
}

void Test_GPIOSetDirection_BankIsInvalid_ShouldNotSetRegister(void) {
  test_regs[BANK_NUM(GP_BANK_LEN)].MODER = 0x00000000UL;
  gp_set_direction(GP_BANK_LEN, 0U, GP_DIR_OU);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM(GP_BANK_LEN)].MODER);
}

void Test_GPIOSetDirection_PinIsInvalid_ShouldNotSetRegister(void) {
  test_regs[BANK_NUM('A')].MODER = 0x00000000UL;
  gp_set_direction('A', 16U, GP_DIR_OU);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM('A')].MODER);
}

void Test_GPIOSetOType_EdgeCase_ShouldSetRegisterProperly(void) {
  test_regs[BANK_NUM(GP_BANK_LEN - 1)].OTYPER = 0x00000000UL;
  gp_set_output_type(GP_BANK_LEN - 1, 15U, GP_OTYPE_OD);
  TEST_ASSERT_EQUAL_HEX32(0x00008000UL,
                          test_regs[BANK_NUM(GP_BANK_LEN - 1)].OTYPER);
}

void Test_GPIOSetOType_TypeIsInvalid_ShouldNotSetRegister(void) {
  test_regs[BANK_NUM('A')].OTYPER = 0x00000000UL;
  gp_set_output_type('A', 0U, 0x3U);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM('A')].OTYPER);
}

void Test_GPIOSetOType_BankIsInvalid_ShouldNotSetRegister(void) {
  test_regs[BANK_NUM(GP_BANK_LEN)].OTYPER = 0x00000000UL;
  gp_set_output_type(GP_BANK_LEN, 0U, GP_OTYPE_OD);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL,
                          test_regs[BANK_NUM(GP_BANK_LEN)].OTYPER);
}

void Test_GPIOSetOType_PinIsInvalid_ShouldNotSetRegister(void) {
  test_regs[BANK_NUM('A')].OTYPER = 0x00000000UL;
  gp_set_output_type('A', 16U, GP_OTYPE_OD);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM('A')].OTYPER);
}

void Test_GPIOSetSpeed_EdgeCase_ShouldSetRegisterProperly(void) {
  test_regs[BANK_NUM(GP_BANK_LEN - 1)].OSPEEDR = 0x00000000UL;
  gp_set_speed(GP_BANK_LEN - 1, 15U, GP_SPEED_HIG);
  TEST_ASSERT_EQUAL_HEX32(0xC0000000UL,
                          test_regs[BANK_NUM(GP_BANK_LEN - 1)].OSPEEDR);
}

void Test_GPIOSetSpeed_SpeedIsInvalid_ShouldNotSetRegister(void) {
  test_regs[BANK_NUM('A')].OSPEEDR = 0x00000000UL;
  gp_set_speed('A', 0U, 0x4U);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM('A')].OSPEEDR);
}

void Test_GPIOSetSpeed_BankIsInvalid_ShouldNotSetRegister(void) {
  test_regs[BANK_NUM(GP_BANK_LEN)].OSPEEDR = 0x00000000UL;
  gp_set_speed(GP_BANK_LEN, 0U, GP_SPEED_HIG);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL,
                          test_regs[BANK_NUM(GP_BANK_LEN)].OSPEEDR);
}

void Test_GPIOSetSpeed_PinIsInvalid_ShouldNotSetRegister(void) {
  test_regs[BANK_NUM('A')].OSPEEDR = 0x00000000UL;
  gp_set_speed('A', 16U, GP_SPEED_HIG);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM('A')].OSPEEDR);
}

void Test_GPIOSetPUPD_EdgeCase_ShouldSetRegisterProperly(void) {
  test_regs[BANK_NUM(GP_BANK_LEN - 1)].PUPDR = 0x00000000UL;
  gp_set_pupd(GP_BANK_LEN - 1, 15U, GP_PUPD_PLDO);
  TEST_ASSERT_EQUAL_HEX32(0x80000000UL,
                          test_regs[BANK_NUM(GP_BANK_LEN - 1)].PUPDR);
}

void Test_GPIOSetPUPD_PUPDIsInvalid_ShouldNotSetRegister(void) {
  test_regs[BANK_NUM('A')].PUPDR = 0x00000000UL;
  gp_set_pupd('A', 0U, 0x3U);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM('A')].PUPDR);
}

void Test_GPIOSetPUPD_BankIsInvalid_ShouldNotSetRegister(void) {
  test_regs[BANK_NUM(GP_BANK_LEN)].PUPDR = 0x00000000UL;
  gp_set_pupd(GP_BANK_LEN, 0U, GP_PUPD_PLDO);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM(GP_BANK_LEN)].PUPDR);
}

void Test_GPIOSetPUPD_PinIsInvalid_ShouldNotSetRegister(void) {
  test_regs[BANK_NUM('A')].PUPDR = 0x00000000UL;
  gp_set_pupd('A', 16U, GP_PUPD_PLDO);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM('A')].PUPDR);
}

void Test_GPIOSetVal_EdgeCase_ShouldSetRegisterProperly(void) {
  test_regs[BANK_NUM(GP_BANK_LEN - 1)].BSSR = 0x00000000UL;
  gp_set_val(GP_BANK_LEN - 1, 15U, 1U);
  TEST_ASSERT_EQUAL_HEX32(0x00008000UL,
                          test_regs[BANK_NUM(GP_BANK_LEN - 1)].BSSR);
}

void Test_GPIOSetVal_BankIsInvalid_ShouldNotSetRegister(void) {
  test_regs[BANK_NUM(GP_BANK_LEN)].BSSR = 0x00000000UL;
  gp_set_val(GP_BANK_LEN, 0U, 1U);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM(GP_BANK_LEN)].BSSR);
}

void Test_GPIOSetVal_PinIsInvalid_ShouldNotSetRegister(void) {
  test_regs[BANK_NUM('A')].BSSR = 0x00000000UL;
  gp_set_val('A', 16U, 1U);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM('A')].BSSR);
}

void Test_GPIORead_EdgeCase_ShouldSetRegisterProperly(void) {
  test_regs[BANK_NUM('A')].IDR = 0x00000004UL;
  TEST_ASSERT_EQUAL_HEX8(0x01U, gp_read_val('A', 2U));
}

void Test_GPIORead_BankIsInvalid_ShouldNotSetRegister(void) {
  test_regs[BANK_NUM(GP_BANK_LEN)].IDR = 0x00000004UL;
  TEST_ASSERT_EQUAL_HEX8(0x00U, gp_read_val(GP_BANK_LEN, 2U));
}

void Test_GPIORead_PinIsInvalid_ShouldNotSetRegister(void) {
  test_regs[BANK_NUM('A')].IDR = 0x00010000UL;
  TEST_ASSERT_EQUAL_HEX8(0x00U, gp_read_val('A', 16U));
}

void Test_GPIOSetAF_EdgeCase_ShouldSetRegisterProperly(void) {
  test_regs[BANK_NUM(GP_BANK_LEN - 1)].AFR[1] = 0x00000000UL;
  gp_set_af(GP_BANK_LEN - 1, 15U, 15U);
  TEST_ASSERT_EQUAL_HEX32(0xF0000000UL,
                          test_regs[BANK_NUM(GP_BANK_LEN - 1)].AFR[1]);
}

void Test_GPIOSetAF_AFIsInvalid_ShouldNotSetRegister(void) {
  test_regs[BANK_NUM('A')].AFR[0] = 0x00000000UL;
  gp_set_af('A', 0U, 16U);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM('A')].AFR[0]);
}

void Test_GPIOSetAF_BankIsInvalid_ShouldNotSetRegister(void) {
  test_regs[BANK_NUM(GP_BANK_LEN)].AFR[0] = 0x00000000UL;
  gp_set_af(GP_BANK_LEN, 0U, 1U);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL,
                          test_regs[BANK_NUM(GP_BANK_LEN)].AFR[0]);
}

void Test_GPIOSetAF_PinIsInvalid_ShouldNotSetRegister(void) {
  test_regs[BANK_NUM('A')].AFR[1] = 0x00000000UL;
  gp_set_af('A', 16U, 1U);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[BANK_NUM('A')].AFR[1]);
}

void setUp() {}

void tearDown() {}

int main(void) {
  UNITY_BEGIN();

  /* gp_set_direction() */
  RUN_TEST(Test_GPIOSetDirection_EdgeCase_ShouldSetRegisterProperly);
  RUN_TEST(Test_GPIOSetDirection_DirectionIsInvalid_ShouldNotSetRegister);
  RUN_TEST(Test_GPIOSetDirection_BankIsInvalid_ShouldNotSetRegister);
  RUN_TEST(Test_GPIOSetDirection_PinIsInvalid_ShouldNotSetRegister);
  /* gp_set_output_type() */
  RUN_TEST(Test_GPIOSetOType_EdgeCase_ShouldSetRegisterProperly);
  RUN_TEST(Test_GPIOSetOType_TypeIsInvalid_ShouldNotSetRegister);
  RUN_TEST(Test_GPIOSetOType_BankIsInvalid_ShouldNotSetRegister);
  RUN_TEST(Test_GPIOSetOType_PinIsInvalid_ShouldNotSetRegister);
  /* gp_set_speed() */
  RUN_TEST(Test_GPIOSetSpeed_EdgeCase_ShouldSetRegisterProperly);
  RUN_TEST(Test_GPIOSetSpeed_SpeedIsInvalid_ShouldNotSetRegister);
  RUN_TEST(Test_GPIOSetSpeed_BankIsInvalid_ShouldNotSetRegister);
  RUN_TEST(Test_GPIOSetSpeed_PinIsInvalid_ShouldNotSetRegister);
  /* gp_set_pupd() */
  RUN_TEST(Test_GPIOSetPUPD_EdgeCase_ShouldSetRegisterProperly);
  RUN_TEST(Test_GPIOSetPUPD_PUPDIsInvalid_ShouldNotSetRegister);
  RUN_TEST(Test_GPIOSetPUPD_BankIsInvalid_ShouldNotSetRegister);
  RUN_TEST(Test_GPIOSetPUPD_PinIsInvalid_ShouldNotSetRegister);
  /* gp_set_val() */
  RUN_TEST(Test_GPIOSetVal_EdgeCase_ShouldSetRegisterProperly);
  RUN_TEST(Test_GPIOSetVal_BankIsInvalid_ShouldNotSetRegister);
  RUN_TEST(Test_GPIOSetVal_PinIsInvalid_ShouldNotSetRegister);
  /* gp_read_val() */
  RUN_TEST(Test_GPIORead_EdgeCase_ShouldSetRegisterProperly);
  RUN_TEST(Test_GPIORead_BankIsInvalid_ShouldNotSetRegister);
  RUN_TEST(Test_GPIORead_PinIsInvalid_ShouldNotSetRegister);
  /* gp_set_af() */
  RUN_TEST(Test_GPIOSetAF_EdgeCase_ShouldSetRegisterProperly);
  RUN_TEST(Test_GPIOSetAF_AFIsInvalid_ShouldNotSetRegister);
  RUN_TEST(Test_GPIOSetAF_BankIsInvalid_ShouldNotSetRegister);
  RUN_TEST(Test_GPIOSetAF_PinIsInvalid_ShouldNotSetRegister);

  return UNITY_END();
}
