#ifndef ADD_FRAME_H
#define ADD_FRAME_H

#include<opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;


Mat addframe(Mat img, int frame_num);
Mat addframe_cv(Mat img, int mode);
static Mat org,img,mask,frame,dst,final;
static int top, bottom;
static int borderType;

#endif // ADD_FRAME_H
