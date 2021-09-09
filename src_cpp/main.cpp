//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: main.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 31-Aug-2021 17:43:02
//

//***********************************************************************
// This automatically generated example C++ main file shows how to call
// entry-point functions that MATLAB Coder generated. You must customize
// this file for your application. Do not modify this file directly.
// Instead, make a copy of this file, modify it, and integrate it into
// your development environment.
//
// This file initializes entry-point function arguments to a default
// size and value before calling the entry-point functions. It does
// not store or use any values returned from the entry-point functions.
// If necessary, it does pre-allocate memory for returned values.
// You can use this file as a starting point for a main function that
// you can deploy in your application.
//
// After you copy the file, and before you deploy it, you must make the
// following changes:
// * For variable-size function arguments, change the example sizes to
// the sizes that your application requires.
// * Change the example values of function arguments to the values that
// your application requires.
// * If the entry-point functions return values, store these values or
// otherwise use them as required by your application.
//
//***********************************************************************

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include "expalts.h"
#include <cstddef>
#include <cstdlib>
#include <iostream>

//
// Function Declarations
extern int main(int argc, const char * const argv[]);
// Arguments    : int argc
//                const char * const argv[]
// Return Type  : int
//
int main(int, const char * const [])
{
    
    coder::array<double, 2U> x; //x = {1 2 4 5};   
    x.set_size(1, 20);
    // linearly spaced array of increasing values
    double endpts[2] = {-10 ,10};
    for (int id = 0; id < x.size(1); id++) {
        x[id] = (endpts[1]-endpts[0])/(double)x.size(1);
        x[id] = endpts[0] + endpts[1]*( x[id]);
    } 
    
    // use expalts library
    coder::array<double, 2U> y1;
    coder::array<double, 2U> y2;
    for (int id = 0; id < x.size(1); id++) {
        y1[id] = expalts::ebits((x[id]));
        y2[id] = expalts::byones((x[id]), 0);
    }      
    
    // stream output to console
    for (int i = 0; i < x.size(1); i++) {
        if (i > 0) {
            std::cout << "";
            std::cout << "x \t y1 \t y2"<< std::endl;
        }
        std::cout << x[i] << "\t" << y1[i] << "\t" << y2[i] << std::endl;
    }
    std::cout << std::endl;
    // terminate the application.
    // You do not need to do this more than one time.
    return 0;
}

//
// File trailer for main.cpp
//
// [EOF]
//
