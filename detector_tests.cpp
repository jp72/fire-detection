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
            image.at<cv::Vec3b>(1, 1) = cv::Vec3b(80, 140, 160);
            const cv::Mat rgb = RGBDetect(image);
            const cv::Mat ycrcb = YCbCrDetect(image);
            require(rgb.at<unsigned char>(1, 1) == 255, "RGB missed candidate");
            require(ycrcb.at<unsigned char>(1, 1) == 255, "YCrCb missed candidate");
            require(cv::countNonZero(rgb) == 1 && cv::countNonZero(ycrcb) == 1,
                    "Background must remain zero");
        }
        cv::Mat regions = cv::Mat::zeros(30, 40, CV_8UC1);
        regions(cv::Rect(3, 3, 5, 5)).setTo(255);
        regions.at<unsigned char>(20, 20) = 255;
        const cv::Mat before = regions.clone();
        const cv::Mat cleaned = CleanFireMask(regions, 25);
        require(cv::countNonZero(cleaned) == 25, "Small noise should be removed");
        require(cv::countNonZero(regions != before) == 0, "Cleanup modified input");
        require(CleanFireMask(regions, 26).at<unsigned char>(5, 5) == 0,
                "Area threshold should be configurable");
        require(cv::countNonZero(CleanFireMask(cv::Mat::zeros(9, 13, CV_8UC1))) == 0,
                "Empty mask must remain empty");
        cv::Mat fragments = cv::Mat::zeros(20, 20, CV_8UC1);
        fragments(cv::Rect(3, 4, 4, 5)).setTo(255);
        fragments(cv::Rect(8, 4, 4, 5)).setTo(255);
        const cv::Mat joined = CleanFireMask(fragments, 25);
        require(joined.at<unsigned char>(6, 7) == 255, "Small gap should be closed");
        require(cv::countNonZero(joined) == 45, "Joined fragments should survive filtering");
        cv::Mat edge = cv::Mat::zeros(20, 20, CV_8UC1);
        edge(cv::Rect(0, 5, 5, 5)).setTo(255);
        require(cv::countNonZero(CleanFireMask(edge)) == 25, "Border candidate lost");
        std::cout << "Detector tests passed\n";
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
