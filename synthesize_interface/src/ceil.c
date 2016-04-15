/*
 * File: ceil.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 28-Mar-2016 13:59:42
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "getxcorr2.h"
#include "synthesize.h"
#include "ceil.h"

/* Function Definitions */

/*
 * Arguments    : double x[2]
 * Return Type  : void
 */
void b_ceil(double x[2])
{
  int k;
  for (k = 0; k < 2; k++) {
    x[k] = ceil(x[k]);
  }
}

/*
 * File trailer for ceil.c
 *
 * [EOF]
 */
