
#include "Lab8.h"

void filter(Mat imageIn, Mat imageOut, double* matrix, int sizeX, int sizeY, double sum)
{
	for (int x = 0; x < imageIn.rows; x++)
	{
		for (int y = 0; y < imageIn.cols; y++)
		{
			double res = 0;
			for (int matrixX = 0; matrixX < sizeX; matrixX++)
			{
				for (int matrixY = 0; matrixY < sizeY; matrixY++)
				{
					res += matrix[matrixX * sizeY + matrixY] * imageIn.at<uchar>(x < sizeX / 2 ? sizeX / 2 : (x > (imageIn.rows - sizeX / 2) ? (imageIn.rows - sizeX / 2) : x) - (sizeX / 2) + matrixX,
						y < sizeY / 2 ? sizeY / 2 : (y > (imageIn.cols - sizeY / 2) ? (imageIn.cols - sizeY / 2) : y) - (sizeY / 2) + matrixY);
				}
			}
			imageOut.at<uchar>(x, y) = abs(res / sum);
		}
	}
}


uchar* hist(Mat imageIn)
{
	uchar* hist = new uchar[256];
	for (int x = 0; x < imageIn.rows; x++)
	{
		for (int y = 0; y < imageIn.cols; y++)
		{
			hist[imageIn.at<uchar>(x, y)]++;
		}
	}
	return hist;
}

uchar avarage(Mat imageIn)
{
	long unsigned int sum = 0;
	for (int x = 0; x < imageIn.rows; x++)
	{
		for (int y = 0; y < imageIn.cols; y++)
		{
			sum += imageIn.at<uchar>(x, y);
		}
	}
	return sum / (imageIn.rows * imageIn.cols);
}

void threshold(Mat imageIn, Mat imageOut)
{
	uchar* histArr = hist(imageIn);

	uchar T0 = 0;
	uchar T1 = avarage(imageIn);

	int m0 = 0;
	int m1 = 0;

	int n = 0;
	while (T0 != T1)
	{
		n++;
		int divider = 0;
		int divident = 0;

		for (int i = 0; i < T1; i++)
		{
			divident += i * histArr[i];
			divider += histArr[i];
		}

		m0 = divident / divider;
		divident = 0; divider = 0;


		for (int i = T1 + 1; i < 255; i++)
		{
			divident += i * histArr[i];
			divider += histArr[i];
		}

		m1 = divident / divider;
		divident = 0; divider = 0;

		T0 = T1;
		T1 = (m0 + m1) / 2;
	}

	cout << (int)T1 << " : " << n << endl;

	for (int x = 0; x < imageIn.rows; x++)
	{
		for (int y = 0; y < imageIn.cols; y++)
		{
			imageOut.at<uchar>(x, y) = imageIn.at<uchar>(x, y) < T1 ? 0 : 255;
		}
	}
}


void test_Lab8()
{
	Mat image = imread("C:/Code/C++/MMOZ/Tif/IM13.tif", IMREAD_GRAYSCALE);

	if (image.data == 0)
	{
		cout << "Could not open or find the image" << std::endl;
		return;
	}

	Mat thresholdedImage = image.clone();

	threshold(image, thresholdedImage);

	namedWindow("Original"), imshow("Original", image);
	namedWindow("Thresholded"), imshow("Thresholded", thresholdedImage);


	waitKey(1000000000000);
}