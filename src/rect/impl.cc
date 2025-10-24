#include "impls.h"


std::pair<cv::Rect, cv::RotatedRect> get_rect_by_contours(const cv::Mat& input) {
    /**
     * 要求：
     * 使用findCountours函数找出输入图像（彩色图像）中的矩形轮廓，并且返回它的外接矩形，以及
     * 最小面积外接矩形。所需要的函数自行查找。
     * 
     * 通过条件：
     * 运行测试点，你找到的矩形跟答案一样就行。
    */
    std::pair<cv::Rect, cv::RotatedRect> res;
    // IMPLEMENT YOUR CODE HERE
     
    cv::Mat gray;
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);

    cv::Mat binary;
    cv::threshold(gray, binary, 127, 255, cv::THRESH_BINARY_INV); 


    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(binary, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);


    for (int i = 0; i < contours.size(); ++i) {
        const std::vector<cv::Point>& contour = contours[i];
        // 轮廓近似：使用Douglas-Peucker算法简化轮廓
        double epsilon = 0.02 * cv::arcLength(contour, true); // 近似精度，为轮廓周长的2%
        std::vector<cv::Point> approx;
        cv::approxPolyDP(contour, approx, epsilon, true);

        if (approx.size() == 4 && cv::isContourConvex(approx)) {
           
            cv::Rect bounding_rect = cv::boundingRect(approx);
            cv::RotatedRect rotated_rect = cv::minAreaRect(approx);

            res = {bounding_rect, rotated_rect};
            break; 
        }
    }

    return res;
}