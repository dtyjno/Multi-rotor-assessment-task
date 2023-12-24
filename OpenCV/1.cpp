#include<iostream>
#include </usr/local/include/opencv4/opencv2/opencv.hpp>

using namespace cv;

int main()
{
    try
    {
        // call OpenCV
        VideoCapture cap(0);
        if(!cap.isOpened())
        {
            std::cout<<"Failed to open camera."<<std::endl;
            return -1;
        }

        Mat frame, edge;
        namedWindow("edges", WINDOW_AUTOSIZE);
        while(1)
        {
            cap >> frame;
            //cvtColor(frame, edge, COLOR_BGR2GRAY);
            GaussianBlur(edge, edge, Size(7, 7), 1.5, 1.5);
            Canny(edge, edge, 0, 30, 3);
            imshow("edges", edge);
            if(waitKey(30) >= 0) break;
        }
        return 0;
    }
    catch (const cv::Exception& e)
    {
        const char* err_msg = e.what();
        std::cout << "exception caught: " << err_msg << std::endl;
    }
}