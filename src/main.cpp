#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <iostream>
#include <thread>

#include "pclvisualize.h"

using namespace std::chrono_literals;

namespace py = pybind11;


py::array_t<double> add_arrays(py::array_t<double> input1, py::array_t<double> input2) {
   /* read input arrays buffer_info */
   py::buffer_info buf1 = input1.request(), buf2 = input2.request();
   if (buf1.size != buf2.size)
      throw std::runtime_error("Input shapes must match");

   /* allocate the output buffer */
   py::array_t<double> result = py::array_t<double>(buf1.size);
   py::buffer_info buf3 = result.request();
   double *ptr1 = (double *) buf1.ptr, *ptr2 = (double *) buf2.ptr, *ptr3 = (double *)buf3.ptr;
   size_t X = buf1.shape[0];
   size_t Y = buf1.shape[1];

   /* Add both arrays */
   for (size_t idx = 0; idx < X; idx++)
       for (size_t idy = 0; idy < Y; idy++)
           ptr3[idx*Y + idy] = ptr1[idx*Y+ idy] + ptr2[idx*Y+ idy];

   /* Reshape result to have same shape as input */
   result.resize({X,Y});

   return result;
}


int add(int i, int j) {	
return i + j;
}








PYBIND11_MODULE(pclwrapper, m) {
    py::class_<PCLviewerPy>(m, "PCLviewerPy")
        .def(py::init<const std::string &>())
        .def("setName", &PCLviewerPy::setName)
        .def("getName", &PCLviewerPy::getName)
        .def("__repr__",
        [](const Pet &a) {
            return "<example.Pet named '" + a.name + "'>";
        });


    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: pclwrapper

        .. autosummary::
           :toctree: _generate

           add
           subtract
    )pbdoc";

    m.def("add", &add, R"pbdoc(
        Add two numbers

        Some other explanation about the add function.
    )pbdoc");

    m.def("subtract", [](int i, int j) { return i - j; }, R"pbdoc(
        Subtract two numbers

        Some other explanation about the subtract function.
    )pbdoc");

    m.doc() = "Add two vectors using pybind11"; // optional module docstring
    m.def("add_arrays", &add_arrays, "Add two NumPy arrays");

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}

