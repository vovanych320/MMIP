#pragma once
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <opencv2/core/mat.hpp>

using namespace cv;

void MyCanny(const Mat& src, Mat& workImg, int upperThreshold, int lowerThreshold, double size);

void test_Lab5();