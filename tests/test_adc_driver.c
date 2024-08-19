/** @file test_adc_driver.c
 *  @brief Unit tests for the ADC driver
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
#include "adc.h"

struct ADCRegs empty_regs = {0};
struct ADCRegs test_regs[ADC_NUM + 1];
struct ADCRegs *ADC_(const uint8_t number) {
  return &test_regs[number - 1];
}

struct ADCCommonRegs empty_cregs = {0};
struct ADCCommonRegs test_cregs;
struct ADCCommonRegs *ADC_COMMON = &test_cregs;

void Test_ADCSetPrescaler_EdgeCase_RegisterShouldSetProperly(void) {
  adc_set_prescaler(ADC_PRESCALER_DIV8);
  TEST_ASSERT_EQUAL_HEX32(0x00030000UL, test_cregs.CCR);
}

void Test_ADCSetPrescaler_PrescaleIsInvalid_RegisterShouldNotSet(void) {
  adc_set_prescaler(0x4U);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_cregs.CCR);
}

void Test_ADCSetResolution_EdgeCase_RegisterShouldSetProperly(void) {
  adc_set_resolution(ADC_NUM, ADC_RES_B06);
  TEST_ASSERT_EQUAL_HEX32(0x03000000UL, test_regs[ADC_NUM - 1].CR1);
}

void Test_ADCSetResolution_ADCIsInvalid_RegisterShouldNotSet(void) {
  adc_set_resolution(ADC_NUM + 1, ADC_RES_B06);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[ADC_NUM].CR1);
}

void Test_ADCSetResolution_ResolutionIsInvalid_RegisterShouldNotSet(void) {
  adc_set_resolution(1U, 0x4U);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[0].CR1);
}

void Test_ADCSetSamplerate_EdgeCase_RegisterShouldSetProperly(void) {
  adc_set_samplerate(ADC_NUM, 18U, ADC_SAMPLERATE_C480);
  TEST_ASSERT_EQUAL_HEX32(0x07000000UL, test_regs[ADC_NUM - 1].SMPR[0]);
}

void Test_ADCSetSamplerate_ADCIsInvalid_RegisterShouldNotSet(void) {
  adc_set_samplerate(ADC_NUM + 1, 18U, ADC_SAMPLERATE_C480);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[ADC_NUM].SMPR[0]);
}

void Test_ADCSetSamplerate_ChannelIsInvalid_RegisterShouldNotSet(void) {
  adc_set_samplerate(1U, 19U, ADC_SAMPLERATE_C480);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[0].SMPR[0]);
}

void Test_ADCSetSamplerate_SamplerateIsInvalid_RegisterShouldNotSet(void) {
  adc_set_samplerate(1U, 0U, 0x8U);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[0].SMPR[1]);
}

void Test_ADCSetModes_EdgeCase_RegistersShouldSetProperly(void) {
  struct ADCModes modes = {1U, 1U, 1U, 1U, 1U};
  adc_set_modes(ADC_NUM, modes);
  TEST_ASSERT_EQUAL_HEX32_MESSAGE(0x00000900UL, test_regs[ADC_NUM - 1].CR1,
                                  "Register is CR1");
  TEST_ASSERT_EQUAL_HEX32_MESSAGE(0x00000302UL, test_regs[ADC_NUM - 1].CR2,
                                  "Register is CR2");
}

void Test_ADCSetModes_ADCIsInvalid_RegistersShouldNotSet(void) {
  struct ADCModes modes = {1U, 1U, 1U, 1U, 1U};
  adc_set_modes(ADC_NUM + 1, modes);
  TEST_ASSERT_EQUAL_HEX32_MESSAGE(0x00000000UL, test_regs[ADC_NUM].CR1,
                                  "Register is CR1");
  TEST_ASSERT_EQUAL_HEX32_MESSAGE(0x00000000UL, test_regs[ADC_NUM].CR2,
                                  "Register is CR2");
}

void Test_ADCSetSeq_EdgeCase_RegistersShouldSetProperly(void) {
  uint8_t seq[16] = {0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12,
                     0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12, 0x12};
  adc_set_seq(ADC_NUM, seq, 15U);
  TEST_ASSERT_EQUAL_HEX32_MESSAGE(0x00F94A52UL, test_regs[ADC_NUM - 1].SQR[0],
                                  "Register is SQR1");
  TEST_ASSERT_EQUAL_HEX32_MESSAGE(0x25294A52UL, test_regs[ADC_NUM - 1].SQR[1],
                                  "Register is SQR2");
  TEST_ASSERT_EQUAL_HEX32_MESSAGE(0x25294A52UL, test_regs[ADC_NUM - 1].SQR[2],
                                  "Register is SQR3");
}

void Test_ADCSetSeq_ADCIsInvalid_RegistersShouldNotSet(void) {
  uint8_t seq[16] = {0x12, 0x00, 0x12, 0x12, 0x12, 0x00, 0x12, 0x00,
                     0x00, 0x12, 0x12, 0x12, 0x00, 0x12, 0x12, 0x12};
  adc_set_seq(ADC_NUM + 1, seq, 15U);
  TEST_ASSERT_EQUAL_HEX32_MESSAGE(0x00000000UL, test_regs[ADC_NUM].SQR[0],
                                  "Register is SQR1");
  TEST_ASSERT_EQUAL_HEX32_MESSAGE(0x00000000UL, test_regs[ADC_NUM].SQR[1],
                                  "Register is SQR2");
  TEST_ASSERT_EQUAL_HEX32_MESSAGE(0x00000000UL, test_regs[ADC_NUM].SQR[2],
                                  "Register is SQR3");
}

void Test_ADCSetSeq_SomeSequencesAreInvalid_ShouldClearTheirRegisterBits(void) {
  uint8_t seq[16] = {0x13, 0x12, 0x12, 0x12, 0x12, 0x12, 0x13, 0x12,
                     0x12, 0x12, 0x12, 0x12, 0x13, 0x12, 0x12, 0x12};
  adc_set_seq(1U, seq, 15U);
  TEST_ASSERT_EQUAL_HEX32_MESSAGE(0x00F94A40UL, test_regs[0].SQR[0],
                                  "Register is SQR1");
  TEST_ASSERT_EQUAL_HEX32_MESSAGE(0x25294A40UL, test_regs[0].SQR[1],
                                  "Register is SQR2");
  TEST_ASSERT_EQUAL_HEX32_MESSAGE(0x25294A40UL, test_regs[0].SQR[2],
                                  "Register is SQR3");
}

void Test_ADCSetSeq_CountIsInvalid_ShouldClearItsRegisterBits(void) {
  uint8_t seq[16] = {0};
  adc_set_seq(1U, seq, 18U);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[0].SQR[0]);
}

void Test_ADCOn_EdgeCase_RegisterShouldSetProperly(void) {
  adc_on(ADC_NUM);
  TEST_ASSERT_EQUAL_HEX32(0x40000001UL, test_regs[ADC_NUM - 1].CR2);
}

void Test_ADCOn_ADCIsInvalid_RegisterShouldNotSet(void) {
  adc_on(ADC_NUM + 1);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[ADC_NUM].CR2);
}

void Test_ADCOff_EdgeCase_RegisterShouldSetProperly(void) {
  test_regs[ADC_NUM - 1].CR2 = 0x00000001UL;
  adc_off(ADC_NUM);
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, test_regs[ADC_NUM - 1].CR2);
}

void Test_ADCOff_ADCIsInvalid_RegisterShouldNotSet(void) {
  test_regs[ADC_NUM].CR2 = 0x00000001UL;
  adc_off(ADC_NUM + 1);
  TEST_ASSERT_EQUAL_HEX32(0x00000001UL, test_regs[ADC_NUM].CR2);
}

void Test_ADCRead_EdgeCase_RegisterShouldBeReadProperly(void) {
  test_regs[ADC_NUM - 1].DR = 0xFFFFFFFFUL;
  test_regs[ADC_NUM - 1].SR = 0x00000002UL;
  TEST_ASSERT_EQUAL_HEX32(0x0000FFFFUL, adc_read(ADC_NUM));
}

void Test_ADCRead_ADCIsInvalid_RegisterShouldNotBeRead(void) {
  test_regs[ADC_NUM].DR = 0xFFFFFFFFUL;
  test_regs[ADC_NUM].SR = 0x00000002UL;
  TEST_ASSERT_EQUAL_HEX32(0x00000000UL, adc_read(ADC_NUM + 1));
}

void setUp(void) {
  for (uint8_t i = 0; i < 3; i++) { test_regs[i] = empty_regs; }
  test_cregs = empty_cregs;
}

void tearDown(void) {}

int main(void) {
  UNITY_BEGIN();

  /* adc_set_prescaler() */
  RUN_TEST(Test_ADCSetPrescaler_EdgeCase_RegisterShouldSetProperly);
  RUN_TEST(Test_ADCSetPrescaler_PrescaleIsInvalid_RegisterShouldNotSet);
  /* adc_set_resolution() */
  RUN_TEST(Test_ADCSetResolution_EdgeCase_RegisterShouldSetProperly);
  RUN_TEST(Test_ADCSetResolution_ADCIsInvalid_RegisterShouldNotSet);
  RUN_TEST(Test_ADCSetResolution_ResolutionIsInvalid_RegisterShouldNotSet);
  /* adc_set_samplerate() */
  RUN_TEST(Test_ADCSetSamplerate_EdgeCase_RegisterShouldSetProperly);
  RUN_TEST(Test_ADCSetSamplerate_ADCIsInvalid_RegisterShouldNotSet);
  RUN_TEST(Test_ADCSetSamplerate_ChannelIsInvalid_RegisterShouldNotSet);
  RUN_TEST(Test_ADCSetSamplerate_SamplerateIsInvalid_RegisterShouldNotSet);
  /* adc_set_modes() */
  RUN_TEST(Test_ADCSetModes_EdgeCase_RegistersShouldSetProperly);
  RUN_TEST(Test_ADCSetModes_ADCIsInvalid_RegistersShouldNotSet);
  /* adc_set_seq() */
  RUN_TEST(Test_ADCSetSeq_EdgeCase_RegistersShouldSetProperly);
  RUN_TEST(Test_ADCSetSeq_ADCIsInvalid_RegistersShouldNotSet);
  RUN_TEST(Test_ADCSetSeq_SomeSequencesAreInvalid_ShouldClearTheirRegisterBits);
  RUN_TEST(Test_ADCSetSeq_CountIsInvalid_ShouldClearItsRegisterBits);
  /* adc_on() */
  RUN_TEST(Test_ADCOn_EdgeCase_RegisterShouldSetProperly);
  RUN_TEST(Test_ADCOn_ADCIsInvalid_RegisterShouldNotSet);
  /* adc_off() */
  RUN_TEST(Test_ADCOff_EdgeCase_RegisterShouldSetProperly);
  RUN_TEST(Test_ADCOff_ADCIsInvalid_RegisterShouldNotSet);
  /* adc_read() */
  RUN_TEST(Test_ADCRead_EdgeCase_RegisterShouldBeReadProperly);
  RUN_TEST(Test_ADCRead_ADCIsInvalid_RegisterShouldNotBeRead);

  return UNITY_END();
}
