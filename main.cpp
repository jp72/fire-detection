#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace std;
using namespace cv;

Mat RGBDetect(Mat image)
{
    // R -> means RED, G -> Green, B -> Blue
    // Rule 1 : R(x,y)>= R_treshold [115..135]
    // Rule 2:  R(x,y) >= G(x,y) >= B(x,y)
    // Rule 3:  much more interesting :)
    //if(B(x,y)>=117){y1=100-0.48*B(x,y)}else{y1=79.27-0.311*B(x,y)}
    //double pow_value = -1*B(x,y)/77.6027
    //y2 = -2.0147+90*pow(exp(1), pow_value)
    // S(x,y) -> Saturation
    // rule itself: Y2 <= S(x,y) <= Y1
    // Final binary mask creation rule
    // if all conditions are matched -> It is a fire!!!
    Size original_size = image.size();
    int Rows = image.rows;
    int Cols = image.cols;
    // Create matrices for each color channel
    Mat Blue = cvCreateImage(original_size,8,1);
    Mat Green = cvCreateImage(original_size,8,1);
    Mat Red = cvCreateImage(original_size,8,1);
    // Extract color channels and put them into individual matrices
    extractChannel(image,Blue,0);
    extractChannel(image,Green,1);
    extractChannel(image,Red,2);
    // Perform 1st rule:
    // Binary Red matrix
    Mat BinaryRed = cvCreateImage(original_size,8,1);
    int x,y;
    for (x = 0; x < Cols; ++x){
        for (y = 0; y < Rows; ++y){
            int pixel = Red.at<uchar>(y,x);
            if(pixel>114 && pixel<136){
                BinaryRed.at<uchar>(y,x)=255;
            }

        }
    }

    // Perform 2nd Rule:
    // Rule 2:  R(x,y) >= G(x,y) >= B(x,y)
    Mat BinaryRule2 = cvCreateImage(original_size,8,1);
    for (x = 0; x < Cols; ++x){
        for (y = 0; y < Rows; ++y){
            int RedHere = Red.at<uchar>(y,x);
            int GreenHere = Green.at<uchar>(y,x);
            int BlueHere = Blue.at<uchar>(y,x);
            if(RedHere >= GreenHere and GreenHere >= BlueHere){
                BinaryRule2.at<uchar>(y,x)=255;
            }

        }
    }


    Mat FinalBinary = cvCreateImage(original_size,8,1);
    for (x = 0; x < Cols; ++x){
            for (y = 0; y < Rows; ++y){
                if(BinaryRed.at<uchar>(y,x) == 255 && BinaryRule2.at<uchar>(y,x) == 255)
                    FinalBinary.at<uchar>(y,x)=255;
            }
    }
    Mat binaryImage = FinalBinary;
    return binaryImage;

}

int main(int argc, char** argv)
{
    if ( argc != 2 )
      {
          printf("usage: DisplayImage.out <Image_Path>\n");
          double myexp = exp(1);
          printf("%.9lf\n", myexp);
          return -1;
      }
      Mat image;
      image = imread( argv[1], 1 );
      if ( !image.data )
      {
          printf("No image data \n");
          return -1;
      }
      namedWindow("Display Image", WINDOW_AUTOSIZE );
      image = RGBDetect(image);
      imshow("Display Image", image);
      waitKey(0);
      return 0;
}


