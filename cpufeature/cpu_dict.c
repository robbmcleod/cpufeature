
#include "cpu_dict.h"

#if defined(__x86_64__) || defined(__amd64__) || defined(_M_X64)

char *arch_name = "x86_64";
#include "cpu_dict_x86.c"

#elif defined(__i386) || defined(_M_IX86)

char *arch_name = "x86";
#include "cpu_dict_x86.c"

#elif defined(__aarch64__)

char *arch_name = "aarch64";
void init_cpu_dict(PyObject *dictCPU) {}

#elif defined(__arm__)

char *arch_name = "arm";
void init_cpu_dict(PyObject *dictCPU) {}

#else

char *arch_name = "UNKNOWN";
void init_cpu_dict(PyObject *dictCPU) {}

#endif

