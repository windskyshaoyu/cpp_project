#ifndef BIG_EYE_H
#define BIG_EYE_H

#include<opencv2/opencv.hpp>


using namespace std;
using namespace cv;

Mat eyesBigger(Mat input_image,double howBig = 1.2);

Mat changeBackground(Mat image,int color_flag);

Mat addear(Mat image, Mat logo);

#endif // BIG_EYE_H
