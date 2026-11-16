#include "detectors.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

namespace {
void usage(std::ostream& out)
{
    out << "Usage: fire <image> [--method rgb|ycrcb] [--output <prefix>]\n"
           "Defaults: --method ycrcb --output fire-result\n"
           "Writes <prefix>-mask.png and <prefix>-overlay.png.\n";
}
}

int main(int argc, char** argv)
{
    if (argc == 2 && (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h")) {
        usage(std::cout);
        return 0;
    }
    if (argc < 2) {
        usage(std::cerr);
        return 1;
    }

    std::string method = "ycrcb";
    std::string prefix = "fire-result";
    for (int i = 2; i < argc; ++i) {
        const std::string option = argv[i];
        if ((option != "--method" && option != "--output") || i + 1 >= argc) {
            std::cerr << "Unknown option or missing value: " << option << '\n';
            usage(std::cerr);
            return 1;
        }
        const std::string value = argv[++i];
        if (option == "--method") method = value;
        else prefix = value;
    }
    if ((method != "rgb" && method != "ycrcb") || prefix.empty()) {
        std::cerr << "Method must be rgb or ycrcb; output prefix must not be empty.\n";
        return 1;
    }

    try {
        const cv::Mat image = cv::imread(argv[1], cv::IMREAD_COLOR);
        if (image.empty()) {
            std::cerr << "Cannot read image: " << argv[1] << '\n';
            return 1;
        }
        const cv::Mat mask = method == "rgb" ? RGBDetect(image) : YCbCrDetect(image);
        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(mask.clone(), contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        cv::Mat overlay = image.clone();
        for (const auto& contour : contours) {
            cv::rectangle(overlay, cv::boundingRect(contour), cv::Scalar(0, 255, 0), 2);
        }

        const std::string maskPath = prefix + "-mask.png";
        const std::string overlayPath = prefix + "-overlay.png";
        if (!cv::imwrite(maskPath, mask) || !cv::imwrite(overlayPath, overlay)) {
            std::cerr << "Failed to write output images.\n";
            return 1;
        }
        const int candidates = cv::countNonZero(mask);
        std::cout << "Method: " << method << "\nCandidate pixels: " << candidates
                  << " (" << 100.0 * candidates / image.total() << "%)\n"
                  << "Mask: " << maskPath << "\nOverlay: " << overlayPath << '\n';
        return 0;
    } catch (const cv::Exception& error) {
        std::cerr << "OpenCV error: " << error.what() << '\n';
        return 1;
    }
}
