#pragma once
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;



void HistogramEquslization(const Mat& in_image, Mat& out_image, Mat& in_histogram, Mat& out_histogram);

void makeDarker(const Mat& in_image, Mat& out_image);

void makeHist(const Mat& in_im, Mat& out_im);

void test_Lab2();