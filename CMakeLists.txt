cmake_minimum_required(VERSION 3.20)
project(drivers VERSION 0.1)

enable_language(C ASM)

# Folder that includes CMSIS etc.
set(VENDOR "external")

# GCC ARM compiler flags
set(C_WARNS "-Wall -Wextra -Werror")
set(MCU_FLAGS "-mcpu=cortex-m4 -mthumb -DSTM32F446xx")
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER ${CMAKE_C_COMPILER})
set(CMAKE_C_FLAGS "-g ${MCU_FLAGS} ${C_WARNS} -nostdlib -Wl,-Map=${PROJECT_NAME}.map")

# Linker flags
set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/linker_script.ld")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -T ${LINKER_SCRIPT}")

# Needed to make clangd functional
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ARM Compilation
set(C_FILES "src/main.c"
            "src/startup_stm32f446xx.S"
            "${VENDOR}/CMSIS/Device/ST/STM32F4/Source/Templates/system_stm32f4xx.c")

add_executable(${PROJECT_NAME}.elf ${C_FILES})

target_include_directories(${PROJECT_NAME}.elf PUBLIC
                           "src/"
                           "${VENDOR}/CMSIS/CMSIS/Core/Include/"
                           "${VENDOR}/CMSIS/Device/ST/STM32F4/Include/")
set_target_properties(${PROJECT_NAME}.elf PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND cp ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json
)

# Flashing MCU
set(PROG openocd)
set(PROG_TARGET "target/stm32f4x.cfg")
set(PROG_INTERFACE "interface/stlink.cfg")
set(PROG_FLAGS -f ${PROG_INTERFACE} -f ${PROG_TARGET})

add_custom_target(flash
    COMMAND ${PROG} ${PROG_FLAGS} -c "program ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.elf verify reset exit"
    DEPENDS ${PROJECT_NAME}.elf
    COMMENT "Flashing the chip"
)

# Debugging MCU
add_custom_target(debug
    COMMAND ${PROG} ${PROG_FLAGS}
    DEPENDS ${PROJECT_NAME}.elf
    COMMENT "Debugging the chip"
)

