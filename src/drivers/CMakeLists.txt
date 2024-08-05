# Create a sublibrary under drivers/ for modularity and
# compatibility with unit tests.
file(GLOB DRV_SRCS "*.c")
add_library(drivers STATIC ${DRV_SRCS})

# Add include directories for the drivers library
target_include_directories(drivers PUBLIC
    "${CMAKE_SOURCE_DIR}/src/common"
    "${EXTERNAL}/CMSIS/CMSIS/Core/Include"
    "${EXTERNAL}/CMSIS/Device/ST/STM32F4/Include"
)
