#include <iostream>
#include <opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>


using namespace std;

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
    cv::Mat inter1;
    cv::Mat output1;
    cv::Mat inter2;
    cv::Mat intermediate1  
     


    // using the built-in function
    cv::filter2D(img, inter1, -1,gaussian_v1 , cv::Point(-1, -1), 0.0, cv::BorderTypes::BORDER_REPLICATE);
     cv::filter2D(inter1, output1, -1,gaussian_h1 , cv::Point(-1, -1), 0.0, cv::BorderTypes::BORDER_REPLICATE);
      cv::filter2D(output1, inter2, -1,gaussian_v2 , cv::Point(-1, -1), 0.0, cv::BorderTypes::BORDER_REPLICATE);
       cv::filter2D(img, inter2, -1,gaussian_h2 , cv::Point(-1, -1), 0.0, cv::BorderTypes::BORDER_REPLICATE);
        img.convertTo(img_f, CV_64FC1);
    cv::imshow("filter 2D output", img_f);
    cv::waitKey(0);
    return 0;
}