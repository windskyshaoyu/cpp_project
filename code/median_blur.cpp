//#include "median_blur.h"
//#include <iostream>
//#include <opencv2/core.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/imgproc.hpp>

//using namespace std;
//using namespace cv;



//static Mat dst;
////const int g_nMedianBlurMaxValue = 5;
////static int g_nMedianBlurValue;
//static int g_nkernelSize;
////string addr;

//// Define callback function
////void on_medianBlurTrackBar(int, void*);

//Mat median_blur(Mat org,int k)
//{

//    //addr = address;
//    /* Testing
//    if(org.empty())
//    {
//        cout << "Fail to load the picture!" << endl;
//        return;
//    }
//    */

//    //Test whether the image is CV_8U
//    if(org.depth() > 255 | org.depth() <0)
//    {
//        cout << "The depth of image is not CV_8U. The program will exit soon..." << endl;
//        //return;
//    }

//    //imshow("org", org);

//    // Name window
//    //namedWindow("Median blur picture", WINDOW_AUTOSIZE);
////    char medianBlurName[20];
////    sprintf(medianBlurName, "MedianBlurMaxValue %d", g_nMedianBlurMaxValue);
////    k = 1;

//    //Create Track Bar
//    //createTrackbar(medianBlurName, "Median blur picture", &g_nMedianBlurValue, g_nMedianBlurMaxValue, on_medianBlurTrackBar);
//    on_medianBlurTrackBar(k, org);
//    //waitKey(0);
//    return dst;
//}

//void on_medianBlurTrackBar(int m, Mat org)
//{
//    //Recalculate the size, which should be an odd number and larger than 1.
//    g_nkernelSize = m * 2 + 1;
//    medianBlur(org, dst, g_nkernelSize);
//    //imshow("Median blur picture", dst);
//}

#include "median_blur.h"
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

static Mat org;
static Mat dst;


Mat median_blur(Mat org, int k)
{
    k = k*2+1;
    medianBlur(org, dst, k);
    return dst;
}
