// Detect and describe A-KAZE features on a synthetic image, the way AllFeature-VSLAM does (Feature_akaze61.cpp).
#include <akaze/AKAZE.h>

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
    cv::Mat img_32;
    img.convertTo(img_32, CV_32F, 1.0 / 255.0, 0);

    AKAZEOptions options;
    options.img_width = img_32.cols;
    options.img_height = img_32.rows;
    libAKAZE::AKAZE evolution(options);
    evolution.Create_Nonlinear_Scale_Space(img_32);

    std::vector<cv::KeyPoint> keypoints;
    cv::Mat descriptors;
    evolution.Feature_Detection(keypoints);
    evolution.Compute_Descriptors(keypoints, descriptors);

    std::printf("akaze: %zu keypoints, descriptors %dx%d\n", keypoints.size(), descriptors.rows, descriptors.cols);
    return keypoints.empty() || descriptors.rows != static_cast<int>(keypoints.size()) ? 1 : 0;
}
