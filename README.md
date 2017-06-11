# STest - is simple unit tests for C/C++


## Description

STest is simple unit tests for C/C++.

### Features:

* The code uses only the standard C99 This allows you to use the template in the oldest projects with older compilers.
* The code has no dependencies, and imprisoned in the one file.
* Support simple (single) tests.
* Support case(s) of tests.
* Support `init` and `clean` functions for test case.
* Support three levels (`PASS`, `SKIP`, `FAIL`)
* Support macro `ASSERT` and `STATIC_ASSERT`
* Support color in console (optional).


## Usage

#### To start working, perform the following steps:
1. You need to include [stest.h](./stest.h) file in your .c/.cpp file.
2. Use the macro `TEST(name)` to write test.
3. Use the macros `TEST_PASS(msg)`, `TEST_SKIP(msg)`, `TEST_FAIL(msg)` for exit from test.
4. Or use the macros `TEST_ASSERT(expr)`, `TEST_ASSERT2(expr, msg)`
5. Use the macro `MAIN_*` for declare function main.
6. Compile and run test.


## License

[BSD-3-Clause](./LICENSE).


## Copyright
Copyright (C) 2017 Koynov Stas - skojnov@yandex.ru
