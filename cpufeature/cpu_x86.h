/* cpu_x86.h
 * 
 * C99/Python Author: Robert A. McLeod
 * Original Author  : Alexander J. Yee
 * Date Created     : 04/12/2014
 */

#pragma once
#ifndef _CPU_X86_H
#define _CPU_X86_H

//  Dependencies
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>



struct cpu_x86{
    //  Vendor
    char* VendorID;
    enum {
        UNSUPPORTED = 0,
        INTEL       = 1, 
        AMD         = 2
    } vendor_enum;

    // Core features
    int num_threads_per_core;   // if greater than 1 generally indicates Intel Hyperthreading (R) or other multi-threading architecture
    int num_virtual_cores;
    int num_physical_cores;
    int num_cpus;

    int cache_line_size;  // Bytes
    int cache_L1_size;    // Bytes
    int cache_L2_size;    // Bytes
    int cache_L3_size;    // Bytes

    //  OS Features
    bool OS_x64;
    bool OS_AVX;
    bool OS_AVX512;

    //  Misc.
    bool HW_MMX;
    bool HW_x64;
    bool HW_ABM;
    bool HW_RDRAND;
    bool HW_BMI1;
    bool HW_BMI2;
    bool HW_ADX;
    bool HW_PREFETCHWT1;
    bool HW_MPX;

    //  SIMD: 128-bit
    bool HW_SSE;
    bool HW_SSE2;
    bool HW_SSE3;
    bool HW_SSSE3;
    bool HW_SSE41;
    bool HW_SSE42;
    bool HW_SSE4a;
    bool HW_AES;
    bool HW_SHA;

    //  SIMD: 256-bit
    bool HW_AVX;
    bool HW_XOP;
    bool HW_FMA3;
    bool HW_FMA4;
    bool HW_AVX2;

    //  SIMD: 512-bit
    bool HW_AVX512_F;
    bool HW_AVX512_PF;
    bool HW_AVX512_ER;
    bool HW_AVX512_CD;
    bool HW_AVX512_VL;
    bool HW_AVX512_BW;
    bool HW_AVX512_DQ;
    bool HW_AVX512_IFMA;
    bool HW_AVX512_VBMI;
    bool HW_AVX512_VBMI2;
    bool HW_AVX512_VNNI;
};

// Global 
// We could pass this struct around as an argument, but since you can't have 
// two on a machine, it's a natural singleton
extern struct cpu_x86 *this_x86;


extern void init_cpu_x86(void);
extern void free_cpu_x86(void);
extern void detect_host(void);

extern void get_vendor_string(void);
extern void detect_cores(void);
extern void detect_cache(void);

// Docs on cpuid can be found in the Intel(R) 64 and IA-32 Architectures 
// Software Developer Manuals:
// https://software.intel.com/en-us/articles/intel-sdm
//
// Presently in Vol 2A on pp. 3-190 to 3-205
// 
// For AMD:
// https://www.amd.com/system/files/TechDocs/54945_3.03_ppr_ZP_B2_pub.zip
extern void cpuid(int32_t out[4], int32_t level, int32_t count);

extern bool detect_OS_x64(void);
extern bool detect_OS_AVX(void);
extern bool detect_OS_AVX512(void);



#endif