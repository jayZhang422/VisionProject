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
#include "string"
const int max_value_H = 360/2;
const int max_value_S = 255;
const int max_value_V = 255;

const std::string window_image_name = "Lego image";
const std::string window_detection_name = "object detection";

int low_H = 0 , low_S = 0 , low_V = 0;
int high_H = max_value_H , high_S = max_value_S , high_V = max_value_V;


static void on_low_H_trackbar(int pos,void* userdata)
{
    (void)pos;
    (void)userdata;
    low_H = cv::min(low_H,high_H-1);
    cv::setTrackbarPos("Low_H", window_detection_name, low_H);



}
   
static void on_low_S_trackbar(int pos,void* userdata)
{
    (void)pos;
    (void)userdata;
    low_S = cv::min(low_S,high_S-1);
    cv::setTrackbarPos("Low_S", window_detection_name, low_S);
    


}

static void on_low_V_trackbar(int pos,void* userdata)
{
    (void)pos;
    (void)userdata;
    low_V = cv::min(low_V,high_V-1);
    cv::setTrackbarPos("Low_V", window_detection_name, low_V);
    


}

static void on_high_H_trackbar(int pos,void* userdata)
{
    (void)pos;
    (void)userdata;
    high_H = cv::max(high_H,low_H+1);
    cv::setTrackbarPos("High_H", window_detection_name, high_H);
    


}

static void on_high_S_trackbar(int pos,void* userdata)
{
    (void)pos;
    (void)userdata;
    high_S = cv::max(high_S,low_S+1);   
    cv::setTrackbarPos("High_S", window_detection_name, high_S);
    


}


static void on_high_V_trackbar(int pos,void* userdata)
{
    (void)pos;
    (void)userdata;
    high_V = cv::max(high_V,low_V+1);
    cv::setTrackbarPos("High_V", window_detection_name, high_V);
    

}



int main()
{

    cv::Mat lego = cv::imread("/home/jayzhang/VisionProject/data/Lego.jpg");

    if(lego.empty())
    {
        std::cout<<"could not open the image"<<std::endl;
        return -1;
    }

    cv::namedWindow(window_image_name);
    cv::namedWindow(window_detection_name);

    cv::createTrackbar("Low_H", window_detection_name, &low_H, max_value_H,on_low_H_trackbar);
    cv::createTrackbar("Low_S", window_detection_name, &low_S, max_value_S,on_low_S_trackbar);
    cv::createTrackbar("Low_V", window_detection_name, &low_V, max_value_V,on_low_V_trackbar);
    cv::createTrackbar("High_H", window_detection_name, &high_H, max_value_H,on_high_H_trackbar);
    cv::createTrackbar("High_S", window_detection_name, &high_S, max_value_S,on_high_S_trackbar);
    cv::createTrackbar("High_V", window_detection_name, &high_V, max_value_V,on_high_V_trackbar);
    on_high_H_trackbar(0, 0);
    on_high_S_trackbar(0, 0);
    on_high_V_trackbar(0, 0);
    on_low_H_trackbar(0, 0);
    on_low_S_trackbar(0, 0);
    on_low_V_trackbar(0, 0);
    cv::Mat image_HSV,dst;
    cv::cvtColor(lego, image_HSV, cv::COLOR_BGR2HSV);
   while (true) {
       
        cv::inRange(image_HSV, cv::Scalar(low_H, low_S, low_V), cv::Scalar(high_H, high_S, high_V), dst);
        
        
        cv::imshow(window_image_name, lego);
        cv::imshow(window_detection_name, dst);
   
        
        if (cv::waitKey(30) == 27) {
            break;
        }
    }
    
    
}