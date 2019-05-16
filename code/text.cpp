#include "graph_scene.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <QGraphicsSceneMouseEvent>
#include <QtCore>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <unistd.h>
using std::string;

using namespace cv;

void GraphScreen::add_text(int mx,int my, int size,QString text_content){
    std::cout<<"here add_text "<<size<<endl;
    QPainter painter(& *ScreenPic); //为这个QImage构造一个QPainter
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    QPen pen = painter.pen();
    pen.setColor(Qt::white);
    QFont font = painter.font();
    font.setBold(true);//加粗
    font.setPixelSize(size);//改变字体大小
    painter.setPen(pen);
    painter.setFont(font);
//    QString text_content;
//   text_content = textEdt->toPlainText();
//    text_content = "Hello";
    painter.drawText(mx,my,text_content);
//    cout<< "draw "<<main_screen->text_x<<endl;
//    cout<< "draw:"<< main_screen->text_y<<endl;

  //  display_screen();

}

void GraphScreen::set_m_text(bool state){
    m_text = state;//bug
    qDebug()<<state;
}
void GraphScreen::set_text_size(int size){
    text_size = size;
}

void GraphScreen::set_text_content(QString content){
    text_content = content;
}
