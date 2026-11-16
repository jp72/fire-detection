#include "detectors.hpp"

#include <initializer_list>
#include <iostream>
#include <stdexcept>

namespace {
void require(bool condition, const char* message)
{
    if (!condition) throw std::runtime_error(message);
}
}

int main()
{
    try {
        // Both landscape and portrait inputs exercise row/column handling.
        for (const cv::Size size : {cv::Size(7, 3), cv::Size(3, 7)}) {
            const cv::Mat black(size, CV_8UC3, cv::Scalar(0, 0, 0));
            const cv::Mat gray(size, CV_8UC3, cv::Scalar(128, 128, 128));
            for (const cv::Mat& image : {black, gray}) {
                for (const cv::Mat& mask : {RGBDetect(image), YCbCrDetect(image)}) {
                    require(mask.type() == CV_8UC1 && mask.size() == size,
                            "Incorrect mask type or dimensions");
                    require(cv::countNonZero(mask) == 0, "Neutral image should have no candidates");
                }
            }
            cv::Mat image = black.clone();
            image.at<cv::Vec3b>(1, 1) = cv::Vec3b(80, 150, 230);
            const cv::Mat rgb = RGBDetect(image);
            const cv::Mat ycrcb = YCbCrDetect(image);
            require(rgb.at<unsigned char>(1, 1) == 255, "RGB missed candidate");
            require(ycrcb.at<unsigned char>(1, 1) == 255, "YCrCb missed candidate");
            require(cv::countNonZero(rgb) == 1 && cv::countNonZero(ycrcb) == 1,
                    "Background must remain zero");
        }
        std::cout << "Detector tests passed\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
