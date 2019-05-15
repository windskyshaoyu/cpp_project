/*
 * File: crop.cpp
 * ------------------
 * This file implements the clipping.h interface.
 * This program outputs a picture after clipping by mouse.
 */
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

/*
 * Function: onMouse
 * Usage: return void;
 * --------------------------------------------
 *
 */

static Mat img, org, org2, tmp;
static int k = 0, width, height, x_rec, y_rec;
Point pre_pt; // Initial coordinates.
Point cur_pt; // Current coordinates.

static void onMouse(int event, int x, int y, int flags, void *)
{
    static char temp[16];
    if (event == EVENT_LBUTTONDOWN) // The left button of mouse is pressed. Then read initial coordinate and draw a circle around it.
    {
        org.copyTo(img);
        sprintf(temp, "(%d, %d)", x, y);
        pre_pt = Point(x, y);
        putText(img, temp, pre_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,0, 255)); // Show coordinate on the window
        circle(img, pre_pt, 2, Scalar(255, 0, 0, 0), FILLED, LINE_AA, 0); // Draw a circle
        imshow("img", img);
        printf("(%d, %d)", pre_pt.x, pre_pt.y);
    }

    else if (event == EVENT_MOUSEMOVE && ! (flags & EVENT_FLAG_LBUTTON)) { // If the left button is not pressed while mouse is moving; Not necessary
        img.copyTo(tmp); // Copy img to temporary tmp to show current corrdinates.
        sprintf(temp, "(%d, %d)", x, y);
        cur_pt = Point(x, y);
        putText(tmp, temp, cur_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
        imshow("img", tmp); // tmp??/??
    }
    else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON)) { // When the left button is pressed, the mouse moves to draw a rectangle on the image
        img.copyTo(tmp);
        sprintf(temp, "(%d, %d)", x, y);
        cur_pt = Point(x,y);
        putText(tmp, temp, cur_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 0, 255));
        rectangle(tmp, pre_pt, cur_pt, Scalar(0, 255, 0, 0), 1, 8, 0);
        imshow("img", tmp);
    }
    else if (event == EVENT_LBUTTONUP) { // When releasing the left button, draw the rectangle on picture
        org.copyTo(img);
        sprintf(temp, "(%d, %d)", x, y);
        cur_pt = Point(x, y);
        putText(img, temp, cur_pt, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0, 0, 255));
        circle(img, cur_pt, 2, Scalar(255, 0, 0), FILLED, LINE_AA, 0);
        rectangle(img, pre_pt, cur_pt, Scalar(0, 255, 0, 0), 1, 8, 0); // Based on the initial point and ending point, draw the rectangle on img.
        imshow("img", img);
        img.copyTo(tmp);

        // Clip the picture within the rectangle and save it to dst
        width = abs(pre_pt.x - cur_pt.x);
        height = abs(pre_pt.y - cur_pt.y);
        if (width == 0 || height ==0) // Need change.
        {
            return;
        }

        x_rec = min(cur_pt.x, pre_pt.x);
        y_rec = min(cur_pt.y, pre_pt.y);
        cout << x_rec << y_rec<<width<<height;
        Rect rec = Rect(x_rec, y_rec, width, height);
        Mat dst;
        org(rec).copyTo(dst);
        imshow("img", dst);
        waitKey(0);
    }

}

Mat crop(Mat org){
    //org = cv::imread(address, cv::IMREAD_COLOR);
    //org2 = cv::imread(address, cv::IMREAD_COLOR);
    org.copyTo(img);
    org.copyTo(tmp);
//    namedWindow("img");
    setMouseCallback("img", onMouse);
//    imshow("img", img);
//    waitKey(0);
    return img;
}
