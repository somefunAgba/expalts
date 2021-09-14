//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  expalts.h
//
//  Code generation for function 'expalts'
//


#ifndef EXPALTS_H
#define EXPALTS_H

// Include files
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
class expalts
{
 public:
  static double bones(double x, unsigned char mode);
  static double ebits(double x);
  static double isq(double x);
  static boolean_T ieven(int n);
  static double elap(double x);
};

// #include <pybind11/pybind11.h>
// 
// namespace py = pybind11;
// 
// PYBIND11_MODULE(expalts, m) {
//     py::class_<expalts>(m, "expalts")
//         .def(py::init<>())
//         .def_static("ebits", &expalts::ebits)
//         .def_static("elap", &expalts::elap)
//         .def_static("isq", &expalts::isq)
//         .def_static("ieven", &expalts::ieven)
//         .def_static("bones", &expalts::bones);
// }
// 
// #endif

// End of code generation (expalts.h)
