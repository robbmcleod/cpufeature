#pragma once
#ifndef _CPU_DICT_H
#define _CPU_DICT_H

#include <Python.h>

extern char *arch_name;

void init_cpu_dict(PyObject* dictCPU);

#endif
