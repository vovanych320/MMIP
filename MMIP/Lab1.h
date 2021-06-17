#pragma once
#pragma once

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;


void increase(const Mat in_image, Mat& out_image, int n = 2);

void decrease(const Mat in_image, Mat& out_image, int n = 2);

void test_Lab1();
