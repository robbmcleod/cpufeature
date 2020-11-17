/* cpu_x86_linux.c
 * 
 * C99/Python Author: Robert A. McLeod
 * Original Author  : Alexander J. Yee
 * Date Created     : 04/12/2014
 */

//  Dependencies
#include <cpuid.h>
#include "cpu_x86.h"
#include <pthread.h>
#include <unistd.h>

#ifdef __linux__
#include <sys/sysinfo.h>
#endif

#if defined(__DragonFly__) || \
    defined(__OpenBSD__)   || \
    defined(__FreeBSD__)   || \
    defined(__NetBSD__)    || \
    defined(__APPLE__)
#include <sys/sysctl.h>
#endif

void cpuid(int32_t out[4], int32_t eax, int32_t ecx) {
    // For GCC-specific cpuid
    // https://github.com/gcc-mirror/gcc/blob/master/gcc/config/i386/cpuid.h
    //
    // Docs on cpuid can be found in the Intel(R) 64 and IA-32 Architectures 
    // Software Developer Manuals:
    // https://software.intel.com/en-us/articles/intel-sdm
    //
    // Presently (2017) found in Vol 2A on pp. 3-190 to 3-205
    __cpuid_count(eax, ecx, out[0], out[1], out[2], out[3]);
}

uint64_t xgetbv(unsigned int index) {
    uint32_t eax, edx;
    __asm__ __volatile__("xgetbv" : "=a"(eax), "=d"(edx) : "c"(index));
    return ((uint64_t)edx << 32) | eax;
}
#define _XCR_XFEATURE_ENABLED_MASK  0

//  Detect 64-bit
bool detect_OS_x64(void) {
    //  We only support x64 on Linux.
    return true;
}

// Counts total number of logical cores on a system, for determining if there 
// multiple CPU chips in a machine.
// Code modified from: os_cpu_count_impl in https://github.com/python/cpython/blob/3.9/Modules/posixmodule.c
int hardware_concurrency() {
    int ncpu = 0;
#if defined(__hpux)
    ncpu = mpctl(MPC_GETNUMSPUS, NULL, NULL);
#elif defined(HAVE_SYSCONF) && defined(_SC_NPROCESSORS_ONLN)
    ncpu = sysconf(_SC_NPROCESSORS_ONLN);
#elif defined(__DragonFly__) || \
      defined(__OpenBSD__)   || \
      defined(__FreeBSD__)   || \
      defined(__NetBSD__)    || \
      defined(__APPLE__)
    int mib[2];
    size_t len = sizeof(ncpu);
    mib[0] = CTL_HW;
    mib[1] = HW_NCPU;
    if (sysctl(mib, 2, &ncpu, &len, NULL, 0) != 0)
        ncpu = 0;
#endif
    return ncpu;
}