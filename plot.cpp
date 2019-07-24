#include <algorithm>
#include "wrappy/wrappy.h"
#include "numpy/arrayobject.h"
#include "pybind11/numpy.h"
#define NUMPY_IMPORT_ARRAY_RETVAL

void plot() {
  import_array();
  std::vector<double> x {1.0, 2.0, 3.0, 4.0}, y {1.5, 1.0, 1.3, 2.0};
  npy_intp dims[1] {x.size()};

  PyObject *a1 = PyArray_SimpleNewFromData(1, dims, NPY_DOUBLE, x.data());
  PyObject *a2 = PyArray_SimpleNewFromData(1, dims, NPY_DOUBLE, y.data());

  wrappy::PythonObject ax(wrappy::PythonObject::borrowed {}, a1);
  wrappy::PythonObject ay(wrappy::PythonObject::borrowed {}, a2);

  wrappy::call("matplotlib.pyplot.plot", ax, ay);
  wrappy::call("matplotlib.pyplot.show");
}

PYBIND11_MODULE(plot, m) {
  m.def("plot", &plot, "plot");
}
