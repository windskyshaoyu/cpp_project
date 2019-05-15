#ifndef FLITER_COLOR_H
#define FLITER_COLOR_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

Mat filter_color(Mat org, int mode);
#endif // FLITER_COLOR_H
