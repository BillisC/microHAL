# Create a sublibrary under drivers/ for modularity and
# compatibility with unit tests.
file(GLOB DRV_SRCS "*.c"
                   "${CMSIS_SYSTEM}")
add_library(drivers STATIC ${DRV_SRCS})

# Add include directories for the drivers library
target_include_directories(drivers PUBLIC
    "${CMAKE_SOURCE_DIR}/src/common"
    "${CMSIS_CORE}"
    "${CMSIS_DEVICE}"
)
target_compile_definitions(drivers PUBLIC ${C_DEFINES})
