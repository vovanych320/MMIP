
#include "Lab4.h"

void convolution(const Mat& in_image, const double* mask, int ksize, double koef, double* data)
{

    double sum = 0;
    for (int i = ksize / 2; i < in_image.rows - ksize / 2; i++)
    {
        for (int j = ksize / 2; j < in_image.cols - ksize / 2; j++)
        {
            sum = 0;
            for (int a = 0; a < ksize; a++)
            {
                for (int b = 0; b < ksize; b++)
                {
                    sum += in_image.data[(i + a - ksize / 2) * in_image.cols + j + b - ksize / 2] * mask[a * ksize + b];
                }
            }
            data[i * in_image.cols + j] = sum * koef;
        }
    }

}


void SobelOperator(const Mat& in_image, Mat& out_image)
{
    out_image = Mat(in_image.rows, in_image.cols, CV_8UC1, Scalar(255));
    double* data1 = new double[in_image.rows * in_image.cols];
    double* data2 = new double[in_image.rows * in_image.cols];

    for (int i = 0; i < in_image.rows * in_image.cols; i++)
    {
        data1[i] = 0;
        data2[i] = 0;
    }

    const int ksize = 3;
    double koef = 1.0 / 4.0;

    double mask1[ksize * ksize] = { -1, 0, 1,-2,0, 2, -1, 0, 1 };
    convolution(in_image, mask1, ksize, koef, data1);

    double mask2[ksize * ksize] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
    convolution(in_image, mask2, ksize, koef, data2);

    double value = 0;
    for (int i = 0; i < in_image.rows * in_image.cols; i++)
    {
        value = sqrt(pow(data1[i], 2) + pow(data2[i], 2));
        if (value > 255)
        {
            value = 255;
        }
        out_image.data[i] = value;
    }


    delete[] data1;
    delete[] data2;

}

void test_Lab4()
{
    Mat in_image = imread("C:/Code/C++/MMOZ/Tif/Geneva.tif", IMREAD_GRAYSCALE);
    Mat out_image;

    imshow("Input image", in_image);

    SobelOperator(in_image, out_image);

    imshow("Output image", out_image);

    waitKey(100000000);
}
