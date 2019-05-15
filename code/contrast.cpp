#include "contrast.h"
#include <iostream>
#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

//定义全局变量
static Mat g_DstImage;


Mat contrast(Mat g_SrcImage,int k)
{
    g_DstImage = Mat::zeros(g_SrcImage.size(),g_SrcImage.type());


    //在创建的窗体中创建轨迹条并命名

    //调用回调函数
    on_AlphaTrackbar(k, g_SrcImage);
    return g_DstImage;

}

void on_AlphaTrackbar(int m,Mat g_SrcImage)
{
//    m = m-10;
    double value;
    value = double(m )/ 10;
    for(int y = 0; y < g_DstImage.rows; y++)
    {
        for(int x = 0; x < g_DstImage.cols; x++)
        {
            for(int c = 0; c < 3; c++)
            {
                g_DstImage.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(value *
                (g_SrcImage.at<Vec3b>(y, x)[c]));
            }
        }
    }
}
