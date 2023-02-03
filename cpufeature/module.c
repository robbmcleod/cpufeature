/* module.c
 * 
 * C99/Python Author: Robert A. McLeod
 * Date Created     : 2017 Dec 30
 */

#include <Python.h>

#include "cpu_x86.h"

// Python 3 module initialization
static struct PyModuleDef module_def = {
    PyModuleDef_HEAD_INIT,
    "extension",
    NULL,
    -1,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

PyMODINIT_FUNC
PyInit_extension(void)
{
    PyObject *dictCPU;

    PyObject *m = PyModule_Create(&module_def);
    if (m == NULL)
    {
        PyErr_Format(PyExc_RuntimeError, "Python interpreter not started.\n");
        return NULL;
    }

    extern struct cpu_x86 *this_x86;
    init_cpu_x86();
    // Interrogate the machine with light slaps.
    detect_host();
    
    // Dictionary that encapsulates our struct
    // Alternatively we could use `struct.unpack()`
    dictCPU = PyDict_New();
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "VendorId"), Py_BuildValue("s", this_x86->VendorID));

    // Core features
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "num_virtual_cores"), Py_BuildValue("i", this_x86->num_virtual_cores));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "num_physical_cores"), Py_BuildValue("i", this_x86->num_physical_cores));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "num_threads_per_core"), Py_BuildValue("i", this_x86->num_threads_per_core));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "num_cpus"), Py_BuildValue("i", this_x86->num_cpus));
    // Cache information
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "cache_line_size"), Py_BuildValue("i", this_x86->cache_line_size));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "cache_L1_size"),   Py_BuildValue("i", this_x86->cache_L1_size));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "cache_L2_size"),   Py_BuildValue("i", this_x86->cache_L2_size));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "cache_L3_size"),   Py_BuildValue("i", this_x86->cache_L3_size));

    // OS support
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "OS_x64"), Py_BuildValue("O", this_x86->OS_x64 ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "OS_AVX"), Py_BuildValue("O", this_x86->OS_AVX ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "OS_AVX512"), Py_BuildValue("O", this_x86->OS_AVX512 ? Py_True: Py_False));

    // Misc
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "MMX"), Py_BuildValue("O", this_x86->HW_MMX ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "x64"), Py_BuildValue("O", this_x86->HW_x64 ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "ABM"), Py_BuildValue("O", this_x86->HW_ABM ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "RDRAND"), Py_BuildValue("O", this_x86->HW_RDRAND ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "BMI1"), Py_BuildValue("O", this_x86->HW_BMI1 ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "BMI2"), Py_BuildValue("O", this_x86->HW_BMI2 ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "ADX"), Py_BuildValue("O", this_x86->HW_ADX ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "PREFETCHWT1"), Py_BuildValue("O", this_x86->HW_PREFETCHWT1 ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "MPX"), Py_BuildValue("O", this_x86->HW_MPX ? Py_True: Py_False));

    // 128-bit SIMD
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "SSE"), Py_BuildValue("O", this_x86->HW_SSE ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "SSE2"), Py_BuildValue("O", this_x86->HW_SSE2 ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "SSE3"), Py_BuildValue("O", this_x86->HW_SSE3 ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "SSSE3"), Py_BuildValue("O", this_x86->HW_SSSE3 ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "SSE4.1"), Py_BuildValue("O", this_x86->HW_SSE41 ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "SSE4.2"), Py_BuildValue("O", this_x86->HW_SSE42 ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "SSE4.a"), Py_BuildValue("O", this_x86->HW_SSE4a ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "AES"), Py_BuildValue("O", this_x86->HW_AES ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "SHA"), Py_BuildValue("O", this_x86->HW_SHA ? Py_True: Py_False));

    // 256-BIT SIMD
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "AVX"), Py_BuildValue("O", this_x86->HW_AVX ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "XOP"), Py_BuildValue("O", this_x86->HW_XOP ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "FMA3"), Py_BuildValue("O", this_x86->HW_FMA3 ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "FMA4"), Py_BuildValue("O", this_x86->HW_FMA4 ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "AVX2"), Py_BuildValue("O", this_x86->HW_AVX2 ? Py_True: Py_False));

    // 512-BIT SIMD
    // Not many version of Python support 512-bit SIMD instructions at present (2017)
    // Perhaps only those build with ICC
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "AVX512f"), Py_BuildValue("O", this_x86->HW_AVX512_F ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "AVX512pf"), Py_BuildValue("O", this_x86->HW_AVX512_PF ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "AVX512er"), Py_BuildValue("O", this_x86->HW_AVX512_ER ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "AVX512cd"), Py_BuildValue("O", this_x86->HW_AVX512_CD ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "AVX512vl"), Py_BuildValue("O", this_x86->HW_AVX512_VL ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "AVX512bw"), Py_BuildValue("O", this_x86->HW_AVX512_BW ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "AVX512dq"), Py_BuildValue("O", this_x86->HW_AVX512_DQ ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "AVX512ifma"), Py_BuildValue("O", this_x86->HW_AVX512_IFMA ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "AVX512vbmi"), Py_BuildValue("O", this_x86->HW_AVX512_VBMI ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "AVX512vbmi2"), Py_BuildValue("O", this_x86->HW_AVX512_VBMI2 ? Py_True: Py_False));
    PyDict_SetItem(dictCPU, Py_BuildValue("s", "AVX512vnni"), Py_BuildValue("O", this_x86->HW_AVX512_VNNI ? Py_True: Py_False));
    PyModule_AddObject(m, "CPUFeature", dictCPU);

    // Integer macros
    //PyModule_AddIntMacro(m, N_THREADS);

    // String macros
    // PyModule_AddStringMacro(m, VERSION);

    // Clean up
    free_cpu_x86();
    return m;
}