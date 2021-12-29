#define PY_SSIZE_T_CLEAN
#include "../main.h"


int loadImage(Image* image)
{
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;
    int i;
    unsigned char * data;

    pName = PyUnicode_DecodeFSDefault("load");
    PyObject *sys = PyImport_ImportModule("sys");
    PyObject *path = PyObject_GetAttrString(sys, "path");
    PyList_Append(path, PyUnicode_FromString("./src/py/"));
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, "load");
        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(1);
            pValue = PyUnicode_DecodeFSDefault(image->path);
            PyTuple_SetItem(pArgs, 0, pValue);
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);   
            if (pValue != NULL) {
                PyArg_ParseTuple(pValue, "iis#", &(image->width), &(image->height), &data, &(image->size));
                image->data = malloc(image->size);
                memcpy(image->data, data, image->size);
                Py_DECREF(pValue);
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PYERR_PRINT();
                return 1;
            }
        }
        else {
            if (PyErr_Occurred())
                PYERR_PRINT();
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PYERR_PRINT();
        return 1;
    }
    return 0;
}
