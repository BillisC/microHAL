## STM32F446xx Drivers

*This repository serves mostly as template, but tests will be included.*

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
