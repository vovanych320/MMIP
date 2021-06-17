#include "Lab1.h"


void test_Lab1()
{
    const string src = "Source image";
    const string inc = "Increased image";
    const string dec = "Decreased image";

    Mat src_image = imread("C:/Code/C++/MMOZ/Labs/IM4.tif", IMREAD_GRAYSCALE);
    Mat inc_image;
    Mat dec_image;


    if (src_image.data == 0)
    {
        std::cout << "Could not open or find the image" << std::endl;
        return;
    }

    {
        increase(src_image, inc_image);
        decrease(src_image, dec_image);
    }



    namedWindow(inc, CV_WINDOW_AUTOSIZE);
    imshow(inc, inc_image);

    namedWindow(src, CV_WINDOW_AUTOSIZE);
    imshow(src, src_image);

    namedWindow(dec, CV_WINDOW_AUTOSIZE);
    imshow(dec, dec_image);

    waitKey(50000);
}



void increase(const Mat in_image, Mat& out_image, int n)
{
    const size_t x = in_image.rows;
    const size_t y = in_image.cols;
    Mat image(x * n, y * n, 0);

    for (size_t i = 0; i < x * n; i += n)
    {
        for (size_t j = 0; j < y * n; j += n)
        {
            image.at<uchar>(i, j) = in_image.at<uchar>(i / n, j / n);
            image.at<uchar>(i, j + 1) = in_image.at<uchar>(i / n, j / n);
            image.at<uchar>(i + 1, j) = in_image.at<uchar>(i / n, j / n);
            image.at<uchar>(i + 1, j + 1) = in_image.at<uchar>(i / n, j / n);
        }

    }

    out_image = image;
}



void decrease(const Mat in_image, Mat& out_image, int n)
{
    const size_t x = in_image.rows;
    const size_t y = in_image.cols;
    Mat image(x / n, y / n, 0);

    for (size_t i = 0; i < x / n; i++)
    {
        for (size_t j = 0; j < y / n; j++)
        {
            image.at<uchar>(i, j) = in_image.at<uchar>(i * n, j * n);
            //image.data[i][j] = in_image[i * n][j * n];
        }
        cout << endl;
    }

    out_image = image;
}

