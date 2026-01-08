#define PY_SSIZE_T_CLEAN
#include <Python.h>

/* Function 1: Calculate factorial */
static PyObject* mathext_factorial(PyObject* self, PyObject* args) 
{
    int n;
    
    /* Parse arguments - expects one integer */
    if (!PyArg_ParseTuple(args, "i", &n)) {
        return NULL;  /* Exception already set by PyArg_ParseTuple */
    }
    
    /* Input validation */
    if (n < 0) {
        PyErr_SetString(PyExc_ValueError, "Factorial requires non-negative integer");
        return NULL;
    }
    
    /* Calculate factorial */
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
        /* Check for overflow */
        if (result < 0) {
            PyErr_SetString(PyExc_OverflowError, "Factorial result too large");
            return NULL;
        }
    }
    
    /* Return result as Python integer */
    return PyLong_FromLongLong(result);
}

/* Method definition table */
static PyMethodDef MathExtMethods[] = {
    {
        "factorial",                    /* Method name in Python */
        mathext_factorial,              /* C function */
        METH_VARARGS,                   /* Accepts positional arguments */
        "Calculate factorial of n"      /* Docstring */
    },
    {NULL, NULL, 0, NULL}  /* Sentinel */
};

/* Module definition structure */
static struct PyModuleDef mathextmodule = {
    PyModuleDef_HEAD_INIT,
    "mathextsimple",                          /* Module name */
    "Simple math extension module",     /* Module docstring */
    -1,                                 /* Module state size (-1 = no state) */
    MathExtMethods
};

/* Module initialization function - must be named PyInit_<modulename> */
PyMODINIT_FUNC PyInit_mathextsimple(void) {
    return PyModule_Create(&mathextmodule);
}