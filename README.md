# calculator

Simple arithmetic calculator that parses textual input and calculates the result.

Input may contain (infix) equations formed out of single digit numbers, round brackets and these operators: + - * / ( ) 

## Build

To build the project you need CMake or any compatible tool of your choice, e.g. Microsoft Visual Studio.
CMake website: https://cmake.org/download/

## Run 

The executable can be found in the build directory under "calculator", e.g. "build\Release_x64\calculator\calculator.exe".
It expects the user to type the equations. An empty input terminates the programm.

## Test

The test runner is its own executable and can be found in the build directory under "tests", e.g. "build\Release_x64\tests\test_calculator.exe".