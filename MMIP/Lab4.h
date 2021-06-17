#pragma once

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>

using namespace cv;

void convolution(const Mat& in_image, const double* mask, int ksize, double koef, double* data);
void SobelOperator(const Mat& in_image, Mat& out_image);

void test_Lab4();