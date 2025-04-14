# CMAKE PC-Lint helper

STM32 Project with cmake, PC-Lint, Gtest, Gmock with various unit test examples

## Requirements

### PC-Lint executable

pc lint binary is `/opt/pclp/pclp64_linux`
Adjust paths for your installation in `linter/pcLint.cmake`

Toolchain

* CMake
* Ninja
* GoogleTest expected in `/opt/googletest`
* arm-none-eabi-gcc for STM32, adjust paths in `build-elf` and `linter/pcLint.cmake`
* gcc for tests, adjust paths in `run-tests` and `linter/pcLint.cmake`

## Build

For the stm32

`build-elf -t blinky`

For the tests

`run-tests`

Linter output is in html


## Unit tests

Example with all tests under one directory

```
tests
```

Example with one test for a module

```
common/template
```

