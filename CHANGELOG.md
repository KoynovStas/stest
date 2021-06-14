# Change Log


[**STest**](https://github.com/KoynovStas/stest) - is simple unit tests for C/C++.

License: BSD 3-Clause

Copyright (C) 2017 Koynov Stas - skojnov@yandex.ru



---
## Ver 2.0 (2021-06-14)


### What's New

 - New: add option `STEST_RETURN_TYPE`
 - Fix: add attribute((un/used)) for fix warning static-analizer
 - New: add macro `STEST_xxx_MORE_INFO`
 - New: add macros to customize color printing
 - New: add macro `stest_printf` - for select print in embeded system
 - New: now arg of test function is `*test_case` (was `*data`)
 - Fix: fixed warning: variable data don't using
 - Fix: use `__INCLUDE_LEVEL__` in `STATIC_ASSERT` for fix ODR in headers
 - Fix:Makefile: rename `GCC` to `CC` use standart name
 - New: add file name and line_num in `print_title`
 - New: add `NULL` to empty msg


### Refactoring

 - Ref: add color for digit + total
 - Ref: add prefix stest_ for fix ODR
 - Ref: add prefix `STEST` for `SIZE_OF_ARRAY` macro
 - Ref: use table in print_status
 - Ref: use array for `status_xxx`
 - Ref: rename Totatls -> Total (more correct)
 - Ref: use `TEST_CASE` macro in `MAIN_TESTS`



## Ver 1.0 (2017-06-11)
