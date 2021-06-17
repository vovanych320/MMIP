
#include "Lab2.h"

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>


using namespace cv;
using namespace std;


void makeDarker(const Mat& in_image, Mat& out_image)
{

	out_image = cv::Mat(in_image.rows, in_image.cols, CV_8UC1, cv::Scalar(0));
	const int size = 256;
	int hist[size];
	int cum_hist[size];
	double alfa = 255.0 / double(in_image.rows * in_image.cols);

	for (int i = 0; i < size; i++)
	{
		hist[i] = 0;
		cum_hist[i] = 0;
	}

	for (int i = 0; i < in_image.rows * in_image.cols; i++)
	{
		int value = in_image.data[i];
		hist[value]++;
	}

	cum_hist[0] = hist[0];
	for (int i = 1; i < size; i++)
		cum_hist[i] = cum_hist[i - 1] + hist[i];

	for (int i = 0; i < out_image.rows * out_image.cols; i++)
	{
		int value = in_image.data[i];
		out_image.data[i] = alfa * cum_hist[value];
	}

};


void makeHist(const Mat& in_im, Mat& out_im)
{
	Mat src, dst;

	if (!in_im.data)
	{
		cout << "Image not found!!!";
		return;
	}

	src = in_im;

	vector<Mat> bgr_planes;
	split(src, bgr_planes);

	int histSize = 256;

	float range[] = { 0, 256 };
	const float* histRange = { range };

	bool uniform = true;
	bool accumulate = false;

	Mat b_hist, g_hist, r_hist;
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);

	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	/// Draw for each channel
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
	}

	out_im = histImage;
}

void HistogramEquslization(const Mat& in_image, Mat& out_image, Mat& in_histogram, Mat& out_histogram)
{
	makeDarker(in_image, out_image);
	makeHist(in_image, in_histogram);
	makeHist(out_image, out_histogram);

}


void test_Lab2()
{
	Mat in_image, out_image;
	Mat in_hist, out_hist;

	in_image = imread("C:/Code/C++/MMOZ/Tif/Geneva.tif", IMREAD_GRAYSCALE);


	HistogramEquslization(in_image, out_image, in_hist, out_hist);

	namedWindow("Source image", CV_WINDOW_AUTOSIZE);
	imshow("Source image", in_image);

	namedWindow("Histogram for source image", CV_WINDOW_AUTOSIZE);
	imshow("Histogram for source image", in_hist);

	namedWindow("Darker image", CV_WINDOW_AUTOSIZE);
	imshow("Darker image", out_image);

	namedWindow("Histogram for darker image", CV_WINDOW_AUTOSIZE);
	imshow("Histogram for darker image", out_hist);

	waitKey(0);
}