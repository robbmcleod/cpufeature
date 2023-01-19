CPUFeature
==========

CPUFeature is a tool for detecting CPU features on x86/AMD64 processors. In particular it is engineered to have very low overhead on import (~ 1 ms) and to detect features that are often important in high-performance computing where hybrid combinations of multi-threading and multi-processing are used. Detects CPU features such as:

* SIMD instruction support
* Number of cores (both virtual and physical)
* Number of CPUs on the motherboard.
* Cache sizes

It is written in C99. It supports Windows with MSVC and Linux with GCC/LLVM compilers. MacOSX should also work with GCC/LLVM. CPUFeature is licensed under Creative Commons Zero, so it may be freely incorporated as a submodule into your own projects.

CPUFeature is considered to be in an alpha state because while it is tested via GitHub Actions on a variety of platforms, we expect edge cases to appear.

Example
-------

The module generates a `dict` called `CPUFeature` on import which contains useful information regarding optimization and compilation for the host. For my Intel i7-7820X Skylake CPU, it generates the following info:

    > python -c "import cpufeature; cpufeature.print_features()"
  === CPU FEATURES ===
      VendorId                : GenuineIntel
      num_virtual_cores       : 16
      num_physical_cores      : 8
      num_threads_per_core    : 2
      num_cpus                : 1
      cache_line_size         : 64
      cache_L1_size           : 32768
      cache_L2_size           : 1048576
      cache_L3_size           : 11534336
      OS_x64                  : True
      OS_AVX                  : True
      OS_AVX512               : True
      MMX                     : True
      x64                     : True
      ABM                     : True
      RDRAND                  : True
      BMI1                    : True
      BMI2                    : True
      ADX                     : True
      PREFETCHWT1             : False
      MPX                     : True
      SSE                     : True
      SSE2                    : True
      SSE3                    : True
      SSSE3                   : True
      SSE4.1                  : True
      SSE4.2                  : True
      SSE4.a                  : False
      AES                     : True
      SHA                     : False
      AVX                     : True
      XOP                     : False
      FMA3                    : True
      FMA4                    : False
      AVX2                    : True
      AVX512f                 : True
      AVX512pf                : False
      AVX512er                : False
      AVX512cd                : True
      AVX512vl                : True
      AVX512bw                : True
      AVX512dq                : True
      AVX512ifma              : False
      AVX512vbmi              : False

Notes on Fields
---------------

* If `num_threads_per_core > 1` likely Intel Hyperthreading (or equivalent architecture) is present. The physical core count may be unreliable in virtual environments.
* Cache sizes are in bytes.
* For AVX2, check `AVX2` and `OS_AVX2`.
* For AVX512, check `AVX512f` and `OS_AVX512`. Python support for AVX512 instructions is highly limited outside of compilation with ICC. MSVC does not have AVX512 support until MSVC2017.

Authors
-------

* Based on FeatureDetector by Alexander Yee (https://github.com/Mysticial/FeatureDetector).
* Ported to Python by Robert A. McLeod, who added detection of cores, and cache sizes.
* `drfinkus` contributed to AMD support.
* `WidgetA` contributed support for compilation with Clang.

Release Notes
-------------

### 0.2.1 ###

* Supported Python versions are now 3.8 - 3.11.

### 0.2.0 ###

* Added pre-build wheels via `cibuildwheels` and GitHub Actions for Python 3.6-3.9 on Linux/Windows/MacOSX.
* Added support for AMD processors.
* Added a script for `valgrind` to more easier locate problems when the module crashes.

### 0.1.1 ###

* Fixes for compilation with `clang`.

### 0.1.0 ###

* Added detection of processors, cores, and cache sizes
* Created Python wrapper around FeatureDetector
* Reduced FeatureDetector to C99 for better cross-platform compatibility
