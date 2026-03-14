#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>

/**
 * RunOpenCVTest
 * A simple test function to verify OpenCV integration.
 */
inline void RunOpenCVTest() {
    std::cout << "[OpenCV] Testing integration..." << std::endl;
    cv::Mat testMat = cv::Mat::zeros(100, 100, CV_8UC3);
    std::cout << "[OpenCV] Created a " << testMat.cols << "x" << testMat.rows << " matrix." << std::endl;
    std::cout << "[OpenCV] Version: " << CV_VERSION << std::endl;
    std::cout << "[OpenCV] Integration successful!" << std::endl;
}
