#include <cstdio>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/core/hal/interface.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>


const int kernel_size = 5 ;

int main()
{
cv::Mat src = cv::imread("/home/jayzhang/VisionProject/data/LinuxLogo.jpg");

if(src.empty())
{
    std::cout<<"could not open the file"<<std::endl;
}

cv::Mat morph;
cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(kernel_size,kernel_size),cv::Point(-1,-1));

    cv::morphologyEx(src, morph, 4, element);

    cv::imshow("Original Image", src);

    cv::imshow("morph image",morph);
   

    cv::waitKey(0);
    return 0;

    
}