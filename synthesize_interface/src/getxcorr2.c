/*
 * File: getxcorr2.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 28-Mar-2016 13:59:42
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "getxcorr2.h"
#include "synthesize.h"
#include "synthesize_emxutil.h"
#include "conv2.h"
#include "rot90.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *A
 *                const emxArray_real_T *B
 *                emxArray_real_T *Ans
 * Return Type  : void
 */
void b_getxcorr2(const emxArray_real_T *A, const emxArray_real_T *B,
                 emxArray_real_T *Ans)
{
  emxArray_real_T *r7;
  emxArray_real_T *b_B;
  int b_Ans;
  int loop_ub;
  int b_loop_ub;
  int i12;
  int i13;
  emxArray_real_T *b_A;
  int i;
  emxArray_real_T *r8;
  emxArray_real_T *c_A;
  emxArray_real_T *c_B;
  emxInit_real_T(&r7, 2);
  if (A->size[2] == 1) {
    emxInit_real_T(&b_B, 2);
    b_Ans = B->size[0];
    loop_ub = B->size[0];
    b_loop_ub = B->size[1];
    i12 = b_B->size[0] * b_B->size[1];
    b_B->size[0] = loop_ub;
    b_B->size[1] = b_loop_ub;
    emxEnsureCapacity((emxArray__common *)b_B, i12, (int)sizeof(double));
    for (i12 = 0; i12 < b_loop_ub; i12++) {
      for (i13 = 0; i13 < loop_ub; i13++) {
        b_B->data[i13 + b_B->size[0] * i12] = B->data[i13 + b_Ans * i12];
      }
    }

    emxInit_real_T(&b_A, 2);
    rot90(b_B, r7);
    loop_ub = A->size[0];
    b_loop_ub = A->size[1];
    i12 = b_A->size[0] * b_A->size[1];
    b_A->size[0] = loop_ub;
    b_A->size[1] = b_loop_ub;
    emxEnsureCapacity((emxArray__common *)b_A, i12, (int)sizeof(double));
    emxFree_real_T(&b_B);
    for (i12 = 0; i12 < b_loop_ub; i12++) {
      for (i13 = 0; i13 < loop_ub; i13++) {
        b_A->data[i13 + b_A->size[0] * i12] = A->data[i13 + A->size[0] * i12];
      }
    }

    conv2(b_A, r7, Ans);
    emxFree_real_T(&b_A);
  } else {
    emxInit_real_T(&b_B, 2);
    loop_ub = B->size[0];
    b_loop_ub = B->size[1];
    i12 = b_B->size[0] * b_B->size[1];
    b_B->size[0] = loop_ub;
    b_B->size[1] = b_loop_ub;
    emxEnsureCapacity((emxArray__common *)b_B, i12, (int)sizeof(double));
    for (i12 = 0; i12 < b_loop_ub; i12++) {
      for (i13 = 0; i13 < loop_ub; i13++) {
        b_B->data[i13 + b_B->size[0] * i12] = B->data[i13 + B->size[0] * i12];
      }
    }

    emxInit_real_T(&b_A, 2);
    rot90(b_B, r7);
    loop_ub = A->size[0];
    b_loop_ub = A->size[1];
    i12 = b_A->size[0] * b_A->size[1];
    b_A->size[0] = loop_ub;
    b_A->size[1] = b_loop_ub;
    emxEnsureCapacity((emxArray__common *)b_A, i12, (int)sizeof(double));
    emxFree_real_T(&b_B);
    for (i12 = 0; i12 < b_loop_ub; i12++) {
      for (i13 = 0; i13 < loop_ub; i13++) {
        b_A->data[i13 + b_A->size[0] * i12] = A->data[i13 + A->size[0] * i12];
      }
    }

    conv2(b_A, r7, Ans);
    i = 0;
    emxFree_real_T(&b_A);
    emxInit_real_T(&r8, 2);
    emxInit_real_T(&c_A, 2);
    emxInit_real_T(&c_B, 2);
    while (i <= A->size[2] - 2) {
      loop_ub = B->size[0];
      b_loop_ub = B->size[1];
      i12 = c_B->size[0] * c_B->size[1];
      c_B->size[0] = loop_ub;
      c_B->size[1] = b_loop_ub;
      emxEnsureCapacity((emxArray__common *)c_B, i12, (int)sizeof(double));
      for (i12 = 0; i12 < b_loop_ub; i12++) {
        for (i13 = 0; i13 < loop_ub; i13++) {
          c_B->data[i13 + c_B->size[0] * i12] = B->data[i13 + B->size[0] * i12];
        }
      }

      rot90(c_B, r7);
      loop_ub = A->size[0];
      b_loop_ub = A->size[1];
      i12 = c_A->size[0] * c_A->size[1];
      c_A->size[0] = loop_ub;
      c_A->size[1] = b_loop_ub;
      emxEnsureCapacity((emxArray__common *)c_A, i12, (int)sizeof(double));
      for (i12 = 0; i12 < b_loop_ub; i12++) {
        for (i13 = 0; i13 < loop_ub; i13++) {
          c_A->data[i13 + c_A->size[0] * i12] = A->data[(i13 + A->size[0] * i12)
            + A->size[0] * A->size[1] * (i + 1)];
        }
      }

      conv2(c_A, r7, r8);
      i12 = Ans->size[0] * Ans->size[1];
      emxEnsureCapacity((emxArray__common *)Ans, i12, (int)sizeof(double));
      b_Ans = Ans->size[0];
      loop_ub = Ans->size[1];
      loop_ub *= b_Ans;
      for (i12 = 0; i12 < loop_ub; i12++) {
        Ans->data[i12] += r8->data[i12];
      }

      i++;
    }

    emxFree_real_T(&c_B);
    emxFree_real_T(&c_A);
    emxFree_real_T(&r8);
  }

  emxFree_real_T(&r7);
}

/*
 * Arguments    : const emxArray_real_T *A
 *                const emxArray_real_T *B
 *                emxArray_real_T *Ans
 * Return Type  : void
 */
void c_getxcorr2(const emxArray_real_T *A, const emxArray_real_T *B,
                 emxArray_real_T *Ans)
{
  emxArray_real_T *r9;
  emxArray_real_T *r10;
  emxArray_real_T *b_B;
  int loop_ub;
  int b_loop_ub;
  int i14;
  int i15;
  emxArray_real_T *b_A;
  int i;
  emxArray_real_T *c_A;
  emxArray_real_T *c_B;
  int B_idx_0;
  emxInit_real_T(&r9, 2);
  emxInit_real_T(&r10, 2);
  if (A->size[2] == B->size[2]) {
    emxInit_real_T(&b_B, 2);
    loop_ub = B->size[0];
    b_loop_ub = B->size[1];
    i14 = b_B->size[0] * b_B->size[1];
    b_B->size[0] = loop_ub;
    b_B->size[1] = b_loop_ub;
    emxEnsureCapacity((emxArray__common *)b_B, i14, (int)sizeof(double));
    for (i14 = 0; i14 < b_loop_ub; i14++) {
      for (i15 = 0; i15 < loop_ub; i15++) {
        b_B->data[i15 + b_B->size[0] * i14] = B->data[i15 + B->size[0] * i14];
      }
    }

    emxInit_real_T(&b_A, 2);
    rot90(b_B, r10);
    loop_ub = A->size[0];
    b_loop_ub = A->size[1];
    i14 = b_A->size[0] * b_A->size[1];
    b_A->size[0] = loop_ub;
    b_A->size[1] = b_loop_ub;
    emxEnsureCapacity((emxArray__common *)b_A, i14, (int)sizeof(double));
    emxFree_real_T(&b_B);
    for (i14 = 0; i14 < b_loop_ub; i14++) {
      for (i15 = 0; i15 < loop_ub; i15++) {
        b_A->data[i15 + b_A->size[0] * i14] = A->data[i15 + A->size[0] * i14];
      }
    }

    conv2(b_A, r10, Ans);
    i = 1;
    emxFree_real_T(&b_A);
    emxInit_real_T(&c_A, 2);
    emxInit_real_T(&c_B, 2);
    while (i - 1 <= A->size[2] - 2) {
      loop_ub = B->size[0];
      b_loop_ub = B->size[1];
      i14 = c_B->size[0] * c_B->size[1];
      c_B->size[0] = loop_ub;
      c_B->size[1] = b_loop_ub;
      emxEnsureCapacity((emxArray__common *)c_B, i14, (int)sizeof(double));
      for (i14 = 0; i14 < b_loop_ub; i14++) {
        for (i15 = 0; i15 < loop_ub; i15++) {
          c_B->data[i15 + c_B->size[0] * i14] = B->data[(i15 + B->size[0] * i14)
            + B->size[0] * B->size[1] * i];
        }
      }

      rot90(c_B, r10);
      loop_ub = A->size[0];
      b_loop_ub = A->size[1];
      i14 = c_A->size[0] * c_A->size[1];
      c_A->size[0] = loop_ub;
      c_A->size[1] = b_loop_ub;
      emxEnsureCapacity((emxArray__common *)c_A, i14, (int)sizeof(double));
      for (i14 = 0; i14 < b_loop_ub; i14++) {
        for (i15 = 0; i15 < loop_ub; i15++) {
          c_A->data[i15 + c_A->size[0] * i14] = A->data[(i15 + A->size[0] * i14)
            + A->size[0] * A->size[1] * i];
        }
      }

      conv2(c_A, r10, r9);
      i14 = Ans->size[0] * Ans->size[1];
      emxEnsureCapacity((emxArray__common *)Ans, i14, (int)sizeof(double));
      loop_ub = Ans->size[0];
      b_loop_ub = Ans->size[1];
      loop_ub *= b_loop_ub;
      for (i14 = 0; i14 < loop_ub; i14++) {
        Ans->data[i14] += r9->data[i14];
      }

      i++;
    }

    emxFree_real_T(&c_B);
    emxFree_real_T(&c_A);
  } else if (B->size[2] == 1) {
    emxInit_real_T(&b_B, 2);
    B_idx_0 = B->size[0];
    loop_ub = B->size[0];
    b_loop_ub = B->size[1];
    i14 = b_B->size[0] * b_B->size[1];
    b_B->size[0] = loop_ub;
    b_B->size[1] = b_loop_ub;
    emxEnsureCapacity((emxArray__common *)b_B, i14, (int)sizeof(double));
    for (i14 = 0; i14 < b_loop_ub; i14++) {
      for (i15 = 0; i15 < loop_ub; i15++) {
        b_B->data[i15 + b_B->size[0] * i14] = B->data[i15 + B_idx_0 * i14];
      }
    }

    emxInit_real_T(&b_A, 2);
    rot90(b_B, r10);
    loop_ub = A->size[0];
    b_loop_ub = A->size[1];
    i14 = b_A->size[0] * b_A->size[1];
    b_A->size[0] = loop_ub;
    b_A->size[1] = b_loop_ub;
    emxEnsureCapacity((emxArray__common *)b_A, i14, (int)sizeof(double));
    emxFree_real_T(&b_B);
    for (i14 = 0; i14 < b_loop_ub; i14++) {
      for (i15 = 0; i15 < loop_ub; i15++) {
        b_A->data[i15 + b_A->size[0] * i14] = A->data[i15 + A->size[0] * i14];
      }
    }

    conv2(b_A, r10, Ans);
    i = 0;
    emxFree_real_T(&b_A);
    emxInit_real_T(&c_A, 2);
    emxInit_real_T(&c_B, 2);
    while (i <= A->size[2] - 2) {
      B_idx_0 = B->size[0];
      loop_ub = B->size[0];
      b_loop_ub = B->size[1];
      i14 = c_B->size[0] * c_B->size[1];
      c_B->size[0] = loop_ub;
      c_B->size[1] = b_loop_ub;
      emxEnsureCapacity((emxArray__common *)c_B, i14, (int)sizeof(double));
      for (i14 = 0; i14 < b_loop_ub; i14++) {
        for (i15 = 0; i15 < loop_ub; i15++) {
          c_B->data[i15 + c_B->size[0] * i14] = B->data[i15 + B_idx_0 * i14];
        }
      }

      rot90(c_B, r10);
      loop_ub = A->size[0];
      b_loop_ub = A->size[1];
      i14 = c_A->size[0] * c_A->size[1];
      c_A->size[0] = loop_ub;
      c_A->size[1] = b_loop_ub;
      emxEnsureCapacity((emxArray__common *)c_A, i14, (int)sizeof(double));
      for (i14 = 0; i14 < b_loop_ub; i14++) {
        for (i15 = 0; i15 < loop_ub; i15++) {
          c_A->data[i15 + c_A->size[0] * i14] = A->data[(i15 + A->size[0] * i14)
            + A->size[0] * A->size[1] * (i + 1)];
        }
      }

      conv2(c_A, r10, r9);
      i14 = Ans->size[0] * Ans->size[1];
      emxEnsureCapacity((emxArray__common *)Ans, i14, (int)sizeof(double));
      loop_ub = Ans->size[0];
      b_loop_ub = Ans->size[1];
      loop_ub *= b_loop_ub;
      for (i14 = 0; i14 < loop_ub; i14++) {
        Ans->data[i14] += r9->data[i14];
      }

      i++;
    }

    emxFree_real_T(&c_B);
    emxFree_real_T(&c_A);
  } else {
    emxInit_real_T(&b_B, 2);

    /*          if(size(A,3)==1) */
    /*              Ans = getxcorr2(B,A); */
    /*          else */
    loop_ub = B->size[0];
    b_loop_ub = B->size[1];
    i14 = b_B->size[0] * b_B->size[1];
    b_B->size[0] = loop_ub;
    b_B->size[1] = b_loop_ub;
    emxEnsureCapacity((emxArray__common *)b_B, i14, (int)sizeof(double));
    for (i14 = 0; i14 < b_loop_ub; i14++) {
      for (i15 = 0; i15 < loop_ub; i15++) {
        b_B->data[i15 + b_B->size[0] * i14] = B->data[i15 + B->size[0] * i14];
      }
    }

    emxInit_real_T(&b_A, 2);
    rot90(b_B, r10);
    loop_ub = A->size[0];
    b_loop_ub = A->size[1];
    i14 = b_A->size[0] * b_A->size[1];
    b_A->size[0] = loop_ub;
    b_A->size[1] = b_loop_ub;
    emxEnsureCapacity((emxArray__common *)b_A, i14, (int)sizeof(double));
    emxFree_real_T(&b_B);
    for (i14 = 0; i14 < b_loop_ub; i14++) {
      for (i15 = 0; i15 < loop_ub; i15++) {
        b_A->data[i15 + b_A->size[0] * i14] = A->data[i15 + A->size[0] * i14];
      }
    }

    conv2(b_A, r10, Ans);

    /*          end */
    emxFree_real_T(&b_A);
  }

  emxFree_real_T(&r10);
  emxFree_real_T(&r9);
}

/*
 * Arguments    : const emxArray_real_T *A
 *                const emxArray_real_T *B
 *                emxArray_real_T *Ans
 * Return Type  : void
 */
void getxcorr2(const emxArray_real_T *A, const emxArray_real_T *B,
               emxArray_real_T *Ans)
{
  emxArray_real_T *r0;
  emxArray_real_T *r1;
  emxArray_real_T *r2;
  emxArray_real_T *b_B;
  int loop_ub;
  int b_loop_ub;
  int i0;
  int i1;
  emxArray_real_T *b_A;
  int i;
  emxArray_real_T *c_A;
  emxArray_real_T *c_B;
  int B_idx_0;
  emxInit_real_T(&r0, 2);
  emxInit_real_T(&r1, 2);
  emxInit_real_T(&r2, 2);
  if (A->size[2] == B->size[2]) {
    emxInit_real_T(&b_B, 2);
    loop_ub = B->size[0];
    b_loop_ub = B->size[1];
    i0 = b_B->size[0] * b_B->size[1];
    b_B->size[0] = loop_ub;
    b_B->size[1] = b_loop_ub;
    emxEnsureCapacity((emxArray__common *)b_B, i0, (int)sizeof(double));
    for (i0 = 0; i0 < b_loop_ub; i0++) {
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_B->data[i1 + b_B->size[0] * i0] = B->data[i1 + B->size[0] * i0];
      }
    }

    emxInit_real_T(&b_A, 2);
    rot90(b_B, r1);
    loop_ub = A->size[0];
    b_loop_ub = A->size[1];
    i0 = b_A->size[0] * b_A->size[1];
    b_A->size[0] = loop_ub;
    b_A->size[1] = b_loop_ub;
    emxEnsureCapacity((emxArray__common *)b_A, i0, (int)sizeof(double));
    emxFree_real_T(&b_B);
    for (i0 = 0; i0 < b_loop_ub; i0++) {
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_A->data[i1 + b_A->size[0] * i0] = A->data[i1 + A->size[0] * i0];
      }
    }

    conv2(b_A, r1, r2);
    i0 = Ans->size[0] * Ans->size[1];
    Ans->size[0] = r2->size[0];
    Ans->size[1] = r2->size[1];
    emxEnsureCapacity((emxArray__common *)Ans, i0, (int)sizeof(double));
    loop_ub = r2->size[0] * r2->size[1];
    emxFree_real_T(&b_A);
    for (i0 = 0; i0 < loop_ub; i0++) {
      Ans->data[i0] = r2->data[i0];
    }

    i = 1;
    emxInit_real_T(&c_A, 2);
    emxInit_real_T(&c_B, 2);
    while (i - 1 <= A->size[2] - 2) {
      loop_ub = B->size[0];
      b_loop_ub = B->size[1];
      i0 = c_B->size[0] * c_B->size[1];
      c_B->size[0] = loop_ub;
      c_B->size[1] = b_loop_ub;
      emxEnsureCapacity((emxArray__common *)c_B, i0, (int)sizeof(double));
      for (i0 = 0; i0 < b_loop_ub; i0++) {
        for (i1 = 0; i1 < loop_ub; i1++) {
          c_B->data[i1 + c_B->size[0] * i0] = B->data[(i1 + B->size[0] * i0) +
            B->size[0] * B->size[1] * i];
        }
      }

      rot90(c_B, r1);
      loop_ub = A->size[0];
      b_loop_ub = A->size[1];
      i0 = c_A->size[0] * c_A->size[1];
      c_A->size[0] = loop_ub;
      c_A->size[1] = b_loop_ub;
      emxEnsureCapacity((emxArray__common *)c_A, i0, (int)sizeof(double));
      for (i0 = 0; i0 < b_loop_ub; i0++) {
        for (i1 = 0; i1 < loop_ub; i1++) {
          c_A->data[i1 + c_A->size[0] * i0] = A->data[(i1 + A->size[0] * i0) +
            A->size[0] * A->size[1] * i];
        }
      }

      conv2(c_A, r1, r2);
      i0 = r0->size[0] * r0->size[1];
      r0->size[0] = r2->size[0];
      r0->size[1] = r2->size[1];
      emxEnsureCapacity((emxArray__common *)r0, i0, (int)sizeof(double));
      loop_ub = r2->size[0] * r2->size[1];
      for (i0 = 0; i0 < loop_ub; i0++) {
        r0->data[i0] = r2->data[i0];
      }

      i0 = Ans->size[0] * Ans->size[1];
      emxEnsureCapacity((emxArray__common *)Ans, i0, (int)sizeof(double));
      loop_ub = Ans->size[0];
      b_loop_ub = Ans->size[1];
      loop_ub *= b_loop_ub;
      for (i0 = 0; i0 < loop_ub; i0++) {
        Ans->data[i0] += r0->data[i0];
      }

      i++;
    }

    emxFree_real_T(&c_B);
    emxFree_real_T(&c_A);
  } else if (B->size[2] == 1) {
    emxInit_real_T(&b_B, 2);
    B_idx_0 = B->size[0];
    loop_ub = B->size[0];
    b_loop_ub = B->size[1];
    i0 = b_B->size[0] * b_B->size[1];
    b_B->size[0] = loop_ub;
    b_B->size[1] = b_loop_ub;
    emxEnsureCapacity((emxArray__common *)b_B, i0, (int)sizeof(double));
    for (i0 = 0; i0 < b_loop_ub; i0++) {
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_B->data[i1 + b_B->size[0] * i0] = B->data[i1 + B_idx_0 * i0];
      }
    }

    emxInit_real_T(&b_A, 2);
    rot90(b_B, r1);
    loop_ub = A->size[0];
    b_loop_ub = A->size[1];
    i0 = b_A->size[0] * b_A->size[1];
    b_A->size[0] = loop_ub;
    b_A->size[1] = b_loop_ub;
    emxEnsureCapacity((emxArray__common *)b_A, i0, (int)sizeof(double));
    emxFree_real_T(&b_B);
    for (i0 = 0; i0 < b_loop_ub; i0++) {
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_A->data[i1 + b_A->size[0] * i0] = A->data[i1 + A->size[0] * i0];
      }
    }

    conv2(b_A, r1, r2);
    i0 = Ans->size[0] * Ans->size[1];
    Ans->size[0] = r2->size[0];
    Ans->size[1] = r2->size[1];
    emxEnsureCapacity((emxArray__common *)Ans, i0, (int)sizeof(double));
    loop_ub = r2->size[0] * r2->size[1];
    emxFree_real_T(&b_A);
    for (i0 = 0; i0 < loop_ub; i0++) {
      Ans->data[i0] = r2->data[i0];
    }

    i = 0;
    emxInit_real_T(&c_A, 2);
    emxInit_real_T(&c_B, 2);
    while (i <= A->size[2] - 2) {
      B_idx_0 = B->size[0];
      loop_ub = B->size[0];
      b_loop_ub = B->size[1];
      i0 = c_B->size[0] * c_B->size[1];
      c_B->size[0] = loop_ub;
      c_B->size[1] = b_loop_ub;
      emxEnsureCapacity((emxArray__common *)c_B, i0, (int)sizeof(double));
      for (i0 = 0; i0 < b_loop_ub; i0++) {
        for (i1 = 0; i1 < loop_ub; i1++) {
          c_B->data[i1 + c_B->size[0] * i0] = B->data[i1 + B_idx_0 * i0];
        }
      }

      rot90(c_B, r1);
      loop_ub = A->size[0];
      b_loop_ub = A->size[1];
      i0 = c_A->size[0] * c_A->size[1];
      c_A->size[0] = loop_ub;
      c_A->size[1] = b_loop_ub;
      emxEnsureCapacity((emxArray__common *)c_A, i0, (int)sizeof(double));
      for (i0 = 0; i0 < b_loop_ub; i0++) {
        for (i1 = 0; i1 < loop_ub; i1++) {
          c_A->data[i1 + c_A->size[0] * i0] = A->data[(i1 + A->size[0] * i0) +
            A->size[0] * A->size[1] * (i + 1)];
        }
      }

      conv2(c_A, r1, r2);
      i0 = r0->size[0] * r0->size[1];
      r0->size[0] = r2->size[0];
      r0->size[1] = r2->size[1];
      emxEnsureCapacity((emxArray__common *)r0, i0, (int)sizeof(double));
      loop_ub = r2->size[0] * r2->size[1];
      for (i0 = 0; i0 < loop_ub; i0++) {
        r0->data[i0] = r2->data[i0];
      }

      i0 = Ans->size[0] * Ans->size[1];
      emxEnsureCapacity((emxArray__common *)Ans, i0, (int)sizeof(double));
      loop_ub = Ans->size[0];
      b_loop_ub = Ans->size[1];
      loop_ub *= b_loop_ub;
      for (i0 = 0; i0 < loop_ub; i0++) {
        Ans->data[i0] += r0->data[i0];
      }

      i++;
    }

    emxFree_real_T(&c_B);
    emxFree_real_T(&c_A);
  } else {
    emxInit_real_T(&b_B, 2);

    /*          if(size(A,3)==1) */
    /*              Ans = getxcorr2(B,A); */
    /*          else */
    loop_ub = B->size[0];
    b_loop_ub = B->size[1];
    i0 = b_B->size[0] * b_B->size[1];
    b_B->size[0] = loop_ub;
    b_B->size[1] = b_loop_ub;
    emxEnsureCapacity((emxArray__common *)b_B, i0, (int)sizeof(double));
    for (i0 = 0; i0 < b_loop_ub; i0++) {
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_B->data[i1 + b_B->size[0] * i0] = B->data[i1 + B->size[0] * i0];
      }
    }

    emxInit_real_T(&b_A, 2);
    rot90(b_B, r1);
    loop_ub = A->size[0];
    b_loop_ub = A->size[1];
    i0 = b_A->size[0] * b_A->size[1];
    b_A->size[0] = loop_ub;
    b_A->size[1] = b_loop_ub;
    emxEnsureCapacity((emxArray__common *)b_A, i0, (int)sizeof(double));
    emxFree_real_T(&b_B);
    for (i0 = 0; i0 < b_loop_ub; i0++) {
      for (i1 = 0; i1 < loop_ub; i1++) {
        b_A->data[i1 + b_A->size[0] * i0] = A->data[i1 + A->size[0] * i0];
      }
    }

    conv2(b_A, r1, r2);
    i0 = Ans->size[0] * Ans->size[1];
    Ans->size[0] = r2->size[0];
    Ans->size[1] = r2->size[1];
    emxEnsureCapacity((emxArray__common *)Ans, i0, (int)sizeof(double));
    loop_ub = r2->size[0] * r2->size[1];
    emxFree_real_T(&b_A);
    for (i0 = 0; i0 < loop_ub; i0++) {
      Ans->data[i0] = r2->data[i0];
    }

    /*          end */
  }

  emxFree_real_T(&r2);
  emxFree_real_T(&r1);
  emxFree_real_T(&r0);
}

/*
 * File trailer for getxcorr2.c
 *
 * [EOF]
 */
