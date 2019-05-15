#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

// mode 0 you zao dian.....!
Mat blackwhite(Mat org){
    //Mat org = imread(address);
    Mat dst(org.size(), CV_8UC3); //Mat float and channel 3.
    org.convertTo(dst, CV_8UC3);

    Mat R(org.size(), CV_8UC1);
    Mat G(org.size(), CV_8UC1);
    Mat B(org.size(), CV_8UC1);
    Mat I(org.size(), CV_8UC1);
    Mat BW_out(org.size(), CV_8UC1);

    Mat rgb[] = {B, G, R}; // The order of channels.
    cv::split(dst, rgb); //Split channels.

    I = R+G+B;

    for(int i = 0; i < I.rows; i++)
    {
        for(int j = 0; j < I.cols; j++) // for each pixel
        {

          BW_out.at<uchar>(i,j) = 0.2989*R.at<uchar>(i,j) + 0.5870*G.at<uchar>(i,j) + 0.1140*B.at<uchar>(i,j);

        }
    }
//    BW_out=BW_out/255;

    return BW_out;
//    imshow("black-white", BW_out);
//    //imwrite("out.jpg", BW_out*255);
//    waitKey();
//    cout<<"All is well."<<endl;
}

