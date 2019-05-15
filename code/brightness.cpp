#include "brightness.h"
#include <iostream>
#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

static Mat g_DstImage;
//const int g_nBetaTrackbarMaxValue = 100; //Max value.
//static int g_nBetaTrackValue; // Current value.
//double g_dBetaValue;

Mat brightness(Mat g_SrcImage, int k)
{

//    namedWindow("Original Image",WINDOW_AUTOSIZE);
//    imshow("Original Image",g_SrcImage);

    g_DstImage = Mat::zeros(g_SrcImage.size(),g_SrcImage.type());

//    namedWindow("Image Process",WINDOW_AUTOSIZE);
//    g_nBetaTrackValue = 50;

//    char betaTrackName[50];
//    sprintf(betaTrackName,"Brightness",g_nBetaTrackbarMaxValue);
//    createTrackbar(betaTrackName,"Image Process",&g_nBetaTrackValue,g_nBetaTrackbarMaxValue,on_BetaTrackbar);
      on_BetaTrackbar(k, g_SrcImage);

    return g_DstImage;
}

void on_BetaTrackbar(int m,Mat g_SrcImage)
{
    for(int y = 0; y < g_DstImage.rows; y++)
    {
        for(int x = 0; x < g_DstImage.cols; x++)
        {
            for(int c = 0; c < 3; c++)
            {
                g_DstImage.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((g_SrcImage.at<Vec3b>(y, x)[c]) +
                m-50);
            }
        }
    }
//    imshow("Image Process",g_DstImage);
}
