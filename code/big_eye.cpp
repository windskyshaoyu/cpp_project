#include<opencv2/opencv.hpp>
#include "big_eye.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include <iostream>
#include <stdio.h>
#include<QtCore>

using namespace std;
using namespace cv;

// input_image : 输入图像, howBig: 放大的比例 推荐1.15-1.25 太大不自然
Mat eyesBigger(Mat input_image,double howBig)
{
    qDebug()<<"eyesBigger";
    //String eyes_cascade_name = "./haarcascade_eye_tree_eyeglasses.xml"; // eye classifier 的路径
    String eyes_cascade_name = "/Users/rose/Desktop/unipicture0505/haarcascade_eye_tree_eyeglasses.xml";
    qDebug()<<"ss"<<input_image.type();
    string store_address;
    std::vector<Rect> eyes; // 眼睛的

    CascadeClassifier eyes_cascade;
    Mat frame_gray;
    Mat latten;
    Mat roi; //放大后的人眼局部图像

    eyes_cascade.load(eyes_cascade_name);
    //imshow("原图", input_image);
    input_image.copyTo(latten);
    cvtColor(input_image, frame_gray, COLOR_BGR2GRAY);
    eyes_cascade.detectMultiScale(frame_gray, eyes, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
    if (eyes.size() > 0)
    {

            cout << "检测到眼睛";

            for (int i = 0; i < eyes.size(); i++)
            {
                    //不断循环 根据放大的比例来扩大eyes的rect 然后贴回原图

                    Rect eye = eyes[i];
                    //rectangle(latten, eye, Scalar(0, 0, 255), 2);
                    cout << "人眼坐标x" << eye.x <<  "人眼坐标y" << eye.y << endl;

                    roi = input_image(eye);
                    resize(roi, roi, Size(eye.height*howBig, eye.width*howBig));//把人眼放大到原本的n倍

                    roi.copyTo(latten(Rect(eye.x- (eye.height*howBig-roi.cols)/2, eye.y - (eye.width*howBig- roi.rows)/2, roi.cols, roi.rows)));
//                    imshow("人眼fangda ", latten);
            }

    }
    else
    {
            cout<< "未检测到眼睛" << endl;
    }

    return latten.clone();
}
