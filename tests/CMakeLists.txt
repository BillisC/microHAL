file(GLOB CC_SRCS "${CMSIS_SYSTEM}")

set(C_INCL "${CMSIS_CORE}"
           "${CMSIS_DEVICE}")

set(UTESTS "gpio" "adc")

# Build GPIO target
foreach(test ${UTESTS})
    add_executable(utest_${test} ${CC_SRCS} "test_${test}_driver.c")
    target_include_directories(utest_${test} PUBLIC ${C_INCL})
    target_compile_definitions(utest_${test} PUBLIC ${C_DEFINES})
    target_link_libraries(utest_${test} PUBLIC drivers unity)

    add_custom_command(TARGET utest_${test} POST_BUILD
        COMMAND ${CMAKE_BINARY_DIR}/tests/utest_${test}
    )
endforeach()

# Copy compile_commands file back to source, otherwise it won't be detected
add_custom_command(TARGET utest_adc POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json
)