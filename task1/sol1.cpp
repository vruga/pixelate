
#include <iostream>
#include <opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include "convolution.hpp"


using namespace std;
cv::Mat convolve(cv::Mat, cv::Mat);
int main()
{
     cv::Mat img = cv::imread("./assets/hogwarts.png", cv::IMREAD_GRAYSCALE);
    if (img.empty()) {
        cerr << "Could not load image at ./assets/hogwarts.png\n";
        return -1;
    }
     cv::resize(img, img, cv::Size(img.cols*0.5, img.rows*0.5));

    // The two kernels — do not change these
    cv::Mat K1 = (cv::Mat_<double>(3, 3) <<
         1,  2,  1,
         0,  0,  0,
        -1, -2, -1
    );

    cv::Mat K2 = (cv::Mat_<double>(3, 3) <<
         1,  0, -1,
         2,  0, -2,
         1,  0, -1
    );
    cv::Mat gaussian_v1 = (cv::Mat_<double>(3, 1) << 1., 0. , 1.);
    cv::Mat gaussian_h1 = (cv::Mat_<double>(1, 3) << 1., 2. ,1.);
    cv::Mat gaussian_h2 = (cv::Mat_<double>(1, 3) << 1., 0. , 1.);
    cv::Mat gaussian_v2 = (cv::Mat_<double>(3, 1) << 1., 2. ,1.);

    cv::Mat intermediate1 = convolve(img, gaussian_v1);         // Convolve Vertically
    cv::Mat output1 = convolve(intermediate1, gaussian_h1);
    cv::Mat intermediate2 = convolve(output1, gaussian_v2); 
    cv::Mat img_f;        // Convolve Vertically
    img_f= convolve(intermediate2, gaussian_h2);

    
    img.convertTo(img_f, CV_64FC1);

    cv::namedWindow("Output by Naive Seperable Convolution", cv::WINDOW_NORMAL);
    cv::imshow("Output by Naive Seperable Convolution",img_f);
    cv::waitKey(0);
    // TODO: apply K1 and K2 to img_f with as few multiplications per pixel as possible.
    // Print the number of multiplications your approach uses per pixel.

    return 0;
}