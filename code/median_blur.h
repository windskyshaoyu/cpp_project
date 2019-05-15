//#ifndef MEDIAN_BLUR_H
//#define MEDIAN_BLUR_H

///* This is to deal with salt-and-pepper noise. */
//#include <iostream>
//#include <opencv2/core.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>

//using namespace std;
//using namespace cv;


////void on_medianBlurTrackBar(int, void*);

////void median_blur(string address);
//void on_medianBlurTrackBar(int m, Mat org);
//Mat median_blur(Mat org,int k);

//#endif // MEDIAN_BLUR_H

#ifndef MEDIAN_BLUR_H
#define MEDIAN_BLUR_H

/* This is to deal with salt-and-pepper noise. */
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;


//void on_medianBlurTrackBar(int, void*);

//void median_blur(string address);
Mat median_blur(Mat org, int k);
#endif // MEDIAN_BLUR_H
