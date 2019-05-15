#ifndef CONTRAST_H
#define CONTRAST_H

#include <iostream>
#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;
void on_AlphaTrackbar(int m,Mat g_SrcImage);
Mat contrast(Mat g_SrcImage,int k);
//void on_AlphaTrackbar(int m,Mat g_SrcImage, Mat g_DstImage);

#endif // CONTRAST_H
