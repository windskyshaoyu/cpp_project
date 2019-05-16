#include "graph_scene.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <QGraphicsSceneMouseEvent>
#include <QtCore>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <unistd.h>
using std:: string;

using namespace cv;

void GraphScreen::add_sticker(int mx,int my, int size){
    qDebug()<<"add_sticter";
    Mat logo = sticker_img.clone();
    Mat img = QImage2cvMat(*ScreenPic).clone();
    qDebug()<<size;
    cv::resize(logo, logo, Size(size,size), 0, 0, INTER_LINEAR);
    Mat mask;
    qDebug()<<"add_sticter";
    cvtColor(logo,mask,COLOR_BGR2GRAY);
    bitwise_not(mask, mask);
    threshold(mask, mask, 15, 255, THRESH_BINARY);
    qDebug()<<"add_sticter";
    if((mx<img.cols-logo.cols/2 && mx>logo.cols/2)&&(my<img.rows-logo.rows/2 && my>logo.rows/2)){
        qDebug()<<"add_sticter";
            qDebug()<<"paste"<<mx<<my;
            Mat imgROI = img(Rect(mx-logo.cols/2, my-logo.rows/2, logo.cols, logo.rows));
            logo.copyTo(imgROI, mask);
    }
    qDebug()<<"add_sticter";
    Mat cloneimg=img.clone();
    *ScreenPic = cvMat2QImage(cloneimg);
}

void GraphScreen::set_m_addsticker(bool state){
    qDebug()<<"m_addsticker"<<m_addsticker;
    m_addsticker = state;
    qDebug()<<"set_m_addsticker"<<state;
}

void GraphScreen::set_sticker_size(int size){
    sticker_size = size;
}

void GraphScreen::select_sticker(int sticker_idx){
    if (sticker_idx == 1){
//        qDebug()<<QCoreApplication::applicationDirPath();
//        qDebug()<<QDir::currentPath();
//        // using where a relative filename will end up
//        QFileInfo fi("temp");
//        //std::cout << fi.absolutePath() << std::endl;
//        qDebug()<<fi.absolutePath();
//        // explicitly using the relative name of the current working directory
//        QDir dir(".");
//        qDebug()<<dir.absolutePath();
////        QString pwd("");
//        char * PWD;
//        PWD = getenv ("PWD");
//        pwd.append(PWD);
//        qDebug()<<*PWD;
//        long size;
//        char *buf;
//        char *ptr;

//        size = pathconf(".", _PC_PATH_MAX);
//        if ((buf = (char *)malloc((size_t)size)) != NULL)
//            ptr = getcwd(buf, (size_t)size);
//        qDebug()<<*ptr;
        sticker_img = cv::imread("/Users/MacBook/Desktop/unipicture0515/images/s1.jpg");
    }
    else if (sticker_idx == 2){
        //sticker_img = imread(sticker_2_path);
        //imshow("sticker",sticker_img);
    }
}
