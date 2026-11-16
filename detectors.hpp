#ifndef FIRE_DETECTORS_HPP
#define FIRE_DETECTORS_HPP

#include <opencv2/core.hpp>

// Input: nonempty CV_8UC3 BGR image. Output: CV_8UC1 mask (0 or 255).
cv::Mat RGBDetect(const cv::Mat& image);
cv::Mat YCbCrDetect(const cv::Mat& image);

#endif
