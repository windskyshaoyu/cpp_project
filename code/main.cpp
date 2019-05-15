//#include "mainwindow.h"
//#include <QApplication>
//#include <QPixmap>
//#include <QSplashScreen>
//#include <QProcess>
//int main(int argc, char *argv[])
//{
//    QApplication app(argc, argv);

////    QPixmap pixmap(":/images/hello.jpeg");
////    QSplashScreen splash(pixmap);
////    splash.show();
////    app.processEvents();
//    MainWindow w;
//    w.show();
////    splash.finish(&w);
//    return app.exec();
//}



//#include "mainwindow.h"
//#include <QApplication>
//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    return a.exec();
//}

//#include <QApplication>
//#include "ui_main_window.h"
//int main(int argc, char *argv[]){
//    QApplication a(argc, argv);
//    Ui::main_window ui;
//    QWidget *w = new QWidget;
//    ui.setupUi(w);
//    w->show();
//    return a.exec();
//}

//#include <QApplication>
//#include "ui_load.h"
//int main(int argc, char *argv[]){
//    QApplication a(argc, argv);
//    Ui::load ui;
//    QMainWindow *w = new QMainWindow;
//    ui.setupUi(w);
//    w->show();
//    return a.exec();
//}


//--------------
#include <QApplication>
#include "main_window.h"
int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    main_window *w = new main_window;
    w->show();
    return a.exec();
}
//-------------

//#include <QApplication>
//#include "load.h"
//int main(int argc, char *argv[]){
//    QApplication a(argc, argv);
//    load *l = new load;
//    l->show();
//    return a.exec();
//}

//#include <opencv2/opencv.hpp>
//#include <opencv2/highgui.hpp>
//#include <crop.h>
//#include <QApplication>
//int main(int argc, char *argv[]){
    //crop("/Users/MacBook/Desktop/unipicture0428/images/hello.jpeg");
//    crop("images/hello.jpeg");
//    return 0;
//    QApplication a(argc, argv);
//    QString runPath = QCoreApplication::applicationDirPath();
//     QString run = QDir::currentPath();
//    cout << s << endl;
//    cv::Mat imagesrc = cv::imread("zzy1.jpeg");//读取图像
//    cv::namedWindow("openCV");//创建窗口
//    cv::imshow("openCV", imagesrc);
//    crop("/Users/MacBook/Desktop/unipicture0428/images/zzy1.jpeg");
//    return 0;

//}

