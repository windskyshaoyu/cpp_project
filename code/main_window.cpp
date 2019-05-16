#include "main_window.h"

#include <iostream>
#include <QFileDialog>
#include <QtWidgets>
#include <QtCore>
#include <QVBoxLayout>
#include <QPushButton>
#include <QToolButton>
#include <QIcon>
#include <QImage>
#include <QString>
#include "string.h"
#include "graph_scene.h"
#include "big_eye.h"
#include "add_frame.h"
#include <opencv2/imgproc/imgproc.hpp>

#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;




main_window::main_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::main_window)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
//    setMouseTracking(true);
    setAddition();
    setMainButtons();

    setDicText();

    //mia
    Set_Filter();
    //Hide_Filter();
    Set_Tool();
    //Hide_Tool();
    Set_Sticker();
    Set_Mosaic();
    Set_Frame();
    Set_background();

    QPalette pal = this->palette();
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/images/background4.jpeg")));
    setPalette(pal);
    //ui->verticalLayout_2->setGeometry(500);
    ui->scrollArea_Background->setVisible(false); //胡然把background相关代码加上以后要把这行删掉
}

main_window::~main_window()
{
    delete ui;
}

void main_window::setMainButtons(){
    ui->horizontalLayout->addWidget(return_Button);
    ui->horizontalLayout->addWidget(changeSize_Button);
    ui->horizontalLayout->addWidget(close_Button);
//    return_Button->setText("<<");
//    changeSize_Button->setText("< >");
//    close_Button->setText("xxx");

    return_Button->setButtonPicture(return_Img);
    return_Button->setPressPicture(return_PressImg);
    close_Button->setButtonPicture(close_Img);
    close_Button->setPressPicture(close_PressImg);
    changeSize_Button->setButtonPicture(large_Img);
    changeSize_Button->setPressPicture(large_PressImg);
    return_Button->setIconSize(QSize(30,30));
    close_Button->setIconSize(QSize(30,30));
    changeSize_Button->setIconSize(QSize(30,30));


    ui->verticalLayout_4->addWidget(Tool_Button);
    ui->verticalLayout_4->addWidget(Filter_Button);
    ui->verticalLayout_4->addWidget(Sticker_Button);
    ui->verticalLayout_4->addWidget(Text_Button);
    ui->verticalLayout_4->addWidget(Bigeye_Button);//mia
    ui->verticalLayout_4->addWidget(Frame_Button);
    ui->verticalLayout_4->addWidget(Mosaic_Button);
    ui->verticalLayout_4->addWidget(Colorchange_Button);
    ui->verticalLayout_4->addWidget(Collage_Button);

    ui->scrollArea->setFixedSize(QSize(120, 170));
    ui->widget_2->setFixedSize(QSize(120, 170));
    ui->load_button->setFixedSize(QSize(50, 50));
    ui->top_layout->setContentsMargins(5,5,5,5);

    ui->horizontalLayout_5->addWidget(Undo_Button);
    ui->horizontalLayout_5->addWidget(Redo_Button);
    ui->horizontalLayout_5->addWidget(TempSave_Button);
    ui->horizontalLayout_5->addWidget(Delete_Button);
    ui->horizontalLayout_5->addWidget(Download_Button);


    Tool_Button->setButtonPicture(Tool_Img);
    Tool_Button->setPressPicture(Tool_PressImg);

    Filter_Button->setButtonPicture(Filter_Img);
    Filter_Button->setPressPicture(Filter_PressImg);
    Sticker_Button->setButtonPicture(Sticker_Img);
    Sticker_Button->setPressPicture(Sticker_PressImg);
    Text_Button->setButtonPicture(Text_Img);
    Text_Button->setPressPicture(Text_PressImg);
    Bigeye_Button->setButtonPicture(Bigeye_Img);
    Bigeye_Button->setPressPicture(Bigeye_PressImg);

    Frame_Button->setButtonPicture(Frame_Img);
    Frame_Button->setPressPicture(Frame_PressImg);

//    Mosaic_Button->setText("Mosaic");
//    Colorchange_Button->setText("Background Color");
    //Mosaic_Button->setIconSize(QSize(120,40));
    Mosaic_Button->setButtonPicture(Mosaic_Img);
    Mosaic_Button->setPressPicture(Mosaic_PressImg);
    Colorchange_Button->setButtonPicture(BackColor_Img);
    Colorchange_Button->setPressPicture(BackColor_PressImg);
    Collage_Button->setButtonPicture(Collage_Img);
    Collage_Button->setPressPicture(Collage_PressImg);




    Undo_Button->setButtonPicture(undo_Img);
    Undo_Button->setPressPicture(undo_PressImg);
    Redo_Button->setButtonPicture(redo_Img);
    Redo_Button->setPressPicture(redo_PressImg);
    TempSave_Button->setButtonPicture(tempsave_Img);
    TempSave_Button->setPressPicture(tempsave_PressImg);
    Delete_Button->setButtonPicture(delete_Img);
    Delete_Button->setPressPicture(delete_PressImg);
    Download_Button->setButtonPicture(download_Img);
    Download_Button->setPressPicture(download_PressImg);
    Undo_Button->setIconSize(QSize(40,40));
    Redo_Button->setIconSize(QSize(40,40));
    TempSave_Button->setIconSize(QSize(40,40));
    Delete_Button->setIconSize(QSize(40,40));
    Download_Button->setIconSize(QSize(40,40));




//    Save_Button->setText("save");
//    Undo_Button->setText("undo");
//    Delete_Button->setText("delete");
//    TempSave_Button->setText("tempsave");

    connect(changeSize_Button, SIGNAL(released()), this, SLOT(changeWindowSize()));
    connect(close_Button, SIGNAL(released()), this, SLOT(close()));
    connect(return_Button, SIGNAL(released()), this, SLOT(Hide_Filter()));//mia
    connect(return_Button, SIGNAL(released()), this, SLOT(Hide_Tool()));//mia
    connect(return_Button, SIGNAL(released()), this, SLOT(Hide_Sticker()));//mia
    connect(return_Button, SIGNAL(released()), this, SLOT(Hide_Mosaic()));//mia
    connect(return_Button, SIGNAL(released()), this, SLOT(Hide_Frame()));//mia
    connect(return_Button, SIGNAL(released()), this, SLOT(ButtonShow()));//mia
    connect(return_Button, SIGNAL(released()), this, SLOT(Hide_FilterColor_Button()));//mia
    connect(return_Button, SIGNAL(released()), this, SLOT(Hide_Bright_Slider()));//mia
    connect(return_Button, SIGNAL(released()), this, SLOT(Hide_Contrast_Slider()));//mia
    connect(return_Button, SIGNAL(released()), this, SLOT(Hide_Blur_Slider()));//mia
    connect(return_Button, SIGNAL(released()), this, SLOT(Hide_Saturation_Slider()));//mia
    connect(return_Button, SIGNAL(released()), this, SLOT(Hide_Rotate_Button()));//mia
    connect(return_Button, SIGNAL(released()), this, SLOT(Hide_background()));//yh

    connect(Tool_Button, SIGNAL(released()), this, SLOT(ButtonHide()));//mia
    connect(Tool_Button, SIGNAL(released()), this, SLOT(Hide_eyeSlider()));//mia
    connect(Tool_Button, SIGNAL(released()), this, SLOT(Hide_collageButton()));//mia
    //connect(Tool_Button, SIGNAL(released()), this, SLOT(ButtonHide()));//mia
    connect(Tool_Button, SIGNAL(released()), this, SLOT(Show_Tool()));//mia

    connect(Filter_Button, SIGNAL(released()), this, SLOT(ButtonHide()));//mia
    connect(Filter_Button, SIGNAL(released()), this, SLOT(Hide_eyeSlider()));//mia
    connect(Filter_Button, SIGNAL(released()), this, SLOT(Hide_collageButton()));//mia
    connect(Filter_Button, SIGNAL(released()), this, SLOT(Show_Filter()));//mia

    connect(Sticker_Button, SIGNAL(released()), this, SLOT(ButtonHide()));//mia
    connect(Sticker_Button, SIGNAL(released()), this, SLOT(Hide_eyeSlider()));//mia
    connect(Sticker_Button, SIGNAL(released()), this, SLOT(Hide_collageButton()));//mia
    connect(Sticker_Button, SIGNAL(released()), this, SLOT(Show_Sticker()));//mia

    //connect(Bigeye_Button, SIGNAL(released()), this, SLOT(ButtonHide()));//mia
    connect(Bigeye_Button, SIGNAL(released()), this, SLOT(Show_eyeSlider()));//mia
    connect(Bigeye_Button, SIGNAL(released()), this, SLOT(Hide_collageButton()));//mia
    connect(Bigeye_Button, SIGNAL(released()), this, SLOT(Big_eye()));

    connect(Mosaic_Button, SIGNAL(released()), this, SLOT(ButtonHide()));//mia
    connect(Mosaic_Button, SIGNAL(released()), this, SLOT(Hide_eyeSlider()));//mia
    connect(Mosaic_Button, SIGNAL(released()), this, SLOT(Hide_collageButton()));//mia
    connect(Mosaic_Button, SIGNAL(released()), this, SLOT(Show_Mosaic()));

    connect(Frame_Button, SIGNAL(released()), this, SLOT(ButtonHide()));//mia
    connect(Frame_Button, SIGNAL(released()), this, SLOT(Hide_eyeSlider()));//mia
    connect(Frame_Button, SIGNAL(released()), this, SLOT(Hide_collageButton()));//mia
    connect(Frame_Button, SIGNAL(released()), this, SLOT(Show_Frame()));

    connect(Collage_Button, SIGNAL(released()), this, SLOT(Hide_eyeSlider()));//mia
    connect(Collage_Button, SIGNAL(released()), this, SLOT(Show_collageButton()));//mia
    connect(Collage_Button, SIGNAL(released()), this, SLOT(Collage()));

    connect(Colorchange_Button, SIGNAL(released()), this, SLOT(ButtonHide()));//mia
    connect(Colorchange_Button, SIGNAL(released()), this, SLOT(Hide_eyeSlider()));//mia
    connect(Colorchange_Button, SIGNAL(released()), this, SLOT(Hide_collageButton()));//mia
    connect(Colorchange_Button, SIGNAL(released()), this, SLOT(Show_background()));
    //connect(Colorchange_Button, SIGNAL(released()), this, SLOT(Set_background()));
    //胡然要搜索Colorchange_Button,把connect(...)的加在这里，保留上面Hide_collageButton()这行新的，再上面一行Hide_eyeSlider()如果你那边重复有了就删掉，写一遍就可以




    //connect(sticker_button_1, SIGNAL(clicked())), this, SLOT(sticker());
    connect(ui->load_button, SIGNAL(clicked()), this, SLOT(add_image_button()));

    //rotate
    connect(tool_button_RT, SIGNAL(released()), this, SLOT(Hide_Bright_Slider()));//mia
    connect(tool_button_RT, SIGNAL(released()), this, SLOT(Hide_Saturation_Slider()));//mia
    connect(tool_button_RT, SIGNAL(released()), this, SLOT(Hide_Contrast_Slider()));//mia
    connect(tool_button_RT, SIGNAL(released()), this, SLOT(Hide_Blur_Slider()));//mia
    connect(tool_button_RT, SIGNAL(released()), this, SLOT(Hide_FilterColor_Button()));//mia
    connect(tool_button_RT, SIGNAL(released()), this, SLOT(Show_Rotate_Button()));//mia

    //crop
    connect(tool_button_CP, SIGNAL(released()), this, SLOT(Tool_crop()));//mia
    connect(tool_button_CP, SIGNAL(released()), this, SLOT(Hide_Bright_Slider()));//mia
    connect(tool_button_CP, SIGNAL(released()), this, SLOT(Hide_Saturation_Slider()));//mia
    connect(tool_button_CP, SIGNAL(released()), this, SLOT(Hide_Contrast_Slider()));//mia
    connect(tool_button_CP, SIGNAL(released()), this, SLOT(Hide_Blur_Slider()));//mia
    connect(tool_button_CP, SIGNAL(released()), this, SLOT(Hide_FilterColor_Button()));//mia
    connect(tool_button_CP, SIGNAL(released()), this, SLOT(Hide_Rotate_Button()));//mia



    //black_white
    connect(tool_button_BW, SIGNAL(released()), this, SLOT(Tool_blackwhite()));//mia
    connect(tool_button_BW, SIGNAL(released()), this, SLOT(Hide_Bright_Slider()));//mia
    connect(tool_button_BW, SIGNAL(released()), this, SLOT(Hide_Saturation_Slider()));//mia
    connect(tool_button_BW, SIGNAL(released()), this, SLOT(Hide_Contrast_Slider()));//mia
    connect(tool_button_BW, SIGNAL(released()), this, SLOT(Hide_Blur_Slider()));//mia
    connect(tool_button_BW, SIGNAL(released()), this, SLOT(Hide_FilterColor_Button()));//mia
    connect(tool_button_BW, SIGNAL(released()), this, SLOT(Hide_Rotate_Button()));//mia

    //Brightness
    connect(tool_button_BR, SIGNAL(released()), this, SLOT(Tool_brightness()));//mia
    connect(tool_button_BR, SIGNAL(released()), this, SLOT(Show_Bright_Slider()));//mia
    connect(tool_button_BR, SIGNAL(released()), this, SLOT(Hide_Contrast_Slider()));//mia
    connect(tool_button_BR, SIGNAL(released()), this, SLOT(Hide_Blur_Slider()));//mia
    connect(tool_button_BR, SIGNAL(released()), this, SLOT(Hide_Saturation_Slider()));//mia
    connect(tool_button_BR, SIGNAL(released()), this, SLOT(Hide_FilterColor_Button()));//mia
    connect(tool_button_BR, SIGNAL(released()), this, SLOT(Hide_Rotate_Button()));//mia

    //contrast
    connect(tool_button_CT, SIGNAL(released()), this, SLOT(Tool_contrast()));//mia
    connect(tool_button_CT, SIGNAL(released()), this, SLOT(Show_Contrast_Slider()));//mia
    connect(tool_button_CT, SIGNAL(released()), this, SLOT(Hide_Blur_Slider()));//mia
    connect(tool_button_CT, SIGNAL(released()), this, SLOT(Hide_Saturation_Slider()));//mia
    connect(tool_button_CT, SIGNAL(released()), this, SLOT(Hide_Bright_Slider()));//mia
    connect(tool_button_CT, SIGNAL(released()), this, SLOT(Hide_FilterColor_Button()));//mia
    connect(tool_button_CT, SIGNAL(released()), this, SLOT(Hide_Rotate_Button()));//mia

    //color filter
    connect(tool_button_FT, SIGNAL(released()), this, SLOT(Hide_Contrast_Slider()));//mia
    connect(tool_button_FT, SIGNAL(released()), this, SLOT(Hide_Blur_Slider()));//mia
    connect(tool_button_FT, SIGNAL(released()), this, SLOT(Hide_Saturation_Slider()));//mia
    connect(tool_button_FT, SIGNAL(released()), this,SLOT(Hide_Bright_Slider()));//mia
    connect(tool_button_FT, SIGNAL(released()), this, SLOT(Show_FilterColor_Button()));//mia
    connect(tool_button_FT, SIGNAL(released()), this, SLOT(Hide_Rotate_Button()));//mia

    //saturation
    connect(tool_button_ST, SIGNAL(released()), this, SLOT(Tool_saturation()));//mia
    connect(tool_button_ST, SIGNAL(released()), this, SLOT(Hide_Contrast_Slider()));//mia
    connect(tool_button_ST, SIGNAL(released()), this, SLOT(Hide_Blur_Slider()));//mia
    connect(tool_button_ST, SIGNAL(released()), this,SLOT(Hide_Bright_Slider()));//mia
    connect(tool_button_ST, SIGNAL(released()), this, SLOT(Hide_FilterColor_Button()));//mia
    connect(tool_button_ST, SIGNAL(released()), this, SLOT(Show_Saturation_Slider()));//mia
    connect(tool_button_ST, SIGNAL(released()), this, SLOT(Hide_Rotate_Button()));//mia

    //blur
    connect(tool_button_BL, SIGNAL(released()), this, SLOT(Tool_blur()));//mia
    connect(tool_button_BL, SIGNAL(released()), this, SLOT(Show_Blur_Slider()));//mia
    connect(tool_button_BL, SIGNAL(released()), this, SLOT(Hide_Contrast_Slider()));//mia
    connect(tool_button_BL, SIGNAL(released()), this, SLOT(Hide_Saturation_Slider()));//mia
    connect(tool_button_BL, SIGNAL(released()), this, SLOT(Hide_Bright_Slider()));//mia
    connect(tool_button_BL, SIGNAL(released()), this, SLOT(Hide_FilterColor_Button()));//mia
    connect(tool_button_BL, SIGNAL(released()), this, SLOT(Hide_Rotate_Button()));//mia



//    connect(small_mosaic, SIGNAL(released()), this, SLOT(Mosaic()));//mia
//    connect(median_mosaic, SIGNAL(released()), this, SLOT(Mosaic()));//mia
//    connect(large_mosaic, SIGNAL(released()), this, SLOT(Mosaic()));//mia

}

void main_window::setAddition(){
    //brightness
    ui->horizontalLayout->addWidget(spinBox1);
    ui->horizontalLayout->addWidget(slider1);
    spinBox1->setRange(0,100);
    slider1->setRange(0,100);
    connect(spinBox1, SIGNAL(valueChanged(int)), slider1, SLOT(setValue(int)));
    connect(slider1, SIGNAL(valueChanged(int)), spinBox1, SLOT(setValue(int)));
    spinBox1->setVisible(false);
    slider1->setVisible(false);
//    spinBox1->setValue(50);

    //contrast
    ui->horizontalLayout->addWidget(spinBox2);
    ui->horizontalLayout->addWidget(slider2);
    spinBox2->setRange(0,30);
    slider2->setRange(0,30);
    connect(spinBox2, SIGNAL(valueChanged(int)), slider2, SLOT(setValue(int)));
    connect(slider2, SIGNAL(valueChanged(int)), spinBox2, SLOT(setValue(int)));
    spinBox2->setVisible(false);
    slider2->setVisible(false);
//    spinBox1->setValue(0);

    //blur
    ui->horizontalLayout->addWidget(spinBox_blur);
    ui->horizontalLayout->addWidget(slider_blur);
    spinBox_blur->setRange(0,30);
    slider_blur->setRange(0,30);
    connect(spinBox_blur, SIGNAL(valueChanged(int)), slider_blur, SLOT(setValue(int)));
    connect(slider_blur, SIGNAL(valueChanged(int)), spinBox_blur, SLOT(setValue(int)));
    spinBox_blur->setVisible(false);
    slider_blur->setVisible(false);

    //saturation
    ui->horizontalLayout->addWidget(spinBox_saturation);
    ui->horizontalLayout->addWidget(slider_saturation);
    spinBox_saturation->setRange(-100,100);
    slider_saturation->setRange(-100,100);
    connect(spinBox_saturation, SIGNAL(valueChanged(int)), slider_saturation, SLOT(setValue(int)));
    connect(slider_saturation, SIGNAL(valueChanged(int)), spinBox_saturation, SLOT(setValue(int)));
    spinBox_saturation->setVisible(false);
    slider_saturation->setVisible(false);

    //rotate
    ui->horizontalLayout->addWidget(LeftRotate_Button);
    ui->horizontalLayout->addWidget(RightRotate_Button);
    ui->horizontalLayout->addWidget(HorizontalFlip_Button);
    ui->horizontalLayout->addWidget(VerticalFlip_Button);
    ui->horizontalLayout->addWidget(DiagonalFlip_Button);

    LeftRotate_Button->setIconSize(QSize(80,40));
    RightRotate_Button->setIconSize(QSize(80,40));
    HorizontalFlip_Button->setIconSize(QSize(80,40));
    DiagonalFlip_Button->setIconSize(QSize(80,40));
    VerticalFlip_Button->setIconSize(QSize(80,40));

    LeftRotate_Button->setText("Left Rotate");
    RightRotate_Button->setText("Right Rotate");
    HorizontalFlip_Button->setText("Horizontal Flip");
    VerticalFlip_Button->setText("Vertical Flip");
    DiagonalFlip_Button->setText("Diagonal Flip");

    LeftRotate_Button->setVisible(false);
    RightRotate_Button->setVisible(false);
    HorizontalFlip_Button->setVisible(false);
    VerticalFlip_Button->setVisible(false);
    DiagonalFlip_Button->setVisible(false);

    connect(LeftRotate_Button, SIGNAL(released()), this, SLOT(Tool_rotate()));
    connect(RightRotate_Button, SIGNAL(released()), this, SLOT(Tool_rotate()));
    connect(HorizontalFlip_Button, SIGNAL(released()), this, SLOT(Tool_rotate()));
    connect(VerticalFlip_Button, SIGNAL(released()), this, SLOT(Tool_rotate()));
    connect(DiagonalFlip_Button, SIGNAL(released()), this, SLOT(Tool_rotate()));


    //Color Filter
    ui->horizontalLayout->addWidget(cf_red);
    ui->horizontalLayout->addWidget(cf_orange);
    ui->horizontalLayout->addWidget(cf_yellow);
    ui->horizontalLayout->addWidget(cf_green);
    ui->horizontalLayout->addWidget(cf_blue);
    ui->horizontalLayout->addWidget(cf_purple);
    ui->horizontalLayout->addWidget(cf_pink);

    cf_red->setButtonPicture(red_Img);
    cf_red->setPressPicture(red_Img);
    cf_orange->setButtonPicture(orange_Img);
    cf_orange->setPressPicture(orange_Img);
    cf_yellow->setButtonPicture(yellow_Img);
    cf_yellow->setPressPicture(yellow_Img);
    cf_green->setButtonPicture(green_Img);
    cf_green->setPressPicture(green_Img);
    cf_blue->setButtonPicture(blue_Img);
    cf_blue->setPressPicture(blue_Img);
    cf_purple->setButtonPicture(purple_Img);
    cf_purple->setPressPicture(purple_Img);
    cf_pink->setButtonPicture(pink_Img);
    cf_pink->setPressPicture(pink_Img);

    cf_red->setButtonSize(40,40);
    cf_orange->setButtonSize(40,40);
    cf_yellow->setButtonSize(40,40);
    cf_green->setButtonSize(40,40);
    cf_blue->setButtonSize(40,40);
    cf_purple->setButtonSize(40,40);
    cf_pink->setButtonSize(40,40);

    cf_red->setVisible(false);
    cf_orange->setVisible(false);
    cf_yellow->setVisible(false);
    cf_green->setVisible(false);
    cf_blue->setVisible(false);
    cf_purple->setVisible(false);
    cf_pink->setVisible(false);

    connect(cf_red, SIGNAL(released()), this, SLOT(Tool_cf()));//mia
    connect(cf_orange, SIGNAL(released()), this, SLOT(Tool_cf()));//mia
    connect(cf_yellow, SIGNAL(released()), this, SLOT(Tool_cf()));//mia
    connect(cf_green, SIGNAL(released()), this, SLOT(Tool_cf()));//mia
    connect(cf_blue, SIGNAL(released()), this, SLOT(Tool_cf()));//mia
    connect(cf_purple, SIGNAL(released()), this, SLOT(Tool_cf()));//mia
    connect(cf_pink, SIGNAL(released()), this, SLOT(Tool_cf()));//mia


    //Sticker
    ui->horizontalLayout->addWidget(spinBox_sticker);
    ui->horizontalLayout->addWidget(slider_sticker);
    spinBox_sticker->setRange(0,30);
    slider_sticker->setRange(0,30);
    connect(spinBox_sticker, SIGNAL(valueChanged(int)), slider_sticker, SLOT(setValue(int)));
    connect(slider_sticker, SIGNAL(valueChanged(int)), spinBox_sticker, SLOT(setValue(int)));
    spinBox_sticker->setVisible(false);
    slider_sticker->setVisible(false);

    connect(sticker1, SIGNAL(released()), this, SLOT(Sticker_Add()));//mia
    connect(sticker2, SIGNAL(released()), this, SLOT(Sticker_Add()));//mia
    connect(sticker3, SIGNAL(released()), this, SLOT(Sticker_Add()));//mia
    connect(sticker4, SIGNAL(released()), this, SLOT(Sticker_Add()));//mia
    connect(sticker5, SIGNAL(released()), this, SLOT(Sticker_Add()));//mia
    connect(sticker6, SIGNAL(released()), this, SLOT(Sticker_Add()));//mia
    connect(sticker7, SIGNAL(released()), this, SLOT(Sticker_Add()));//mia

    //big eye
    ui->horizontalLayout->addWidget(spinBox_eye);
    ui->horizontalLayout->addWidget(slider_eye);
    spinBox_eye->setRange(0,10);
    slider_eye->setRange(0,10);
    connect(spinBox_eye, SIGNAL(valueChanged(int)), slider_eye, SLOT(setValue(int)));
    connect(slider_eye, SIGNAL(valueChanged(int)), spinBox_eye, SLOT(setValue(int)));
    spinBox_eye->setVisible(false);
    slider_eye->setVisible(false);

    //change background
    connect(red_back, SIGNAL(released()), this, SLOT(back_flag()));
    connect(white_back, SIGNAL(released()), this, SLOT(back_flag()));
    connect(blue_back, SIGNAL(released()), this, SLOT(back_flag()));

    //collage
    ui->horizontalLayout->addWidget(collage_h);
    ui->horizontalLayout->addWidget(collage_v);
    collage_h->setVisible(false);
    collage_v->setVisible(false);
    connect(collage_h, SIGNAL(released()), this, SLOT(Collage()));
    connect(collage_v, SIGNAL(released()), this, SLOT(Collage()));
    collage_h->setButtonSize(120,30);
    collage_v->setButtonSize(120,30);
    collage_h->setButtonPicture(collageH_Img);
    collage_h->setPressPicture(collageH_Img);
    collage_v->setButtonPicture(collageV_Img);
    collage_v->setPressPicture(collageV_Img);

    //undoredo save
    connect(Undo_Button, SIGNAL(released()), this, SLOT(UndoAction()));
    connect(Redo_Button, SIGNAL(released()), this, SLOT(RedoAction()));
    connect(TempSave_Button, SIGNAL(released()), this, SLOT(DoAction()));
    connect(Download_Button, SIGNAL(released()), this, SLOT(DownloadAction()));
    connect(Delete_Button, SIGNAL(released()), this, SLOT(DeleteAction()));
}

void main_window::changeWindowSize()
{
    if(notChange){
        setWindowState(Qt::WindowMaximized );
        changeSize_Button->setButtonPicture(small_Img);
        changeSize_Button->setPressPicture(small_PressImg);
    }else {
        setWindowState(Qt::WindowNoState );
        changeSize_Button->setButtonPicture(large_Img);
        changeSize_Button->setPressPicture(large_PressImg);
    }
    notChange = !notChange;
}

void main_window::MainClose(){
    close();
}

void main_window::setDicText(){
    ui->horizontalLayout_4->addWidget(dictum);
    QPalette p = dictum->palette();
    p.setBrush(QPalette::Base,QBrush(QColor(255,0,0,0)));
    dictum->setPalette(p);
    dictum->setTextColor(Qt::white);
    dictum->setText("To be different. To be inreplaceable!!!");
    dictum->setAlignment( Qt::AlignCenter );

}

void main_window::ButtonHide(){
    Tool_Button->setVisible(false);
    Filter_Button->setVisible(false);
    Sticker_Button->setVisible(false);
    Text_Button->setVisible(false);
    Bigeye_Button->setVisible(false);//mia
    Mosaic_Button->setVisible(false);
    Frame_Button->setVisible(false);
    Colorchange_Button->setVisible(false);
    Collage_Button->setVisible(false);
    //ui->load_button->setVisible(false);

}

//mia
void main_window::ButtonShow(){
    Tool_Button->setVisible(true);
    Filter_Button->setVisible(true);
    Sticker_Button->setVisible(true);
    Text_Button->setVisible(true);
    Bigeye_Button->setVisible(true);//mia
    Mosaic_Button->setVisible(true);
    Frame_Button->setVisible(true);
    Colorchange_Button->setVisible(true);
    Collage_Button->setVisible(true);
}


//Rose-----------------------------------------------------------------------------------
/*
 * when the load_button is clicked, it will ask the user to pick
 * an image and show it as a image button in the scroll area
 */
void main_window::add_image_button()
{
    int i = num;
    num++;

    QString filename(get_imagefile_name());
    std::cout<<filename.toStdString()<<std::endl;
    listButtons.push_back(new QToolButton());
    QImage* img = new QImage, * scaledimg = new QImage;

    if(! ( img->load(filename) ) )
    {
        QMessageBox::information(this,
                                 tr("error message"),
                                 tr("fail to load the image!"));
        delete img;
        return;
    }

    int Owidth = img->width(),Oheight = img->height();
    int Fwidth, Fheight;           //the new image size
    int Mul;

    if (Owidth >= Oheight) Mul = Owidth/55;
    else Mul = Oheight/55;

    Fwidth = Owidth/Mul;
    Fheight = Oheight/Mul;

    *scaledimg = img->scaled(Fwidth,Fheight,Qt::KeepAspectRatio);
    std::cout<<i<<std::endl;
    listButtons[i]->setFixedSize(QSize(55, 55));
    listButtons[i]->setIcon(QPixmap::fromImage(*img));
    listButtons[i]->setIconSize(QSize(Fwidth, Fheight));
    //listButtons[i]->setAttribute(Qt::WA_LayoutUsesWidgetRect);
    ui->top_layout->addWidget(listButtons[i],Qt::AlignCenter);


    connect(listButtons[i],SIGNAL(clicked()), buttonMapper, SLOT(map()));
    buttonMapper->setMapping(listButtons[i], filename);
    connect(buttonMapper, SIGNAL(mapped(QString)), this, SLOT(display_image(QString)));
}

void main_window::on_button_clicked(){
    std::cout<<"testing_button"<<std::endl;
}

/*
 * when the load_button is clicked,
 * this function will get the name of the image
 */
QString main_window::get_imagefile_name()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg *.jpeg)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString fileName = QFileDialog::getOpenFileName(this,
       tr("Open Images"), "/home/rpi/Desktop/Picture/Sample Pictures", tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));
    if (!fileName.isEmpty())
    {
        return fileName;
    }

}

/*
 * display the image on the canvas
 */

void main_window::display_image(QString filename)
{   //QString filename = "/Users/rose/Desktop/photo.jpeg";
    QImage* image = new QImage,* scaledimg = new QImage;
    if(! ( image->load(filename) ) )
            {
                QMessageBox::information(this,
                                         tr("error message"),
                                         tr("fail to load the image!"));
                qDebug()<<"error";
                delete image;
                return;
            }

    float Owidth = image->width(),Oheight = image->height();
    int Fwidth, Fheight;           //the new image size
    float Mul;

    if (Owidth >= Oheight) Mul = Owidth/500;
    else Mul = Oheight/500;

    Fwidth = floor(Owidth/Mul);
    Fheight = floor(Oheight/Mul);

    *scaledimg = image->scaled(500,500,Qt::KeepAspectRatio);
    *main_pic = *scaledimg;
    display_screen();

}

void main_window::display_screen(){
    GraphScreen *pic = new GraphScreen;
    main_screen = pic;
    pic->display(main_pic);
    ui->graphicsView->setScene(pic);
    ui->graphicsView->fitInView(pic->itemsBoundingRect(),Qt::KeepAspectRatio);
    ui->graphicsView->show();
}

//Rose-----------------------------------------------------------------------------------

//yh
/* Undo, redo, do */

bool main_window::CanUndo(){
    return (undostack_count > 0);
}

void main_window::DeleteAction(){
    main_pic = new QImage;
    display_screen();
}

void main_window::DownloadAction(){

    {
        QFileDialog fileDialog;
        QString str = fileDialog.getSaveFileName(this,"Open File","","Image File(*.jpg)");
        qDebug()<<str;
        if(str == "")
        {
            return;
        }
        QFile filename(str);
        //main_pic->save (str, 0, -1);
        Mat img2write = QImage2cvMat(*main_pic);
        //imshow("im",img2write);
        string path = str.toStdString();
        cout<<path;
        main_pic->save(&filename,"JPG");
        //imwrite(path.c_str(), img2write);
        //imwrite("/Users/rose/Desktop/hgggg.jpeg", img2write);
        QMessageBox::information(this,"Ssve File","Save File Success",QMessageBox::Ok);
        filename.close();
    }

}

void main_window::UndoAction(){
    if (!undo_stack.empty()){
        redostack_count++;
        *main_pic = undo_stack.top();
        QImage image_copy = main_pic->copy();
        qDebug()<<"undo"<<image_copy.format();
        redo_stack.push(image_copy);
        undo_stack.pop();
        undostack_count--;
        display_screen();
    }
}

void main_window::DoAction(){
    QImage image_copy = main_pic->copy();
    qDebug()<<"do"<<image_copy.format();
    undo_stack.push(image_copy);
}

void main_window::RedoAction(){
    if (!redo_stack.empty()){
    undostack_count++;
    *main_pic = redo_stack.top();
    QImage image_copy = main_pic->copy();
    undo_stack.push(image_copy);
    redo_stack.pop();
    redostack_count--;
    display_screen();
    }
}


//mia-----------------------------------------------------------------------------------
//Tool start++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void main_window::Set_Tool(){
    //QVBoxLayout *Vlayout = new QVBoxLayout(this);
    ui->scrollArea_Tool->setFixedSize(QSize(120, 300));
    ui->scrollAreaWidgetContents_Tool->setLayout(Vlayout_Tool);

    Vlayout_Tool->addWidget(tool_button_CP,0,Qt::AlignCenter);
    Vlayout_Tool->addWidget(tool_button_RT,0,Qt::AlignCenter);
    Vlayout_Tool->addWidget(tool_button_BW,0,Qt::AlignCenter);
    Vlayout_Tool->addWidget(tool_button_BR,0,Qt::AlignCenter);
    Vlayout_Tool->addWidget(tool_button_CT,0,Qt::AlignCenter);
    Vlayout_Tool->addWidget(tool_button_FT,0,Qt::AlignCenter);
    Vlayout_Tool->addWidget(tool_button_ST,0,Qt::AlignCenter);
    Vlayout_Tool->addWidget(tool_button_BL,0,Qt::AlignCenter);

    tool_button_CP->setButtonSize(90,80);
    tool_button_RT->setButtonSize(90,80);
    tool_button_BW->setButtonSize(90,80);
    tool_button_BR->setButtonSize(90,80);
    tool_button_CT->setButtonSize(90,80);
    tool_button_FT->setButtonSize(90,80);
    tool_button_ST->setButtonSize(90,80);
    tool_button_BL->setButtonSize(90,80);
    tool_button_CP->setButtonPicture(Crop_Img);
    tool_button_CP->setPressPicture(Crop_PressImg);
    tool_button_RT->setButtonPicture(Rotation_Img);
    tool_button_RT->setPressPicture(Rotation_PressImg);
    tool_button_BW->setButtonPicture(BlackWhite_Img);
    tool_button_BW->setPressPicture(BlackWhite_PressImg);
    tool_button_BR->setButtonPicture(Brightness_Img);
    tool_button_BR->setPressPicture(Brightness_PressImg);
    tool_button_CT->setButtonPicture(Contrast_Img);
    tool_button_CT->setPressPicture(Contrast_PressImg);
    tool_button_FT->setButtonPicture(ColorFilter_Img);
    tool_button_FT->setPressPicture(ColorFilter_PressImg);
    tool_button_ST->setButtonPicture(Saturation_Img);
    tool_button_ST->setPressPicture(Saturation_PressImg);
    tool_button_BL->setButtonPicture(Blur_Img);
    tool_button_BL->setPressPicture(Blur_PressImg);

    ui->scrollArea_Tool->setVisible(false);
}
//mia
void main_window:: Hide_Tool(){
    ui->scrollArea_Tool->setVisible(false);
}
//mia
void main_window:: Show_Tool(){
    ui->scrollArea_Tool->setVisible(true);
}

void main_window:: Hide_Bright_Slider(){
    spinBox1->setVisible(false);
    slider1->setVisible(false);
}
void main_window:: Show_Bright_Slider(){
    spinBox1->setVisible(true);
    slider1->setVisible(true);
}

void main_window:: Hide_Contrast_Slider(){
    spinBox2->setVisible(false);
    slider2->setVisible(false);
}
void main_window:: Show_Contrast_Slider(){
    spinBox2->setVisible(true);
    slider2->setVisible(true);
}

void main_window:: Hide_Blur_Slider(){
    spinBox_blur->setVisible(false);
    slider_blur->setVisible(false);
}
void main_window:: Show_Blur_Slider(){
    spinBox_blur->setVisible(true);
    slider_blur->setVisible(true);
}

void main_window:: Hide_Saturation_Slider(){
    spinBox_saturation->setVisible(false);
    slider_saturation->setVisible(false);
}

void main_window:: Show_Saturation_Slider(){
    spinBox_saturation->setVisible(true);
    slider_saturation->setVisible(true);
}

void main_window:: Hide_FilterColor_Button(){
    cf_red->setVisible(false);
    cf_orange->setVisible(false);
    cf_yellow->setVisible(false);
    cf_green->setVisible(false);
    cf_blue->setVisible(false);
    cf_purple->setVisible(false);
    cf_pink->setVisible(false);

}

void main_window:: Show_FilterColor_Button(){
    cf_red->setVisible(true);
    cf_orange->setVisible(true);
    cf_yellow->setVisible(true);
    cf_green->setVisible(true);
    cf_blue->setVisible(true);
    cf_purple->setVisible(true);
    cf_pink->setVisible(true);
}

void main_window:: Hide_Rotate_Button(){
    LeftRotate_Button->setVisible(false);
    RightRotate_Button->setVisible(false);
    HorizontalFlip_Button->setVisible(false);
    VerticalFlip_Button->setVisible(false);
    DiagonalFlip_Button->setVisible(false);
}

void main_window:: Show_Rotate_Button(){
    LeftRotate_Button->setVisible(true);
    RightRotate_Button->setVisible(true);
    HorizontalFlip_Button->setVisible(true);
    VerticalFlip_Button->setVisible(true);
    DiagonalFlip_Button->setVisible(true);
}

void main_window::Tool_blackwhite(){
    Mat img = QImage2cvMat(*main_pic);
    Mat bw_img = blackwhite(img);
    *main_pic = cvMat2QImage(bw_img);
    display_screen();
}

void main_window:: Tool_crop(){
    qDebug()<<"crop";
    Mat img = QImage2cvMat(*main_pic);
    //Mat cp_img = crop(img);
    main_screen->set_m_crop(true);
    //*main_pic = cvMat2QImage(cp_img);


}


void main_window::temp_brightness(){
    //imshow("mmm",Temp_*main_pic);
    int bright_value = spinBox1->value();
    Mat br_img =brightness(Temp_main_pic, bright_value);
    *main_pic=cvMat2QImage(br_img);
    display_screen();
    cout << "bbbbbbbbb:"<<endl;
    cout << bright_value<<endl;
}

void main_window::Tool_brightness(){
    spinBox1->disconnect(this);
    slider1->disconnect(this);
    cout << "stat brightness...."<<endl;
    Temp_main_pic = QImage2cvMat(*main_pic).clone();
    spinBox1->setValue(50);
    connect(spinBox1, SIGNAL(valueChanged(int)), this, SLOT(temp_brightness()));
    //connect(slider1, SIGNAL(sliderReleased()), this, SLOT(temp_brightness()));
}


void main_window::temp_contrast(){
    int contrast_value = spinBox2->value()+10;
    Mat contrast_img = contrast(Temp_main_pic, contrast_value);
    *main_pic=cvMat2QImage(contrast_img);
    display_screen();
    cout << "ccccccccccc:"<<endl;
    cout << contrast_value<<endl;
}

void main_window::Tool_contrast(){
      cout << "stat contrast...."<<endl;
    spinBox2->disconnect(this);
    slider2->disconnect(this);
    Temp_main_pic = QImage2cvMat(*main_pic).clone();
    spinBox2->setValue(0);
    connect(spinBox2, SIGNAL(valueChanged(int)), this, SLOT(temp_contrast()));
    //connect(slider2, SIGNAL(sliderReleased()), this, SLOT(temp_contrast()));
}

void main_window::temp_blur(){
    int blur_value = spinBox_blur->value();
    Mat blur_img = median_blur(Temp_main_pic, blur_value);
    //Mat blur_img = Temp_main_pic;
    *main_pic=cvMat2QImage(blur_img);
    display_screen();
    cout << "blur:"<<endl;
    cout << blur_value<<endl;
}

void main_window::Tool_blur(){
    cout << "stat blur...."<<endl;
    spinBox_blur->disconnect(this);
    slider_blur->disconnect(this);
    Temp_main_pic = QImage2cvMat(*main_pic).clone();
    spinBox_blur->setValue(0);
    connect(spinBox_blur, SIGNAL(valueChanged(int)), this, SLOT(temp_blur()));
}

void main_window::temp_saturation(){
    int saturation_value = spinBox_saturation->value();
    Mat saturation_img = saturation(Temp_main_pic, saturation_value);
    *main_pic=cvMat2QImage(saturation_img);
    display_screen();
    cout << "saturation:"<<endl;
    cout << saturation_value<<endl;
}

void main_window::Tool_saturation(){
    cout << "stat saturation...."<<endl;
    spinBox_saturation->disconnect(this);
    slider_saturation->disconnect(this);
    Temp_main_pic = QImage2cvMat(*main_pic).clone();
    spinBox_saturation->setValue(0);
    connect(spinBox_saturation, SIGNAL(valueChanged(int)), this, SLOT(temp_saturation()));
    //connect(slider2, SIGNAL(sliderReleased()), this, SLOT(temp_contrast()));
}

void main_window::Tool_rotate(){
     Mat img = QImage2cvMat(*main_pic);
     int mode=-1;
     if (sender()==LeftRotate_Button){
         mode=1;
         cout<< "left rotate"<<endl;
     }
     else if (sender()==RightRotate_Button){
         mode=2;
         cout<< "right rotate"<<endl;
     }
     else if (sender()==HorizontalFlip_Button){
         mode=3;
         cout<< "Horizontal Flip"<<endl;
     }
     else if (sender()==VerticalFlip_Button){
         mode=4;
         cout<< "Vertical Flip"<<endl;
     }
     else if (sender()==DiagonalFlip_Button){
         mode=5;
         cout<< "Diagonal Flip"<<endl;
     }
     Mat rotate_img = rotate(img, mode);
     *main_pic = cvMat2QImage(rotate_img);
    display_screen();
}



void main_window::Tool_cf(){
    Mat img = QImage2cvMat(*main_pic);
    int mode = 0;
    if (sender()==cf_red){
        mode=1;
        cout<< "red mode"<<endl;
    }
    else if (sender()==cf_orange){
        mode=2;
        cout<< "orange mode"<<endl;
    }
    else if (sender()==cf_yellow){
        mode=3;
        cout<< "yellow mode"<<endl;
    }
    else if (sender()==cf_green){
        mode=4;
        cout<< "green mode"<<endl;
    }
    else if (sender()==cf_blue){
        mode=5;
        cout<< "blue mode"<<endl;
    }
    else if (sender()==cf_purple){
        mode=6;
        cout<< "purple mode"<<endl;
    }
    else if (sender()==cf_pink){
        mode=7;
        cout<< "pink mode"<<endl;
    }
    Mat cf_img = filter_color(img, mode);
    *main_pic = cvMat2QImage(cf_img);

    display_screen();
}
//Tool end++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//Sticker start+++++++++++++++++++++++++++++++++++++++++++++++++++++
void main_window::Set_Sticker(){
    ui->scrollArea_Sticker->setFixedSize(QSize(120, 300));
    ui->scrollAreaWidgetContents_Sticker->setLayout(Vlayout_Sticker);

    QPalette pa;
    pa.setColor(QPalette::Text,Qt::white);

    Vlayout_Sticker->addWidget(basic_sticker_label,Qt::AlignCenter);
    basic_sticker_label->setText("Basic");
    basic_sticker_label->setAlignment(Qt::AlignCenter);
    basic_sticker_label->setStyleSheet("background:transparent");
    basic_sticker_label->setFont(QFont("Timers" , 18 ,  QFont::Bold));
    basic_sticker_label->setPalette(pa);

//    Vlayout_Sticker->addWidget(sticker1,0,Qt::AlignCenter);
//    Vlayout_Sticker->addWidget(sticker2,0,Qt::AlignCenter);
//    Vlayout_Sticker->addWidget(sticker3,0,Qt::AlignCenter);
//    Vlayout_Sticker->addWidget(sticker4,0,Qt::AlignCenter);
//    Vlayout_Sticker->addWidget(sticker5,0,Qt::AlignCenter);
//    Vlayout_Sticker->addWidget(sticker6,0,Qt::AlignCenter);
//    Vlayout_Sticker->addWidget(sticker7,0,Qt::AlignCenter);
    Vlayout_Sticker->addWidget(sticker1,Qt::AlignCenter);
    Vlayout_Sticker->addWidget(sticker2,Qt::AlignCenter);
    Vlayout_Sticker->addWidget(sticker3,Qt::AlignCenter);
    Vlayout_Sticker->addWidget(sticker4,Qt::AlignCenter);
    Vlayout_Sticker->addWidget(sticker5,Qt::AlignCenter);
    Vlayout_Sticker->addWidget(sticker6,Qt::AlignCenter);

    Vlayout_Sticker->addWidget(advanced_sticker_label,Qt::AlignCenter);
    advanced_sticker_label->setText("Advanced");
    advanced_sticker_label->setAlignment(Qt::AlignCenter);
    advanced_sticker_label->setStyleSheet("background:transparent");
    advanced_sticker_label->setFont(QFont("Timers" , 18 ,  QFont::Bold));
    advanced_sticker_label->setPalette(pa);
    Vlayout_Sticker->addWidget(sticker7,Qt::AlignCenter);


    sticker1->setButtonSize(90,90);
    sticker2->setButtonSize(90,90);
    sticker3->setButtonSize(90,90);
    sticker4->setButtonSize(90,90);
    sticker5->setButtonSize(90,90);
    sticker6->setButtonSize(90,90);
    sticker7->setButtonSize(90,90);
//    sticker1->setButtonSize(80,90);
//    sticker2->setButtonSize(90,70);
//    sticker3->setButtonSize(70,70);
//    sticker4->setButtonSize(70,70);
//    sticker5->setButtonSize(70,70);
//    sticker6->setButtonSize(70,70);
//    sticker7->setButtonSize(70,70);

    sticker1->setButtonPicture(Sticker1_Img);
    sticker1->setPressPicture(Sticker1_Img);
    sticker2->setButtonPicture(Sticker2_Img);
    sticker2->setPressPicture(Sticker2_Img);
    sticker3->setButtonPicture(Sticker3_Img);
    sticker3->setPressPicture(Sticker3_Img);
    sticker4->setButtonPicture(Sticker4_Img);
    sticker4->setPressPicture(Sticker4_Img);
    sticker5->setButtonPicture(Sticker5_Img);
    sticker5->setPressPicture(Sticker5_Img);
    sticker6->setButtonPicture(Sticker6_Img);
    sticker6->setPressPicture(Sticker6_Img);
    sticker7->setButtonPicture(Sticker7_Img);
    sticker7->setPressPicture(Sticker7_Img);


    ui->scrollArea_Sticker->setVisible(false);
}

void main_window:: Hide_Sticker(){
    ui->scrollArea_Sticker->setVisible(false);
    spinBox_sticker->setVisible(false);
    slider_sticker->setVisible(false);
}

void main_window:: Show_Sticker(){
    ui->scrollArea_Sticker->setVisible(true);
    spinBox_sticker->setValue(15);    //贴纸大小初始值
    spinBox_sticker->setVisible(true);
    slider_sticker->setVisible(true);
}

void main_window::Sticker_Add(){

    if (sender()==sticker1){
        //sticker address = "1"
        main_screen->select_sticker(1);
        main_screen->set_m_addsticker(true);
        cout<< "choose sticker1"<<endl;
    }
    else if (sender()==sticker2){
        //sticker address = "2"
        main_screen->select_sticker(2);
        main_screen->set_m_addsticker(true);
        cout<< "choose sticker2"<<endl;
    }
    else if (sender()==sticker3){
        main_screen->select_sticker(3);
        main_screen->set_m_addsticker(true);
        //sticker address = "1"
        cout<< "choose sticker3"<<endl;
    }
    else if (sender()==sticker4){
        main_screen->select_sticker(4);
        main_screen->set_m_addsticker(true);
        //sticker address = "1"
        cout<< "choose sticker4"<<endl;
    }
    else if (sender()==sticker5){
        //sticker address = "1"
        main_screen->select_sticker(5);
        main_screen->set_m_addsticker(true);
        cout<< "choose sticker5"<<endl;
    }
    else if (sender()==sticker6){
        main_screen->select_sticker(6);
        main_screen->set_m_addsticker(true);
        //sticker address = "1"
        cout<< "choose sticker6"<<endl;
    }
    else if (sender()==sticker7){
        main_screen->select_sticker(7);
        main_screen->set_m_addsticker(true);
        //sticker address = "1"
        cout<< "choose sticker7"<<endl;
    }

    spinBox_sticker->disconnect(this);
    slider_sticker->disconnect(this);
    cout << "start add stickers...."<<endl;
    Temp_main_pic = QImage2cvMat(*main_pic); //暂存原始图片
//    spinBox_sticker->setValue(15);    //贴纸大小初始值
    connect(spinBox_sticker, SIGNAL(valueChanged(int)), this, SLOT(temp_StickerAdd()));

}
void main_window::temp_StickerAdd(){
    int stickerSize_value = spinBox_sticker->value();
        main_screen->set_sticker_size(stickerSize_value);

        cout << "Add one sticker with size:"<<endl;
        cout << stickerSize_value<<endl;
}


//void Hide_Sticker_Slider(){
//    spinBox_sticker->setVisible(false);
//    slider_sticker->setVisible(false);
//}

//void Show_Sticker_Slider(){
//    spinBox_sticker->setVisible(true);
//    slider_sticker->setVisible(true);
//}


//Sticker end+++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Big eye start+++++++++++++++++++++++++++++++++++++++++++++++++++++
void main_window:: Show_eyeSlider(){
    spinBox_eye->setVisible(true);
    spinBox_eye->setValue(5);
    slider_eye->setVisible(true);
}
void main_window:: Hide_eyeSlider(){
    spinBox_eye->setVisible(false);
    slider_eye->setVisible(false);
}

void main_window::Big_eye(){
    spinBox_eye->disconnect(this);
    slider_eye->disconnect(this);
    cout << "start big eye...."<<endl;
    Temp_main_pic = QImage2cvMat(*main_pic).clone(); //暂存原始图片
    connect(spinBox_eye, SIGNAL(valueChanged(int)), this, SLOT(temp_BigEye()));

}

void main_window::temp_BigEye(){
    float eyeSize_value = (float(spinBox_eye->value()))/100+1;
    qDebug()<<"eyeSize_value"<<eyeSize_value;
    Mat bigEye_img; //加上一个贴纸后的图
    bigEye_img = eyesBigger(Temp_main_pic, eyeSize_value);   //把这个bigeye()改成你要调用的加贴纸函数,去掉上一行
    *main_pic=cvMat2QImage(bigEye_img);
    display_screen();
    cout << "eye size:"<<endl;
    cout << eyeSize_value<<endl;
}

//Big eye end+++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Mosaic start+++++++++++++++++++++++++++++++++++++++++++++++++++++++
void main_window:: Set_Mosaic(){
    ui->scrollArea_Mosaic->setFixedSize(QSize(120, 300));
    ui->scrollAreaWidgetContents_Mosaic->setLayout(Vlayout_Mosaic);
    Vlayout_Mosaic->addWidget(small_mosaic);
    Vlayout_Mosaic->addWidget(median_mosaic);
    Vlayout_Mosaic->addWidget(large_mosaic);
    small_mosaic->setButtonSize(90,80);
    median_mosaic->setButtonSize(90,80);
    large_mosaic->setButtonSize(90,80);
    small_mosaic->setButtonPicture(smallMosaic_Img);
    small_mosaic->setPressPicture(smallMosaic_Img);
    median_mosaic->setButtonPicture(medianMosaic_Img);
    median_mosaic->setPressPicture(medianMosaic_Img);
    large_mosaic->setButtonPicture(largeMosaic_Img);
    large_mosaic->setPressPicture(largeMosaic_Img);
    ui->scrollArea_Mosaic->setVisible(false);

    connect(small_mosaic, SIGNAL(released()), this, SLOT(Mosaic()));//mia
    connect(median_mosaic, SIGNAL(released()), this, SLOT(Mosaic()));//mia
    connect(large_mosaic, SIGNAL(released()), this, SLOT(Mosaic()));//mia
}

    void main_window:: Hide_Mosaic(){
        ui->scrollArea_Mosaic->setVisible(false);
    }

    void main_window:: Show_Mosaic(){
        ui->scrollArea_Mosaic->setVisible(true);
    }
    void main_window::Mosaic(){
        qDebug()<<"Mosaic()";
        int size;
        main_screen->set_m_mosaic(true);
        cout << "start use mosaic...."<<endl;
        if (sender()==small_mosaic){
            size = 3;
            cout<< "choose small mosaic"<<endl;
        }
        else if (sender()==median_mosaic){
            size = 10;
            cout<< "choose median mosain"<<endl;
        }
        else if (sender()==large_mosaic){
            size = 20;
            cout<< "choose large mosaic"<<endl;
        }

        main_screen->set_mosaic_size(size);

        //Mat img = QImage2cvMat(*main_pic); //暂存原始图片

        //Mat cf_img = main_screen->mosaic(img, size);
        //*main_pic = cvMat2QImage(cf_img);
        //display_screen();

    }


//Mosaic end+++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//Frame start+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    void main_window:: Set_Frame(){
        ui->scrollArea_Frame->setFixedSize(QSize(120, 300));
        ui->scrollAreaWidgetContents_Frame->setLayout(Vlayout_Frame);
        Vlayout_Frame->addWidget(frame1);
        Vlayout_Frame->addWidget(frame2);
        Vlayout_Frame->addWidget(frame3);
        Vlayout_Frame->addWidget(frame4);
        Vlayout_Frame->addWidget(frame5);
        Vlayout_Frame->addWidget(frame6);
        Vlayout_Frame->addWidget(frame7);
        Vlayout_Frame->addWidget(frame8);
        frame1->setButtonSize(90,80);
        frame2->setButtonSize(90,80);
        frame3->setButtonSize(90,80);
        frame4->setButtonSize(90,80);
        frame5->setButtonSize(90,80);
        frame6->setButtonSize(90,80);
        frame7->setButtonSize(90,80);
        frame8->setButtonSize(90,80);
        frame1->setButtonPicture(fr_Black_Img);
        frame1->setPressPicture(fr_Black_Img);
        frame2->setButtonPicture(fr_White_Img);
        frame2->setPressPicture(fr_White_Img);
        frame3->setButtonPicture(fr_Cocoa_Img);
        frame3->setPressPicture(fr_Cocoa_Img);
        frame4->setButtonPicture(fr_Heart_Img);
        frame4->setPressPicture(fr_Heart_Img);
        frame5->setButtonPicture(fr_Vintage_Img);
        frame5->setPressPicture(fr_Vintage_Img);
        frame6->setButtonPicture(fr_Gaudy_Img);
        frame6->setPressPicture(fr_Gaudy_Img);
        frame7->setButtonPicture(fr_Dynamic_Img);
        frame7->setPressPicture(fr_Dynamic_Img);
        frame8->setButtonPicture(fr_Mirror_Img);
        frame8->setPressPicture(fr_Mirror_Img);
        ui->scrollArea_Frame->setVisible(false);
        connect(frame1, SIGNAL(released()), this, SLOT(Frame()));//mia
        connect(frame2, SIGNAL(released()), this, SLOT(Frame()));//mia
        connect(frame3, SIGNAL(released()), this, SLOT(Frame()));//mia
        connect(frame4, SIGNAL(released()), this, SLOT(Frame()));//mia
        connect(frame5, SIGNAL(released()), this, SLOT(Frame()));//mia
        connect(frame6, SIGNAL(released()), this, SLOT(Frame()));//mia
        connect(frame7, SIGNAL(released()), this, SLOT(Frame()));//mia
        connect(frame8, SIGNAL(released()), this, SLOT(Frame()));//mia
    }

        void main_window:: Hide_Frame(){
            ui->scrollArea_Frame->setVisible(false);
        }

        void main_window:: Show_Frame(){
            ui->scrollArea_Frame->setVisible(true);
        }
        void main_window::Frame(){
            Mat img = QImage2cvMat(*main_pic).clone();
            Mat FrameImg;
            cout << "start use frame...."<<endl;
            if (sender()==frame1){
                FrameImg = addframe_cv(img,3);
                cout<< "black"<<endl;
            }
            else if (sender()==frame2){
                FrameImg =addframe_cv(img,4);

                cout<< "choose frame2"<<endl;
            }
            else if (sender()==frame3){

                FrameImg = addframe(img,3);

                cout<< "choose frame3"<<endl;
            }
            else if (sender()==frame4){
                FrameImg =addframe(img,1);

                cout<< "choose heart"<<endl;
            }
            else if (sender()==frame5){
                FrameImg =addframe(img,4);

                cout<< "choose frame5"<<endl;
            }
            else if (sender()==frame6){
                FrameImg =addframe(img,2);

                cout<< "choose frame6"<<endl;
            }
            else if (sender()==frame7){
               FrameImg = addframe_cv(img,1);

                cout<< "choose frame7"<<endl;
            }
            else if (sender()==frame8){
                FrameImg = addframe_cv(img,2);

                cout<< "choose frame8"<<endl;
            }

            *main_pic = cvMat2QImage(FrameImg);
            display_screen();
        }


//Frame end+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//Filter start++++++++++++++++++++++++++++++++++++++++++++++++++++++
void main_window:: Set_Filter(){
    //QVBoxLayout *Vlayout = new QVBoxLayout(this);
    ui->scrollArea_Filter->setFixedSize(QSize(120, 300));
    ui->scrollAreaWidgetContents_Filter->setLayout(Vlayout_Filter);

//    QFont ft;
//    ft.setPointSize(18);
    QPalette pa;
    pa.setColor(QPalette::Text,Qt::white);

    Vlayout_Filter->addWidget(basic_filter_label,Qt::AlignCenter);
    basic_filter_label->setText("Basic");
    basic_filter_label->setAlignment(Qt::AlignCenter);
    //basic_filter_label->setStyleSheet("color:white");//文本颜色
    basic_filter_label->setStyleSheet("background:transparent");
    basic_filter_label->setFont(QFont("Timers" , 18 ,  QFont::Bold));
//    basic_filter_label->setFont(ft);
    basic_filter_label->setPalette(pa);
    Vlayout_Filter->addWidget(filter_button_old,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_comic,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_pepper,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_grain,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_exposure,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_magic,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_silence,Qt::AlignCenter);

    filter_button_old->setButtonSize(90,80);
    filter_button_comic->setButtonSize(90,80);
    filter_button_pepper->setButtonSize(90,80);
    filter_button_grain->setButtonSize(90,80);
    filter_button_exposure->setButtonSize(90,80);
    filter_button_magic->setButtonSize(90,80);
    filter_button_silence->setButtonSize(90,80);

    filter_button_old->setButtonPicture(fOld_Img);
    filter_button_old->setPressPicture(fOld_Img);

    filter_button_comic->setButtonPicture(fComic_Img);
    filter_button_comic->setPressPicture(fComic_Img);

    filter_button_pepper->setButtonPicture(fPepper_Img);
    filter_button_pepper->setPressPicture(fPepper_Img);

    filter_button_grain->setButtonPicture(fGrain_Img);
    filter_button_grain->setPressPicture(fGrain_Img);

    filter_button_exposure->setButtonPicture(fExposure_Img);
    filter_button_exposure->setPressPicture(fExposure_Img);

    filter_button_magic->setButtonPicture(fMagic_Img);
    filter_button_magic->setPressPicture(fMagic_Img);

    filter_button_silence->setButtonPicture(fSilence_Img);
    filter_button_silence->setPressPicture(fSilence_Img);

    Vlayout_Filter->addWidget(advanced_filter_label,Qt::AlignCenter);
    advanced_filter_label->setText("Advanced");
    advanced_filter_label->setAlignment(Qt::AlignCenter);
    //advanced_filter_label->setStyleSheet("color:white");//文本颜色
    advanced_filter_label->setStyleSheet("background:transparent");
    advanced_filter_label->setFont(QFont("Timers" , 18 ,  QFont::Bold));
//    advanced_filter_label->setFont(ft);
    advanced_filter_label->setPalette(pa);

    Vlayout_Filter->addWidget(filter_button_beauty,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_highlight,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_softlight,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_diffuse,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_expand,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_shrink,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_strike,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_volution,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_wave,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_sketch,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_neon,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_carve,Qt::AlignCenter);
    Vlayout_Filter->addWidget(filter_button_embossment,Qt::AlignCenter);

    filter_button_beauty->setButtonSize(90,80);
    filter_button_highlight->setButtonSize(90,80);
    filter_button_softlight->setButtonSize(90,80);
    filter_button_diffuse->setButtonSize(90,80);
    filter_button_expand->setButtonSize(90,80);
    filter_button_shrink->setButtonSize(90,80);
    filter_button_strike->setButtonSize(90,80);
    filter_button_volution->setButtonSize(90,80);
    filter_button_wave->setButtonSize(90,80);
    filter_button_sketch->setButtonSize(90,80);
    filter_button_neon->setButtonSize(90,80);
    filter_button_carve->setButtonSize(90,80);
    filter_button_embossment->setButtonSize(90,80);

    filter_button_beauty->setButtonPicture(fBeauty_Img);
    filter_button_beauty->setPressPicture(fBeauty_Img);

    filter_button_highlight->setButtonPicture(fHighlight_Img);
    filter_button_highlight->setPressPicture(fHighlight_Img);

    filter_button_softlight->setButtonPicture(fSoftlight_Img);
    filter_button_softlight->setPressPicture(fSoftlight_Img);

    filter_button_diffuse->setButtonPicture(fDiffuse_Img);
    filter_button_diffuse->setPressPicture(fDiffuse_Img);

    filter_button_expand->setButtonPicture(fExpand_Img);
    filter_button_expand->setPressPicture(fExpand_Img);

    filter_button_shrink->setButtonPicture(fShrink_Img);
    filter_button_shrink->setPressPicture(fShrink_Img);

    filter_button_strike->setButtonPicture(fStrike_Img);
    filter_button_strike->setPressPicture(fStrike_Img);

    filter_button_volution->setButtonPicture(fVolution_Img);
    filter_button_volution->setPressPicture(fVolution_Img);

    filter_button_wave->setButtonPicture(fWave_Img);
    filter_button_wave->setPressPicture(fWave_Img);

    filter_button_sketch->setButtonPicture(fSketch_Img);
    filter_button_sketch->setPressPicture(fSketch_Img);

    filter_button_neon->setButtonPicture(fNeon_Img);
    filter_button_neon->setPressPicture(fNeon_Img);

    filter_button_carve->setButtonPicture(fCarve_Img);
    filter_button_carve->setPressPicture(fCarve_Img);

    filter_button_embossment->setButtonPicture(fEmbossment_Img);
    filter_button_embossment->setPressPicture(fEmbossment_Img);

    ui->scrollArea_Filter->setVisible(false);
    connect(filter_button_old, SIGNAL(released()), this, SLOT(Filter()));//mia
    connect(filter_button_comic, SIGNAL(released()), this, SLOT(Filter()));//mia
    connect(filter_button_exposure, SIGNAL(released()), this, SLOT(Filter()));//mia
    connect(filter_button_magic, SIGNAL(released()), this, SLOT(Filter()));//mia
    connect(filter_button_silence, SIGNAL(released()), this, SLOT(Filter()));//mia
    connect(filter_button_beauty, SIGNAL(released()), this, SLOT(Filter()));//mia
    connect(filter_button_highlight, SIGNAL(released()), this, SLOT(Filter()));//mia
    connect(filter_button_softlight, SIGNAL(released()), this, SLOT(Filter()));//mia
    connect(filter_button_diffuse, SIGNAL(released()), this, SLOT(Filter()));//mia
    connect(filter_button_expand, SIGNAL(released()), this, SLOT(Filter()));//mia
    connect(filter_button_shrink, SIGNAL(released()), this, SLOT(Filter()));//mia
    connect(filter_button_strike, SIGNAL(released()), this, SLOT(Filter()));//mia
    connect(filter_button_volution, SIGNAL(released()), this, SLOT(Filter()));//mia
    connect(filter_button_wave, SIGNAL(released()), this, SLOT(Filter()));//mia
    connect(filter_button_sketch, SIGNAL(released()), this, SLOT(Filter()));//mia
    connect(filter_button_neon, SIGNAL(released()), this, SLOT(Filter()));//mia
    connect(filter_button_carve, SIGNAL(released()), this, SLOT(Filter()));//mia
    connect(filter_button_embossment, SIGNAL(released()), this, SLOT(Filter()));//mia

    connect(filter_button_pepper, SIGNAL(released()), this, SLOT(Filter()));//mia
    connect(filter_button_grain, SIGNAL(released()), this, SLOT(Filter()));//mia

}
//mia
void main_window:: Hide_Filter(){
    ui->scrollArea_Filter->setVisible(false);
}
//mia
void main_window:: Show_Filter(){
    ui->scrollArea_Filter->setVisible(true);
}

//background start+++++++++++++++++++++++++++++++++++++++++++++++++++++
void main_window:: Set_background(){
    //background
    ui->scrollArea_Background->setFixedSize(QSize(120, 300));
    ui->scrollAreaWidgetContents_Background->setLayout(Vlayout_Background);

    Vlayout_Background->addWidget(red_back);
    Vlayout_Background->addWidget(blue_back);
    Vlayout_Background->addWidget(white_back);
    red_back->setButtonPicture(red_Img);
    red_back->setPressPicture(red_Img);
    blue_back->setButtonPicture(blue_Img);
    blue_back->setPressPicture(blue_Img);
    white_back->setButtonPicture(white_Img);
    white_back->setPressPicture(white_Img);
    ui->scrollArea_Background->setVisible(false);

}
void main_window:: Hide_background(){

    ui->scrollArea_Background->setVisible(false);

}

void main_window:: Show_background(){

    ui->scrollArea_Background->setVisible(true);

}

void main_window::back_flag(){
    Mat img = QImage2cvMat(*main_pic);
    int mode = 0;
    if (sender()==red_back){
        mode=1;
        cout<< "red mode"<<endl;
    }
    else if (sender()==white_back){
        mode=0;
        cout<< "white mode"<<endl;
    }
    else if (sender()==blue_back){
        mode=2;
        cout<< "blue mode"<<endl;
    }
    Mat back_img = changeBackground(img, mode);
    *main_pic = cvMat2QImage(back_img);

    display_screen();
}
//background end+++++++++++++++++++++++++++++++++++++++++++++++++++++++


void main_window:: Filter(){
     Mat img = QImage2cvMat(*main_pic).clone();
     Mat FilterImg;
    if (sender()==filter_button_old){
        FilterImg = old(img);
        cout<< "old"<<endl;
    }
    else if (sender()==filter_button_magic){
        FilterImg = magic(img);
        cout<< "magic"<<endl;
    }
    else if (sender()==filter_button_pepper){
        FilterImg = noise(img,0);
        cout<< "pepper"<<endl;
    }
    else if (sender()==filter_button_grain){
        FilterImg = noise(img,1);
        cout<< "grain"<<endl;
    }
    else if (sender()==filter_button_exposure){
        FilterImg = exposure(img);
        cout<< "exposure"<<endl;
    }
    else if (sender()==filter_button_comic){
        FilterImg = comic(img);
        cout<< "comic"<<endl;
    }
    else if (sender()==filter_button_silence){
        FilterImg = silence(img);
        cout<< "silence"<<endl;
    }
    else if (sender()==filter_button_beauty){
        FilterImg = beauty(img);
        cout<< "beauty"<<endl;
    }
    else if (sender()==filter_button_highlight){
        FilterImg = highLight(img);
        cout<< "highlight"<<endl;
    }
    else if (sender()==filter_button_softlight){
        FilterImg = softLight(img);
        cout<< "softlight"<<endl;
    }
    else if (sender()==filter_button_diffuse){
        FilterImg = diffuse(img);
        cout<< "diffuse"<<endl;
    }
    else if (sender()==filter_button_expand){
        FilterImg = expand(img);
        cout<< "expand"<<endl;
    }
    else if (sender()==filter_button_shrink){
        FilterImg = shrink(img);
        cout<< "shrink"<<endl;
    }
    else if (sender()==filter_button_strike){
        FilterImg = strike(img);
        cout<< "strike"<<endl;
    }
    else if (sender()==filter_button_volution){
        FilterImg = volution(img);
        cout<< "volution"<<endl;
    }
    else if (sender()==filter_button_wave){
        FilterImg = wave(img);
        cout<< "wave"<<endl;
    }
    else if (sender()==filter_button_carve){
        FilterImg = carve(img);
        cout<< "carve"<<endl;
    }
    else if (sender()==filter_button_sketch){
        FilterImg = sketch(img);
        cout<< "sketch"<<endl;
    }
    else if (sender()==filter_button_neon){
        FilterImg = neon(img);
        cout<< "neon"<<endl;
    }
    else if (sender()==filter_button_embossment){
        FilterImg = embossment(img);
        cout<< "embossment"<<endl;
    }

    *main_pic = cvMat2QImage(FilterImg);
    display_screen();

}
//Filter end+++++++++++++++++++++++++++++++++++++++++++++++++++++++


//Collage start+++++++++++++++++++++++++++++++++++++++++++++++++++++
void main_window:: Show_collageButton(){
    collage_h->setVisible(true);
    collage_v->setVisible(true);
}
void main_window:: Hide_collageButton(){
    collage_h->setVisible(false);
    collage_v->setVisible(false);
}

void main_window::Collage(){
    Mat img = QImage2cvMat(*main_pic).clone();
    Mat CollageImg;
   if (sender()==collage_h){
       //CollageImg = collage(img,horizontal);
       CollageImg=img; //删掉
       cout<< "horizontal collage"<<endl;
   }
   else if (sender()==collage_v){
       //CollageImg = collage(img,vertical);
       CollageImg=img; //删掉
       cout<< "vertical"<<endl;
   }
   *main_pic = cvMat2QImage(CollageImg);
    display_screen();
}


//Collage end+++++++++++++++++++++++++++++++++++++++++++++++++++++++




//Mouse ===================================================================
void main_window::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bPressed)
        move(event->pos() - m_point + pos());
}

void main_window::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_bPressed = false;
}

void main_window::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_bPressed = true;
        m_point = event->pos();
    }
}


//format change between QImage & cvMat
Mat QImage2cvMat(QImage image) {
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
        qDebug()<<"cvt CV_8UC3";
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    }
    qDebug() <<"Qimage: "<< image.format()<<"mat: "<<mat.type();
    return mat;
}

QImage cvMat2QImage(const cv::Mat& mat)
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

