#ifndef __INTERFACE__
#define __INTERFACE__

#include "synthesize.h"

void initImgIn();
void initImgOut();
void setImgIn(double *val);
void init();
double* getTexture(double *in, int width, int height);

#endif