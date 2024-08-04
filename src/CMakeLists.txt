file(GLOB C_SRCS "*.c"
                 "*.S"
                 "drivers/*.c"
                 "${EXTERNAL}/CMSIS/Device/ST/STM32F4/Source/Templates/system_stm32f4xx.c")

set(C_INCL "src/drivers/"
           "src/common/"
           "${EXTERNAL}/CMSIS/CMSIS/Core/Include/"
           "${EXTERNAL}/CMSIS/Device/ST/STM32F4/Include/")

# Target build
add_executable(${PROJECT_NAME} ${C_SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC ${C_INCL})
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})

# Copy compile_commands file back to source, otherwise it won't be detected
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND cp ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json
)
