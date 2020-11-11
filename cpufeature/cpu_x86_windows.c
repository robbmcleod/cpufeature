/* cpu_x86_windows.c
 * 
 * C99/Python Author: Robert A. McLeod
 * Original Author  : Alexander J. Yee
 * Date Created     : 04/12/2014
 */


//  Dependencies
#include <Windows.h>
#include <intrin.h>
#include "cpu_x86.h"

void cpuid(int32_t out[4], int32_t eax, int32_t ecx) {
    // MSVC specific usage for cpuid:
    // https://msdn.microsoft.com/en-us/library/hskdteyh.aspx
    //
    // Docs on cpuid can be found in the Intel(R) 64 and IA-32 Architectures 
    // Software Developer Manuals:
    // https://software.intel.com/en-us/articles/intel-sdm
    //
    // Presently (2017) found in Vol 2A on pp. 3-190 to 3-205
    __cpuidex(out, eax, ecx);
}
__int64 xgetbv(unsigned int x) {
    return _xgetbv(x);
}


//  Detect 64-bit - Note that this snippet of code for detecting 64-bit has been copied from MSDN.
typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
BOOL IsWow64(void)
{
    BOOL bIsWow64 = FALSE;

    LPFN_ISWOW64PROCESS fnIsWow64Process = (LPFN_ISWOW64PROCESS) GetProcAddress(
        GetModuleHandle(TEXT("kernel32")), "IsWow64Process");

    if (NULL != fnIsWow64Process)
    {
        if (!fnIsWow64Process(GetCurrentProcess(), &bIsWow64))
        {
            printf("Error Detecting Operating System.\n");
            printf("Defaulting to 32-bit OS.\n\n");
            bIsWow64 = FALSE;
        }
    }
    return bIsWow64;
}

bool detect_OS_x64(void){
#ifdef _M_X64
    return true;
#else
    return IsWow64() != 0;
#endif
}

// Counts total number of logical cores on a system, for determining if there 
// multiple CPU chips in a machine.
// Code modified from: os_cpu_count_impl in https://github.com/python/cpython/blob/3.9/Modules/posixmodule.c
int hardware_concurrency() {
    // Requires Windows 7 or greater
    int ncpu = GetActiveProcessorCount(ALL_PROCESSOR_GROUPS);
    return ncpu;
}