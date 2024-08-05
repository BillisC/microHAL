cmake_minimum_required(VERSION 3.20)
project(release C)

enable_language(ASM)

# Folder that includes CMSIS etc.
set(EXTERNAL "${CMAKE_SOURCE_DIR}/external")

# GCC ARM compiler flags
set(C_WARNS "-Wall -Wextra -Werror -Wno-unused-but-set-variable -pedantic")
set(MCU_FLAGS "-mcpu=cortex-m4 -mthumb -DSTM32F446xx")
set(CMAKE_C_FLAGS "-g -Og ${MCU_FLAGS} ${C_WARNS} -nostdlib -std=gnu17 -Wl,-Map=${PROJECT_NAME}.map")

# Linker flags
set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/linker_script.ld")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${LINKER_SCRIPT}")

# Needed to make clangd functional
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Source compilation
add_subdirectory(src)

# Static Analysis
set(ALZ cppcheck)
set(ALZ_TARGET ${CMAKE_SOURCE_DIR}/src/)
set(ALZ_FLAGS --enable=all
              --error-exitcode=1
              --suppress=missingInclude
              --suppress=unusedFunction
              -I ${CMAKE_SOURCE_DIR}/src/
              -I ${CMAKE_SOURCE_DIR}/src/drivers/)

add_custom_target(analysis
  COMMAND ${ALZ} ${ALZ_FLAGS} ${ALZ_TARGET}
  COMMENT "Performing static analysis"
)

# Flashing MCU
set(PROG openocd)
set(PROG_TARGET "target/stm32f4x.cfg")
set(PROG_INTERFACE "interface/stlink.cfg")
set(PROG_FLAGS -f ${PROG_INTERFACE} -f ${PROG_TARGET})

add_custom_target(flash
    COMMAND ${PROG} ${PROG_FLAGS} -c "program ${CMAKE_BINARY_DIR}/src/${PROJECT_NAME} verify reset exit"
    COMMENT "Flashing the chip"
)

# Debugging MCU
add_custom_target(debug
    COMMAND ${PROG} ${PROG_FLAGS}
    COMMENT "Debugging the chip"
)
