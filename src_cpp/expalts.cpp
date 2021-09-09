//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: expalts.cpp
//
// MATLAB Coder version            : 5.1
// C/C++ source code generated on  : 09-Sep-2021 09:54:41
//

// Include Files
#include "expalts.h"
#include <cmath>

// Function Definitions
//
// function y = ieven(x)
// IEVEN
//  tests if an input integer x is even or not
//  returns 1 for even x, 0 for  odd x.
// Arguments    : double x
// Return Type  : boolean_T
//
boolean_T expalts::ieven(double x)
{
  // IS INTEGER EVEN?
  //              arguments
  //                  x
  //              end
  // 'expalts:151' y = ~(bitand(x,1));
  return !((static_cast<unsigned long long>(x) & 1ULL) != 0.0);

  //  ~(x & 1)
}

//
// function y = isq(x,n)
// ISQ
//  integer exponentiation by squaring
//  iexpbsq: iteration
// Arguments    : double x
// Return Type  : double
//
double expalts::isq(double x)
{
  double n;
  double y;
  n = 1.6777216E+7;

  // INTEGER EXPONENTIATION BY SQUARING
  //              arguments
  //                  x {mustBeNumeric}
  //                  n
  //              end
  // 'expalts:112' if ~isrow(x)
  // 'expalts:114' else
  // 'expalts:115' y = ones(1,numel(x));
  y = 1.0;

  //
  //  n < 0
  // 'expalts:119' if n < 0
  //
  // 'expalts:128' while (n > 1)
  while (n > 1.0) {
    // 'expalts:129' if (expalts.ieven(n))
    if (expalts::ieven((n))) {
      // 'expalts:130' x = x.*x;
      x *= x;

      // 'expalts:131' n = n/2;
      n /= 2.0;
    } else {
      // 'expalts:132' else
      // 'expalts:133' y = x.*y;
      y *= x;

      // 'expalts:134' x = x.*x;
      x *= x;

      // 'expalts:135' n = (n-1)/2;
      n = (n - 1.0) / 2.0;
    }
  }

  // 'expalts:138' y = x.*y;
  y *= x;
  return y;
}

//
// function y = byones(x,mode)
// BYONES
//  Gradual natural exponentiation
//  reducing power x to the closed range [-1 1]
//  for increased accuracy of fast exponential approximations
//  by bit shifting and integer squaring.
// Arguments    : double x
//                double mode
// Return Type  : double
//
double expalts::byones(double x, double mode)
{
  double y;

  // EXPALTS: ALTERNATIVE NATURAL EXPONENTIAL COMPUTATIONS
  //  Oluwasegun Somefun.
  //  OAS.<oasomefun@futa.edu.ng, somefuno@oregonstate.edu>
  //  Original: 2020,
  //  Revised: 2021
  //
  //  UseCase: Test
  //
  //  x = -10:0.01:10
  //
  //  - 1. bit-shift and integer squares approx. of the limit-theorem
  //  y = expalts.ebits(x);
  //
  //  - 2. gradual exponentation: - useful for improved accuracy
  //    esp. in resource-constrained embedded systems.
  //  y = expalts.byones(x, 0);
  //  - compare with the inbuilt exp.
  //  y = expalts.byones(x, 1);
  //
  // EXPBONE: EXP BY ONES
  //              arguments
  //                  x {mustBeNumeric}
  //                  mode {mustBeMember(mode,[0,1])}= 0
  //              end
  // 'expalts:37' if ~isrow(x)
  // 'expalts:39' else
  // 'expalts:40' y = ones(1,numel(x));
  y = 1.0;

  //
  // 'expalts:43' if mode == 0
  if (mode == 0.0) {
    //  limit theorem:
    //  bit shift and integer squaring fcn implementation
    // 'expalts:46' if x > 1
    if (x > 1.0) {
      // 'expalts:47' while x > 1
      while (x > 1.0) {
        // 'expalts:48' y = y.*expalts.ebits(1);
        y *= expalts::ebits((1.0));

        // 'expalts:49' x = x-1;
        x--;
      }
    } else {
      if (x < -1.0) {
        // 'expalts:51' elseif x < -1
        // 'expalts:52' while x < -1
        while (x < -1.0) {
          // 'expalts:53' y = y.*expalts.ebits(-1);
          y *= expalts::ebits((-1.0));

          // 'expalts:54' x = x+1;
          x++;
        }
      }
    }

    // 'expalts:57' y = y.*expalts.ebits(x);
    y *= expalts::ebits((x));
  } else {
    if (mode == 1.0) {
      // 'expalts:58' elseif mode == 1
      //  in-built exponential fcn implementation
      // 'expalts:60' if x > 1
      if (x > 1.0) {
        // 'expalts:61' while x > 1
        while (x > 1.0) {
          // 'expalts:62' y = y.*exp(1);
          y *= 2.7182818284590455;

          // 'expalts:63' x = x-1;
          x--;
        }
      } else {
        if (x < -1.0) {
          // 'expalts:65' elseif x < -1
          // 'expalts:66' while x < -1
          while (x < -1.0) {
            // 'expalts:67' y = y.*exp(-1);
            y *= 0.36787944117144233;

            // 'expalts:68' x = x+1;
            x++;
          }
        }
      }

      // 'expalts:71' y = y.*exp(x);
      y *= std::exp(x);
    }
  }

  return y;
}

//
// function y = ebits(x)
// EBITS
//  Exponentiatiobn by the Limit Theoremm.
//  implements natural exponentiation function
//  using the limit theorem as n -> infinity
//  y =  ( (1 + (x)*(1/n)) )^n
// Arguments    : double x
// Return Type  : double
//
double expalts::ebits(double x)
{
  // EXP COMPUTATION BY LIMIT THEOREM AND BIT-SHIFTS
  //              arguments
  //                  x {mustBeNumeric}
  //              end
  //  - bit-shift
  //  bitwise realization of
  //  xx = (1 + (x).*(1/n)) = 1 + (x .* bitsra(1,16));
  //  n = 2^k =>  k = 16, n = 65536
  //  k = 24, n = 16777216
  // 'expalts:93' y = 1 + bitsra(x, 24);
  //  - integer squares
  //  y = (xx).^n; choose n = 2^16 -> infty;
  // 'expalts:96' y = expalts.isq(y, 16777216);
  return expalts::isq((std::ldexp(x, -24) + 1.0));

  //  - end
}

//
// File trailer for expalts.cpp
//
// [EOF]
//
