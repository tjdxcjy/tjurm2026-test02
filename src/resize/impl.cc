#include "impls.h"


cv::Mat my_resize(const cv::Mat& input, float scale) {
    /**
     * 要求：
     *      实现resize算法，只能使用基础的语法，比如说for循环，Mat的基本操作。不能
     * 用cv::resize。resize算法的内容自行查找学习，不是很难。
     * 
     * 提示：
     * 无。
     * 
     * 通过条件：
     * 运行测试点，你的结果跟答案长的差不多就行。
     */
    int new_rows = input.rows * scale, new_cols = input.cols * scale;
    // IMPLEMENT YOUR CODE HERE
    
 
    cv::Mat output = cv::Mat::zeros(new_rows, new_cols, CV_8UC3);
    
 
    for (int i = 0; i < new_rows; ++i) {
        for (int j = 0; j < new_cols; ++j) {
         
            float src_i = static_cast<float>(i) / scale; 
            float src_j = static_cast<float>(j) / scale;  
            
            int i1 = static_cast<int>(std::floor(src_i));  
            int j1 = static_cast<int>(std::floor(src_j));
            int i2 = i1 + 1;  
            int j2 = j1 + 1;  
            
            i1=i1<0?0:i1>input.rows-1?input.rows-1:i1;
            i2=i2<0?0:i2>input.rows-1?input.rows-1:i2;
            j1=j1<0?0:j1>input.cols-1?input.cols-1:j1;
            j2=j2<0?0:j2>input.cols-1?input.cols-1:j2;
           
            float w1 = i2 - src_i;  
            float w2 = src_i - i1;  
            float w3 = j2 - src_j;  
            float w4 = src_j - j1;  
            
            cv::Vec3b p11 = input.at<cv::Vec3b>(i1, j1);  // (i1,j1)的B、G、R值
            cv::Vec3b p21 = input.at<cv::Vec3b>(i2, j1);  // (i2,j1)的B、G、R值
            cv::Vec3b p12 = input.at<cv::Vec3b>(i1, j2);  // (i1,j2)的B、G、R值
            cv::Vec3b p22 = input.at<cv::Vec3b>(i2, j2);  // (i2,j2)的B、G、R值
            
            // 对每个通道分别进行双线性插值计算
            uchar b = static_cast<uchar>(  
                w1 * w3 * p11[0] +  
                w2 * w3 * p21[0] +  
                w1 * w4 * p12[0] +  
                w2 * w4 * p22[0]    
            );
            uchar g = static_cast<uchar>(  
                w1 * w3 * p11[1] + 
                w2 * w3 * p21[1] + 
                w1 * w4 * p12[1] + 
                w2 * w4 * p22[1]
            );
            uchar r = static_cast<uchar>( 
                w1 * w3 * p11[2] + 
                w2 * w3 * p21[2] + 
                w1 * w4 * p12[2] + 
                w2 * w4 * p22[2]
            );
            
            
            output.at<cv::Vec3b>(i, j) = cv::Vec3b(b, g, r);
        }
    }
    
    return output;

}