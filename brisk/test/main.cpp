// Detect and describe BRISK features on a synthetic image, the way AllFeature-VSLAM does (Feature_brisk48.cpp).
#include <brisk/brisk.h>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include <cstdio>
#include <vector>

int main()
{
    cv::Mat img(480, 640, CV_8UC1, cv::Scalar(0));
    cv::RNG rng(0);
    for (int i = 0; i < 200; ++i)
        cv::rectangle(img, cv::Rect(rng.uniform(0, 600), rng.uniform(0, 440), 30, 30),
                      cv::Scalar(rng.uniform(64, 255)), cv::FILLED);

    brisk::BriskFeatureDetector detector(34, 4, true);
    brisk::BriskDescriptorExtractor extractor(true, true, brisk::BriskDescriptorExtractor::Version::briskV2);
    std::vector<cv::KeyPoint> keypoints;
    cv::Mat descriptors;
    detector.detect(img, keypoints);
    extractor.compute(img, keypoints, descriptors);

    std::printf("brisk: %zu keypoints, descriptors %dx%d\n", keypoints.size(), descriptors.rows, descriptors.cols);
    return keypoints.empty() || descriptors.rows != static_cast<int>(keypoints.size()) ? 1 : 0;
}
