#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat RGBDetect(Mat image);
Mat YCbCrDetect(Mat image);
float ChannelMean(Mat image, int channel);
double Polynome(int Cr, int PolynomeNumber);
void HSIDetect(Mat* pImage, Mat* pHSIDetectedImage, int* width, int* height);
Mat RGB2HSIConvert(Mat* pImage);
