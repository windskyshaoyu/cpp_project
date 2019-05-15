#ifndef SLIDER_H
#define SLIDER_H

#include <QWidget>
#include <QSlider>
#include <QSpinBox>
#include <QLabel>
#include <QMouseEvent>

class Slider : public QSlider {
    Q_OBJECT



public:
    explicit Slider(QWidget *parent = Q_NULLPTR);
    ~Slider();
//    Slider(QWidget *parent=0);
//        ~Slider();

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    QLabel* m_displayLabel;

//private slots:
//    void slider_release(Mat img);

};




#endif // SLIDER_H
