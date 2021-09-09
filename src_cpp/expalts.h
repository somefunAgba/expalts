//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: expalts.h
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 09-Sep-2021 09:54:41
//
#ifndef EXPALTS_H
#define EXPALTS_H

// Include Files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
class expalts
{
 public:
  static double ebits(double x);
  static double isq(double x);
  static boolean_T ieven(double x);
  static double byones(double x, double mode);
};


// #include <pybind11/pybind11.h>
// 
// namespace py = pybind11;
// 
// PYBIND11_MODULE(expalts, m) {
//     py::class_<expalts>(m, "expalts")
//         .def(py::init<>())
//         .def_static("ebits", &expalts::ebits)
//         .def_static("isq", &expalts::isq)
//         .def_static("ieven", &expalts::ieven)
//         .def_static("byones", &expalts::byones);
// }

#endif

//
// File trailer for expalts.h
//
// [EOF]
//
