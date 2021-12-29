#include "../main.h"


int saveImage(char * fileName, Image image)
{
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;
    int i;

    pName = PyUnicode_DecodeFSDefault("save");
    PyObject *sys = PyImport_ImportModule("sys");
    PyObject *path = PyObject_GetAttrString(sys, "path");
    PyList_Append(path, PyUnicode_FromString("./src/py/"));
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, "save");
        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(3);

            pValue = PyUnicode_DecodeFSDefault(fileName);
            PyTuple_SetItem(pArgs, 0, pValue);

            pValue = PyTuple_New(2);
            PyTuple_SetItem(pValue, 0, PyLong_FromLong(image.width));
            PyTuple_SetItem(pValue, 1, PyLong_FromLong(image.height));
            PyTuple_SetItem(pArgs, 1, pValue);

            pValue = PyBytes_FromStringAndSize((uint8_t *)image.data, image.size);
            PyTuple_SetItem(pArgs, 2, pValue);

            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL) {
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