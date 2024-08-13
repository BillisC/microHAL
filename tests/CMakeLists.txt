file(GLOB C_SRCS "*.c"
                 "${CMSIS_SYSTEM}")

set(C_INCL "${CMAKE_SOURCE_DIR}/src/common/"
           "${CMSIS_CORE}"
           "${CMSIS_DEVICE}")

# Target build
add_executable(utest ${C_SRCS})
target_include_directories(utest PUBLIC ${C_INCL})
target_compile_definitions(utest PUBLIC ${C_DEFINES})
target_link_libraries(utest PUBLIC drivers unity)

# Copy compile_commands file back to source, otherwise it won't be detected
add_custom_command(TARGET utest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json
)
