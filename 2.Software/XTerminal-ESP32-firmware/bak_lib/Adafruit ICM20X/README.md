# Adafruit ICM20X [![Build Status](https://github.com/adafruit/Adafruit_ICM20X/workflows/Arduino%20Library%20CI/badge.svg)](https://github.com/adafruit/Adafruit_ICM20X/actions)[![Documentation](https://github.com/adafruit/ci-arduino/blob/master/assets/doxygen_badge.svg)](http://adafruit.github.io/Adafruit_ICM20X/html/index.html)

This is the Adafruit ICM20X Arduino Library for use with the TDK Invensense ICM20649 and ICM20948 motion sensors.


### Tested and works great with the following Adafruit ICM20X Family Breakout Boards:

[<img src="assets/649.jpg?raw=true" width="300px">](https://www.adafruit.com/products/4464)
[<img src="assets/948.png?raw=true" width="300px">](https://www.adafruit.com/products/4554)


#### Compatible sensor breakouts available in the Adafruit store:
* [Adafruit ICM-20649 Wide Range ±30g ±4000dps 6-DoF IMU](https://www.adafruit.com/products/4464)
* [Adafruit ICM-20948 9-DoF IMU](https://www.adafruit.com/products/4554)

Adafruit invests time and resources providing this open source code, please support Adafruit and open-source hardware by purchasing products from Adafruit!

# Installation
To install, use the Arduino Library Manager and search for "Adafruit ICM20X" and install the library.

## Dependencies
 * [Adafruit BusIO](https://github.com/adafruit/Adafruit_BusIO)
 * [Adafruit Unified Sensor Driver](https://github.com/adafruit/Adafruit_Sensor)

# Contributing

Contributions are welcome! Please read our [Code of Conduct](https://github.com/adafruit/Adafruit_ICM20X/blob/master/CODE_OF_CONDUCT.md>)
before contributing to help this project stay welcoming.

## Documentation and doxygen
Documentation is produced by doxygen. Contributions should include documentation for any new code added.

Some examples of how to use doxygen can be found in these guide pages:

https://learn.adafruit.com/the-well-automated-arduino-library/doxygen

https://learn.adafruit.com/the-well-automated-arduino-library/doxygen-tips

## Formatting and clang-format
This library uses [`clang-format`](https://releases.llvm.org/download.html) to standardize the formatting of `.cpp` and `.h` files. 
Contributions should be formatted using `clang-format`:

The `-i` flag will make the changes to the file.
```bash
clang-format -i *.cpp *.h
```
If you prefer to make the changes yourself, running `clang-format` without the `-i` flag will print out a formatted version of the file. You can save this to a file and diff it against the original to see the changes.

Note that the formatting output by `clang-format` is what the automated formatting checker will expect. Any diffs from this formatting will result in a failed build until they are addressed. Using the `-i` flag is highly recommended.

### clang-format resources
  * [Binary builds and source available on the LLVM downloads page](https://releases.llvm.org/download.html)
  * [Documentation and IDE integration](https://clang.llvm.org/docs/ClangFormat.html)

## About this Driver
Written by Bryan Siepert for Adafruit Industries.
BSD license, check license.txt for more information
All text above must be included in any redistribution
