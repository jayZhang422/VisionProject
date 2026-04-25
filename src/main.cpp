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

 
const char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char* trackbar_value = "Value";
cv::Mat src,dst,src_gray;

int threshold_value = 0 ;
int threshold_type = 3;

int const max_value = 255 ;
int const max_binary_value = 255;
int const max_type = 4;

static void Threshold_Demo(int pos , void* userdata)
{
    (void)pos;
    (void)userdata;

    cv::threshold(src_gray, dst, threshold_value, max_binary_value, threshold_type);
    cv::imshow("Threshold image",dst);

}
    
int main()
{
    src = cv::imread("/home/jayzhang/VisionProject/data/test.jpg");
    if(src.empty())
    {
        std::cout<<"could not open the file"<<std::endl;
        return -1;   
    }

    cv::cvtColor(src, src_gray, cv::COLOR_BGR2GRAY);

    cv::namedWindow("Threshold image");

    cv::createTrackbar(trackbar_type, "Threshold image", &threshold_type, max_type,Threshold_Demo);
    cv::createTrackbar(trackbar_value, "Threshold image", &threshold_value, max_value,Threshold_Demo);
    Threshold_Demo( 0, 0 );
    cv::waitKey(0);
    
}