
# `libieee754round`

A C/C++/Python library for floating-point arithmetic with IEEE 754-compliant
rounding.


## Motivation and mechanism

C and C++ have a function `fesetround` in `fenv.h` to set floating-point
rounding mode, but a modification through this interface may be disregarded
depending on compilers' optimization flags.  This behavior can be prevented with
`#pragma STDC FENV_ACCESS ON` in C++, but it seems that no compiler supports
this sentence.

In contrast, almost all compilers have `_MM_SET_ROUNDING_MODE` in `immintrin.h`
which does the same as `fesetround` but does not seem to be optimized away.
Therefore, this function is employed in this library.

Additionally, Python does not have an access to the rounding mode, so there is a
need for this library.


## Installation

```
$ sudo apt update
$ sudo apt install python3-pip
$ pip3 install --user --upgrade pip setuptools
$ pip3 install --user git+https://github.com/Terminus-IMRC/libieee754round.git
```


## Running tests

```
$ git clone https://github.com/Terminus-IMRC/libieee754round.git
$ cd libieee754round/
$ python3 setup.py build_ext --inplace
$ python3 -m doctest -v ieee754round/__init__.py
```
