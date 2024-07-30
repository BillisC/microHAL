## STM32F446xx Drivers

*This repository serves mostly as template, but tests will be included.*

### Preparation
Install the required tools:

**Debian** `sudo apt install gcc-arm-none-eabi gdb-multiarch cmake openocd -y`

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
Initialize cmake configuration:
```
cmake -B build/ . -DCMAKE_TOOLCHAIN_FILE=arm-toolchain.cmake
```
Finally compile and flash the project:
```
cmake --build build/ --target flash
```

### Debugging
The following will launch a GDB server at port **3333**:
```
cmake --build build/ --target debug
```
To connect to it launch another GDB instance:
```
gdb-multiarch -tui drivers.elf
(gdb) target remote :3333
```
