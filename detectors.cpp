#include "detectors.hpp"

#include <cmath>
#include <vector>
#include <opencv2/imgproc.hpp>

cv::Mat CleanFireMask(const cv::Mat& mask, int minArea)
{
    CV_Assert(!mask.empty() && mask.type() == CV_8UC1 && minArea >= 1);
    cv::Mat closed;
    cv::morphologyEx(mask, closed, cv::MORPH_CLOSE,
                     cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3)));
    cv::Mat labels, stats, centroids;
    const int count = cv::connectedComponentsWithStats(closed, labels, stats, centroids, 8);
    std::vector<unsigned char> keep(count, 0);
    for (int label = 1; label < count; ++label) {
        if (stats.at<int>(label, cv::CC_STAT_AREA) >= minArea) keep[label] = 255;
    }
    cv::Mat result = cv::Mat::zeros(mask.size(), CV_8UC1);
    for (int y = 0; y < result.rows; ++y) {
        for (int x = 0; x < result.cols; ++x) {
            result.at<unsigned char>(y, x) = keep[labels.at<int>(y, x)];
        }
    }
    return result;
}

cv::Mat RGBDetect(const cv::Mat& image)
{
    CV_Assert(!image.empty() && image.type() == CV_8UC3);
    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);
    cv::Mat mask = cv::Mat::zeros(image.size(), CV_8UC1);

    for (int y = 0; y < image.rows; ++y) {
        for (int x = 0; x < image.cols; ++x) {
            const cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);
            const int b = pixel[0], g = pixel[1], r = pixel[2];
            const double saturation = hsv.at<cv::Vec3b>(y, x)[1] * 100.0 / 255.0;
            const double upper = b >= 117 ? 100.0 - 0.48 * b : 79.27 - 0.311 * b;
            const double lower = -2.0147 + 90.0 * std::exp(-b / 77.6027);
            // Interpret the legacy 115..135 comment as a threshold range;
            // use its lower end rather than rejecting brighter red pixels.
            if (r >= 115 && r >= g && g >= b &&
                saturation >= lower && saturation <= upper) {
                mask.at<unsigned char>(y, x) = 255;
            }
        }
    }
    return mask;
}

cv::Mat YCbCrDetect(const cv::Mat& image)
{
    CV_Assert(!image.empty() && image.type() == CV_8UC3);
    cv::Mat ycrcb;
    cv::cvtColor(image, ycrcb, cv::COLOR_BGR2YCrCb);
    const cv::Scalar average = cv::mean(ycrcb);
    cv::Mat mask = cv::Mat::zeros(image.size(), CV_8UC1);

    for (int y = 0; y < image.rows; ++y) {
        for (int x = 0; x < image.cols; ++x) {
            const cv::Vec3b pixel = ycrcb.at<cv::Vec3b>(y, x);
            const int luminance = pixel[0], cr = pixel[1], cb = pixel[2];
            // Keep the four documented rules. The legacy polynomial boundaries
            // have no documented provenance and are intentionally not used.
            if (luminance > cb && cr > cb && luminance > average[0] &&
                cb < average[2] && cr > average[1] && std::abs(cb - cr) >= 40) {
                mask.at<unsigned char>(y, x) = 255;
            }
        }
    }
    return mask;
}
