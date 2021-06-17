
#include "Lab6.h"

void convolution_for_eros(const Mat& in_image, const double* mask, int ksize, double koef, double* data)
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


void my_erosion(Mat in_image, Mat out_image, bool* matrix, int size)
{

    for (int x = 0; x < in_image.rows; x++)
    {
        for (int y = 0; y < in_image.cols; y++)
        {

            bool res = true;

            for (int matrixX = 0; matrixX < size; matrixX++)
            {
                for (int matrixY = 0; matrixY < size; matrixY++)
                {

                    if (x < size / 2)
                    {
                        size / 2;
                    }
                    else
                    {
                        if (x > in_image.rows - size / 2) 
                        { 
                            in_image.rows - size / 2;
                        }
                        else 
                        { 
                            x; 
                        }
                    }

                    if (y < size / 2)
                    {
                        size / 2;
                    }
                    else
                    {
                        if (y > (in_image.cols - size / 2) )
                        { 
                            in_image.cols - size / 2;
                        }
                        else 
                        { 
                            y;
                        }
                    }

                    res &= matrix[matrixX * size + matrixY] & (255 == in_image.data[(x - (size / 2) + matrixX) * out_image.cols + (y - (size / 2) + matrixY)]);

                }
            }
            out_image.data[x * out_image.cols + y] = res * 255;
        }
    }

}




void test_Lab6()
{
    Mat in_image = imread("C:/Code/C++/MMOZ/Tif/contour.tif", IMREAD_GRAYSCALE);
    Mat erosionImage ;
    Mat contourImage ;

    bool* ErosionMatrix = new bool[9]{ 1,1,1,1,1,1,1,1,1 };

    my_erosion(in_image, erosionImage, ErosionMatrix, 3);
    contourImage = in_image - erosionImage;
    imshow("Start", in_image);

    imshow("Finish", contourImage);
    waitKey(1000000000000000);
}
