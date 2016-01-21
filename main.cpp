#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <math.h>

using namespace std;
using namespace cv;

Mat RGBDetect(Mat image);
Mat YCbCrDetect(Mat image);
float ChannelMean(Mat image, int channel);
double Polynome(int Cr, int PolynomeNumber);
void HSIDetect(Mat* pImage, Mat* pHSIDetectedImage, int* width, int* height);
void HSIConvert(Mat* pImage, Mat* pHSIImage, int* width, int* height);

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
      //namedWindow("OriginalImage", WINDOW_AUTOSIZE);
      //imshow("OriginalImage", image);
      //namedWindow("RGB Image", WINDOW_AUTOSIZE );
      //imshow("RGB Image", RGBDetect(image));
      Mat HSIDetectedImage = Mat(image.size().height,image.size().width,CV_32F);
      //namedWindow("YCbCr Image", WINDOW_AUTOSIZE);
      //imshow("YCbCr Image", YCbCrDetect(image));
      int width = image.size().width;
      int height = image.size().height;
      cout << "image address:" << &image << endl;
      HSIConvert(&image, &HSIDetectedImage, &width, &height);
      //namedWindow("HSI Image", WINDOW_AUTOSIZE);
      //imshow("HSI Image", HSIDetectedImage);



      waitKey(0);
      return 0;
}

void HSIDetect(Mat* pImage, Mat* pHSIDetectedImage, int* width, int* height){
    *pHSIDetectedImage = *pImage;
    cout << "pImage address:" << pImage << endl;
    cout << "pHSIDetectedImage address: " << pHSIDetectedImage << endl;
    Mat HSIConvertedImage = cvCreateImage(cvSize(*width, *height),8,3);
    // RGB -> HSI convertion
}

void HSIConvert(Mat* pImage, Mat* pHSIImage, int* width, int* height){
    Mat HSIImage = *pHSIImage;
    Mat Image = *pImage;
    for(int x = 0; x < *width ; ++x){
        for(int y = 0; y < *height; ++y){
            // Let's make RGB variables
            int B = Image.at<Vec3b>(y,x)[0];
            int G = Image.at<Vec3b>(y,x)[1];
            int R = Image.at<Vec3b>(y,x)[2];
            //cout << "B: " << B << " G: " << G << " R: " << R << endl;
            //I conversion
            HSIImage.at<Vec3f>(y,x)[2] = (B+G+R)/3;
            //S conversion
            // B, G, R min
            double BGRmin = (B < G)? B : G;
            BGRmin = (BGRmin < R)? BGRmin: R;
            double S = 1-3*(BGRmin/(B+G+R));
            S = (S < 0.00001)? 0 : (S > 0.99999)? 1 : S;
            HSIImage.at<Vec3f>(y,x)[1] = S;
           //H conversion
            if(B<=G){
                HSIImage.at<Vec3f>(y,x)[0] = 0;
            }else{
                double Theta = (0.5*((R-G)+(R-B)))/(sqrt(pow(R-G,2)+(R-B)*(G-B)));

                Theta = pow(cos(Theta),-1);
                HSIImage.at<Vec3f>(y,x)[0] = 360 - Theta;
                cout << "H: " << HSIImage.at<Vec3f>(y,x)[0] << endl;
            }

        }
    }
    *pHSIImage = HSIImage;
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

Mat YCbCrDetect(Mat image){
    /*В общем, состоит из следующих этапов:
    1. Y(x,y) > Cb(x,y)
    2. Cr(x,y) > Cb (x,y)
    3. Pixel is fire if Y(x,y) > Mean(Y), Cb(x,y)<Mean(Cb),Cr(x,y)>Mean(Cr)
    4. Pixel is fire if abs(Cb(x,y)-Cr(x,y) >= tau. Tau = 40;
    */
    Mat ImageCbCr = cvCreateImage(image.size(),8,3);
    cvtColor(image, ImageCbCr, CV_BGR2YCrCb);
    int x = 0, y = 0;
    int Rows = image.size().height;
    int Cols = image.size().width;
    Vec3b YCrCbPixel;
    // 1st step.
    Mat FirstSecondStepBinary = cvCreateImage(image.size(),8,1);
    Mat ThirdStepBinary = cvCreateImage(image.size(),8,1);
    Mat FourthStepBinary = cvCreateImage(image.size(),8,1);
    Mat FithStepBinary = cvCreateImage(image.size(),8,1);
    Mat FinalBinary = cvCreateImage(image.size(),8,1);
    float MeanY = ChannelMean(ImageCbCr,0);
    float MeanCb = ChannelMean(ImageCbCr,2);
    float MeanCr = ChannelMean(ImageCbCr,1);

    for (x = 0; x < Cols; ++x){
        for (y = 0; y < Rows; ++y){
            YCrCbPixel = ImageCbCr.at<Vec3b>(y,x);
            // First and second steps
            if(YCrCbPixel[0]>YCrCbPixel[2] && YCrCbPixel[1]>YCrCbPixel[2]){
                FirstSecondStepBinary.at<uchar>(y,x)=255;
            }
            //Third step.
            //Calculate mean for Y, Cb, Cr.
            if(YCrCbPixel[0]>MeanY && YCrCbPixel[2]<MeanCb && YCrCbPixel[1]>MeanCr){
                ThirdStepBinary.at<uchar>(y,x)=255;
            }
            // Fourth Step.
            if(abs(YCrCbPixel[2]-YCrCbPixel[1])>=40){
                FourthStepBinary.at<uchar>(y,x)=255;
            }
            // Final, 5th Step.
            /* cout << YCrCbPixel << endl;
            //printf("%.9lf\n", YCrCbPixel[1]);
            cout << "Polynome 1: " << Polynome(YCrCbPixel[1],1) << endl;
            cout << "Polynome 2: " << Polynome(YCrCbPixel[1],2) << endl;
            cout << "Polynome 3: " << Polynome(YCrCbPixel[1],3) << endl; */
            if(YCrCbPixel[2]>=Polynome(YCrCbPixel[1],1) && YCrCbPixel[2]<=Polynome(YCrCbPixel[1],3) && YCrCbPixel[2] <= Polynome(YCrCbPixel[1],2)){
                FithStepBinary.at<uchar>(y,x)=255;
            }
            // Combine all of above into one image:
            if(FirstSecondStepBinary.at<uchar>(y,x) == 255 && ThirdStepBinary.at<uchar>(y,x) == 255 && ThirdStepBinary.at<uchar>(y,x) == 255 && FourthStepBinary.at<uchar>(y,x) == 255){
                FinalBinary.at<uchar>(y,x)=255;
            }

        }

     }

    //Mat FinalBinary = FourthStepBinary;



    return FithStepBinary;
}

float ChannelMean(Mat image, int channel){
    Mat ExtractedChannel = cvCreateImage(image.size(),8,1);
    extractChannel(image, ExtractedChannel, channel);
    Scalar ChannelMean = mean(ExtractedChannel);
    return ChannelMean[0];
}

double Polynome(int Cr, int PolynomeNumber){
    if(PolynomeNumber == 1){
        return -2.6*pow(10,-10)*pow(Cr,7)+3.3*pow(10,-7)*pow(Cr,6)-1.7*pow(10,-4)*pow(Cr,5)+5.16*pow(10,-2)*pow(Cr,4)-9.10*pow(Cr,3)+9.6*pow(10,2)*pow(Cr,2)-5.6*pow(10,4)*Cr-1.4*pow(10,6);
    }else if (PolynomeNumber == 2) {
        return -6.77*pow(10,-8)*pow(Cr,5)+5.5*pow(10,-5)*pow(Cr,4)-1.76*pow(10,-2)*pow(Cr,3)+2.78*pow(Cr,2)-2.15*100*Cr+6.62*1000;
    }else if (PolynomeNumber == 3) {
        return 1.81*pow(10,-4)*pow(Cr,4)-1.02*pow(10,-1)*pow(Cr,3)+2.17*10*pow(Cr,2)-2.05*1000*Cr+7.29*pow(10,4);
    }else{
        return 0;
    }
}
