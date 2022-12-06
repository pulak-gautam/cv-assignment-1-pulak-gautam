#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>

cv::Scalar redLow = cv::Scalar(0, 100, 20);
cv::Scalar redHigh = cv::Scalar(10, 255, 255);

int main(int argc, char** argv)
{
    cv::Mat image = cv::imread("img.png");

    cv::Mat background;
    image.copyTo(background);

    cv::cvtColor(image, image, cv::COLOR_BGR2HSV);

    cv::Mat mask;
    cv::inRange(image, redLow, redHigh, mask);

    // cv::imshow("mask", mask);

    std::vector <std::vector <cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

    std::cout << contours.size();

    cv::drawContours(background, contours, -1, (0, 255, 0), 3);
    

    std::vector <cv::Point> centers; 

    for (int i=0; i<contours.size(); i++){
        cv::Moments M = cv::moments(contours[i]);
        cv::Point center(M.m10/M.m00, M.m01/M.m00);

        cv::circle(background, center, 7, (255, 255, 255), -1);
        centers.push_back(center);
    }


    cv::imshow("contours", background);

    cv::imwrite("final.png", background);


    cv::waitKey(0);

    return 0;
}