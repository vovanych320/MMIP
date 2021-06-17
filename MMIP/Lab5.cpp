#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <opencv2/core/mat.hpp>
using namespace cv;


void MyCanny(const Mat& src, Mat& workImg, int upperThreshold, int lowerThreshold, double size)
{
    workImg = Mat(src.rows, src.cols, CV_8UC1, Scalar(255));
    workImg = src.clone();

    GaussianBlur(src, workImg, cv::Size(5, 5), 1.4);

    Mat magX = Mat(src.rows, src.cols, CV_32F);
    Mat magY = Mat(src.rows, src.cols, CV_32F);
    Sobel(workImg, magX, CV_32F, 1, 0, size);
    Sobel(workImg, magY, CV_32F, 0, 1, size);

    Mat direction = Mat(workImg.rows, workImg.cols, CV_32F);
    divide(magY, magX, direction);

    Mat sum = Mat(workImg.rows, workImg.cols, CV_64F);
    Mat prodX = Mat(workImg.rows, workImg.cols, CV_64F);
    Mat prodY = Mat(workImg.rows, workImg.cols, CV_64F);
    multiply(magX, magX, prodX);
    multiply(magY, magY, prodY);
    sum = prodX + prodY;
    sqrt(sum, sum);

    Mat returnImg = Mat(src.rows, src.cols, CV_8U);

    returnImg.setTo(cv::Scalar(0));

    MatIterator_<float>itMag = sum.begin<float>();
    MatIterator_<float>itDirection = direction.begin<float>();

    MatIterator_<unsigned char>itRet = returnImg.begin<unsigned char>();

    MatIterator_<float>itend = sum.end<float>();

    for (; itMag != itend; ++itDirection, ++itRet, ++itMag)
    {
        const cv::Point pos = itRet.pos();

        float currentDirection = atan(*itDirection) * 180 / 3.142;

        while (currentDirection < 0) currentDirection += 180;

        *itDirection = currentDirection;

        if (*itMag < upperThreshold) continue;

        bool flag = true;

        if (currentDirection > 112.5 && currentDirection <= 157.5)
        {
            if (pos.y > 0 && pos.x < workImg.cols - 1 && *itMag <= sum.at<float>(pos.y - 1, pos.x + 1)) flag = false;
            if (pos.y < workImg.rows - 1 && pos.x>0 && *itMag <= sum.at<float>(pos.y + 1, pos.x - 1)) flag = false;
        }

        else if (currentDirection > 67.5 && currentDirection <= 112.5)
        {
            if (pos.y > 0 && *itMag <= sum.at<float>(pos.y - 1, pos.x)) flag = false;
            if (pos.y < workImg.rows - 1 && *itMag <= sum.at<float>(pos.y + 1, pos.x)) flag = false;
        }
        else if (currentDirection > 22.5 && currentDirection <= 67.5)
        {
            if (pos.y > 0 && pos.x > 0 && *itMag <= sum.at<float>(pos.y - 1, pos.x - 1)) flag = false;
            if (pos.y < workImg.rows - 1 && pos.x < workImg.cols - 1 && *itMag <= sum.at<float>(pos.y + 1, pos.x + 1)) flag = false;
        }

        else
        {
            if (pos.x > 0 && *itMag <= sum.at<float>(pos.y, pos.x - 1)) flag = false;
            if (pos.x < workImg.cols - 1 && *itMag <= sum.at<float>(pos.y, pos.x + 1)) flag = false;
        }

        if (flag)
        {
            *itRet = 255;
        }
    }

    bool imageChanged = true;
    int i = 0;
    while (imageChanged)
    {
        imageChanged = false;

        i++;

        itMag = sum.begin<float>();
        itDirection = direction.begin<float>();
        itRet = returnImg.begin<unsigned char>();
        itend = sum.end<float>();
        for (; itMag != itend; ++itMag, ++itDirection, ++itRet)
        {
            Point pos = itRet.pos();
            if (pos.x < 2 || pos.x >= src.cols - 2 || pos.y < 2 || pos.y >= src.rows - 2)
                continue;
            float currentDirection = *itDirection;

            if (*itRet == 255)
            {
                *itRet = (unsigned char)64;

                if (currentDirection > 112.5 && currentDirection <= 157.5)
                {
                    if (pos.y > 0 && pos.x > 0)
                    {
                        if (lowerThreshold <= sum.at<float>(pos.y - 1, pos.x - 1) &&
                            returnImg.at<unsigned char>(pos.y - 1, pos.x - 1) != 64 &&
                            direction.at<float>(pos.y - 1, pos.x - 1) > 112.5 &&
                            direction.at<float>(pos.y - 1, pos.x - 1) <= 157.5 &&
                            sum.at<float>(pos.y - 1, pos.x - 1) > sum.at<float>(pos.y - 2, pos.x) &&
                            sum.at<float>(pos.y - 1, pos.x - 1) > sum.at<float>(pos.y, pos.x - 2))
                        {
                            returnImg.ptr<unsigned char>(pos.y - 1, pos.x - 1)[0] = 255;
                            imageChanged = true;
                        }
                    }
                    if (pos.y < workImg.rows - 1 && pos.x < workImg.cols - 1)
                    {
                        if (lowerThreshold <= sum.at<float>(cv::Point(pos.x + 1, pos.y + 1)) &&
                            returnImg.at<unsigned char>(pos.y + 1, pos.x + 1) != 64 &&
                            direction.at<float>(pos.y + 1, pos.x + 1) > 112.5 &&
                            direction.at<float>(pos.y + 1, pos.x + 1) <= 157.5 &&
                            sum.at<float>(pos.y - 1, pos.x - 1) > sum.at<float>(pos.y + 2, pos.x) &&
                            sum.at<float>(pos.y - 1, pos.x - 1) > sum.at<float>(pos.y, pos.x + 2))
                        {
                            returnImg.ptr<unsigned char>(pos.y + 1, pos.x + 1)[0] = 255;
                            imageChanged = true;
                        }
                    }
                }
                else if (currentDirection > 67.5 && currentDirection <= 112.5)
                {
                    if (pos.x > 0)
                    {
                        if (lowerThreshold <= sum.at<float>(cv::Point(pos.x - 1, pos.y)) &&
                            returnImg.at<unsigned char>(pos.y, pos.x - 1) != 64 &&
                            direction.at<float>(pos.y, pos.x - 1) > 67.5 &&
                            direction.at<float>(pos.y, pos.x - 1) <= 112.5 &&
                            sum.at<float>(pos.y, pos.x - 1) > sum.at<float>(pos.y - 1, pos.x - 1) &&
                            sum.at<float>(pos.y, pos.x - 1) > sum.at<float>(pos.y + 1, pos.x - 1))
                        {
                            returnImg.ptr<unsigned char>(pos.y, pos.x - 1)[0] = 255;
                            imageChanged = true;
                        }
                    }
                    if (pos.x < workImg.cols - 1)
                    {
                        if (lowerThreshold <= sum.at<float>(cv::Point(pos.x + 1, pos.y)) &&
                            returnImg.at<unsigned char>(pos.y, pos.x + 1) != 64 &&
                            direction.at<float>(pos.y, pos.x + 1) > 67.5 &&
                            direction.at<float>(pos.y, pos.x + 1) <= 112.5 &&
                            sum.at<float>(pos.y, pos.x + 1) > sum.at<float>(pos.y - 1, pos.x + 1) &&
                            sum.at<float>(pos.y, pos.x + 1) > sum.at<float>(pos.y + 1, pos.x + 1))
                        {
                            returnImg.ptr<unsigned char>(pos.y, pos.x + 1)[0] = 255;
                            imageChanged = true;
                        }
                    }
                }
                else if (currentDirection > 22.5 && currentDirection <= 67.5)
                {
                    if (pos.y > 0 && pos.x < workImg.cols - 1)
                    {
                        if (lowerThreshold <= sum.at<float>(cv::Point(pos.x + 1, pos.y - 1)) &&
                            returnImg.at<unsigned char>(pos.y - 1, pos.x + 1) != 64 &&
                            direction.at<float>(pos.y - 1, pos.x + 1) > 22.5 &&
                            direction.at<float>(pos.y - 1, pos.x + 1) <= 67.5 &&
                            sum.at<float>(pos.y - 1, pos.x + 1) > sum.at<float>(pos.y - 2, pos.x) &&
                            sum.at<float>(pos.y - 1, pos.x + 1) > sum.at<float>(pos.y, pos.x + 2))
                        {
                            returnImg.ptr<unsigned char>(pos.y - 1, pos.x + 1)[0] = 255;
                            imageChanged = true;
                        }
                    }
                    if (pos.y < workImg.rows - 1 && pos.x>0)
                    {
                        if (lowerThreshold <= sum.at<float>(cv::Point(pos.x - 1, pos.y + 1)) &&
                            returnImg.at<unsigned char>(pos.y + 1, pos.x - 1) != 64 &&
                            direction.at<float>(pos.y + 1, pos.x - 1) > 22.5 &&
                            direction.at<float>(pos.y + 1, pos.x - 1) <= 67.5 &&
                            sum.at<float>(pos.y + 1, pos.x - 1) > sum.at<float>(pos.y, pos.x - 2) &&
                            sum.at<float>(pos.y + 1, pos.x - 1) > sum.at<float>(pos.y + 2, pos.x))
                        {
                            returnImg.ptr<unsigned char>(pos.y + 1, pos.x - 1)[0] = 255;
                            imageChanged = true;
                        }
                    }
                }
                else
                {
                    if (pos.y > 0)
                    {
                        if (lowerThreshold <= sum.at<float>(cv::Point(pos.x, pos.y - 1)) &&
                            returnImg.at<unsigned char>(pos.y - 1, pos.x) != 64 &&
                            (direction.at<float>(pos.y - 1, pos.x) < 22.5 ||
                                direction.at<float>(pos.y - 1, pos.x) >= 157.5) &&
                            sum.at<float>(pos.y - 1, pos.x) > sum.at<float>(pos.y - 1, pos.x - 1) &&
                            sum.at<float>(pos.y - 1, pos.x) > sum.at<float>(pos.y - 1, pos.x + 2))
                        {
                            returnImg.ptr<unsigned char>(pos.y - 1, pos.x)[0] = 255;
                            imageChanged = true;
                        }
                    }
                    if (pos.y < workImg.rows - 1)
                    {
                        if (lowerThreshold <= sum.at<float>(cv::Point(pos.x, pos.y + 1)) &&
                            returnImg.at<unsigned char>(pos.y + 1, pos.x) != 64 &&
                            (direction.at<float>(pos.y + 1, pos.x) < 22.5 ||
                                direction.at<float>(pos.y + 1, pos.x) >= 157.5) &&
                            sum.at<float>(pos.y + 1, pos.x) > sum.at<float>(pos.y + 1, pos.x - 1) &&
                            sum.at<float>(pos.y + 1, pos.x) > sum.at<float>(pos.y + 1, pos.x + 1))
                        {
                            returnImg.ptr<unsigned char>(pos.y + 1, pos.x)[0] = 255;
                            imageChanged = true;
                        }
                    }
                }
            }
        }
    }

    MatIterator_<unsigned char>current = returnImg.begin<unsigned char>();
    MatIterator_<unsigned char>final = returnImg.end<unsigned char>();
    for (; current != final; ++current)
    {
        if (*current == 64)
            *current = 255;
    }

    workImg = returnImg.clone();
}


void test_Lab5()
{
    Mat in_image = imread("C:/Code/C++/MMOZ/Tif/Geneva.tif", IMREAD_GRAYSCALE);
    Mat out_image;

    imshow("Input image", in_image);

    MyCanny(in_image, out_image, 55, 45, 3);

    imshow("Output image", out_image);

    waitKey(1000000000);
}


