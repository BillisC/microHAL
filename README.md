## STM32F446xx Drivers

![CI](https://github.com/BillisC/stm32f446xx-drivers/actions/workflows/ci.yml/badge.svg)

What's this repo about?
- Provides a simple HAL
- Provides simple driver implementations
- Uses CMSIS where needed
- Tries to be MISRA C (2023) compliant *can't be sure though*
- Attempts to be cross-compatible *cough*
- Serves as a template for future projects

Can I use it for **any** STM32 F4 series MCU?
- Probably, but its designed for F446RE so don't blame me if anything burns

### Preparation
Install the required tools (CMake **must** be >= 3.21):

**Debian** `sudo apt install gcc-arm-none-eabi gdb-multiarch git cmake openocd cppcheck -y`

**Other distros** `Not available yet`

Clone the repository:
```
git clone --recursive https://github.com/BillisC/stm32f446xx-drivers.git
```
Or initialize the submodules seperately:
```
git submodule init
git submodule update
```

### Compile and flash
Available configurations: Debug / Release

Initialize cmake configuration:
```
cmake -B build/{config}/ . --toolchain arm-toolchain.cmake
```
Finally compile and flash the project:
```
cmake --build build/{config}/ --target flash
```

### Unit testing
Just don't include the `--toolchain arm-toolchain.cmake`.
Execute the build output `utest` to run all tests **natively**.

### Debugging
The following will launch a GDB server at port **3333**:
```
cmake --build build/{config}/ --target debug
```
To connect to it launch another GDB instance:
```
gdb-multiarch -tui drivers.elf
(gdb) target remote :3333
```
