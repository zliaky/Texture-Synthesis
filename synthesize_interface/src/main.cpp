#include <highgui.h>
#include <cv.h>
#include <stdio.h>
#include <iostream>
#include "interface.h"
using namespace std;

IplImage *input, *output;
int width, height;
double* dataIn, *dataOut;

void getInputImage()
{
	input = cvLoadImage("res/444.png");
	width = input->width;
	height = input->height;
}

void getDataIn()
{
	dataIn = new double[3*height*width];
	for (int k = 0; k < 3; k++)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				CvScalar s;
				s = cvGet2D(input, i, j);
				dataIn[k*height*width+i*width+j] = s.val[k];
			}
		}
	}
}

void createOutputImage()
{
	output = cvCreateImage(cvSize(width*3, height*3), 8, 3);
	cvZero(output);
}

void show()
{
	cvNamedWindow("input", 1);
	cvShowImage("input", input);
	cvNamedWindow("output", 1);
	cvShowImage("output", output);
	cvSaveImage("result/output.png", output);
	cvWaitKey(0);
}

void setOutput()
{
	int outWidth = width*3;
	int outHeight = height*3;
	for (int i = 0; i < outHeight; i++)
	{
		for (int j = 0; j < outWidth; j++)
		{
			double b = dataOut[0*outHeight*outWidth+i*outWidth+j];
			double g = dataOut[1*outHeight*outWidth+i*outWidth+j];
			double r = dataOut[2*outHeight*outWidth+i*outWidth+j];
			cvSet2D(output, i, j, CvScalar(b, g, r));
		}
	}
}

int main(int argc, char const *argv[])
{
	getInputImage();
	getDataIn();

	dataOut = getTexture(dataIn, width, height);

	createOutputImage();
	setOutput();
	show();
	return 0;
}
