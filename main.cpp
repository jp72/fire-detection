#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <math.h>
#include "detectors.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    if ( argc != 2 )
      {
          printf("usage: DisplayImage.out <Image_Path>\n");         
          return -1;
      }
      Mat image;
      image = imread( argv[1], 1 );
      if ( !image.data )
      {
          printf("No image data \n");
          return -1;
      }
      Mat HSIImage = Mat::zeros(image.rows, image.cols, CV_32FC3);
      HSIImage = RGB2HSIConvert(&image);


      waitKey(0);
      return 0;
}
