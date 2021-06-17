

#include "Lab7.h"


Mat ApplyGrowingRegions(const Mat& Image, const Point point, const uchar threshold)
{
    Mat GrowingRegionsImage = Image.clone();
    // Initialize the dynamic mark array
    bool** marked = new bool* [GrowingRegionsImage.rows];

    for (int row = 0; row < GrowingRegionsImage.rows; row++)
    {
        marked[row] = new bool[GrowingRegionsImage.cols];
    }


    // Initialize the array with zero-values
    for (int row = 0; row < GrowingRegionsImage.rows; row++)
    {
        for (int col = 0; col < GrowingRegionsImage.cols; col++)
        {
            marked[row][col] = false;
        }
    }


    // Get the brightness value of the point
    uchar brightness = GrowingRegionsImage.at<uchar>(point.y, point.x);

    // Iterate through image, mark the valuable points
    for (int row = 0; row < GrowingRegionsImage.rows; row++)
    {
        for (int col = 0; col < GrowingRegionsImage.cols; col++)
        {
            if (abs(GrowingRegionsImage.at<uchar>(row, col) - brightness) < threshold)
            {
                marked[row][col] = true;
            }
        }
    }

    // Make the marked regions to the 255 value, either to 0
    for (int row = 0; row < GrowingRegionsImage.rows; row++)
    {
        for (int col = 0; col < GrowingRegionsImage.cols; col++)
        {
            if (marked[row][col])
            {
                GrowingRegionsImage.at<uchar>(row, col) = 255;
            }
            else
            {
                GrowingRegionsImage.at<uchar>(row, col) = 0;
            }
        }
    }

    // Free the memory per mark array of booleans
    for (int row = 0; row < GrowingRegionsImage.rows; row++)
    {
        delete marked[row];
    }
    delete[] marked;
    return GrowingRegionsImage;
}


void test_Lab7()
{
    string RegularImageLabel = "Image";
    string GrowingRegionsLabel = "Growing Regions Image";

    Mat Image = imread("C:/Code/C++/MMOZ/Tif/Geneva.tif", IMREAD_GRAYSCALE);
    Mat GrowingRegionsImage;

    Point point = Point(100, 100);
    GrowingRegionsImage = ApplyGrowingRegions(Image, point, 1);
    imshow(RegularImageLabel, Image);
    imshow(GrowingRegionsLabel, GrowingRegionsImage);
    waitKey(10000000000000);
}

