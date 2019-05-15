#include "slider.h"
#include <QPalette>

Slider::Slider(QWidget *parent)
    :QSlider(parent)
{
   m_displayLabel=new QLabel(this);
   m_displayLabel->setFixedSize(QSize(20,20));
   //设置游标背景为白色
   m_displayLabel->setAutoFillBackground(true);
   QPalette palette;
   palette.setColor(QPalette::Background, Qt::white);
   m_displayLabel->setPalette(palette);

   m_displayLabel->setAlignment(Qt::AlignCenter);

   m_displayLabel->setVisible(false);
   m_displayLabel->move(0,3);
   this->setOrientation(Qt::Horizontal);
}

Slider::~Slider()
{

}

void Slider::mousePressEvent(QMouseEvent *event)
{
    if(!m_displayLabel->isVisible())
    {
        m_displayLabel->setVisible(true);
        m_displayLabel->setText(QString::number(this->value()));
    }
    QSlider::mousePressEvent(event);
}

void Slider::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_displayLabel->isVisible())
    {
        m_displayLabel->setVisible(false);
    }
    QSlider::mouseReleaseEvent(event);
    emit sliderReleased();
}

void Slider::mouseMoveEvent(QMouseEvent *event)
{
    m_displayLabel->setText(QString::number(this->value()));
    m_displayLabel->move((this->width()-m_displayLabel->width())*this->value()/(this->maximum()-this->minimum()),3);
    QSlider::mouseMoveEvent(event);
}



//void Button::mousePressEvent(QMouseEvent *event){
//    Q_UNUSED(event);
//    this->setIcon(QIcon(*PressPicture));
//    emit clicked();
//}

//void Button::mouseReleaseEvent(QMouseEvent *event){
//    Q_UNUSED(event);
//    this->setIcon(QIcon(*ButtonPicture));
//    emit released();
//}



//void Button::enterEvent(QEvent *event){
//    Q_UNUSED(event);
//    this->setIcon(QIcon(*hoverPicture));
//}
//void Button::leaveEvent(QEvent *event){
//    Q_UNUSED(event);
//    this->setIcon(QIcon(*buttonPicture));
//}

