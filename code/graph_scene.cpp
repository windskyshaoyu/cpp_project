#include "graph_scene.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <QGraphicsSceneMouseEvent>

#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;

void GraphScreen::display(QImage* image){
    ScreenPic = image;
    this->addPixmap(QPixmap::fromImage(*image));
}

//move mouse event
void GraphScreen::mouseMoveEvent(QGraphicsSceneMouseEvent* event){
    //qDebug()<<"Qgraphmove"<<event->scenePos();
}

void GraphScreen::mousePressEvent(QGraphicsSceneMouseEvent* event){
//    int mx = event->scenePos().x();
//    int my = event->scenePos().y();
    qDebug()<<m_addsticker;
    this->addPixmap(QPixmap::fromImage(*ScreenPic));
    qDebug()<<"Qgraphpress"<<event->scenePos();
 if(m_addsticker){
    int mx = event->scenePos().x();
    int my = event->scenePos().y();
    add_sticker(mx, my, sticker_size);
    this->addPixmap(QPixmap::fromImage(*ScreenPic));
    qDebug()<<"Qgraphpress"<<event->scenePos();
    }

    else if (m_mosaic){

        qDebug()<<"begin mosaik";
        int mx = event->scenePos().x();
        int my = event->scenePos().y();

        qDebug()<<mx<<"  "<<my<<" when press ";
        mosaicPtL = Point(mx, my);
        this->addPixmap(QPixmap::fromImage(*ScreenPic));

    }

    else if (m_text){
        qDebug()<<"begin text";
        int mx = event->scenePos().x();
        int my = event->scenePos().y();
        add_text(mx,my,text_size, text_content);
        this->addPixmap(QPixmap::fromImage(*ScreenPic));
    }
}


void GraphScreen::mouseReleaseEvent(QGraphicsSceneMouseEvent* event){
    if(m_mosaic){
        int mx = event->scenePos().x();
        int my = event->scenePos().y();
        mosaicPtR = Point(mx, my);
        mosaic(mosaicPtR, mosaicPtR, mosaic_size);
        this->addPixmap(QPixmap::fromImage(*ScreenPic));
        qDebug()<<"Qgraphpress"<<event->scenePos();
  }
}

//format change between QImage & cvMat
Mat GraphScreen::QImage2cvMat(QImage image) {
    cv::Mat mat;

    switch(image.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        cvtColor(mat,mat,COLOR_BGRA2BGR);
        qDebug()<<"cvt 4c23c";
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cvtColor(mat, mat, cv::COLOR_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    }
    qDebug() <<"Qimage: "<< image.format()<<"mat: "<<mat.type();
    return mat;
}

QImage GraphScreen::cvMat2QImage(const cv::Mat& mat)
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if(mat.type() == CV_8UC1)
    {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for(int i = 0; i < 256; i++)
        {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar *pSrc = mat.data;
        for(int row = 0; row < mat.rows; row ++)
        {
            uchar *pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        qDebug() <<"Qimage: "<< image.format()<<"mat: "<<mat.type();
        return image;
    }
    else if(mat.type() == CV_8UC3)
    {
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
       qDebug() <<"Qimage: "<< image.format()<<"mat: "<<mat.type();
        return image.rgbSwapped();
    }
    else if(mat.type() == CV_8UC4)
    {
        qDebug() << "CV_8UC4";
        // Copy input Mat
        const uchar *pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        qDebug() <<"Qimage: "<< image.format()<<"mat: "<<mat.type();
        return image.copy();
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }

}


//void GraphScreen::set_m_addsticker(bool state){
//    m_text = state;

//}
