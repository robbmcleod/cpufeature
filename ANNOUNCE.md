Announcing CPUFeature 0.2.0
===========================

Hi everyone,

CPUFeature is a tool for detecting CPU features on x86/AMD64 processors. In particular it is engineered to have very low overhead on import (~ 1 ms) and to detect features that are often important in high-performance computing where hybrid combinations of multi-threading and multi-processing are used. Detects CPU features such as:

* SIMD instruction support
* Number of cores (both virtual and physical)
* Number of CPUs on the motherboard.
* Cache sizes

It is written in C99. It supports Windows with MSVC and Linux with GCC/LLVM compilers. MacOSX should also work with GCC/LLVM. CPUFeature is licensed under Creative Commons Zero, so it may be freely incorporated as a submodule into your own projects.

CPUFeature is considered to be in an alpha state because while it is tested via GitHub Actions on a variety of platforms, we expect edge cases to appear.

Changes for 0.2.0
-----------------

* Added support for AMD processors.
* Added a script for `valgrind` to more easier locate problems when the module crashes.
