/*
 * File: synthesize.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 28-Mar-2016 13:59:42
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "getxcorr2.h"
#include "synthesize.h"
#include "synthesize_emxutil.h"
#include "sum.h"
#include "power.h"
#include "rand.h"
#include "ceil.h"

/* Function Declarations */
static double rt_roundd_snf(double u);

/* Function Definitions */

/*
 * Arguments    : double u
 * Return Type  : double
 */
static double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/*
 * Matlab code to do Image Quilting as presented in the SIGGRAPH 2002 paper by Efros & Freeman.
 *
 *  Note: this isn't Efros & Freeman's code, just my implementation of it.
 *
 *  Texture Synthesize
 *      IMOUT = SYNTHESIZE(IMGIN , SIZEOUT, TILESIZE, OVERLAP [, ISDEBUG])
 *                       returns an image that is Texture Synthesized
 *
 *      IMGIN
 *            the code both works on grascale images or color images
 *
 *      SIZEOUT
 *            An 1*2 array , the size of output image
 *            e.g.   size(texture)*3
 *
 *      TILESIZE
 *            TILESIZE of each block
 *
 *      OVERLAP
 *            size of overlap bar between blocks
 *
 *      ISDEBUG
 *            equals 0 (default) if no debug function
 *            the algorithm will shows progress of each step, a little more
 *            time will be cost in plotting.
 *
 *        A little confuse I meet with when the block overlaped with two
 *       block, I solved it with a simple way.
 *        licheng09@mails.tsinghua.edu.cn
 * Arguments    : const emxArray_int32_T *imin
 *                const int sizeout[3]
 *                int tilesize
 *                int overlap
 *                int isdebug
 *                emxArray_real_T *imout
 * Return Type  : void
 */
void synthesize(const emxArray_int32_T *imin, const int sizeout[3], int tilesize,
                int overlap, int isdebug, emxArray_real_T *imout)
{
  emxArray_real_T *b_imin;
  int i2;
  int loop_ub;
  int iv0[3];
  short sizein[2];
  emxArray_real_T *r3;
  emxArray_real_T *r4;
  emxArray_real_T *errtop;
  emxArray_real_T *r5;
  emxArray_real_T *errside;
  emxArray_real_T *r6;
  long i3;
  int ii;
  emxArray_real_T *errsidesmall;
  int i4;
  int i;
  emxArray_real_T *shared;
  emxArray_real_T *err;
  emxArray_real_T *errmat;
  emxArray_real_T *fph;
  emxArray_real_T *pathh;
  emxArray_int32_T *b_index;
  emxArray_real_T *path;
  emxArray_real_T *allerr;
  emxArray_real_T *ibest;
  emxArray_real_T *jbest;
  emxArray_boolean_T *x;
  emxArray_int32_T *b_ii;
  emxArray_int32_T *jj;
  emxArray_real_T *indx;
  emxArray_real_T *extremum;
  emxArray_real_T *b_imout;
  emxArray_real_T *c_imout;
  emxArray_real_T *d_imout;
  emxArray_real_T *e_imout;
  emxArray_real_T *b_err;
  emxArray_int32_T *c_index;
  emxArray_int32_T *d_index;
  emxArray_int32_T *e_index;
  emxArray_real_T *c_err;
  emxArray_int32_T *f_index;
  emxArray_int32_T *g_index;
  emxArray_int32_T *h_index;
  emxArray_real_T *d_err;
  emxArray_int32_T *i_index;
  emxArray_int32_T *j_index;
  emxArray_int32_T *k_index;
  emxArray_int32_T *l_index;
  emxArray_int32_T *m_index;
  emxArray_int32_T *n_index;
  int i5;
  int i6;
  int j;
  int i7;
  int i8;
  int i9;
  int ix;
  int ixstart;
  int b_loop_ub;
  int b_ix;
  int b_jj;
  int idx;
  int iv1[1];
  emxArray_real_T b_shared;
  double c;
  int iv2[1];
  boolean_T exitg14;
  int nx;
  boolean_T exitg13;
  boolean_T guard3 = false;
  double pos[2];
  int itmp;
  boolean_T exitg12;
  boolean_T exitg11;
  short outsz[2];
  short b_outsz;
  boolean_T exitg10;
  boolean_T exitg9;
  double min_err_bound_data[1000];
  double min_err_boundh_data[1000];
  double tmp_data[3000];
  double b_tmp_data[3000];
  double c_tmp_data[3];
  int iv3[1];
  boolean_T exitg8;
  boolean_T exitg7;
  boolean_T guard2 = false;
  boolean_T exitg6;
  boolean_T exitg5;
  int iv4[1];
  boolean_T exitg4;
  boolean_T exitg3;
  boolean_T guard1 = false;
  boolean_T exitg2;
  boolean_T exitg1;
  (void)isdebug;
  b_emxInit_real_T(&b_imin, 3);
  i2 = b_imin->size[0] * b_imin->size[1] * b_imin->size[2];
  b_imin->size[0] = imin->size[0];
  b_imin->size[1] = imin->size[1];
  b_imin->size[2] = imin->size[2];
  emxEnsureCapacity((emxArray__common *)b_imin, i2, (int)sizeof(double));
  loop_ub = imin->size[0] * imin->size[1] * imin->size[2];
  for (i2 = 0; i2 < loop_ub; i2++) {
    b_imin->data[i2] = imin->data[i2];
  }

  if (b_imin->size[2] == 1) {
    i2 = imout->size[0] * imout->size[1] * imout->size[2];
    imout->size[0] = sizeout[0];
    emxEnsureCapacity((emxArray__common *)imout, i2, (int)sizeof(double));
    i2 = imout->size[0] * imout->size[1] * imout->size[2];
    imout->size[1] = sizeout[1];
    emxEnsureCapacity((emxArray__common *)imout, i2, (int)sizeof(double));
    i2 = imout->size[0] * imout->size[1] * imout->size[2];
    imout->size[2] = sizeout[2];
    emxEnsureCapacity((emxArray__common *)imout, i2, (int)sizeof(double));
    loop_ub = sizeout[0] * sizeout[1] * sizeout[2];
    for (i2 = 0; i2 < loop_ub; i2++) {
      imout->data[i2] = 0.0;
    }
  } else {
    for (i2 = 0; i2 < 2; i2++) {
      iv0[i2] = sizeout[i2];
    }

    iv0[2] = b_imin->size[2];
    i2 = imout->size[0] * imout->size[1] * imout->size[2];
    imout->size[0] = iv0[0];
    emxEnsureCapacity((emxArray__common *)imout, i2, (int)sizeof(double));
    i2 = imout->size[0] * imout->size[1] * imout->size[2];
    imout->size[1] = iv0[1];
    emxEnsureCapacity((emxArray__common *)imout, i2, (int)sizeof(double));
    i2 = imout->size[0] * imout->size[1] * imout->size[2];
    imout->size[2] = iv0[2];
    emxEnsureCapacity((emxArray__common *)imout, i2, (int)sizeof(double));
    loop_ub = iv0[0] * iv0[1] * iv0[2];
    for (i2 = 0; i2 < loop_ub; i2++) {
      imout->data[i2] = 0.0;
    }
  }

  loop_ub = imout->size[2];
  for (i2 = 0; i2 < loop_ub; i2++) {
    imout->data[imout->size[0] * imout->size[1] * i2] = 255.0;
  }

  for (i2 = 0; i2 < 2; i2++) {
    sizein[i2] = (short)b_imin->size[i2];
  }

  b_emxInit_real_T(&r3, 3);
  emxInit_real_T(&r4, 2);
  power(b_imin, r3);
  i2 = r4->size[0] * r4->size[1];
  r4->size[0] = overlap;
  emxEnsureCapacity((emxArray__common *)r4, i2, (int)sizeof(double));
  i2 = r4->size[0] * r4->size[1];
  r4->size[1] = tilesize;
  emxEnsureCapacity((emxArray__common *)r4, i2, (int)sizeof(double));
  loop_ub = overlap * tilesize;
  for (i2 = 0; i2 < loop_ub; i2++) {
    r4->data[i2] = 1.0;
  }

  emxInit_real_T(&errtop, 2);
  emxInit_real_T(&r5, 2);
  b_getxcorr2(r3, r4, errtop);
  power(b_imin, r3);
  i2 = r5->size[0] * r5->size[1];
  r5->size[0] = tilesize;
  emxEnsureCapacity((emxArray__common *)r5, i2, (int)sizeof(double));
  i2 = r5->size[0] * r5->size[1];
  r5->size[1] = overlap;
  emxEnsureCapacity((emxArray__common *)r5, i2, (int)sizeof(double));
  loop_ub = tilesize * overlap;
  emxFree_real_T(&r4);
  for (i2 = 0; i2 < loop_ub; i2++) {
    r5->data[i2] = 1.0;
  }

  emxInit_real_T(&errside, 2);
  emxInit_real_T(&r6, 2);
  b_getxcorr2(r3, r5, errside);
  i3 = (long)tilesize - overlap;
  if (i3 > 2147483647L) {
    i3 = 2147483647L;
  } else {
    if (i3 < -2147483648L) {
      i3 = -2147483648L;
    }
  }

  ii = (int)i3;
  power(b_imin, r3);
  i2 = r6->size[0] * r6->size[1];
  r6->size[0] = ii;
  emxEnsureCapacity((emxArray__common *)r6, i2, (int)sizeof(double));
  i2 = r6->size[0] * r6->size[1];
  r6->size[1] = overlap;
  emxEnsureCapacity((emxArray__common *)r6, i2, (int)sizeof(double));
  loop_ub = ii * overlap;
  emxFree_real_T(&r5);
  for (i2 = 0; i2 < loop_ub; i2++) {
    r6->data[i2] = 1.0;
  }

  emxInit_real_T(&errsidesmall, 2);
  b_getxcorr2(r3, r6, errsidesmall);

  /* B1overlap = zeros(overlap,tilesize); */
  /* B2overlap = zeros(overlap,tilesize); */
  i3 = (long)tilesize - overlap;
  if (i3 > 2147483647L) {
    i3 = 2147483647L;
  } else {
    if (i3 < -2147483648L) {
      i3 = -2147483648L;
    }
  }

  i2 = (int)i3;
  i3 = (long)sizeout[0] - tilesize;
  if (i3 > 2147483647L) {
    i3 = 2147483647L;
  } else {
    if (i3 < -2147483648L) {
      i3 = -2147483648L;
    }
  }

  i3 = (int)i3 + 1L;
  if (i3 > 2147483647L) {
    i3 = 2147483647L;
  } else {
    if (i3 < -2147483648L) {
      i3 = -2147483648L;
    }
  }

  i4 = (int)i3;
  i = 1;
  emxFree_real_T(&r6);
  b_emxInit_real_T(&shared, 3);
  emxInit_real_T(&err, 2);
  emxInit_real_T(&errmat, 2);
  emxInit_real_T(&fph, 2);
  emxInit_real_T(&pathh, 2);
  emxInit_int32_T(&b_index, 2);
  emxInit_real_T(&path, 2);
  emxInit_real_T(&allerr, 2);
  c_emxInit_real_T(&ibest, 1);
  c_emxInit_real_T(&jbest, 1);
  emxInit_boolean_T(&x, 2);
  b_emxInit_int32_T(&b_ii, 1);
  b_emxInit_int32_T(&jj, 1);
  emxInit_real_T(&indx, 2);
  emxInit_real_T(&extremum, 2);
  b_emxInit_real_T(&b_imout, 3);
  b_emxInit_real_T(&c_imout, 3);
  b_emxInit_real_T(&d_imout, 3);
  b_emxInit_real_T(&e_imout, 3);
  emxInit_real_T(&b_err, 2);
  b_emxInit_int32_T(&c_index, 1);
  b_emxInit_int32_T(&d_index, 1);
  b_emxInit_int32_T(&e_index, 1);
  emxInit_real_T(&c_err, 2);
  b_emxInit_int32_T(&f_index, 1);
  b_emxInit_int32_T(&g_index, 1);
  b_emxInit_int32_T(&h_index, 1);
  emxInit_real_T(&d_err, 2);
  b_emxInit_int32_T(&i_index, 1);
  b_emxInit_int32_T(&j_index, 1);
  b_emxInit_int32_T(&k_index, 1);
  b_emxInit_int32_T(&l_index, 1);
  b_emxInit_int32_T(&m_index, 1);
  b_emxInit_int32_T(&n_index, 1);
  while (((i2 > 0) && (i <= i4)) || ((i2 < 0) && (i >= i4))) {
    i3 = (long)tilesize - overlap;
    if (i3 > 2147483647L) {
      i3 = 2147483647L;
    } else {
      if (i3 < -2147483648L) {
        i3 = -2147483648L;
      }
    }

    i5 = (int)i3;
    i3 = (long)sizeout[1] - tilesize;
    if (i3 > 2147483647L) {
      i3 = 2147483647L;
    } else {
      if (i3 < -2147483648L) {
        i3 = -2147483648L;
      }
    }

    i3 = (int)i3 + 1L;
    if (i3 > 2147483647L) {
      i3 = 2147483647L;
    } else {
      if (i3 < -2147483648L) {
        i3 = -2147483648L;
      }
    }

    i6 = (int)i3;
    j = 1;
    while (((i5 > 0) && (j <= i6)) || ((i5 < 0) && (j >= i6))) {
      if ((i > 1) && (j > 1)) {
        /*  extract top shared region */
        i3 = (long)i + overlap;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i7 = (int)i3 - 1;
        if (i > i7) {
          i8 = 1;
          i7 = 1;
        } else {
          i8 = i;
          i7++;
        }

        i3 = (long)j + tilesize;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i9 = (int)i3 - 1;
        if (j > i9) {
          ix = 1;
          i9 = 1;
        } else {
          ix = j;
          i9++;
        }

        loop_ub = imout->size[2];
        ixstart = shared->size[0] * shared->size[1] * shared->size[2];
        shared->size[0] = i7 - i8;
        shared->size[1] = i9 - ix;
        shared->size[2] = loop_ub;
        emxEnsureCapacity((emxArray__common *)shared, ixstart, (int)sizeof
                          (double));
        for (ixstart = 0; ixstart < loop_ub; ixstart++) {
          b_loop_ub = i9 - ix;
          for (b_ix = 0; b_ix < b_loop_ub; b_ix++) {
            b_jj = i7 - i8;
            for (idx = 0; idx < b_jj; idx++) {
              shared->data[(idx + shared->size[0] * b_ix) + shared->size[0] *
                shared->size[1] * ixstart] = imout->data[(((i8 + idx) +
                imout->size[0] * ((ix + b_ix) - 1)) + imout->size[0] *
                imout->size[1] * ixstart) - 1];
            }
          }
        }

        c_getxcorr2(b_imin, shared, err);
        ixstart = imout->size[2];
        iv1[0] = (i7 - i8) * (i9 - ix) * ixstart;
        b_shared = *shared;
        b_shared.size = (int *)&iv1;
        b_shared.numDimensions = 1;
        b_power(&b_shared, ibest);
        i7 = err->size[0] * err->size[1];
        err->size[0] = errtop->size[0];
        err->size[1] = errtop->size[1];
        emxEnsureCapacity((emxArray__common *)err, i7, (int)sizeof(double));
        c = sum(ibest);
        loop_ub = errtop->size[0] * errtop->size[1];
        for (i7 = 0; i7 < loop_ub; i7++) {
          err->data[i7] = (errtop->data[i7] - 2.0 * err->data[i7]) + c;
        }

        /*  trim invalid data at edges, and off bottom where we don't want */
        /*  tiles to go over the edge */
        c = (double)err->size[0] - (double)tilesize;
        if (c < 2.147483648E+9) {
          if (c >= -2.147483648E+9) {
            i7 = (int)c;
          } else {
            i7 = MIN_int32_T;
          }
        } else {
          i7 = MAX_int32_T;
        }

        i3 = i7 + 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i7 = (int)i3;
        if (overlap > i7) {
          i8 = 0;
          i7 = 0;
        } else {
          i8 = overlap - 1;
        }

        c = (double)err->size[1] - (double)tilesize;
        if (c < 2.147483648E+9) {
          if (c >= -2.147483648E+9) {
            i9 = (int)c;
          } else {
            i9 = MIN_int32_T;
          }
        } else {
          i9 = MAX_int32_T;
        }

        i3 = i9 + 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i9 = (int)i3;
        if (tilesize > i9) {
          ix = 0;
          i9 = 0;
        } else {
          ix = tilesize - 1;
        }

        ixstart = d_err->size[0] * d_err->size[1];
        d_err->size[0] = i7 - i8;
        d_err->size[1] = i9 - ix;
        emxEnsureCapacity((emxArray__common *)d_err, ixstart, (int)sizeof(double));
        loop_ub = i9 - ix;
        for (i9 = 0; i9 < loop_ub; i9++) {
          b_loop_ub = i7 - i8;
          for (ixstart = 0; ixstart < b_loop_ub; ixstart++) {
            d_err->data[ixstart + d_err->size[0] * i9] = err->data[(i8 + ixstart)
              + err->size[0] * (ix + i9)];
          }
        }

        i7 = err->size[0] * err->size[1];
        err->size[0] = d_err->size[0];
        err->size[1] = d_err->size[1];
        emxEnsureCapacity((emxArray__common *)err, i7, (int)sizeof(double));
        loop_ub = d_err->size[1];
        for (i7 = 0; i7 < loop_ub; i7++) {
          b_loop_ub = d_err->size[0];
          for (i8 = 0; i8 < b_loop_ub; i8++) {
            err->data[i8 + err->size[0] * i7] = d_err->data[i8 + d_err->size[0] *
              i7];
          }
        }

        /*  extract left shared region, skipping bit already checked */
        i3 = (long)i + overlap;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i7 = (int)i3;
        i3 = (long)i + tilesize;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i8 = (int)i3 - 1;
        if (i7 > i8) {
          i7 = 1;
          i8 = 1;
        } else {
          i8++;
        }

        i3 = (long)j + overlap;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i9 = (int)i3 - 1;
        if (j > i9) {
          ix = 1;
          i9 = 1;
        } else {
          ix = j;
          i9++;
        }

        loop_ub = imout->size[2];
        ixstart = shared->size[0] * shared->size[1] * shared->size[2];
        shared->size[0] = i8 - i7;
        shared->size[1] = i9 - ix;
        shared->size[2] = loop_ub;
        emxEnsureCapacity((emxArray__common *)shared, ixstart, (int)sizeof
                          (double));
        for (ixstart = 0; ixstart < loop_ub; ixstart++) {
          b_loop_ub = i9 - ix;
          for (b_ix = 0; b_ix < b_loop_ub; b_ix++) {
            b_jj = i8 - i7;
            for (idx = 0; idx < b_jj; idx++) {
              shared->data[(idx + shared->size[0] * b_ix) + shared->size[0] *
                shared->size[1] * ixstart] = imout->data[(((i7 + idx) +
                imout->size[0] * ((ix + b_ix) - 1)) + imout->size[0] *
                imout->size[1] * ixstart) - 1];
            }
          }
        }

        c_getxcorr2(b_imin, shared, path);
        ixstart = imout->size[2];
        iv2[0] = (i8 - i7) * (i9 - ix) * ixstart;
        b_shared = *shared;
        b_shared.size = (int *)&iv2;
        b_shared.numDimensions = 1;
        b_power(&b_shared, ibest);
        i7 = path->size[0] * path->size[1];
        path->size[0] = errsidesmall->size[0];
        path->size[1] = errsidesmall->size[1];
        emxEnsureCapacity((emxArray__common *)path, i7, (int)sizeof(double));
        c = sum(ibest);
        loop_ub = errsidesmall->size[0] * errsidesmall->size[1];
        for (i7 = 0; i7 < loop_ub; i7++) {
          path->data[i7] = (errsidesmall->data[i7] - 2.0 * path->data[i7]) + c;
        }

        /*  sum(shared(:).^2); trim invalid data at edges, and where we */
        /*  don't want tiles to go over the edges */
        c = (double)path->size[0] - (double)tilesize;
        if (c < 2.147483648E+9) {
          if (c >= -2.147483648E+9) {
            i7 = (int)c;
          } else {
            i7 = MIN_int32_T;
          }
        } else {
          i7 = MAX_int32_T;
        }

        i3 = (long)i7 + overlap;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i3 = (int)i3 + 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i7 = (int)i3;
        if (tilesize > i7) {
          i7 = 0;
        } else {
          i7 = tilesize - 1;
        }

        c = (double)path->size[1] - (double)tilesize;
        if (c < 2.147483648E+9) {
          if (c >= -2.147483648E+9) {
            i8 = (int)c;
          } else {
            i8 = MIN_int32_T;
          }
        } else {
          i8 = MAX_int32_T;
        }

        i3 = i8 + 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i8 = (int)i3;
        if (overlap > i8) {
          i8 = 0;
        } else {
          i8 = overlap - 1;
        }

        i9 = err->size[0] * err->size[1];
        emxEnsureCapacity((emxArray__common *)err, i9, (int)sizeof(double));
        loop_ub = err->size[1];
        for (i9 = 0; i9 < loop_ub; i9++) {
          b_loop_ub = err->size[0];
          for (ix = 0; ix < b_loop_ub; ix++) {
            err->data[ix + err->size[0] * i9] += path->data[(i7 + ix) +
              path->size[0] * (i8 + i9)];
          }
        }

        ixstart = 1;
        b_jj = err->size[0] * err->size[1];
        c = err->data[0];
        ii = err->size[0] * err->size[1];
        if (ii > 1) {
          if (rtIsNaN(err->data[0])) {
            ix = 2;
            exitg14 = false;
            while ((!exitg14) && (ix <= b_jj)) {
              ixstart = ix;
              if (!rtIsNaN(err->data[ix - 1])) {
                c = err->data[ix - 1];
                exitg14 = true;
              } else {
                ix++;
              }
            }
          }

          ii = err->size[0] * err->size[1];
          if (ixstart < ii) {
            while (ixstart + 1 <= b_jj) {
              if (err->data[ixstart] < c) {
                c = err->data[ixstart];
              }

              ixstart++;
            }
          }
        }

        i7 = x->size[0] * x->size[1];
        x->size[0] = err->size[0];
        x->size[1] = err->size[1];
        emxEnsureCapacity((emxArray__common *)x, i7, (int)sizeof(boolean_T));
        c *= 1.1110000000000002;
        loop_ub = err->size[0] * err->size[1];
        for (i7 = 0; i7 < loop_ub; i7++) {
          x->data[i7] = (err->data[i7] <= c);
        }

        nx = x->size[0] * x->size[1];
        idx = 0;
        i7 = b_ii->size[0];
        b_ii->size[0] = nx;
        emxEnsureCapacity((emxArray__common *)b_ii, i7, (int)sizeof(int));
        i7 = jj->size[0];
        jj->size[0] = nx;
        emxEnsureCapacity((emxArray__common *)jj, i7, (int)sizeof(int));
        if (nx == 0) {
          i7 = b_ii->size[0];
          b_ii->size[0] = 0;
          emxEnsureCapacity((emxArray__common *)b_ii, i7, (int)sizeof(int));
          i7 = jj->size[0];
          jj->size[0] = 0;
          emxEnsureCapacity((emxArray__common *)jj, i7, (int)sizeof(int));
        } else {
          ii = 1;
          b_jj = 1;
          exitg13 = false;
          while ((!exitg13) && (b_jj <= x->size[1])) {
            guard3 = false;
            if (x->data[(ii + x->size[0] * (b_jj - 1)) - 1]) {
              idx++;
              b_ii->data[idx - 1] = ii;
              jj->data[idx - 1] = b_jj;
              if (idx >= nx) {
                exitg13 = true;
              } else {
                guard3 = true;
              }
            } else {
              guard3 = true;
            }

            if (guard3) {
              ii++;
              if (ii > x->size[0]) {
                ii = 1;
                b_jj++;
              }
            }
          }

          if (nx == 1) {
            if (idx == 0) {
              i7 = b_ii->size[0];
              b_ii->size[0] = 0;
              emxEnsureCapacity((emxArray__common *)b_ii, i7, (int)sizeof(int));
              i7 = jj->size[0];
              jj->size[0] = 0;
              emxEnsureCapacity((emxArray__common *)jj, i7, (int)sizeof(int));
            }
          } else {
            i7 = b_ii->size[0];
            if (1 > idx) {
              b_ii->size[0] = 0;
            } else {
              b_ii->size[0] = idx;
            }

            emxEnsureCapacity((emxArray__common *)b_ii, i7, (int)sizeof(int));
            i7 = jj->size[0];
            if (1 > idx) {
              jj->size[0] = 0;
            } else {
              jj->size[0] = idx;
            }

            emxEnsureCapacity((emxArray__common *)jj, i7, (int)sizeof(int));
          }
        }

        i7 = ibest->size[0];
        ibest->size[0] = b_ii->size[0];
        emxEnsureCapacity((emxArray__common *)ibest, i7, (int)sizeof(double));
        loop_ub = b_ii->size[0];
        for (i7 = 0; i7 < loop_ub; i7++) {
          ibest->data[i7] = b_ii->data[i7];
        }

        i7 = jbest->size[0];
        jbest->size[0] = jj->size[0];
        emxEnsureCapacity((emxArray__common *)jbest, i7, (int)sizeof(double));
        loop_ub = jj->size[0];
        for (i7 = 0; i7 < loop_ub; i7++) {
          jbest->data[i7] = jj->data[i7];
        }

        c = b_rand() * (double)ibest->size[0];
        c = ceil(c);
        pos[0] = ibest->data[(int)c - 1];
        pos[1] = jbest->data[(int)c - 1];
        i3 = (long)i + overlap;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i7 = (int)i3 - 1;
        if (i > i7) {
          i8 = 0;
          i7 = 0;
        } else {
          i8 = i - 1;
        }

        i3 = (long)j + tilesize;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i9 = (int)i3 - 1;
        if (j > i9) {
          ix = 0;
          i9 = 0;
        } else {
          ix = j - 1;
        }

        /*  shared */
        c = rt_roundd_snf(pos[0] + (double)overlap);
        if (c < 2.147483648E+9) {
          if (c >= -2.147483648E+9) {
            ixstart = (int)c;
          } else {
            ixstart = MIN_int32_T;
          }
        } else if (c >= 2.147483648E+9) {
          ixstart = MAX_int32_T;
        } else {
          ixstart = 0;
        }

        i3 = ixstart - 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        if ((int)pos[0] > (int)i3) {
          ixstart = 0;
        } else {
          ixstart = (int)pos[0] - 1;
        }

        c = rt_roundd_snf(pos[1] + (double)tilesize);
        if (c < 2.147483648E+9) {
          if (c >= -2.147483648E+9) {
            b_ix = (int)c;
          } else {
            b_ix = MIN_int32_T;
          }
        } else if (c >= 2.147483648E+9) {
          b_ix = MAX_int32_T;
        } else {
          b_ix = 0;
        }

        i3 = b_ix - 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        if ((int)pos[1] > (int)i3) {
          b_ix = 0;
        } else {
          b_ix = (int)pos[1] - 1;
        }

        loop_ub = imout->size[2];
        idx = e_imout->size[0] * e_imout->size[1] * e_imout->size[2];
        e_imout->size[0] = i7 - i8;
        e_imout->size[1] = i9 - ix;
        e_imout->size[2] = loop_ub;
        emxEnsureCapacity((emxArray__common *)e_imout, idx, (int)sizeof(double));
        for (idx = 0; idx < loop_ub; idx++) {
          b_loop_ub = i9 - ix;
          for (ii = 0; ii < b_loop_ub; ii++) {
            b_jj = i7 - i8;
            for (nx = 0; nx < b_jj; nx++) {
              e_imout->data[(nx + e_imout->size[0] * ii) + e_imout->size[0] *
                e_imout->size[1] * idx] = imout->data[((i8 + nx) + imout->size[0]
                * (ix + ii)) + imout->size[0] * imout->size[1] * idx] -
                b_imin->data[((ixstart + nx) + b_imin->size[0] * (b_ix + ii)) +
                b_imin->size[0] * b_imin->size[1] * idx];
            }
          }
        }

        power(e_imout, r3);
        b_sum(r3, errmat);
        i7 = fph->size[0] * fph->size[1];
        fph->size[0] = overlap;
        fph->size[1] = tilesize;
        emxEnsureCapacity((emxArray__common *)fph, i7, (int)sizeof(double));
        loop_ub = overlap * tilesize;
        for (i7 = 0; i7 < loop_ub; i7++) {
          fph->data[i7] = 0.0;
        }

        i7 = pathh->size[0] * pathh->size[1];
        pathh->size[0] = overlap;
        pathh->size[1] = tilesize;
        emxEnsureCapacity((emxArray__common *)pathh, i7, (int)sizeof(double));
        loop_ub = overlap * tilesize;
        for (i7 = 0; i7 < loop_ub; i7++) {
          pathh->data[i7] = 0.0;
        }

        loop_ub = errmat->size[0] - 1;
        for (i7 = 0; i7 <= loop_ub; i7++) {
          fph->data[i7 + fph->size[0] * (tilesize - 1)] = errmat->data[i7 +
            errmat->size[0] * (tilesize - 1)];
        }

        for (idx = tilesize - 1; idx > 0; idx--) {
          for (nx = 0; nx + 1 <= overlap; nx++) {
            if (1 < nx) {
              b_jj = nx;
            } else {
              b_jj = 1;
            }

            ii = nx + 2;
            if (overlap <= ii) {
              ii = overlap;
            }

            if (ii < b_jj) {
              b_loop_ub = 0;
            } else {
              b_loop_ub = (ii - b_jj) + 1;
            }

            i7 = b_index->size[0] * b_index->size[1];
            b_index->size[0] = 1;
            b_index->size[1] = b_loop_ub;
            emxEnsureCapacity((emxArray__common *)b_index, i7, (int)sizeof(int));
            if (b_loop_ub > 0) {
              b_index->data[0] = b_jj;
              for (ii = 2; ii <= b_loop_ub; ii++) {
                b_jj++;
                b_index->data[ii - 1] = b_jj;
              }
            }

            ixstart = 1;
            i7 = l_index->size[0];
            l_index->size[0] = b_index->size[1];
            emxEnsureCapacity((emxArray__common *)l_index, i7, (int)sizeof(int));
            loop_ub = b_index->size[1];
            for (i7 = 0; i7 < loop_ub; i7++) {
              l_index->data[i7] = b_index->data[b_index->size[0] * i7];
            }

            b_loop_ub = l_index->size[0];
            c = fph->data[(b_index->data[0] + fph->size[0] * idx) - 1];
            itmp = 0;
            i7 = m_index->size[0];
            m_index->size[0] = b_index->size[1];
            emxEnsureCapacity((emxArray__common *)m_index, i7, (int)sizeof(int));
            loop_ub = b_index->size[1];
            for (i7 = 0; i7 < loop_ub; i7++) {
              m_index->data[i7] = b_index->data[b_index->size[0] * i7];
            }

            if (m_index->size[0] > 1) {
              if (rtIsNaN(c)) {
                ix = 2;
                exitg12 = false;
                while ((!exitg12) && (ix <= b_loop_ub)) {
                  ixstart = ix;
                  if (!rtIsNaN(fph->data[(b_index->data[b_index->size[0] * (ix -
                         1)] + fph->size[0] * idx) - 1])) {
                    c = fph->data[(b_index->data[b_index->size[0] * (ix - 1)] +
                                   fph->size[0] * idx) - 1];
                    itmp = ix - 1;
                    exitg12 = true;
                  } else {
                    ix++;
                  }
                }
              }

              i7 = n_index->size[0];
              n_index->size[0] = b_index->size[1];
              emxEnsureCapacity((emxArray__common *)n_index, i7, (int)sizeof(int));
              loop_ub = b_index->size[1];
              for (i7 = 0; i7 < loop_ub; i7++) {
                n_index->data[i7] = b_index->data[b_index->size[0] * i7];
              }

              if (ixstart < n_index->size[0]) {
                while (ixstart + 1 <= b_loop_ub) {
                  if (fph->data[(b_index->data[b_index->size[0] * ixstart] +
                                 fph->size[0] * idx) - 1] < c) {
                    c = fph->data[(b_index->data[b_index->size[0] * ixstart] +
                                   fph->size[0] * idx) - 1];
                    itmp = ixstart;
                  }

                  ixstart++;
                }
              }
            }

            fph->data[nx + fph->size[0] * (idx - 1)] = c;
            fph->data[nx + fph->size[0] * (idx - 1)] += errmat->data[nx +
              errmat->size[0] * (idx - 1)];
            pathh->data[nx + pathh->size[0] * (idx - 1)] = b_index->data[itmp];
          }
        }

        i3 = (long)i + tilesize;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i7 = (int)i3 - 1;
        if (i > i7) {
          i8 = 0;
          i7 = 0;
        } else {
          i8 = i - 1;
        }

        i3 = (long)j + overlap;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i9 = (int)i3 - 1;
        if (j > i9) {
          ix = 0;
          i9 = 0;
        } else {
          ix = j - 1;
        }

        /*  shared */
        c = rt_roundd_snf(pos[0] + (double)tilesize);
        if (c < 2.147483648E+9) {
          if (c >= -2.147483648E+9) {
            ixstart = (int)c;
          } else {
            ixstart = MIN_int32_T;
          }
        } else if (c >= 2.147483648E+9) {
          ixstart = MAX_int32_T;
        } else {
          ixstart = 0;
        }

        i3 = ixstart - 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        if ((int)pos[0] > (int)i3) {
          ixstart = 0;
        } else {
          ixstart = (int)pos[0] - 1;
        }

        c = rt_roundd_snf(pos[1] + (double)overlap);
        if (c < 2.147483648E+9) {
          if (c >= -2.147483648E+9) {
            b_ix = (int)c;
          } else {
            b_ix = MIN_int32_T;
          }
        } else if (c >= 2.147483648E+9) {
          b_ix = MAX_int32_T;
        } else {
          b_ix = 0;
        }

        i3 = b_ix - 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        if ((int)pos[1] > (int)i3) {
          b_ix = 0;
        } else {
          b_ix = (int)pos[1] - 1;
        }

        loop_ub = imout->size[2];
        idx = d_imout->size[0] * d_imout->size[1] * d_imout->size[2];
        d_imout->size[0] = i7 - i8;
        d_imout->size[1] = i9 - ix;
        d_imout->size[2] = loop_ub;
        emxEnsureCapacity((emxArray__common *)d_imout, idx, (int)sizeof(double));
        for (idx = 0; idx < loop_ub; idx++) {
          b_loop_ub = i9 - ix;
          for (ii = 0; ii < b_loop_ub; ii++) {
            b_jj = i7 - i8;
            for (nx = 0; nx < b_jj; nx++) {
              d_imout->data[(nx + d_imout->size[0] * ii) + d_imout->size[0] *
                d_imout->size[1] * idx] = imout->data[((i8 + nx) + imout->size[0]
                * (ix + ii)) + imout->size[0] * imout->size[1] * idx] -
                b_imin->data[((ixstart + nx) + b_imin->size[0] * (b_ix + ii)) +
                b_imin->size[0] * b_imin->size[1] * idx];
            }
          }
        }

        power(d_imout, r3);
        b_sum(r3, errmat);
        i7 = err->size[0] * err->size[1];
        err->size[0] = tilesize;
        err->size[1] = overlap;
        emxEnsureCapacity((emxArray__common *)err, i7, (int)sizeof(double));
        loop_ub = tilesize * overlap;
        for (i7 = 0; i7 < loop_ub; i7++) {
          err->data[i7] = 0.0;
        }

        i7 = path->size[0] * path->size[1];
        path->size[0] = tilesize;
        path->size[1] = overlap;
        emxEnsureCapacity((emxArray__common *)path, i7, (int)sizeof(double));
        loop_ub = tilesize * overlap;
        for (i7 = 0; i7 < loop_ub; i7++) {
          path->data[i7] = 0.0;
        }

        loop_ub = errmat->size[1] - 1;
        for (i7 = 0; i7 <= loop_ub; i7++) {
          err->data[(tilesize + err->size[0] * i7) - 1] = errmat->data[(tilesize
            + errmat->size[0] * i7) - 1];
        }

        for (idx = tilesize - 1; idx > 0; idx--) {
          for (nx = 0; nx + 1 <= overlap; nx++) {
            if (1 < nx) {
              b_jj = nx;
            } else {
              b_jj = 1;
            }

            ii = nx + 2;
            if (overlap <= ii) {
              ii = overlap;
            }

            if (ii < b_jj) {
              b_loop_ub = 0;
            } else {
              b_loop_ub = (ii - b_jj) + 1;
            }

            i7 = b_index->size[0] * b_index->size[1];
            b_index->size[0] = 1;
            b_index->size[1] = b_loop_ub;
            emxEnsureCapacity((emxArray__common *)b_index, i7, (int)sizeof(int));
            if (b_loop_ub > 0) {
              b_index->data[0] = b_jj;
              for (ii = 2; ii <= b_loop_ub; ii++) {
                b_jj++;
                b_index->data[ii - 1] = b_jj;
              }
            }

            ixstart = 1;
            i7 = i_index->size[0];
            i_index->size[0] = b_index->size[1];
            emxEnsureCapacity((emxArray__common *)i_index, i7, (int)sizeof(int));
            loop_ub = b_index->size[1];
            for (i7 = 0; i7 < loop_ub; i7++) {
              i_index->data[i7] = b_index->data[b_index->size[0] * i7];
            }

            b_loop_ub = i_index->size[0];
            i7 = b_ii->size[0];
            b_ii->size[0] = b_index->size[1];
            emxEnsureCapacity((emxArray__common *)b_ii, i7, (int)sizeof(int));
            loop_ub = b_index->size[1];
            for (i7 = 0; i7 < loop_ub; i7++) {
              b_ii->data[i7] = b_index->data[b_index->size[0] * i7];
            }

            c = err->data[idx + err->size[0] * (b_ii->data[0] - 1)];
            itmp = 1;
            i7 = j_index->size[0];
            j_index->size[0] = b_index->size[1];
            emxEnsureCapacity((emxArray__common *)j_index, i7, (int)sizeof(int));
            loop_ub = b_index->size[1];
            for (i7 = 0; i7 < loop_ub; i7++) {
              j_index->data[i7] = b_index->data[b_index->size[0] * i7];
            }

            if (j_index->size[0] > 1) {
              if (rtIsNaN(c)) {
                ix = 2;
                exitg11 = false;
                while ((!exitg11) && (ix <= b_loop_ub)) {
                  ixstart = ix;
                  i7 = b_ii->size[0];
                  b_ii->size[0] = b_index->size[1];
                  emxEnsureCapacity((emxArray__common *)b_ii, i7, (int)sizeof
                                    (int));
                  loop_ub = b_index->size[1];
                  for (i7 = 0; i7 < loop_ub; i7++) {
                    b_ii->data[i7] = b_index->data[b_index->size[0] * i7];
                  }

                  if (!rtIsNaN(err->data[idx + err->size[0] * (b_ii->data[ix - 1]
                        - 1)])) {
                    i7 = b_ii->size[0];
                    b_ii->size[0] = b_index->size[1];
                    emxEnsureCapacity((emxArray__common *)b_ii, i7, (int)sizeof
                                      (int));
                    loop_ub = b_index->size[1];
                    for (i7 = 0; i7 < loop_ub; i7++) {
                      b_ii->data[i7] = b_index->data[b_index->size[0] * i7];
                    }

                    c = err->data[idx + err->size[0] * (b_ii->data[ix - 1] - 1)];
                    itmp = ix;
                    exitg11 = true;
                  } else {
                    ix++;
                  }
                }
              }

              i7 = k_index->size[0];
              k_index->size[0] = b_index->size[1];
              emxEnsureCapacity((emxArray__common *)k_index, i7, (int)sizeof(int));
              loop_ub = b_index->size[1];
              for (i7 = 0; i7 < loop_ub; i7++) {
                k_index->data[i7] = b_index->data[b_index->size[0] * i7];
              }

              if (ixstart < k_index->size[0]) {
                for (ix = ixstart + 1; ix <= b_loop_ub; ix++) {
                  i7 = b_ii->size[0];
                  b_ii->size[0] = b_index->size[1];
                  emxEnsureCapacity((emxArray__common *)b_ii, i7, (int)sizeof
                                    (int));
                  loop_ub = b_index->size[1];
                  for (i7 = 0; i7 < loop_ub; i7++) {
                    b_ii->data[i7] = b_index->data[b_index->size[0] * i7];
                  }

                  if (err->data[idx + err->size[0] * (b_ii->data[ix - 1] - 1)] <
                      c) {
                    i7 = b_ii->size[0];
                    b_ii->size[0] = b_index->size[1];
                    emxEnsureCapacity((emxArray__common *)b_ii, i7, (int)sizeof
                                      (int));
                    loop_ub = b_index->size[1];
                    for (i7 = 0; i7 < loop_ub; i7++) {
                      b_ii->data[i7] = b_index->data[b_index->size[0] * i7];
                    }

                    c = err->data[idx + err->size[0] * (b_ii->data[ix - 1] - 1)];
                    itmp = ix;
                  }
                }
              }
            }

            err->data[(idx + err->size[0] * nx) - 1] = c;
            err->data[(idx + err->size[0] * nx) - 1] += errmat->data[(idx +
              errmat->size[0] * nx) - 1];
            path->data[(idx + path->size[0] * nx) - 1] = b_index->data[itmp - 1];
          }
        }

        if (1 > overlap) {
          loop_ub = 0;
        } else {
          loop_ub = overlap;
        }

        if (1 > overlap) {
          b_loop_ub = 0;
        } else {
          b_loop_ub = overlap;
        }

        i7 = allerr->size[0] * allerr->size[1];
        allerr->size[0] = loop_ub;
        allerr->size[1] = b_loop_ub;
        emxEnsureCapacity((emxArray__common *)allerr, i7, (int)sizeof(double));
        for (i7 = 0; i7 < b_loop_ub; i7++) {
          for (i8 = 0; i8 < loop_ub; i8++) {
            allerr->data[i8 + allerr->size[0] * i7] = err->data[i8 + err->size[0]
              * i7] + fph->data[i8 + fph->size[0] * i7];
          }
        }

        for (i7 = 0; i7 < 2; i7++) {
          outsz[i7] = (short)allerr->size[i7];
        }

        i7 = extremum->size[0] * extremum->size[1];
        extremum->size[0] = 1;
        extremum->size[1] = outsz[1];
        emxEnsureCapacity((emxArray__common *)extremum, i7, (int)sizeof(double));
        b_outsz = outsz[1];
        i7 = b_index->size[0] * b_index->size[1];
        b_index->size[0] = 1;
        emxEnsureCapacity((emxArray__common *)b_index, i7, (int)sizeof(int));
        i7 = b_index->size[0] * b_index->size[1];
        b_index->size[1] = outsz[1];
        emxEnsureCapacity((emxArray__common *)b_index, i7, (int)sizeof(int));
        loop_ub = b_outsz;
        for (i7 = 0; i7 < loop_ub; i7++) {
          b_index->data[i7] = 1;
        }

        b_loop_ub = allerr->size[0];
        ix = 0;
        ii = -1;
        for (b_jj = 1; b_jj <= allerr->size[1]; b_jj++) {
          ixstart = ix;
          nx = ix + b_loop_ub;
          c = allerr->data[ix];
          itmp = 1;
          if (b_loop_ub > 1) {
            idx = 1;
            if (rtIsNaN(allerr->data[ix])) {
              b_ix = ix + 1;
              exitg10 = false;
              while ((!exitg10) && (b_ix + 1 <= nx)) {
                idx++;
                ixstart = b_ix;
                if (!rtIsNaN(allerr->data[b_ix])) {
                  c = allerr->data[b_ix];
                  itmp = idx;
                  exitg10 = true;
                } else {
                  b_ix++;
                }
              }
            }

            if (ixstart + 1 < nx) {
              for (b_ix = ixstart + 1; b_ix + 1 <= nx; b_ix++) {
                idx++;
                if (allerr->data[b_ix] < c) {
                  c = allerr->data[b_ix];
                  itmp = idx;
                }
              }
            }
          }

          ii++;
          extremum->data[ii] = c;
          b_index->data[ii] = itmp;
          ix += b_loop_ub;
        }

        i7 = indx->size[0] * indx->size[1];
        indx->size[0] = 1;
        indx->size[1] = b_index->size[1];
        emxEnsureCapacity((emxArray__common *)indx, i7, (int)sizeof(double));
        loop_ub = b_index->size[0] * b_index->size[1];
        for (i7 = 0; i7 < loop_ub; i7++) {
          indx->data[i7] = b_index->data[i7];
        }

        ixstart = 1;
        b_loop_ub = extremum->size[1];
        c = extremum->data[0];
        itmp = 0;
        if (extremum->size[1] > 1) {
          if (rtIsNaN(extremum->data[0])) {
            ix = 2;
            exitg9 = false;
            while ((!exitg9) && (ix <= b_loop_ub)) {
              ixstart = ix;
              if (!rtIsNaN(extremum->data[ix - 1])) {
                c = extremum->data[ix - 1];
                itmp = ix - 1;
                exitg9 = true;
              } else {
                ix++;
              }
            }
          }

          if (ixstart < extremum->size[1]) {
            while (ixstart + 1 <= b_loop_ub) {
              if (extremum->data[ixstart] < c) {
                c = extremum->data[ixstart];
                itmp = ixstart;
              }

              ixstart++;
            }
          }
        }

        c = rt_roundd_snf(pos[0] + (double)overlap);
        if (c < 2.147483648E+9) {
          if (c >= -2.147483648E+9) {
            i7 = (int)c;
          } else {
            i7 = MIN_int32_T;
          }
        } else if (c >= 2.147483648E+9) {
          i7 = MAX_int32_T;
        } else {
          i7 = 0;
        }

        c = rt_roundd_snf(pos[0] + (double)tilesize);
        if (c < 2.147483648E+9) {
          if (c >= -2.147483648E+9) {
            i8 = (int)c;
          } else {
            i8 = MIN_int32_T;
          }
        } else if (c >= 2.147483648E+9) {
          i8 = MAX_int32_T;
        } else {
          i8 = 0;
        }

        i3 = i8 - 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i8 = (int)i3;
        if (i7 > i8) {
          i7 = 1;
          i8 = 0;
        }

        c = rt_roundd_snf(pos[1] + (double)overlap);
        if (c < 2.147483648E+9) {
          if (c >= -2.147483648E+9) {
            i9 = (int)c;
          } else {
            i9 = MIN_int32_T;
          }
        } else if (c >= 2.147483648E+9) {
          i9 = MAX_int32_T;
        } else {
          i9 = 0;
        }

        c = rt_roundd_snf(pos[1] + (double)tilesize);
        if (c < 2.147483648E+9) {
          if (c >= -2.147483648E+9) {
            ix = (int)c;
          } else {
            ix = MIN_int32_T;
          }
        } else if (c >= 2.147483648E+9) {
          ix = MAX_int32_T;
        } else {
          ix = 0;
        }

        i3 = ix - 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        ix = (int)i3;
        if (i9 > ix) {
          i9 = 1;
          ix = 0;
        }

        i3 = (long)i + overlap;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        ixstart = (int)i3;
        i3 = (long)i + tilesize;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        if (ixstart > (int)i3 - 1) {
          ixstart = 0;
        } else {
          ixstart--;
        }

        i3 = (long)j + overlap;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        b_ix = (int)i3;
        i3 = (long)j + tilesize;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        if (b_ix > (int)i3 - 1) {
          b_ix = 0;
        } else {
          b_ix--;
        }

        loop_ub = b_imin->size[2] - 1;
        for (idx = 0; idx <= loop_ub; idx++) {
          b_loop_ub = ix - i9;
          for (ii = 0; ii <= b_loop_ub; ii++) {
            b_jj = i8 - i7;
            for (nx = 0; nx <= b_jj; nx++) {
              imout->data[((ixstart + nx) + imout->size[0] * (b_ix + ii)) +
                imout->size[0] * imout->size[1] * idx] = b_imin->data[(((i7 + nx)
                + b_imin->size[0] * ((i9 + ii) - 1)) + b_imin->size[0] *
                b_imin->size[1] * idx) - 1];
            }
          }
        }

        /* imout(i:i+tilesize-1,j:j+tilesize-1) = imin(pos(1):pos(1)+tilesize-1,pos(2):pos(2)+tilesize-1); */
        for (i7 = 0; i7 < tilesize; i7++) {
          min_err_bound_data[i7] = 0.0;
        }

        for (i7 = 0; i7 < tilesize; i7++) {
          min_err_boundh_data[i7] = 0.0;
        }

        min_err_bound_data[(int)indx->data[itmp] - 1] = itmp + 1;
        min_err_boundh_data[itmp] = indx->data[itmp];
        c = rt_roundd_snf(indx->data[itmp] + 1.0);
        if (c < 2.147483648E+9) {
          if (c >= -2.147483648E+9) {
            idx = (int)c;
          } else {
            idx = MIN_int32_T;
          }
        } else if (c >= 2.147483648E+9) {
          idx = MAX_int32_T;
        } else {
          idx = 0;
        }

        while (idx <= tilesize) {
          min_err_bound_data[idx - 1] = path->data[(idx + path->size[0] * ((int)
            min_err_bound_data[idx - 2] - 1)) - 2];
          idx++;
        }

        for (idx = itmp; idx + 2 <= tilesize; idx++) {
          min_err_boundh_data[idx + 1] = pathh->data[((int)
            min_err_boundh_data[idx] + pathh->size[0] * idx) - 1];
        }

        for (idx = overlap; idx <= tilesize; idx++) {
          i7 = (int)(pos[0] + min_err_boundh_data[idx - 1]);
          c = rt_roundd_snf(pos[0] + (double)overlap);
          if (c < 2.147483648E+9) {
            if (c >= -2.147483648E+9) {
              i8 = (int)c;
            } else {
              i8 = MIN_int32_T;
            }
          } else if (c >= 2.147483648E+9) {
            i8 = MAX_int32_T;
          } else {
            i8 = 0;
          }

          i3 = i8 - 1L;
          if (i3 > 2147483647L) {
            i3 = 2147483647L;
          } else {
            if (i3 < -2147483648L) {
              i3 = -2147483648L;
            }
          }

          i8 = (int)i3;
          if (i7 > i8) {
            i7 = 0;
            i8 = 0;
          } else {
            i7--;
          }

          c = rt_roundd_snf((double)i + min_err_boundh_data[idx - 1]);
          if (c < 2.147483648E+9) {
            if (c >= -2.147483648E+9) {
              i9 = (int)c;
            } else {
              i9 = MIN_int32_T;
            }
          } else if (c >= 2.147483648E+9) {
            i9 = MAX_int32_T;
          } else {
            i9 = 0;
          }

          i3 = (long)i + overlap;
          if (i3 > 2147483647L) {
            i3 = 2147483647L;
          } else {
            if (i3 < -2147483648L) {
              i3 = -2147483648L;
            }
          }

          if (i9 > (int)i3 - 1) {
            i9 = 0;
          } else {
            i9--;
          }

          i3 = (long)j + idx;
          if (i3 > 2147483647L) {
            i3 = 2147483647L;
          } else {
            if (i3 < -2147483648L) {
              i3 = -2147483648L;
            }
          }

          ix = (int)i3 - 2;
          loop_ub = b_imin->size[2];
          c = rt_roundd_snf(pos[1] + (double)idx);
          if (c < 2.147483648E+9) {
            if (c >= -2.147483648E+9) {
              ixstart = (int)c;
            } else {
              ixstart = MIN_int32_T;
            }
          } else if (c >= 2.147483648E+9) {
            ixstart = MAX_int32_T;
          } else {
            ixstart = 0;
          }

          i3 = ixstart - 1L;
          if (i3 > 2147483647L) {
            i3 = 2147483647L;
          } else {
            if (i3 < -2147483648L) {
              i3 = -2147483648L;
            }
          }

          b_jj = (int)i3;
          ii = i8 - i7;
          for (ixstart = 0; ixstart < loop_ub; ixstart++) {
            b_loop_ub = i8 - i7;
            for (b_ix = 0; b_ix < b_loop_ub; b_ix++) {
              tmp_data[b_ix + ii * ixstart] = b_imin->data[((i7 + b_ix) +
                b_imin->size[0] * (b_jj - 1)) + b_imin->size[0] * b_imin->size[1]
                * ixstart];
            }
          }

          for (i7 = 0; i7 < loop_ub; i7++) {
            for (i8 = 0; i8 < ii; i8++) {
              imout->data[((i9 + i8) + imout->size[0] * ix) + imout->size[0] *
                imout->size[1] * i7] = tmp_data[i8 + ii * i7];
            }
          }
        }

        for (idx = overlap; idx <= tilesize; idx++) {
          i7 = (int)(pos[1] + min_err_bound_data[idx - 1]);
          c = rt_roundd_snf(pos[1] + (double)overlap);
          if (c < 2.147483648E+9) {
            if (c >= -2.147483648E+9) {
              i8 = (int)c;
            } else {
              i8 = MIN_int32_T;
            }
          } else if (c >= 2.147483648E+9) {
            i8 = MAX_int32_T;
          } else {
            i8 = 0;
          }

          i3 = i8 - 1L;
          if (i3 > 2147483647L) {
            i3 = 2147483647L;
          } else {
            if (i3 < -2147483648L) {
              i3 = -2147483648L;
            }
          }

          i8 = (int)i3;
          if (i7 > i8) {
            i7 = 0;
            i8 = 0;
          } else {
            i7--;
          }

          c = rt_roundd_snf((double)j + min_err_bound_data[idx - 1]);
          if (c < 2.147483648E+9) {
            if (c >= -2.147483648E+9) {
              i9 = (int)c;
            } else {
              i9 = MIN_int32_T;
            }
          } else if (c >= 2.147483648E+9) {
            i9 = MAX_int32_T;
          } else {
            i9 = 0;
          }

          i3 = (long)j + overlap;
          if (i3 > 2147483647L) {
            i3 = 2147483647L;
          } else {
            if (i3 < -2147483648L) {
              i3 = -2147483648L;
            }
          }

          if (i9 > (int)i3 - 1) {
            i9 = 0;
          } else {
            i9--;
          }

          i3 = (long)i + idx;
          if (i3 > 2147483647L) {
            i3 = 2147483647L;
          } else {
            if (i3 < -2147483648L) {
              i3 = -2147483648L;
            }
          }

          ix = (int)i3 - 2;
          loop_ub = b_imin->size[2];
          c = rt_roundd_snf(pos[0] + (double)idx);
          if (c < 2.147483648E+9) {
            if (c >= -2.147483648E+9) {
              ixstart = (int)c;
            } else {
              ixstart = MIN_int32_T;
            }
          } else if (c >= 2.147483648E+9) {
            ixstart = MAX_int32_T;
          } else {
            ixstart = 0;
          }

          i3 = ixstart - 1L;
          if (i3 > 2147483647L) {
            i3 = 2147483647L;
          } else {
            if (i3 < -2147483648L) {
              i3 = -2147483648L;
            }
          }

          b_jj = (int)i3;
          ii = i8 - i7;
          for (ixstart = 0; ixstart < loop_ub; ixstart++) {
            b_loop_ub = i8 - i7;
            for (b_ix = 0; b_ix < b_loop_ub; b_ix++) {
              b_tmp_data[b_ix + ii * ixstart] = b_imin->data[((b_jj +
                b_imin->size[0] * (i7 + b_ix)) + b_imin->size[0] * b_imin->size
                [1] * ixstart) - 1];
            }
          }

          for (i7 = 0; i7 < loop_ub; i7++) {
            for (i8 = 0; i8 < ii; i8++) {
              imout->data[(ix + imout->size[0] * (i9 + i8)) + imout->size[0] *
                imout->size[1] * i7] = b_tmp_data[i8 + ii * i7];
            }
          }
        }

        for (idx = (int)indx->data[itmp]; idx < overlap; idx++) {
          for (nx = itmp + 1; nx < overlap; nx++) {
            if ((idx >= (int)min_err_boundh_data[nx - 1]) && (nx >= (int)
                 min_err_bound_data[idx - 1])) {
              i3 = (long)i + idx;
              if (i3 > 2147483647L) {
                i3 = 2147483647L;
              } else {
                if (i3 < -2147483648L) {
                  i3 = -2147483648L;
                }
              }

              i7 = (int)i3 - 1;
              i3 = (long)j + nx;
              if (i3 > 2147483647L) {
                i3 = 2147483647L;
              } else {
                if (i3 < -2147483648L) {
                  i3 = -2147483648L;
                }
              }

              i8 = (int)i3 - 1;
              loop_ub = b_imin->size[2];
              c = rt_roundd_snf(pos[1] + (double)nx);
              if (c < 2.147483648E+9) {
                if (c >= -2.147483648E+9) {
                  b_jj = (int)c;
                } else {
                  b_jj = MIN_int32_T;
                }
              } else if (c >= 2.147483648E+9) {
                b_jj = MAX_int32_T;
              } else {
                b_jj = 0;
              }

              c = rt_roundd_snf(pos[0] + (double)idx);
              if (c < 2.147483648E+9) {
                if (c >= -2.147483648E+9) {
                  ii = (int)c;
                } else {
                  ii = MIN_int32_T;
                }
              } else if (c >= 2.147483648E+9) {
                ii = MAX_int32_T;
              } else {
                ii = 0;
              }

              for (i9 = 0; i9 < loop_ub; i9++) {
                c_tmp_data[i9] = b_imin->data[((ii + b_imin->size[0] * (b_jj - 1))
                  + b_imin->size[0] * b_imin->size[1] * i9) - 1];
              }

              for (i9 = 0; i9 < loop_ub; i9++) {
                imout->data[(i7 + imout->size[0] * i8) + imout->size[0] *
                  imout->size[1] * i9] = c_tmp_data[i9];
              }
            }
          }
        }
      } else if (i > 1) {
        i3 = (long)i + overlap;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i7 = (int)i3 - 1;
        if (i > i7) {
          i8 = 1;
          i7 = 1;
        } else {
          i8 = i;
          i7++;
        }

        i3 = (long)j + tilesize;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i3 = (int)i3 - 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i9 = (int)i3;
        if (j > i9) {
          ix = 1;
          i9 = 1;
        } else {
          ix = j;
          i9++;
        }

        loop_ub = imout->size[2];
        ixstart = shared->size[0] * shared->size[1] * shared->size[2];
        shared->size[0] = i7 - i8;
        shared->size[1] = i9 - ix;
        shared->size[2] = loop_ub;
        emxEnsureCapacity((emxArray__common *)shared, ixstart, (int)sizeof
                          (double));
        for (ixstart = 0; ixstart < loop_ub; ixstart++) {
          b_loop_ub = i9 - ix;
          for (b_ix = 0; b_ix < b_loop_ub; b_ix++) {
            b_jj = i7 - i8;
            for (idx = 0; idx < b_jj; idx++) {
              shared->data[(idx + shared->size[0] * b_ix) + shared->size[0] *
                shared->size[1] * ixstart] = imout->data[(((i8 + idx) +
                imout->size[0] * ((ix + b_ix) - 1)) + imout->size[0] *
                imout->size[1] * ixstart) - 1];
            }
          }
        }

        c_getxcorr2(b_imin, shared, err);
        ixstart = imout->size[2];
        iv3[0] = (i7 - i8) * (i9 - ix) * ixstart;
        b_shared = *shared;
        b_shared.size = (int *)&iv3;
        b_shared.numDimensions = 1;
        b_power(&b_shared, ibest);
        i7 = err->size[0] * err->size[1];
        err->size[0] = errtop->size[0];
        err->size[1] = errtop->size[1];
        emxEnsureCapacity((emxArray__common *)err, i7, (int)sizeof(double));
        c = sum(ibest);
        loop_ub = errtop->size[0] * errtop->size[1];
        for (i7 = 0; i7 < loop_ub; i7++) {
          err->data[i7] = (errtop->data[i7] - 2.0 * err->data[i7]) + c;
        }

        /*  trim invalid data at edges */
        c = (double)err->size[0] - (double)tilesize;
        if (c < 2.147483648E+9) {
          if (c >= -2.147483648E+9) {
            i7 = (int)c;
          } else {
            i7 = MIN_int32_T;
          }
        } else {
          i7 = MAX_int32_T;
        }

        i3 = i7 + 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i7 = (int)i3;
        if (overlap > i7) {
          i8 = 0;
          i7 = 0;
        } else {
          i8 = overlap - 1;
        }

        c = (double)err->size[1] - (double)tilesize;
        if (c < 2.147483648E+9) {
          if (c >= -2.147483648E+9) {
            i9 = (int)c;
          } else {
            i9 = MIN_int32_T;
          }
        } else {
          i9 = MAX_int32_T;
        }

        i3 = i9 + 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i9 = (int)i3;
        if (tilesize > i9) {
          ix = 0;
          i9 = 0;
        } else {
          ix = tilesize - 1;
        }

        ii = err->size[0];
        ixstart = c_err->size[0] * c_err->size[1];
        c_err->size[0] = i7 - i8;
        c_err->size[1] = i9 - ix;
        emxEnsureCapacity((emxArray__common *)c_err, ixstart, (int)sizeof(double));
        loop_ub = i9 - ix;
        for (i9 = 0; i9 < loop_ub; i9++) {
          b_loop_ub = i7 - i8;
          for (ixstart = 0; ixstart < b_loop_ub; ixstart++) {
            c_err->data[ixstart + c_err->size[0] * i9] = err->data[(i8 + ixstart)
              + ii * (ix + i9)];
          }
        }

        i7 = err->size[0] * err->size[1];
        err->size[0] = c_err->size[0];
        err->size[1] = c_err->size[1];
        emxEnsureCapacity((emxArray__common *)err, i7, (int)sizeof(double));
        loop_ub = c_err->size[1];
        for (i7 = 0; i7 < loop_ub; i7++) {
          b_loop_ub = c_err->size[0];
          for (i8 = 0; i8 < b_loop_ub; i8++) {
            err->data[i8 + err->size[0] * i7] = c_err->data[i8 + c_err->size[0] *
              i7];
          }
        }

        ixstart = 1;
        b_jj = err->size[0] * err->size[1];
        c = err->data[0];
        ii = err->size[0] * err->size[1];
        if (ii > 1) {
          if (rtIsNaN(err->data[0])) {
            ix = 2;
            exitg8 = false;
            while ((!exitg8) && (ix <= b_jj)) {
              ixstart = ix;
              if (!rtIsNaN(err->data[ix - 1])) {
                c = err->data[ix - 1];
                exitg8 = true;
              } else {
                ix++;
              }
            }
          }

          ii = err->size[0] * err->size[1];
          if (ixstart < ii) {
            while (ixstart + 1 <= b_jj) {
              if (err->data[ixstart] < c) {
                c = err->data[ixstart];
              }

              ixstart++;
            }
          }
        }

        i7 = x->size[0] * x->size[1];
        x->size[0] = err->size[0];
        x->size[1] = err->size[1];
        emxEnsureCapacity((emxArray__common *)x, i7, (int)sizeof(boolean_T));
        c *= 1.1110000000000002;
        loop_ub = err->size[0] * err->size[1];
        for (i7 = 0; i7 < loop_ub; i7++) {
          x->data[i7] = (err->data[i7] <= c);
        }

        nx = x->size[0] * x->size[1];
        idx = 0;
        i7 = b_ii->size[0];
        b_ii->size[0] = nx;
        emxEnsureCapacity((emxArray__common *)b_ii, i7, (int)sizeof(int));
        i7 = jj->size[0];
        jj->size[0] = nx;
        emxEnsureCapacity((emxArray__common *)jj, i7, (int)sizeof(int));
        if (nx == 0) {
          i7 = b_ii->size[0];
          b_ii->size[0] = 0;
          emxEnsureCapacity((emxArray__common *)b_ii, i7, (int)sizeof(int));
          i7 = jj->size[0];
          jj->size[0] = 0;
          emxEnsureCapacity((emxArray__common *)jj, i7, (int)sizeof(int));
        } else {
          ii = 1;
          b_jj = 1;
          exitg7 = false;
          while ((!exitg7) && (b_jj <= x->size[1])) {
            guard2 = false;
            if (x->data[(ii + x->size[0] * (b_jj - 1)) - 1]) {
              idx++;
              b_ii->data[idx - 1] = ii;
              jj->data[idx - 1] = b_jj;
              if (idx >= nx) {
                exitg7 = true;
              } else {
                guard2 = true;
              }
            } else {
              guard2 = true;
            }

            if (guard2) {
              ii++;
              if (ii > x->size[0]) {
                ii = 1;
                b_jj++;
              }
            }
          }

          if (nx == 1) {
            if (idx == 0) {
              i7 = b_ii->size[0];
              b_ii->size[0] = 0;
              emxEnsureCapacity((emxArray__common *)b_ii, i7, (int)sizeof(int));
              i7 = jj->size[0];
              jj->size[0] = 0;
              emxEnsureCapacity((emxArray__common *)jj, i7, (int)sizeof(int));
            }
          } else {
            i7 = b_ii->size[0];
            if (1 > idx) {
              b_ii->size[0] = 0;
            } else {
              b_ii->size[0] = idx;
            }

            emxEnsureCapacity((emxArray__common *)b_ii, i7, (int)sizeof(int));
            i7 = jj->size[0];
            if (1 > idx) {
              jj->size[0] = 0;
            } else {
              jj->size[0] = idx;
            }

            emxEnsureCapacity((emxArray__common *)jj, i7, (int)sizeof(int));
          }
        }

        i7 = ibest->size[0];
        ibest->size[0] = b_ii->size[0];
        emxEnsureCapacity((emxArray__common *)ibest, i7, (int)sizeof(double));
        loop_ub = b_ii->size[0];
        for (i7 = 0; i7 < loop_ub; i7++) {
          ibest->data[i7] = b_ii->data[i7];
        }

        i7 = jbest->size[0];
        jbest->size[0] = jj->size[0];
        emxEnsureCapacity((emxArray__common *)jbest, i7, (int)sizeof(double));
        loop_ub = jj->size[0];
        for (i7 = 0; i7 < loop_ub; i7++) {
          jbest->data[i7] = jj->data[i7];
        }

        c = b_rand() * (double)ibest->size[0];
        c = ceil(c);
        pos[0] = ibest->data[(int)c - 1];
        pos[1] = jbest->data[(int)c - 1];
        c = rt_roundd_snf(pos[0] + (double)tilesize);
        if (c < 2.147483648E+9) {
          if (c >= -2.147483648E+9) {
            i7 = (int)c;
          } else {
            i7 = MIN_int32_T;
          }
        } else if (c >= 2.147483648E+9) {
          i7 = MAX_int32_T;
        } else {
          i7 = 0;
        }

        i3 = i7 - 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i7 = (int)i3;
        if ((int)pos[0] > i7) {
          i8 = 1;
          i7 = 0;
        } else {
          i8 = (int)pos[0];
        }

        c = rt_roundd_snf(pos[1] + (double)tilesize);
        if (c < 2.147483648E+9) {
          if (c >= -2.147483648E+9) {
            i9 = (int)c;
          } else {
            i9 = MIN_int32_T;
          }
        } else if (c >= 2.147483648E+9) {
          i9 = MAX_int32_T;
        } else {
          i9 = 0;
        }

        i3 = i9 - 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i9 = (int)i3;
        if ((int)pos[1] > i9) {
          ix = 1;
          i9 = 0;
        } else {
          ix = (int)pos[1];
        }

        i3 = (long)i + tilesize;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        if (i > (int)i3 - 1) {
          ixstart = 0;
        } else {
          ixstart = i - 1;
        }

        i3 = (long)j + tilesize;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i3 = (int)i3 - 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        if (j > (int)i3) {
          b_ix = 0;
        } else {
          b_ix = j - 1;
        }

        loop_ub = b_imin->size[2] - 1;
        for (idx = 0; idx <= loop_ub; idx++) {
          b_loop_ub = i9 - ix;
          for (ii = 0; ii <= b_loop_ub; ii++) {
            b_jj = i7 - i8;
            for (nx = 0; nx <= b_jj; nx++) {
              imout->data[((ixstart + nx) + imout->size[0] * (b_ix + ii)) +
                imout->size[0] * imout->size[1] * idx] = b_imin->data[(((i8 + nx)
                + b_imin->size[0] * ((ix + ii) - 1)) + b_imin->size[0] *
                b_imin->size[1] * idx) - 1];
            }
          }
        }

        i3 = (long)i + overlap;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i7 = (int)i3 - 1;
        if (i > i7) {
          i8 = 0;
          i7 = 0;
        } else {
          i8 = i - 1;
        }

        i3 = (long)j + tilesize;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i3 = (int)i3 - 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i9 = (int)i3;
        if (j > i9) {
          ix = 0;
          i9 = 0;
        } else {
          ix = j - 1;
        }

        /*  shared */
        c = rt_roundd_snf(pos[0] + (double)overlap);
        if (c < 2.147483648E+9) {
          if (c >= -2.147483648E+9) {
            ixstart = (int)c;
          } else {
            ixstart = MIN_int32_T;
          }
        } else if (c >= 2.147483648E+9) {
          ixstart = MAX_int32_T;
        } else {
          ixstart = 0;
        }

        i3 = ixstart - 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        if ((int)pos[0] > (int)i3) {
          ixstart = 0;
        } else {
          ixstart = (int)pos[0] - 1;
        }

        c = rt_roundd_snf(pos[1] + (double)tilesize);
        if (c < 2.147483648E+9) {
          if (c >= -2.147483648E+9) {
            b_ix = (int)c;
          } else {
            b_ix = MIN_int32_T;
          }
        } else if (c >= 2.147483648E+9) {
          b_ix = MAX_int32_T;
        } else {
          b_ix = 0;
        }

        i3 = b_ix - 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        if ((int)pos[1] > (int)i3) {
          b_ix = 0;
        } else {
          b_ix = (int)pos[1] - 1;
        }

        loop_ub = imout->size[2];
        idx = c_imout->size[0] * c_imout->size[1] * c_imout->size[2];
        c_imout->size[0] = i7 - i8;
        c_imout->size[1] = i9 - ix;
        c_imout->size[2] = loop_ub;
        emxEnsureCapacity((emxArray__common *)c_imout, idx, (int)sizeof(double));
        for (idx = 0; idx < loop_ub; idx++) {
          b_loop_ub = i9 - ix;
          for (ii = 0; ii < b_loop_ub; ii++) {
            b_jj = i7 - i8;
            for (nx = 0; nx < b_jj; nx++) {
              c_imout->data[(nx + c_imout->size[0] * ii) + c_imout->size[0] *
                c_imout->size[1] * idx] = imout->data[((i8 + nx) + imout->size[0]
                * (ix + ii)) + imout->size[0] * imout->size[1] * idx] -
                b_imin->data[((ixstart + nx) + b_imin->size[0] * (b_ix + ii)) +
                b_imin->size[0] * b_imin->size[1] * idx];
            }
          }
        }

        power(c_imout, r3);
        b_sum(r3, errmat);
        i7 = fph->size[0] * fph->size[1];
        fph->size[0] = overlap;
        fph->size[1] = tilesize;
        emxEnsureCapacity((emxArray__common *)fph, i7, (int)sizeof(double));
        loop_ub = overlap * tilesize;
        for (i7 = 0; i7 < loop_ub; i7++) {
          fph->data[i7] = 0.0;
        }

        i7 = pathh->size[0] * pathh->size[1];
        pathh->size[0] = overlap;
        pathh->size[1] = tilesize;
        emxEnsureCapacity((emxArray__common *)pathh, i7, (int)sizeof(double));
        loop_ub = overlap * tilesize;
        for (i7 = 0; i7 < loop_ub; i7++) {
          pathh->data[i7] = 0.0;
        }

        loop_ub = errmat->size[0] - 1;
        for (i7 = 0; i7 <= loop_ub; i7++) {
          fph->data[i7 + fph->size[0] * (tilesize - 1)] = errmat->data[i7 +
            errmat->size[0] * (tilesize - 1)];
        }

        for (idx = tilesize - 1; idx > 0; idx--) {
          for (nx = 0; nx + 1 <= overlap; nx++) {
            if (1 < nx) {
              b_jj = nx;
            } else {
              b_jj = 1;
            }

            ii = nx + 2;
            if (overlap <= ii) {
              ii = overlap;
            }

            if (ii < b_jj) {
              b_loop_ub = 0;
            } else {
              b_loop_ub = (ii - b_jj) + 1;
            }

            i7 = b_index->size[0] * b_index->size[1];
            b_index->size[0] = 1;
            b_index->size[1] = b_loop_ub;
            emxEnsureCapacity((emxArray__common *)b_index, i7, (int)sizeof(int));
            if (b_loop_ub > 0) {
              b_index->data[0] = b_jj;
              for (ii = 2; ii <= b_loop_ub; ii++) {
                b_jj++;
                b_index->data[ii - 1] = b_jj;
              }
            }

            ixstart = 1;
            i7 = f_index->size[0];
            f_index->size[0] = b_index->size[1];
            emxEnsureCapacity((emxArray__common *)f_index, i7, (int)sizeof(int));
            loop_ub = b_index->size[1];
            for (i7 = 0; i7 < loop_ub; i7++) {
              f_index->data[i7] = b_index->data[b_index->size[0] * i7];
            }

            b_loop_ub = f_index->size[0];
            c = fph->data[(b_index->data[0] + fph->size[0] * idx) - 1];
            itmp = 0;
            i7 = g_index->size[0];
            g_index->size[0] = b_index->size[1];
            emxEnsureCapacity((emxArray__common *)g_index, i7, (int)sizeof(int));
            loop_ub = b_index->size[1];
            for (i7 = 0; i7 < loop_ub; i7++) {
              g_index->data[i7] = b_index->data[b_index->size[0] * i7];
            }

            if (g_index->size[0] > 1) {
              if (rtIsNaN(c)) {
                ix = 2;
                exitg6 = false;
                while ((!exitg6) && (ix <= b_loop_ub)) {
                  ixstart = ix;
                  if (!rtIsNaN(fph->data[(b_index->data[b_index->size[0] * (ix -
                         1)] + fph->size[0] * idx) - 1])) {
                    c = fph->data[(b_index->data[b_index->size[0] * (ix - 1)] +
                                   fph->size[0] * idx) - 1];
                    itmp = ix - 1;
                    exitg6 = true;
                  } else {
                    ix++;
                  }
                }
              }

              i7 = h_index->size[0];
              h_index->size[0] = b_index->size[1];
              emxEnsureCapacity((emxArray__common *)h_index, i7, (int)sizeof(int));
              loop_ub = b_index->size[1];
              for (i7 = 0; i7 < loop_ub; i7++) {
                h_index->data[i7] = b_index->data[b_index->size[0] * i7];
              }

              if (ixstart < h_index->size[0]) {
                while (ixstart + 1 <= b_loop_ub) {
                  if (fph->data[(b_index->data[b_index->size[0] * ixstart] +
                                 fph->size[0] * idx) - 1] < c) {
                    c = fph->data[(b_index->data[b_index->size[0] * ixstart] +
                                   fph->size[0] * idx) - 1];
                    itmp = ixstart;
                  }

                  ixstart++;
                }
              }
            }

            fph->data[nx + fph->size[0] * (idx - 1)] = c;
            fph->data[nx + fph->size[0] * (idx - 1)] += errmat->data[nx +
              errmat->size[0] * (idx - 1)];
            pathh->data[nx + pathh->size[0] * (idx - 1)] = b_index->data[itmp];
          }
        }

        for (i7 = 0; i7 < tilesize; i7++) {
          min_err_boundh_data[i7] = 0.0;
        }

        ixstart = 1;
        b_loop_ub = fph->size[1];
        c = fph->data[0];
        itmp = 1;
        i7 = fph->size[1];
        if (i7 > 1) {
          if (rtIsNaN(c)) {
            ix = 2;
            exitg5 = false;
            while ((!exitg5) && (ix <= b_loop_ub)) {
              ixstart = ix;
              if (!rtIsNaN(fph->data[fph->size[0] * (ix - 1)])) {
                c = fph->data[fph->size[0] * (ix - 1)];
                itmp = ix;
                exitg5 = true;
              } else {
                ix++;
              }
            }
          }

          i7 = fph->size[1];
          if (ixstart < i7) {
            for (ix = ixstart + 1; ix <= b_loop_ub; ix++) {
              if (fph->data[fph->size[0] * (ix - 1)] < c) {
                c = fph->data[fph->size[0] * (ix - 1)];
                itmp = ix;
              }
            }
          }
        }

        min_err_boundh_data[0] = itmp;
        for (idx = 0; idx + 2 <= tilesize; idx++) {
          min_err_boundh_data[idx + 1] = pathh->data[((int)
            min_err_boundh_data[idx] + pathh->size[0] * idx) - 1];
        }

        for (idx = 1; idx <= tilesize; idx++) {
          i7 = (int)(pos[0] + min_err_boundh_data[idx - 1]);
          c = rt_roundd_snf(pos[0] + (double)tilesize);
          if (c < 2.147483648E+9) {
            if (c >= -2.147483648E+9) {
              i8 = (int)c;
            } else {
              i8 = MIN_int32_T;
            }
          } else if (c >= 2.147483648E+9) {
            i8 = MAX_int32_T;
          } else {
            i8 = 0;
          }

          i8--;
          if (i7 > i8) {
            i7 = 0;
            i8 = 0;
          } else {
            i7--;
          }

          c = rt_roundd_snf((double)i + min_err_boundh_data[idx - 1]);
          if (c < 2.147483648E+9) {
            if (c >= -2.147483648E+9) {
              i9 = (int)c;
            } else {
              i9 = MIN_int32_T;
            }
          } else if (c >= 2.147483648E+9) {
            i9 = MAX_int32_T;
          } else {
            i9 = 0;
          }

          i3 = (long)i + tilesize;
          if (i3 > 2147483647L) {
            i3 = 2147483647L;
          } else {
            if (i3 < -2147483648L) {
              i3 = -2147483648L;
            }
          }

          if (i9 > (int)i3 - 1) {
            i9 = 0;
          } else {
            i9--;
          }

          i3 = (long)j + idx;
          if (i3 > 2147483647L) {
            i3 = 2147483647L;
          } else {
            if (i3 < -2147483648L) {
              i3 = -2147483648L;
            }
          }

          ix = (int)i3 - 2;
          loop_ub = b_imin->size[2];
          c = rt_roundd_snf(pos[1] + (double)idx);
          if (c < 2.147483648E+9) {
            if (c >= -2.147483648E+9) {
              b_jj = (int)c;
            } else {
              b_jj = MIN_int32_T;
            }
          } else if (c >= 2.147483648E+9) {
            b_jj = MAX_int32_T;
          } else {
            b_jj = 0;
          }

          ii = i8 - i7;
          for (ixstart = 0; ixstart < loop_ub; ixstart++) {
            b_loop_ub = i8 - i7;
            for (b_ix = 0; b_ix < b_loop_ub; b_ix++) {
              tmp_data[b_ix + ii * ixstart] = b_imin->data[((i7 + b_ix) +
                b_imin->size[0] * (b_jj - 2)) + b_imin->size[0] * b_imin->size[1]
                * ixstart];
            }
          }

          for (i7 = 0; i7 < loop_ub; i7++) {
            for (i8 = 0; i8 < ii; i8++) {
              imout->data[((i9 + i8) + imout->size[0] * ix) + imout->size[0] *
                imout->size[1] * i7] = tmp_data[i8 + ii * i7];
            }
          }
        }
      } else if (j > 1) {
        i3 = (long)i + tilesize;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i3 = (int)i3 - 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i7 = (int)i3;
        if (i > i7) {
          i8 = 1;
          i7 = 1;
        } else {
          i8 = i;
          i7++;
        }

        i3 = (long)j + overlap;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i9 = (int)i3 - 1;
        if (j > i9) {
          ix = 1;
          i9 = 1;
        } else {
          ix = j;
          i9++;
        }

        loop_ub = imout->size[2];
        ixstart = shared->size[0] * shared->size[1] * shared->size[2];
        shared->size[0] = i7 - i8;
        shared->size[1] = i9 - ix;
        shared->size[2] = loop_ub;
        emxEnsureCapacity((emxArray__common *)shared, ixstart, (int)sizeof
                          (double));
        for (ixstart = 0; ixstart < loop_ub; ixstart++) {
          b_loop_ub = i9 - ix;
          for (b_ix = 0; b_ix < b_loop_ub; b_ix++) {
            b_jj = i7 - i8;
            for (idx = 0; idx < b_jj; idx++) {
              shared->data[(idx + shared->size[0] * b_ix) + shared->size[0] *
                shared->size[1] * ixstart] = imout->data[(((i8 + idx) +
                imout->size[0] * ((ix + b_ix) - 1)) + imout->size[0] *
                imout->size[1] * ixstart) - 1];
            }
          }
        }

        c_getxcorr2(b_imin, shared, err);
        ixstart = imout->size[2];
        iv4[0] = (i7 - i8) * (i9 - ix) * ixstart;
        b_shared = *shared;
        b_shared.size = (int *)&iv4;
        b_shared.numDimensions = 1;
        b_power(&b_shared, ibest);
        i7 = err->size[0] * err->size[1];
        err->size[0] = errside->size[0];
        err->size[1] = errside->size[1];
        emxEnsureCapacity((emxArray__common *)err, i7, (int)sizeof(double));
        c = sum(ibest);
        loop_ub = errside->size[0] * errside->size[1];
        for (i7 = 0; i7 < loop_ub; i7++) {
          err->data[i7] = (errside->data[i7] - 2.0 * err->data[i7]) + c;
        }

        /*  trim invalid data at edges */
        c = (double)err->size[0] - (double)tilesize;
        if (c < 2.147483648E+9) {
          if (c >= -2.147483648E+9) {
            i7 = (int)c;
          } else {
            i7 = MIN_int32_T;
          }
        } else {
          i7 = MAX_int32_T;
        }

        i3 = i7 + 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i7 = (int)i3;
        if (tilesize > i7) {
          i8 = 0;
          i7 = 0;
        } else {
          i8 = tilesize - 1;
        }

        c = (double)err->size[1] - (double)tilesize;
        if (c < 2.147483648E+9) {
          if (c >= -2.147483648E+9) {
            i9 = (int)c;
          } else {
            i9 = MIN_int32_T;
          }
        } else {
          i9 = MAX_int32_T;
        }

        i3 = i9 + 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i9 = (int)i3;
        if (overlap > i9) {
          ix = 0;
          i9 = 0;
        } else {
          ix = overlap - 1;
        }

        ixstart = b_err->size[0] * b_err->size[1];
        b_err->size[0] = i7 - i8;
        b_err->size[1] = i9 - ix;
        emxEnsureCapacity((emxArray__common *)b_err, ixstart, (int)sizeof(double));
        loop_ub = i9 - ix;
        for (i9 = 0; i9 < loop_ub; i9++) {
          b_loop_ub = i7 - i8;
          for (ixstart = 0; ixstart < b_loop_ub; ixstart++) {
            b_err->data[ixstart + b_err->size[0] * i9] = err->data[(i8 + ixstart)
              + err->size[0] * (ix + i9)];
          }
        }

        i7 = err->size[0] * err->size[1];
        err->size[0] = b_err->size[0];
        err->size[1] = b_err->size[1];
        emxEnsureCapacity((emxArray__common *)err, i7, (int)sizeof(double));
        loop_ub = b_err->size[1];
        for (i7 = 0; i7 < loop_ub; i7++) {
          b_loop_ub = b_err->size[0];
          for (i8 = 0; i8 < b_loop_ub; i8++) {
            err->data[i8 + err->size[0] * i7] = b_err->data[i8 + b_err->size[0] *
              i7];
          }
        }

        ixstart = 1;
        b_jj = err->size[0] * err->size[1];
        c = err->data[0];
        ii = err->size[0] * err->size[1];
        if (ii > 1) {
          if (rtIsNaN(err->data[0])) {
            ix = 2;
            exitg4 = false;
            while ((!exitg4) && (ix <= b_jj)) {
              ixstart = ix;
              if (!rtIsNaN(err->data[ix - 1])) {
                c = err->data[ix - 1];
                exitg4 = true;
              } else {
                ix++;
              }
            }
          }

          ii = err->size[0] * err->size[1];
          if (ixstart < ii) {
            while (ixstart + 1 <= b_jj) {
              if (err->data[ixstart] < c) {
                c = err->data[ixstart];
              }

              ixstart++;
            }
          }
        }

        i7 = x->size[0] * x->size[1];
        x->size[0] = err->size[0];
        x->size[1] = err->size[1];
        emxEnsureCapacity((emxArray__common *)x, i7, (int)sizeof(boolean_T));
        c *= 1.1110000000000002;
        loop_ub = err->size[0] * err->size[1];
        for (i7 = 0; i7 < loop_ub; i7++) {
          x->data[i7] = (err->data[i7] <= c);
        }

        nx = x->size[0] * x->size[1];
        idx = 0;
        i7 = b_ii->size[0];
        b_ii->size[0] = nx;
        emxEnsureCapacity((emxArray__common *)b_ii, i7, (int)sizeof(int));
        i7 = jj->size[0];
        jj->size[0] = nx;
        emxEnsureCapacity((emxArray__common *)jj, i7, (int)sizeof(int));
        if (nx == 0) {
          i7 = b_ii->size[0];
          b_ii->size[0] = 0;
          emxEnsureCapacity((emxArray__common *)b_ii, i7, (int)sizeof(int));
          i7 = jj->size[0];
          jj->size[0] = 0;
          emxEnsureCapacity((emxArray__common *)jj, i7, (int)sizeof(int));
        } else {
          ii = 1;
          b_jj = 1;
          exitg3 = false;
          while ((!exitg3) && (b_jj <= x->size[1])) {
            guard1 = false;
            if (x->data[(ii + x->size[0] * (b_jj - 1)) - 1]) {
              idx++;
              b_ii->data[idx - 1] = ii;
              jj->data[idx - 1] = b_jj;
              if (idx >= nx) {
                exitg3 = true;
              } else {
                guard1 = true;
              }
            } else {
              guard1 = true;
            }

            if (guard1) {
              ii++;
              if (ii > x->size[0]) {
                ii = 1;
                b_jj++;
              }
            }
          }

          if (nx == 1) {
            if (idx == 0) {
              i7 = b_ii->size[0];
              b_ii->size[0] = 0;
              emxEnsureCapacity((emxArray__common *)b_ii, i7, (int)sizeof(int));
              i7 = jj->size[0];
              jj->size[0] = 0;
              emxEnsureCapacity((emxArray__common *)jj, i7, (int)sizeof(int));
            }
          } else {
            i7 = b_ii->size[0];
            if (1 > idx) {
              b_ii->size[0] = 0;
            } else {
              b_ii->size[0] = idx;
            }

            emxEnsureCapacity((emxArray__common *)b_ii, i7, (int)sizeof(int));
            i7 = jj->size[0];
            if (1 > idx) {
              jj->size[0] = 0;
            } else {
              jj->size[0] = idx;
            }

            emxEnsureCapacity((emxArray__common *)jj, i7, (int)sizeof(int));
          }
        }

        i7 = ibest->size[0];
        ibest->size[0] = b_ii->size[0];
        emxEnsureCapacity((emxArray__common *)ibest, i7, (int)sizeof(double));
        loop_ub = b_ii->size[0];
        for (i7 = 0; i7 < loop_ub; i7++) {
          ibest->data[i7] = b_ii->data[i7];
        }

        i7 = jbest->size[0];
        jbest->size[0] = jj->size[0];
        emxEnsureCapacity((emxArray__common *)jbest, i7, (int)sizeof(double));
        loop_ub = jj->size[0];
        for (i7 = 0; i7 < loop_ub; i7++) {
          jbest->data[i7] = jj->data[i7];
        }

        c = b_rand() * (double)ibest->size[0];
        c = ceil(c);
        pos[0] = ibest->data[(int)c - 1];
        pos[1] = jbest->data[(int)c - 1];
        i3 = (long)i + tilesize;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i3 = (int)i3 - 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i7 = (int)i3;
        if (i > i7) {
          i8 = 0;
          i7 = 0;
        } else {
          i8 = i - 1;
        }

        i3 = (long)j + overlap;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i9 = (int)i3 - 1;
        if (j > i9) {
          ix = 0;
          i9 = 0;
        } else {
          ix = j - 1;
        }

        /*  shared */
        c = rt_roundd_snf(pos[0] + (double)tilesize);
        if (c < 2.147483648E+9) {
          if (c >= -2.147483648E+9) {
            ixstart = (int)c;
          } else {
            ixstart = MIN_int32_T;
          }
        } else if (c >= 2.147483648E+9) {
          ixstart = MAX_int32_T;
        } else {
          ixstart = 0;
        }

        i3 = ixstart - 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        if ((int)pos[0] > (int)i3) {
          ixstart = 0;
        } else {
          ixstart = (int)pos[0] - 1;
        }

        c = rt_roundd_snf(pos[1] + (double)overlap);
        if (c < 2.147483648E+9) {
          if (c >= -2.147483648E+9) {
            b_ix = (int)c;
          } else {
            b_ix = MIN_int32_T;
          }
        } else if (c >= 2.147483648E+9) {
          b_ix = MAX_int32_T;
        } else {
          b_ix = 0;
        }

        i3 = b_ix - 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        if ((int)pos[1] > (int)i3) {
          b_ix = 0;
        } else {
          b_ix = (int)pos[1] - 1;
        }

        loop_ub = imout->size[2];
        idx = b_imout->size[0] * b_imout->size[1] * b_imout->size[2];
        b_imout->size[0] = i7 - i8;
        b_imout->size[1] = i9 - ix;
        b_imout->size[2] = loop_ub;
        emxEnsureCapacity((emxArray__common *)b_imout, idx, (int)sizeof(double));
        for (idx = 0; idx < loop_ub; idx++) {
          b_loop_ub = i9 - ix;
          for (ii = 0; ii < b_loop_ub; ii++) {
            b_jj = i7 - i8;
            for (nx = 0; nx < b_jj; nx++) {
              b_imout->data[(nx + b_imout->size[0] * ii) + b_imout->size[0] *
                b_imout->size[1] * idx] = imout->data[((i8 + nx) + imout->size[0]
                * (ix + ii)) + imout->size[0] * imout->size[1] * idx] -
                b_imin->data[((ixstart + nx) + b_imin->size[0] * (b_ix + ii)) +
                b_imin->size[0] * b_imin->size[1] * idx];
            }
          }
        }

        power(b_imout, r3);
        b_sum(r3, errmat);
        i7 = err->size[0] * err->size[1];
        err->size[0] = tilesize;
        err->size[1] = overlap;
        emxEnsureCapacity((emxArray__common *)err, i7, (int)sizeof(double));
        loop_ub = tilesize * overlap;
        for (i7 = 0; i7 < loop_ub; i7++) {
          err->data[i7] = 0.0;
        }

        i7 = path->size[0] * path->size[1];
        path->size[0] = tilesize;
        path->size[1] = overlap;
        emxEnsureCapacity((emxArray__common *)path, i7, (int)sizeof(double));
        loop_ub = tilesize * overlap;
        for (i7 = 0; i7 < loop_ub; i7++) {
          path->data[i7] = 0.0;
        }

        loop_ub = errmat->size[1] - 1;
        for (i7 = 0; i7 <= loop_ub; i7++) {
          err->data[(tilesize + err->size[0] * i7) - 1] = errmat->data[(tilesize
            + errmat->size[0] * i7) - 1];
        }

        for (idx = tilesize - 1; idx > 0; idx--) {
          for (nx = 0; nx + 1 <= overlap; nx++) {
            if (1 < nx) {
              b_jj = nx;
            } else {
              b_jj = 1;
            }

            ii = nx + 2;
            if (overlap <= ii) {
              ii = overlap;
            }

            if (ii < b_jj) {
              b_loop_ub = 0;
            } else {
              b_loop_ub = (ii - b_jj) + 1;
            }

            i7 = b_index->size[0] * b_index->size[1];
            b_index->size[0] = 1;
            b_index->size[1] = b_loop_ub;
            emxEnsureCapacity((emxArray__common *)b_index, i7, (int)sizeof(int));
            if (b_loop_ub > 0) {
              b_index->data[0] = b_jj;
              for (ii = 2; ii <= b_loop_ub; ii++) {
                b_jj++;
                b_index->data[ii - 1] = b_jj;
              }
            }

            ixstart = 1;
            i7 = c_index->size[0];
            c_index->size[0] = b_index->size[1];
            emxEnsureCapacity((emxArray__common *)c_index, i7, (int)sizeof(int));
            loop_ub = b_index->size[1];
            for (i7 = 0; i7 < loop_ub; i7++) {
              c_index->data[i7] = b_index->data[b_index->size[0] * i7];
            }

            b_loop_ub = c_index->size[0];
            i7 = b_ii->size[0];
            b_ii->size[0] = b_index->size[1];
            emxEnsureCapacity((emxArray__common *)b_ii, i7, (int)sizeof(int));
            loop_ub = b_index->size[1];
            for (i7 = 0; i7 < loop_ub; i7++) {
              b_ii->data[i7] = b_index->data[b_index->size[0] * i7];
            }

            c = err->data[idx + err->size[0] * (b_ii->data[0] - 1)];
            itmp = 1;
            i7 = d_index->size[0];
            d_index->size[0] = b_index->size[1];
            emxEnsureCapacity((emxArray__common *)d_index, i7, (int)sizeof(int));
            loop_ub = b_index->size[1];
            for (i7 = 0; i7 < loop_ub; i7++) {
              d_index->data[i7] = b_index->data[b_index->size[0] * i7];
            }

            if (d_index->size[0] > 1) {
              if (rtIsNaN(c)) {
                ix = 2;
                exitg2 = false;
                while ((!exitg2) && (ix <= b_loop_ub)) {
                  ixstart = ix;
                  i7 = b_ii->size[0];
                  b_ii->size[0] = b_index->size[1];
                  emxEnsureCapacity((emxArray__common *)b_ii, i7, (int)sizeof
                                    (int));
                  loop_ub = b_index->size[1];
                  for (i7 = 0; i7 < loop_ub; i7++) {
                    b_ii->data[i7] = b_index->data[b_index->size[0] * i7];
                  }

                  if (!rtIsNaN(err->data[idx + err->size[0] * (b_ii->data[ix - 1]
                        - 1)])) {
                    i7 = b_ii->size[0];
                    b_ii->size[0] = b_index->size[1];
                    emxEnsureCapacity((emxArray__common *)b_ii, i7, (int)sizeof
                                      (int));
                    loop_ub = b_index->size[1];
                    for (i7 = 0; i7 < loop_ub; i7++) {
                      b_ii->data[i7] = b_index->data[b_index->size[0] * i7];
                    }

                    c = err->data[idx + err->size[0] * (b_ii->data[ix - 1] - 1)];
                    itmp = ix;
                    exitg2 = true;
                  } else {
                    ix++;
                  }
                }
              }

              i7 = e_index->size[0];
              e_index->size[0] = b_index->size[1];
              emxEnsureCapacity((emxArray__common *)e_index, i7, (int)sizeof(int));
              loop_ub = b_index->size[1];
              for (i7 = 0; i7 < loop_ub; i7++) {
                e_index->data[i7] = b_index->data[b_index->size[0] * i7];
              }

              if (ixstart < e_index->size[0]) {
                for (ix = ixstart + 1; ix <= b_loop_ub; ix++) {
                  i7 = b_ii->size[0];
                  b_ii->size[0] = b_index->size[1];
                  emxEnsureCapacity((emxArray__common *)b_ii, i7, (int)sizeof
                                    (int));
                  loop_ub = b_index->size[1];
                  for (i7 = 0; i7 < loop_ub; i7++) {
                    b_ii->data[i7] = b_index->data[b_index->size[0] * i7];
                  }

                  if (err->data[idx + err->size[0] * (b_ii->data[ix - 1] - 1)] <
                      c) {
                    i7 = b_ii->size[0];
                    b_ii->size[0] = b_index->size[1];
                    emxEnsureCapacity((emxArray__common *)b_ii, i7, (int)sizeof
                                      (int));
                    loop_ub = b_index->size[1];
                    for (i7 = 0; i7 < loop_ub; i7++) {
                      b_ii->data[i7] = b_index->data[b_index->size[0] * i7];
                    }

                    c = err->data[idx + err->size[0] * (b_ii->data[ix - 1] - 1)];
                    itmp = ix;
                  }
                }
              }
            }

            err->data[(idx + err->size[0] * nx) - 1] = c;
            err->data[(idx + err->size[0] * nx) - 1] += errmat->data[(idx +
              errmat->size[0] * nx) - 1];
            path->data[(idx + path->size[0] * nx) - 1] = b_index->data[itmp - 1];
          }
        }

        for (i7 = 0; i7 < tilesize; i7++) {
          min_err_bound_data[i7] = 0.0;
        }

        ixstart = 1;
        b_loop_ub = err->size[1];
        c = err->data[0];
        itmp = 1;
        i7 = err->size[1];
        if (i7 > 1) {
          if (rtIsNaN(c)) {
            ix = 2;
            exitg1 = false;
            while ((!exitg1) && (ix <= b_loop_ub)) {
              ixstart = ix;
              if (!rtIsNaN(err->data[err->size[0] * (ix - 1)])) {
                c = err->data[err->size[0] * (ix - 1)];
                itmp = ix;
                exitg1 = true;
              } else {
                ix++;
              }
            }
          }

          i7 = err->size[1];
          if (ixstart < i7) {
            for (ix = ixstart + 1; ix <= b_loop_ub; ix++) {
              if (err->data[err->size[0] * (ix - 1)] < c) {
                c = err->data[err->size[0] * (ix - 1)];
                itmp = ix;
              }
            }
          }
        }

        min_err_bound_data[0] = itmp;
        for (idx = 0; idx + 2 <= tilesize; idx++) {
          min_err_bound_data[idx + 1] = path->data[idx + path->size[0] * ((int)
            min_err_bound_data[idx] - 1)];
        }

        for (idx = 1; idx <= tilesize; idx++) {
          i7 = (int)(pos[1] + min_err_bound_data[idx - 1]);
          c = rt_roundd_snf(pos[1] + (double)tilesize);
          if (c < 2.147483648E+9) {
            if (c >= -2.147483648E+9) {
              i8 = (int)c;
            } else {
              i8 = MIN_int32_T;
            }
          } else if (c >= 2.147483648E+9) {
            i8 = MAX_int32_T;
          } else {
            i8 = 0;
          }

          i8--;
          if (i7 > i8) {
            i7 = 0;
            i8 = 0;
          } else {
            i7--;
          }

          c = rt_roundd_snf((double)j + min_err_bound_data[idx - 1]);
          if (c < 2.147483648E+9) {
            if (c >= -2.147483648E+9) {
              i9 = (int)c;
            } else {
              i9 = MIN_int32_T;
            }
          } else if (c >= 2.147483648E+9) {
            i9 = MAX_int32_T;
          } else {
            i9 = 0;
          }

          i3 = (long)j + tilesize;
          if (i3 > 2147483647L) {
            i3 = 2147483647L;
          } else {
            if (i3 < -2147483648L) {
              i3 = -2147483648L;
            }
          }

          if (i9 > (int)i3 - 1) {
            i9 = 0;
          } else {
            i9--;
          }

          ix = (i + idx) - 2;
          loop_ub = b_imin->size[2];
          c = rt_roundd_snf(pos[0] + (double)idx);
          if (c < 2.147483648E+9) {
            if (c >= -2.147483648E+9) {
              b_jj = (int)c;
            } else {
              b_jj = MIN_int32_T;
            }
          } else if (c >= 2.147483648E+9) {
            b_jj = MAX_int32_T;
          } else {
            b_jj = 0;
          }

          ii = i8 - i7;
          for (ixstart = 0; ixstart < loop_ub; ixstart++) {
            b_loop_ub = i8 - i7;
            for (b_ix = 0; b_ix < b_loop_ub; b_ix++) {
              b_tmp_data[b_ix + ii * ixstart] = b_imin->data[((b_jj +
                b_imin->size[0] * (i7 + b_ix)) + b_imin->size[0] * b_imin->size
                [1] * ixstart) - 2];
            }
          }

          for (i7 = 0; i7 < loop_ub; i7++) {
            for (i8 = 0; i8 < ii; i8++) {
              imout->data[(ix + imout->size[0] * (i9 + i8)) + imout->size[0] *
                imout->size[1] * i7] = b_tmp_data[i8 + ii * i7];
            }
          }
        }

        c = rt_roundd_snf(pos[0] + (double)tilesize);
        if (c < 2.147483648E+9) {
          if (c >= -2.147483648E+9) {
            i7 = (int)c;
          } else {
            i7 = MIN_int32_T;
          }
        } else if (c >= 2.147483648E+9) {
          i7 = MAX_int32_T;
        } else {
          i7 = 0;
        }

        i3 = i7 - 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i7 = (int)i3;
        if ((int)pos[0] > i7) {
          i8 = 1;
          i7 = 0;
        } else {
          i8 = (int)pos[0];
        }

        c = rt_roundd_snf(pos[1] + (double)tilesize);
        if (c < 2.147483648E+9) {
          if (c >= -2.147483648E+9) {
            i9 = (int)c;
          } else {
            i9 = MIN_int32_T;
          }
        } else if (c >= 2.147483648E+9) {
          i9 = MAX_int32_T;
        } else {
          i9 = 0;
        }

        i3 = i9 - 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i9 = (int)i3;
        if ((int)pos[1] > i9) {
          ix = 1;
          i9 = 0;
        } else {
          ix = (int)pos[1];
        }

        if (i > (i + tilesize) - 1) {
          ixstart = 0;
        } else {
          ixstart = i - 1;
        }

        i3 = (long)j + tilesize;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        if (j > (int)i3 - 1) {
          b_ix = 0;
        } else {
          b_ix = j - 1;
        }

        ii = imout->size[0];
        b_jj = b_imin->size[0];
        loop_ub = i9 - ix;
        for (i9 = 0; i9 <= loop_ub; i9++) {
          b_loop_ub = i7 - i8;
          for (idx = 0; idx <= b_loop_ub; idx++) {
            imout->data[(ixstart + idx) + ii * (b_ix + i9)] = b_imin->data[((i8
              + idx) + b_jj * ((ix + i9) - 1)) - 1];
          }
        }
      } else {
        c_rand(pos);
        for (i7 = 0; i7 < 2; i7++) {
          pos[i7] *= ((double)sizein[i7] - (double)tilesize) + 1.0;
        }

        b_ceil(pos);
        c = rt_roundd_snf(pos[0] + (double)tilesize);
        if (c < 2.147483648E+9) {
          if (c >= -2.147483648E+9) {
            i7 = (int)c;
          } else {
            i7 = MIN_int32_T;
          }
        } else if (c >= 2.147483648E+9) {
          i7 = MAX_int32_T;
        } else {
          i7 = 0;
        }

        i3 = i7 - 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i7 = (int)i3;
        if ((int)pos[0] > i7) {
          i8 = 1;
          i7 = 0;
        } else {
          i8 = (int)pos[0];
        }

        c = rt_roundd_snf(pos[1] + (double)tilesize);
        if (c < 2.147483648E+9) {
          if (c >= -2.147483648E+9) {
            i9 = (int)c;
          } else {
            i9 = MIN_int32_T;
          }
        } else if (c >= 2.147483648E+9) {
          i9 = MAX_int32_T;
        } else {
          i9 = 0;
        }

        i3 = i9 - 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i9 = (int)i3;
        if ((int)pos[1] > i9) {
          ix = 1;
          i9 = 0;
        } else {
          ix = (int)pos[1];
        }

        i3 = (long)i + tilesize;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i3 = (int)i3 - 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        if (i > (int)i3) {
          ixstart = 0;
        } else {
          ixstart = i - 1;
        }

        i3 = (long)j + tilesize;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        i3 = (int)i3 - 1L;
        if (i3 > 2147483647L) {
          i3 = 2147483647L;
        } else {
          if (i3 < -2147483648L) {
            i3 = -2147483648L;
          }
        }

        if (j > (int)i3) {
          b_ix = 0;
        } else {
          b_ix = j - 1;
        }

        loop_ub = b_imin->size[2] - 1;
        for (idx = 0; idx <= loop_ub; idx++) {
          b_loop_ub = i9 - ix;
          for (ii = 0; ii <= b_loop_ub; ii++) {
            b_jj = i7 - i8;
            for (nx = 0; nx <= b_jj; nx++) {
              imout->data[((ixstart + nx) + imout->size[0] * (b_ix + ii)) +
                imout->size[0] * imout->size[1] * idx] = b_imin->data[(((i8 + nx)
                + b_imin->size[0] * ((ix + ii) - 1)) + b_imin->size[0] *
                b_imin->size[1] * idx) - 1];
            }
          }
        }
      }

      /*      if isdebug~=0 */
      /*          set(h,'CData',uint8(imout)); */
      /*          drawnow; */
      /*      end */
      j += i5;
    }

    i += i2;
  }

  emxFree_int32_T(&n_index);
  emxFree_int32_T(&m_index);
  emxFree_int32_T(&l_index);
  emxFree_int32_T(&k_index);
  emxFree_int32_T(&j_index);
  emxFree_int32_T(&i_index);
  emxFree_real_T(&d_err);
  emxFree_int32_T(&h_index);
  emxFree_int32_T(&g_index);
  emxFree_int32_T(&f_index);
  emxFree_real_T(&c_err);
  emxFree_int32_T(&e_index);
  emxFree_int32_T(&d_index);
  emxFree_int32_T(&c_index);
  emxFree_real_T(&b_err);
  emxFree_real_T(&e_imout);
  emxFree_real_T(&d_imout);
  emxFree_real_T(&c_imout);
  emxFree_real_T(&b_imout);
  emxFree_real_T(&r3);
  emxFree_real_T(&extremum);
  emxFree_real_T(&indx);
  emxFree_int32_T(&jj);
  emxFree_int32_T(&b_ii);
  emxFree_boolean_T(&x);
  emxFree_real_T(&b_imin);
  emxFree_real_T(&jbest);
  emxFree_real_T(&ibest);
  emxFree_real_T(&allerr);
  emxFree_real_T(&path);
  emxFree_int32_T(&b_index);
  emxFree_real_T(&pathh);
  emxFree_real_T(&fph);
  emxFree_real_T(&errmat);
  emxFree_real_T(&err);
  emxFree_real_T(&shared);
  emxFree_real_T(&errsidesmall);
  emxFree_real_T(&errside);
  emxFree_real_T(&errtop);
}

/*
 * File trailer for synthesize.c
 *
 * [EOF]
 */
