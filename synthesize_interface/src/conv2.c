/*
 * File: conv2.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 28-Mar-2016 13:59:42
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "getxcorr2.h"
#include "synthesize.h"
#include "conv2.h"
#include "synthesize_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *arg1
 *                const emxArray_real_T *arg2
 *                emxArray_real_T *c
 * Return Type  : void
 */
void conv2(const emxArray_real_T *arg1, const emxArray_real_T *arg2,
           emxArray_real_T *c)
{
  int mc;
  int nc;
  int u0;
  int iC;
  boolean_T b0;
  int ma;
  int na;
  int lastColB;
  int lastRowB;
  int j;
  int lastColA;
  int k;
  int iB;
  int i;
  int lastRowA;
  int aidx;
  int cidx;
  int r;
  if ((arg1->size[0] == 0) || (arg2->size[0] == 0)) {
    mc = arg1->size[0] + arg2->size[0];
  } else {
    mc = (arg1->size[0] + arg2->size[0]) - 1;
  }

  if ((arg1->size[1] == 0) || (arg2->size[1] == 0)) {
    nc = arg1->size[1] + arg2->size[1];
  } else {
    nc = (arg1->size[1] + arg2->size[1]) - 1;
  }

  u0 = c->size[0] * c->size[1];
  c->size[0] = mc;
  emxEnsureCapacity((emxArray__common *)c, u0, (int)sizeof(double));
  u0 = c->size[0] * c->size[1];
  c->size[1] = nc;
  emxEnsureCapacity((emxArray__common *)c, u0, (int)sizeof(double));
  iC = mc * nc;
  for (u0 = 0; u0 < iC; u0++) {
    c->data[u0] = 0.0;
  }

  if ((arg1->size[0] == 0) || (arg1->size[1] == 0) || ((arg2->size[0] == 0) ||
       (arg2->size[1] == 0)) || ((mc == 0) || (nc == 0))) {
    b0 = true;
  } else {
    b0 = false;
  }

  if (!b0) {
    ma = arg1->size[0];
    na = arg1->size[1];
    if (arg2->size[1] <= nc - 1) {
      lastColB = arg2->size[1];
    } else {
      lastColB = nc;
    }

    if (arg2->size[0] <= mc - 1) {
      lastRowB = arg2->size[0];
    } else {
      lastRowB = mc;
    }

    for (j = 0; j < lastColB; j++) {
      if ((j + na) - 1 < nc - 1) {
        lastColA = na;
      } else {
        lastColA = nc - j;
      }

      for (k = 0; k < lastColA; k++) {
        u0 = j + k;
        if (u0 >= 0) {
        } else {
          u0 = 0;
        }

        iC = u0 * mc;
        u0 = k * ma;
        iB = j * arg2->size[0];
        for (i = 0; i < lastRowB; i++) {
          if (i + ma <= mc - 1) {
            lastRowA = ma;
          } else {
            lastRowA = mc - i;
          }

          aidx = u0;
          cidx = iC;
          for (r = 1; r <= lastRowA; r++) {
            c->data[cidx] += arg2->data[iB] * arg1->data[aidx];
            aidx++;
            cidx++;
          }

          iB++;
          iC++;
        }
      }
    }
  }
}

/*
 * File trailer for conv2.c
 *
 * [EOF]
 */
