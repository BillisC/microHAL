# Create a sublibrary under drivers/ for modularity and
# compatibility with unit tests.
file(GLOB_RECURSE DRV_SRCS "${CMAKE_CURRENT_SOURCE_DIR}" "*.c"
                           "${CMSIS_SYSTEM}")

add_library(drivers STATIC ${DRV_SRCS})

# Add include directories for the drivers library
target_include_directories(drivers PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/common"
    "${CMAKE_CURRENT_SOURCE_DIR}/core"
    "${CMAKE_CURRENT_SOURCE_DIR}/peripherals"
    "${CMAKE_CURRENT_SOURCE_DIR}/peripherals/communication"
    "${CMSIS_CORE}"
    "${CMSIS_DEVICE}"
)
target_compile_definitions(drivers PUBLIC ${C_DEFINES})
