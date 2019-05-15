#ifndef BUTTON_H
#define BUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include <QPixmap>

class Button : public QPushButton {
    Q_OBJECT

public:
    explicit Button(QWidget *parent = Q_NULLPTR);
    ~Button();
    void setButtonPicture(QPixmap *pic);
    void setPressPicture(QPixmap *pic);
    void setButtonSize(int width, int height);
//    void setMode(int mode);

private:
    QPixmap *ButtonPicture = new QPixmap();
    QPixmap *PressPicture = new QPixmap();
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
//    int mode = 0;

};


#endif // BUTTON_H
