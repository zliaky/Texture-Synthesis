/*
 * File: power.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 28-Mar-2016 13:59:42
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "getxcorr2.h"
#include "synthesize.h"
#include "power.h"
#include "synthesize_emxutil.h"

/* Function Declarations */
static void eml_scalexp_alloc(const emxArray_real_T *varargin_1, emxArray_real_T
  *z);

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *varargin_1
 *                emxArray_real_T *z
 * Return Type  : void
 */
static void eml_scalexp_alloc(const emxArray_real_T *varargin_1, emxArray_real_T
  *z)
{
  short iv5[3];
  int i11;
  for (i11 = 0; i11 < 3; i11++) {
    iv5[i11] = (short)varargin_1->size[i11];
  }

  i11 = z->size[0] * z->size[1] * z->size[2];
  z->size[0] = iv5[0];
  z->size[1] = iv5[1];
  z->size[2] = iv5[2];
  emxEnsureCapacity((emxArray__common *)z, i11, (int)sizeof(double));
}

/*
 * Arguments    : const emxArray_real_T *a
 *                emxArray_real_T *y
 * Return Type  : void
 */
void b_power(const emxArray_real_T *a, emxArray_real_T *y)
{
  unsigned int unnamed_idx_0;
  int k;
  unnamed_idx_0 = (unsigned int)a->size[0];
  k = y->size[0];
  y->size[0] = (int)unnamed_idx_0;
  emxEnsureCapacity((emxArray__common *)y, k, (int)sizeof(double));
  for (k = 0; k < (int)unnamed_idx_0; k++) {
    y->data[k] = a->data[k] * a->data[k];
  }
}

/*
 * Arguments    : const emxArray_real_T *a
 *                emxArray_real_T *y
 * Return Type  : void
 */
void power(const emxArray_real_T *a, emxArray_real_T *y)
{
  int i10;
  int k;
  eml_scalexp_alloc(a, y);
  i10 = y->size[0] * y->size[1] * y->size[2];
  for (k = 0; k < i10; k++) {
    y->data[k] = a->data[k] * a->data[k];
  }
}

/*
 * File trailer for power.c
 *
 * [EOF]
 */
