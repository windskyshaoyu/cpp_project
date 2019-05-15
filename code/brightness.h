#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H

#include <iostream>
#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
using namespace std;
using namespace cv;
void on_BetaTrackbar(int m,Mat g_SrcImage);
Mat brightness(Mat g_SrcImage, int k);
#endif // BRIGHTNESS_H
