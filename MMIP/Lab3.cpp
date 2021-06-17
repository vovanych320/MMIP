#include "Lab3.h"



void convolution(const Mat& in_image, const double* Mask, int ksize, double koef, Mat& out_image)
{

	if (!in_image.data)
	{
		cout << "Image not found!!!";
		return;
	}

	out_image = in_image.clone();
	double Sum;
	for (int i = ksize / 2; i < in_image.rows - ksize / 2; i++)
	{
		for (int j = ksize / 2; j < in_image.cols - ksize / 2; j++)
		{

			Sum = 0;
			for (int a = 0; a < ksize; a++)
			{
				for (int b = 0; b < ksize; b++)
				{
					Sum += in_image.data[(i + a - ksize / 2) * in_image.cols + (j + b - ksize / 2)] * Mask[a * ksize + b];
				}
			}
			out_image.data[i * out_image.cols + j] = Sum * koef;
		}
	}

}



void GaussianBlur(const Mat& in_image, Mat& out_image, int ksize, double sigma)
{
	const double pi = 3.14159;
	const double e = 2.718281828459045;
	double koef = 1;


	//Create mask
	double** mask = new double* [ksize];
	for (int i = 0; i < ksize; ++i)
		mask[i] = new double[ksize];

	int d = ksize;


	//Initialize mask
	for (int x = 0; x < ksize; ++x)
	{
		for (int y = 0; y < ksize; ++y)
		{
			mask[x][y] = 1 / (2 * pi * sigma * sigma) * pow(e, (-((x - d / 2) * (x - d / 2) + (y - d / 2) * (y - d / 2)) / (2 * sigma * sigma)));
		}
	}


	double* linear_mask = new double[ksize * ksize];

	for (int i = 0; i < ksize; ++i)
	{
		for (int j = 0; j < ksize; ++j)
		{
			linear_mask[i * ksize + j] = mask[i][j];
			cout << linear_mask[i * ksize + j] << " ";
		}
		cout << endl;
	}

	convolution(in_image, linear_mask, ksize, koef, out_image);


	for (int i = 0; i < ksize; ++i)
		delete[]mask[i];

	delete[]linear_mask;
};



void test_Lab3()
{
	Mat in_image = imread("C:/Code/C++/MMOZ/Tif/Geneva.tif", IMREAD_GRAYSCALE);
	Mat out_image;
	int ksize;
	double sigma;

	cout << "Input extension: ";
	cin >> ksize;
	cout << "Input sigma :";
	cin >> sigma;

	GaussianBlur(in_image, out_image, ksize, sigma);

	namedWindow("Input image", CV_WINDOW_AUTOSIZE);
	imshow("In image window", in_image);

	namedWindow("Out_image", CV_WINDOW_AUTOSIZE);
	imshow("Out image window", out_image);

	waitKey(1000000000);
}