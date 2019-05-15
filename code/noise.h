#ifndef NOISE_H
#define NOISE_H
#include <cstdlib>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

double generateGaussianNoise(double m, double sigma);
Mat addGaussianNoise(Mat &srcImag);
Mat noise(Mat org, int mode);
Mat addSPNoise(const Mat srcImage, int n);

#endif // NOISE_H
