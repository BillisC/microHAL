file(GLOB C_SRCS "*.c"
                 "*.S"
                 "${EXTERNAL}/CMSIS/Device/ST/STM32F4/Source/Templates/system_stm32f4xx.c")

set(C_INCL "${CMAKE_CURRENT_SOURCE_DIR}/drivers/"
           "${CMAKE_CURRENT_SOURCE_DIR}/common/"
           "${EXTERNAL}/CMSIS/CMSIS/Core/Include/"
           "${EXTERNAL}/CMSIS/Device/ST/STM32F4/Include/")

# Include sublibraries
add_subdirectory(drivers)

# Target build
add_executable(${PROJECT_NAME} ${C_SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC ${C_INCL})
target_link_libraries(${PROJECT_NAME} PUBLIC drivers)
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})

# Copy compile_commands file back to source, otherwise it won't be detected
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json
)
