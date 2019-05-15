#include <iostream>
#include<opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "add_frame.h"
using namespace std;
using namespace cv;



Mat addframe(Mat img, int frame_num){

    Mat frame1, frame2, frame3, frame4;

    int parameter = 10;


    if (frame_num == 1)
    {
        parameter = 10;
        frame = imread("/Users/rose/Downloads/unipicture0428/images/heart.jpg",IMREAD_COLOR);
    }

    if (frame_num == 2)
    {
        parameter = 100;
        frame = imread("/Users/rose/Downloads/unipicture0428/images/Gauty.jpg",IMREAD_COLOR);
    }

    if (frame_num == 3)
    {
        parameter = 10;
        frame = imread("/Users/rose/Downloads/unipicture0428/images/COCOa.jpg",IMREAD_COLOR);
    }

    if (frame_num == 4)
    {
        parameter = 30;
        frame = imread("/Users/rose/Downloads/unipicture0428/images/Vintage.jpg",IMREAD_COLOR);
    }

    resize(frame, frame, Size(img.cols,img.rows), 0, 0, INTER_LINEAR);
    cvtColor(frame,mask,COLOR_BGR2GRAY);
    bitwise_not(mask, mask);
//    imshow("mask",mask);
    threshold(mask, mask, parameter, 255, THRESH_BINARY);
    frame.copyTo(img,mask);
    return img.clone();

}


Mat addframe_cv(Mat img, int mode){

    top = int (0.15*img.rows);
    bottom = static_cast<int> (0.15*img.rows);
    int left = static_cast<int> (0.15*img.cols);
    int right = static_cast<int> (0.15*img.cols);

    //边缘模糊
    if(mode == 1){
    borderType=BORDER_REPLICATE;
    copyMakeBorder( img, dst, top, bottom, left, right, borderType);
    }
    //边缘翻转
    if (mode==2){
    borderType=BORDER_REFLECT_101;
    copyMakeBorder( img, dst, top, bottom, left, right, borderType);
    }
    //黑边框
    if(mode == 3){
    Scalar value(0 ,0, 0);
    borderType=BORDER_CONSTANT;
    copyMakeBorder( img, dst, top, bottom, left, right, borderType,value);

    }
    //白边框
    if(mode == 4){
    Scalar value2(255,255,255);
    borderType=BORDER_CONSTANT;
    copyMakeBorder( img, dst, top, bottom, left, right, borderType,value2);

    }
    return dst;
}







