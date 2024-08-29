file(GLOB C_SRCS "*.c"
                 "*.S"
                 "${CMSIS_SYSTEM}")

set(C_INCL "${CMSIS_CORE}"
           "${CMSIS_DEVICE}")

# Target build
add_executable(${PROJECT_NAME} ${C_SRCS})
target_include_directories(${PROJECT_NAME} PRIVATE ${C_INCL})
target_compile_definitions(${PROJECT_NAME} PUBLIC ${C_DEFINES})
target_link_libraries(${PROJECT_NAME} PUBLIC drivers)
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})

# Copy compile_commands file back to source, otherwise it won't be detected
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json
)

# Programmer options
set(PROG openocd)
set(PROG_TARGET "target/stm32f4x.cfg")
set(PROG_INTERFACE "interface/stlink.cfg")
set(PROG_FLAGS -f ${PROG_INTERFACE} -f ${PROG_TARGET})

# Flashing MCU
add_custom_target(flash
    COMMAND ${PROG} ${PROG_FLAGS} -c "program ${CMAKE_BINARY_DIR}/src/${PROJECT_NAME} verify reset exit"
    DEPENDS ${PROJECT_NAME}
    COMMENT "Flashing the chip"
)

# Debugging MCU
add_custom_target(debug
    COMMAND ${PROG} ${PROG_FLAGS}
    DEPENDS ${PROJECT_NAME}
    COMMENT "Debugging the chip"
)
