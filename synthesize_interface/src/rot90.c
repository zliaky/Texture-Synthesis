/*
 * File: rot90.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 28-Mar-2016 13:59:42
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "getxcorr2.h"
#include "synthesize.h"
#include "rot90.h"
#include "synthesize_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *A
 *                emxArray_real_T *B
 * Return Type  : void
 */
void rot90(const emxArray_real_T *A, emxArray_real_T *B)
{
  int m;
  int n;
  int j;
  int i;
  int B_idx_0;
  int A_idx_0;
  m = A->size[0];
  n = A->size[1];
  for (j = 0; j < 2; j++) {
    i = B->size[0] * B->size[1];
    B->size[j] = A->size[j];
    emxEnsureCapacity((emxArray__common *)B, i, (int)sizeof(double));
  }

  for (j = 1; j <= n; j++) {
    for (i = 1; i <= m; i++) {
      B_idx_0 = B->size[0];
      A_idx_0 = A->size[0];
      B->data[(i + B_idx_0 * (j - 1)) - 1] = A->data[(m - i) + A_idx_0 * (n - j)];
    }
  }
}

/*
 * File trailer for rot90.c
 *
 * [EOF]
 */
