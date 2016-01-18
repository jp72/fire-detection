#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace std;
using namespace cv;

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
      imshow("Display Image", image);
      waitKey(0);
      return 0;
}

Mat RGBDetect(Mat** image)
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
}
