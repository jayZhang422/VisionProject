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
#include <vector>

cv::Mat src_gray;
int kernel_size = 3 ;
void thresh_callback(int , void *);
int thresh = 100;
cv::RNG rng(12345);
int main()
{
cv::Mat src = cv::imread("/home/jayzhang/VisionProject/data/Plate_Number.png");

if(src.empty())
{
    std::cout<<"could not open the file"<<std::endl;
}

    cv::cvtColor(src, src_gray, cv::COLOR_BGR2GRAY);
    cv::blur(src_gray,src_gray,cv::Size (kernel_size,kernel_size));
    const  char * source_window = "Source" ;
    cv::namedWindow(source_window);
    const  int max_thresh = 255;
    cv::createTrackbar("canny", source_window, &thresh, max_thresh,thresh_callback);
    thresh_callback(0, 0);
    cv::waitKey(0);

    return 0;

    
}

void thresh_callback(int , void *){

    cv::Mat canny_output;
    Canny( src_gray, canny_output, thresh, thresh*2 );
 
    std::vector<std::vector<cv::Point> > contours;
    cv::findContours( canny_output, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE );
 
    std::vector<std::vector<cv::Point> > contours_poly( contours.size() );
    std::vector<cv::Rect> boundRect( contours.size() );
    std::vector<cv::Point2f>centers( contours.size() );
    std::vector<float>radius( contours.size() );
 
    for( size_t i = 0; i < contours.size(); i++ )
    {
        approxPolyDP( contours[i], contours_poly[i], 3, true );
        boundRect[i] = boundingRect( contours_poly[i] );
        minEnclosingCircle( contours_poly[i], centers[i], radius[i] );
    }
 
    cv::Mat drawing = cv::Mat::zeros( canny_output.size(), CV_8UC3 );
 
    for( size_t i = 0; i< contours.size(); i++ )
    {
        cv::Scalar color = cv::Scalar( rng.uniform(0, 256), rng.uniform(0,256), rng.uniform(0,256) );
        drawContours( drawing, contours_poly, (int)i, color );
        rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), color, 2 );
        circle( drawing, centers[i], (int)radius[i], color, 2 );
    }
 
    imshow( "Contours", drawing );
}