#ifndef CROP_H
#define CROP_H

#include <opencv2/opencv.hpp>
//#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include <stdio.h>

using namespace cv;
using namespace std;

void onMouse(int event, int x, int y, int flags, void *);
Mat crop(Mat org);
#endif // CROP_H
