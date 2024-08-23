cmake_minimum_required(VERSION 3.21)

set(CMAKE_BUILD_TYPE Debug)
project(exec C)

enable_language(ASM)

# Path definitions
set(EXTERNAL "${CMAKE_SOURCE_DIR}/external")
set(STUBS "${CMAKE_SOURCE_DIR}/tests/stubs")
if (CMAKE_CROSSCOMPILING)
  set(CMSIS_CORE "${EXTERNAL}/CMSIS/CMSIS/Core/Include/")
  set(CMSIS_DEVICE "${EXTERNAL}/CMSIS/Device/ST/STM32F4/Include/")
  set(CMSIS_SYSTEM "${EXTERNAL}/CMSIS/Device/ST/STM32F4/Source/Templates/system_stm32f4xx.c")
else ()
  # Set CMSIS mock headers
  set(CMSIS_CORE "")
  set(CMSIS_DEVICE "${STUBS}/CMSIS/")
  set(CMSIS_SYSTEM "${STUBS}/CMSIS/system_stm32f4xx.c")
endif ()

# Needed to make clangd functional
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Chip specific flags
set(CHIP STM32F446xx)
set(MCU_FLAGS "-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16")

# Common compiler flags
set(CC_WARNS "-Wall -Wextra -Werror -Wno-unused-but-set-variable -pedantic")
set(CC_FLAGS ${C_WARNS} -std=gnu17)

if (CMAKE_CROSSCOMPILING)
  message("Toolchain detected, will cross compile for ARM")

  # GCC ARM compiler flags
  set(CMAKE_C_FLAGS "${MCU_FLAGS} ${CC_FLAGS} -nostdlib -Wl,-Map=${PROJECT_NAME}.map")
  set(C_DEFINES ${CHIP})

  # Linker flags
  set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/linker_script.ld")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${LINKER_SCRIPT}")

  # Compile drivers
  add_subdirectory(${CMAKE_SOURCE_DIR}/src/drivers)

  # Source compilation
  add_subdirectory(src)
else ()
  message("No toolchain specified, will run unit tests natively")

  # GCC ARM compiler flags
  set(CMAKE_C_FLAGS "${CC_FLAGS} -Wno-int-to-pointer-cast -fsanitize=address")
  set(C_DEFINES ${CHIP} UTEST)

  # Unit test frameworks
  include(CTest)
  add_subdirectory(${EXTERNAL}/unity)

  # Compile drivers
  add_subdirectory(${CMAKE_SOURCE_DIR}/src/drivers)

  # Source compilation
  add_subdirectory(tests)
endif ()

# Static Analysis
set(ALZ cppcheck)
set(ALZ_TARGET ${CMAKE_SOURCE_DIR}/src/)
set(ALZ_FLAGS --enable=all
              --error-exitcode=1
              --force
              --suppress=missingInclude # Will not check CMSIS too
              --suppress=unusedFunction # This is a template source
              --suppress=knownConditionTrueFalse # Issue with SysTick interrupt
              -DCPPCHECK
              -I ${CMAKE_SOURCE_DIR}/src/
              -I ${CMAKE_SOURCE_DIR}/src/common/
              -I ${CMAKE_SOURCE_DIR}/src/drivers/
              -I ${CMSIS_DEVICE})

add_custom_target(analysis
  COMMAND ${ALZ} ${ALZ_FLAGS} ${ALZ_TARGET}
  COMMENT "Performing static analysis"
)
