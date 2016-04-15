/*
 * File: sum.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 28-Mar-2016 13:59:42
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "getxcorr2.h"
#include "synthesize.h"
#include "sum.h"
#include "synthesize_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                emxArray_real_T *y
 * Return Type  : void
 */
void b_sum(const emxArray_real_T *x, emxArray_real_T *y)
{
  short sz[3];
  int k;
  int vstride;
  int iy;
  int ixstart;
  int j;
  int ix;
  double s;
  for (k = 0; k < 3; k++) {
    sz[k] = (short)x->size[k];
  }

  k = y->size[0] * y->size[1];
  y->size[0] = sz[0];
  y->size[1] = sz[1];
  emxEnsureCapacity((emxArray__common *)y, k, (int)sizeof(double));
  if ((x->size[0] == 0) || (x->size[1] == 0) || (x->size[2] == 0)) {
    k = y->size[0] * y->size[1];
    y->size[0] = sz[0];
    emxEnsureCapacity((emxArray__common *)y, k, (int)sizeof(double));
    k = y->size[0] * y->size[1];
    y->size[1] = sz[1];
    emxEnsureCapacity((emxArray__common *)y, k, (int)sizeof(double));
    vstride = sz[0] * sz[1];
    for (k = 0; k < vstride; k++) {
      y->data[k] = 0.0;
    }
  } else {
    k = 3;
    while ((k > 2) && (x->size[2] == 1)) {
      k = 2;
    }

    if (3 > k) {
      vstride = x->size[0] * x->size[1] * x->size[2];
    } else {
      vstride = 1;
      for (k = 0; k < 2; k++) {
        vstride *= x->size[k];
      }
    }

    iy = -1;
    ixstart = -1;
    for (j = 1; j <= vstride; j++) {
      ixstart++;
      ix = ixstart;
      s = x->data[ixstart];
      for (k = 2; k <= x->size[2]; k++) {
        ix += vstride;
        s += x->data[ix];
      }

      iy++;
      y->data[iy] = s;
    }
  }
}

/*
 * Arguments    : const emxArray_real_T *x
 * Return Type  : double
 */
double sum(const emxArray_real_T *x)
{
  double y;
  int k;
  if (x->size[0] == 0) {
    y = 0.0;
  } else {
    y = x->data[0];
    for (k = 2; k <= x->size[0]; k++) {
      y += x->data[k - 1];
    }
  }

  return y;
}

/*
 * File trailer for sum.c
 *
 * [EOF]
 */
