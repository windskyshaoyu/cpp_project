#include "noise.h"
#include <cstdlib>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;
//Mat addSPNoise(const Mat srcImage, int n);

//double generateGaussianNoise(double m, double sigma);
//Mat addGaussianNoise(Mat &srcImag);

Mat noise(Mat org, int mode){
    if (mode == 0){
        int num = (org.rows * org.cols)/100;
        Mat dst = addSPNoise(org, num);
//        imshow("salt&pepper", dst);
//        waitKey();
        return dst;
    } else {
        Mat dst = addGaussianNoise(org);
//        imshow("Gaussion", dst);
//         waitKey();
        return dst;
    }
}

Mat addSPNoise(const Mat srcImage, int n){
    Mat dstImage = srcImage.clone();
    for (int k = 0; k < n; k++)	{		//随机取值行列
        int i = rand() % dstImage.rows;
        int j = rand() % dstImage.cols;
        //图像通道判定
        if (dstImage.channels() == 1)
        {
            dstImage.at<uchar>(i, j) = 255;		// Salt
        } else {
            dstImage.at<Vec3b>(i, j)[0] = 255;
            dstImage.at<Vec3b>(i, j)[1] = 255;
            dstImage.at<Vec3b>(i, j)[2] = 255;
        }
    }
    for (int k = 0; k < n; k++)	{		//随机取值行列
        int i = rand() % dstImage.rows;
        int j = rand() % dstImage.cols;		//图像通道判定
        if (dstImage.channels() == 1)
        {
            dstImage.at<uchar>(i, j) = 0;		// Pepper
        } else {
            dstImage.at<Vec3b>(i, j)[0] = 0;
            dstImage.at<Vec3b>(i, j)[1] = 0;
            dstImage.at<Vec3b>(i, j)[2] = 0;
        }
    }
    return dstImage;
}

double generateGaussianNoise(double mu, double sigma){
    //定义小值
    const double epsilon = numeric_limits<double>::min();
    static double z0, z1;
    static bool flag = false;
    flag = !flag;	//flag为假构造高斯随机变量X
    if (!flag) {
        return z1 * sigma + mu;
    }
    double u1, u2;	//构造随机变量
    do	{
        u1 = rand() * (1.0 / RAND_MAX);
        u2 = rand() * (1.0 / RAND_MAX);
    } while (u1 <= epsilon);
    //flag为真构造高斯随机变量
    z0 = sqrt(-2.0*log(u1))*cos(2 * CV_PI*u2);
    z1 = sqrt(-2.0*log(u1))*sin(2 * CV_PI*u2);
    return z0*sigma + mu;
}

//为图像添加高斯噪声
Mat addGaussianNoise(Mat &srcImag){
    Mat dstImage = srcImag.clone();
    int channels = dstImage.channels();
    int rowsNumber = dstImage.rows;
    int colsNumber = dstImage.cols*channels;
    //判断图像的连续性
    if (dstImage.isContinuous())
    {
        colsNumber *= rowsNumber;
        rowsNumber = 1;
    }
    for (int i = 0; i < rowsNumber; i++)
    {
        for (int j = 0; j < colsNumber; j++)
        {			//添加高斯噪声
            int val = dstImage.ptr<uchar>(i)[j] + generateGaussianNoise(2, 0.8) * 32;
            if (val < 0)
                val = 0;
            if (val>255)
                val = 255;
            dstImage.ptr<uchar>(i)[j] = uchar(val);
        }
    }
    return dstImage;
}
