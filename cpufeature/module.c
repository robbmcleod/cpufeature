/* module.c
 * 
 * C99/Python Author: Robert A. McLeod
 * Date Created     : 2017 Dec 30
 */

#include <Python.h>

#include "cpu_dict.h"

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

    // Dictionary that encapsulates our struct
    // Alternatively we could use `struct.unpack()`
    dictCPU = PyDict_New();

    PyDict_SetItem(dictCPU, Py_BuildValue("s", "arch"), Py_BuildValue("s", arch_name));

    init_cpu_dict(dictCPU);

    PyModule_AddObject(m, "CPUFeature", dictCPU);

    // Integer macros
    //PyModule_AddIntMacro(m, N_THREADS);

    // String macros
    // PyModule_AddStringMacro(m, VERSION);

    return m;
}
