#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "ImageGray_CUDA.h"

using namespace std;
using namespace cv;

int main()
{
    Mat Input_Image = imread("name.png");
    cout << "Altura: " << Input_Image.rows << "Comprimento: " << Input_Image.cols << "Canais: " << Input_Image.channels() << endl;
    Image_GrayScale_Cuda(Input_Image, Input_Image.cols, Input_Image.rows, Input_Image.channels());
    imwrite("imageGray.png", Input_Image);
    system("pause");
    return 0;
}
