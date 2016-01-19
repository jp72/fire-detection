#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace std;
using namespace cv;

Mat RGBDetect(Mat image);

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


Mat RGBDetect(Mat image)
{
    // R -> means RED, G -> Green, B -> Blue
    // Rule 1 : R(x,y)>= R_treshold [115..135]l
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
    Mat BinaryRule1 = cvCreateImage(original_size,8,1);
    int x,y;
    for (x = 0; x < Cols; ++x){
        for (y = 0; y < Rows; ++y){
            int pixel = Red.at<uchar>(y,x);
            if(pixel>114 && pixel<136){
                BinaryRule1.at<uchar>(y,x)=255;
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
            if(RedHere >= GreenHere && GreenHere >= BlueHere){
                BinaryRule2.at<uchar>(y,x)=255;
            }

        }
    }

    // Rule 3:  much more interesting :)
    //if(B(x,y)>=117){y1=100-0.48*B(x,y)}else{y1=79.27-0.311*B(x,y)}
    //double pow_value = -1*B(x,y)/77.6027
    //y2 = -2.0147+90*pow(exp(1), pow_value)
    // S(x,y) -> Saturation
    // rule itself: Y2 <= S(x,y) <= Y1
    double y1,y2,pow_value;
    Mat HSV = cvCreateImage(original_size,8,3);
    Mat sat = cvCreateImage(original_size,8,1);
    Mat BinaryRule3 = cvCreateImage(original_size,8,1);
    cvtColor(image,HSV,CV_BGR2HSV);
    extractChannel(HSV,sat,1);
    for (x = 0; x < Cols; ++x){
        for (y = 0; y < Rows; ++y){
            int BlueHere = Blue.at<uchar>(y,x);
            if(BlueHere>=117){
                y1 = 100-0.48*BlueHere;
            }else {
                y1 = 79.27-0.311*BlueHere;
            }
            pow_value = (-1*BlueHere)/77.6027;
            y2 = -2.0147+90*pow(exp(1), pow_value);
            Vec3b HSVPixel = HSV.at<Vec3b>(y, x);
            //sat.at<uchar>(y,x);
            double Saturation = HSVPixel.val[1];
            Saturation = Saturation/255*100;
            //std::cout << Saturation << std::endl;
            if(y2 <= Saturation && Saturation >= y1){
                BinaryRule3.at<uchar>(y,x)=255;
            }
        }
    }
    // Calculate final binary image
    Mat FinalBinary = cvCreateImage(original_size,8,1);
    for (x = 0; x < Cols; ++x){
            for (y = 0; y < Rows; ++y){
                if(BinaryRule1.at<uchar>(y,x) == 255 && BinaryRule2.at<uchar>(y,x) == 255 && BinaryRule3.at<uchar>(y,x) == 255)
                    FinalBinary.at<uchar>(y,x)=255;
            }
    }
    Mat binaryImage = BinaryRule3;
    return binaryImage;

}
