//
//  Academic License - for use in teaching, academic research, and meeting
//  course requirements at degree granting institutions only.  Not for
//  government, commercial, or other organizational use.
//
//  expalts.cpp
//
//  Code generation for function 'expalts'
//


// Include files
#include "expalts.h"
#include "rt_nonfinite.h"
#include <cmath>

// Function Declarations
static double rt_powd_snf(double u0, double u1);

// Function Definitions
//
//  function y = ebits(x)

double expalts::ebits(double x)
{
  // EXP COMPUTATION BY LIMIT THEOREM AND BIT-SHIFTS
  //  EBITS
  //  Exponentiatiobn by the Limit Theoremm.
  //  implements natural exponentiation function
  //  using the limit theorem as n -> infinity
  //  y =  ( (1 + (x)*(1/n)) )^n
  //              arguments
  //                  x {mustBeNumeric}
  //              end
  //  - bit-shift
  //  bitwise realization of
  //  xx = (1 + (x).*(1/n)) = 1 + (x .* bitsra(1,16));
  //  n = 2^k =>
  //  k = 2; n = 4;
  //  k = 4; n = 16;
  // 'expalts:134' k = 8;
  // 'expalts:134' n = 256;
  //  k = 10; n = 1024;
  //  k = 16; n = 65536;
  //  k = 24; n = 16777216; % - recommended
  //  k = 28; n = 268435456;
  //  k = 32; n = 4294967295;
  // 'expalts:140' y = 1 + bitsra(x, k);
  //  - integer squares
  //  y = (xx).^n; choose n = 2^16 -> infty;
  // 'expalts:143' y = expalts.isq(y, n);
  return expalts::isq((std::ldexp(x, -8) + 1.0));

  //  - end
}

//
//  function y = elap(x)

double expalts::elap(double x)
{
  double dv[1];
  double b_x;
  double ts;
  double y;
  int id;

  // EXPLAP: EXP BY LAPLACE APPROXIMATION
  // ELAP
  //  Fast Laplace-based Exponential Algorithm
  //  : just a loop and a first-order algebra
  //  x : real-valued input value
  //  k or nts : number of bits, sampling-time power in base 2,
  //  max value is constrained for speed and
  //  integer-precision max-min limit on current
  //  gen. purpose digital computers.
  //  k = 16, n = 65536
  //  k = 24, n = 16777216,
  //  k = 28, n = 268435456
  //  k = 32, n = 4294967295
  //              arguments
  //                  x {mustBeNumeric}
  //              end
  // 'expalts:169' if ~isrow(x)
  // 'expalts:171' else
  // 'expalts:172' y = zeros(1,numel(x));
  y = 0.0;

  //  final time is unity (1.0secs).
  //  loop limit computation N = 2^nts
  // N = bitsll(1,nts); % zero-based indexing
  // N = bitsll(1,nts) + 1; % one-based indexing
  //
  // -k = 2,
  //  N = 4; ts = 0.25;
  //  -k = 4,
  //  N = 16; ts = 0.0625;
  //  - k = 8,
  // 'expalts:186' N = 256;
  // 'expalts:186' ts = 0.0039;
  //  - k = 10,
  //  N = 1024; ts = 9.7656e-4;
  //  - k = 16, % ts = 1.52587890625e-05
  //  N = 65536 - 1; ts = 1.5259e-5; % - recommended
  //  - k = 21, % ts = 4.7684e-7
  //  N = 2097152 - 1; ts = 4.7684e-7;
  //  - k = 24  % ts = 5.960464477539063e-08
  //  N = 16777216 - 1; ts = 5.9605e-8;
  //  - k = 28,  ts = 3.725290298461914e-09
  //  N = 268435456 - 1; ts = 3.7253e-9;
  //  - k = 32, ts =2.328306436538696e-10
  //  N = 4294967296 - 1; ts = 2.3283e-10;
  // nts = 16;
  //  sampling-time computation using bitwise shift right
  // ts = bitsra(1,nts); % 2^-nts = 1/(2^nts)
  // 'expalts:203' ts = x.*ts;
  ts = x * 0.0039;

  //  augmented sampling-time
  //  vectorized form
  // 'expalts:206' for id = 0:N
  for (id = 0; id < 257; id++) {
    // 'expalts:207' y = y + ts.*(y + sign(x).*1);
    b_x = x;
    if (x < 0.0) {
      b_x = -1.0;
    } else if (x > 0.0) {
      b_x = 1.0;
    } else {
      if (x == 0.0) {
        b_x = 0.0;
      }
    }

    y += ts * (y + b_x);
  }

  // 'expalts:209' y = 1 + sign(x).*y;
  b_x = x;
  if (x < 0.0) {
    b_x = -1.0;
  } else if (x > 0.0) {
    b_x = 1.0;
  } else {
    if (x == 0.0) {
      b_x = 0.0;
    }
  }

  y = b_x * y + 1.0;

  // 'expalts:210' y(isnan(y)) = 0;
  dv[0] = y;
  id = 0;
  if (std::isnan(y)) {
    id = 1;
  }

  if (0 <= id - 1) {
    dv[0] = 0.0;
  }

  // 'expalts:211' y(x==0) = 1;
  if (x == 0.0) {
    dv[0] = 1.0;
  }

  return dv[0];

  //              % input is zero, then output is 1
  //              if x == 0, y =1, end
  //              % input is negative-real
  //              if x < 0
  //                  % using a first-order filter:
  //                  % laplace transfer-function
  //                  % impulse response: un = 1, always unity.
  //                  for id = 0:N
  //                      y = y + (ts.*(y-1));
  //                      %y = y.*(1+ts) - ts;
  //                  end
  //                  y = 1 - y;
  //                  % the natural exponential of
  //                  % very large negative numbers tend to zero
  //                  if isnan(y)
  //                      y = 0;
  //                  end
  //              end
  //
  //              % if input is positive real
  //              if x > 0
  //                  % using a first-order filter:
  //                  % laplace transfer-function
  //                  % impulse response: un = 1, always unity.
  //                  for id = 0:N
  //                      y = y + (ts.*(1+y));
  //                      % y = y.*(1+ts) + ts;
  //                  end
  //                  y = 1 + y;
  //              end
}

//
//  function y = ieven(n)

boolean_T expalts::ieven(int n)
{
  // IS INTEGER EVEN?
  // IEVEN
  //  tests if an input integer n is even or not
  //  returns 1 for even n, 0 for  odd n.
  //              arguments
  //                  n
  //              end
  // 'expalts:296' y = ~(bitand(n,1,'int32'));
  return (static_cast<int>(n) & 1) == 0;

  //  ~(n & 1)
}

//
//  function y = isq(x,n)

double expalts::isq(double x)
{
  int n;
  double y;
  n = 256;

  // INTEGER EXPONENTIATION BY SQUARING
  //  ISQ
  //  integer exponentiation by squaring
  //  iexpbsq: iteration
  //              arguments
  //                  x {mustBeNumeric}
  //                  n
  //              end
  // 'expalts:257' if ~isrow(x)
  // 'expalts:259' else
  // 'expalts:260' y = ones(1,numel(x));
  y = 1.0;

  //
  //  n < 0
  // 'expalts:264' if n < 0
  //
  // 'expalts:273' while (n > 1)
  while (n > 1) {
    // 'expalts:274' if (expalts.ieven(n))
    if (expalts::ieven((n))) {
      // 'expalts:275' x = x.*x;
      x *= x;

      // 'expalts:276' n = n/2;
      n /= 2;
    } else {
      // 'expalts:277' else
      // 'expalts:278' y = x.*y;
      y *= x;

      // 'expalts:279' x = x.*x;
      x *= x;

      // 'expalts:280' n = (n-1)/2;
      n = (n - 1) / 2;
    }
  }

  // 'expalts:283' y = x.*y;
  y *= x;
  return y;
}

static double rt_powd_snf(double u0, double u1)
{
  double y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = rtNaN;
  } else {
    double d;
    double d1;
    d = std::abs(u0);
    d1 = std::abs(u1);
    if (std::isinf(u1)) {
      if (d == 1.0) {
        y = 1.0;
      } else if (d > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = rtNaN;
    } else {
      y = std::pow(u0, u1);
    }
  }

  return y;
}

//
//  function y = bones(x,mode)

double expalts::bones(double x, unsigned char mode)
{
  double xfrac;
  double xrepts;
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
  //  - 0. limit-theorem: bit-shift and integer squares approx.
  //  - 2. laplace approximation
  //  - 1: in-built approximation
  //
  //  - gradual natural exponentation: - useful for improved accuracy
  //    esp. in resource-constrained embedded systems.
  //  y = expalts.byones(x, 0);
  //  y = expalts.byones(x, 2);
  //  - compare with the inbuilt exp.
  //  y = expalts.byones(x, 1);
  //
  // EXPBONE: EXP BY ONES
  // BONES
  //  Gradual natural exponentiation
  //  reducing power x to the closed range [-1 1]
  //  for increased accuracy of fast exponential approximations
  //  by bit shifting and integer squaring.
  //              arguments
  //                  x {mustBeNumeric}
  //                  mode {mustBeMember(mode,[0,1,2])}= 0
  //              end
  //
  // 'expalts:40' expone = 2.7183;
  //  2.718281828459046;
  //  Vectorized Implementation
  // 'expalts:44' xrepts = sign(x).*floor(abs(x));
  xrepts = x;
  if (x < 0.0) {
    xrepts = -1.0;
  } else if (x > 0.0) {
    xrepts = 1.0;
  } else {
    if (x == 0.0) {
      xrepts = 0.0;
    }
  }

  xrepts *= std::floor(std::abs(x));

  // 'expalts:45' xfrac = x - xrepts;
  xfrac = x - xrepts;

  // 'expalts:46' y = (expone).^xrepts;
  y = rt_powd_snf(2.7183, xrepts);

  // 'expalts:47' if mode == 0
  if (mode == 0) {
    //  y = (expalts.ebits(sign(x).*1)).^xrepts;
    // 'expalts:49' y = y.*expalts.ebits(xfrac);
    y *= expalts::ebits((xfrac));
  } else if (mode == 1) {
    // 'expalts:50' elseif mode == 1
    // 'expalts:51' y = y.*exp(xfrac);
    y *= std::exp(xfrac);
  } else {
    if (mode == 2) {
      // 'expalts:52' elseif mode == 2
      // 'expalts:53' y = y.*expalts.elap(xfrac);
      y *= expalts::elap((xfrac));
    }
  }

  // 'expalts:56' if isrow(x)&&~isrow(y)
  //  LOOP implementation
  //              for id = 1:numel(x)
  //                  if mode == 0
  //                      % limit theorem:
  //                      % bit shift and integer squaring fcn implementation
  //                       if x(id) > 1
  //                          while x(id) > 1
  //                              y(id) = y(id).*...
  //                                  (expalts.ebits(1) + 0.0053); %n=8;
  //                              x(id) = x(id)-1;
  //                          end
  //                      elseif x(id) < -1
  //                          while x(id) < -1
  //                              y(id) = y(id).*...
  //                                  (expalts.ebits(-1) + 7.1969e-4); %n=8
  //                              x(id) = x(id)+1;
  //                          end
  //                      end
  //                      % x is now a number close to zero, differences from the 
  //                      % truth becomes negligible
  //                      y(id) = y(id).*expalts.ebits(x(id));
  //                  elseif mode == 1
  //                      % in-built exponential fcn implementation
  //                      if x(id) > 1
  //                          while x(id) > 1
  //                              y(id) = y(id).*exp(1);
  //                              x(id) = x(id)-1;
  //                          end
  //                      elseif x(id) < -1
  //                          while x(id) < -1
  //                              y(id) = y(id).*exp(-1);
  //                              x(id) = x(id)+1;
  //                          end
  //                      end
  //                      y(id) = y(id).*exp(x(id));
  //                  elseif mode == 2
  //                      % laplace exponential fcn implementation
  //                      if x(id) > 1
  //                          while x(id) > 1
  //                              y(id) = y(id).*...
  //                                  (expalts.elap(1) - 9.5315e-04); %n=8
  //                              x(id) = x(id)-1;
  //                          end
  //                      elseif x(id) < -1
  //                          while x(id) < -1
  //                              y(id) = y(id).*...
  //                                  (expalts.elap(-1) + 0.0016); % n=8
  //                              x(id) = x(id)+1;
  //                          end
  //                      end
  //                      y(id) = y(id).*expalts.elap(x(id));
  //                  end
  //              end
  return y;
}

// End of code generation (expalts.cpp)
