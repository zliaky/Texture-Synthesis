#include "interface.h"
emxArray_int32_T *imgIn;
emxArray_real_T *imgOut;
int inHeight, inWidth, outHeight, outWidth;

void initImgIn()
{
	imgIn = new emxArray_int32_T;
	imgIn->size = new int[3];
	imgIn->size[0] = inWidth;
	imgIn->size[1] = inHeight;
	imgIn->size[2] = 3;
	imgIn->allocatedSize = inWidth * inHeight * 3;
	imgIn->data = new int[imgIn->allocatedSize];
	imgIn->numDimensions = 3;
}

void initImgOut()
{
	imgOut = new emxArray_real_T;
	imgOut->size = new int[3];
	imgOut->size[0] = outWidth;
	imgOut->size[1] = outHeight;
	imgOut->size[2] = 3;
	imgOut->allocatedSize = outWidth * outHeight * 3;
	imgOut->data = new double[imgOut->allocatedSize];
	imgOut->numDimensions = 3;
}

void setImgIn(double *val)
{
	for (int i = 0; i < inWidth*inHeight*3; i++)
	{
		imgIn->data[i] = val[i];
	}
}

void init(double *in, int width, int height)
{
	inWidth = width;
	inHeight = height;
	outWidth = width*3;
	outHeight = height*3;
	initImgIn();
	initImgOut();
	setImgIn(in);
}

double* getTexture(double *in, int width, int height)
{
	init(in, width, height);
	synthesize(imgIn, imgOut->size, 12, 3, 0, imgOut);
	return imgOut->data;
}