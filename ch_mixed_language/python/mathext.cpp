#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <math.h>

/* Function 1: Calculate factorial */
static PyObject* mathext_factorial(PyObject* self, PyObject* args) {
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

/* Function 2: Calculate distance between two points */
static PyObject* mathext_distance(PyObject* self, PyObject* args) {
    double x1, y1, x2, y2;
    
    /* Parse arguments - expects four doubles */
    if (!PyArg_ParseTuple(args, "dddd", &x1, &y1, &x2, &y2)) {
        return NULL;
    }
    
    /* Calculate distance */
    double dx = x2 - x1;
    double dy = y2 - y1;
    double dist = sqrt(dx * dx + dy * dy);
    
    /* Return result as Python float */
    return PyFloat_FromDouble(dist);
}

/* Function 3: Sum a list of numbers */
static PyObject* mathext_sum_list(PyObject* self, PyObject* args) {
    PyObject* list;
    
    /* Parse arguments - expects a Python object */
    if (!PyArg_ParseTuple(args, "O", &list)) {
        return NULL;
    }
    
    /* Check if it's actually a list */
    if (!PyList_Check(list)) {
        PyErr_SetString(PyExc_TypeError, "Argument must be a list");
        return NULL;
    }
    
    /* Iterate over list and sum */
    Py_ssize_t length = PyList_Size(list);
    double sum = 0.0;
    
    for (Py_ssize_t i = 0; i < length; i++) {
        PyObject* item = PyList_GetItem(list, i);  /* Borrowed reference */
        
        /* Convert to double */
        double value = PyFloat_AsDouble(item);
        if (value == -1.0 && PyErr_Occurred()) {
            return NULL;  /* Conversion failed */
        }
        
        sum += value;
    }
    
    return PyFloat_FromDouble(sum);
}

/* Method definition table */
static PyMethodDef MathExtMethods[] = {
    {
        "factorial",                    /* Method name in Python */
        mathext_factorial,              /* C function */
        METH_VARARGS,                   /* Accepts positional arguments */
        "Calculate factorial of n"      /* Docstring */
    },
    {
        "distance",
        mathext_distance,
        METH_VARARGS,
        "Calculate distance between two 2D points: distance(x1, y1, x2, y2)"
    },
    {
        "sum_list",
        mathext_sum_list,
        METH_VARARGS,
        "Sum all numbers in a list"
    },
    {NULL, NULL, 0, NULL}  /* Sentinel */
};

/* Module definition structure */
static struct PyModuleDef mathextmodule = {
    PyModuleDef_HEAD_INIT,
    "mathext",                          /* Module name */
    "Simple math extension module",     /* Module docstring */
    -1,                                 /* Module state size (-1 = no state) */
    MathExtMethods
};

/* Module initialization function - must be named PyInit_<modulename> */
PyMODINIT_FUNC PyInit_mathext(void) {
    return PyModule_Create(&mathextmodule);
}