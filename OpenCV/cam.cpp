#include <opencv2/opencv.hpp>
#include <iostream> // Add missing include directive

int main()
{
    cv::VideoCapture cap(0); // 打开默认相机
    if (!cap.isOpened()) // 检查相机是否打开
    {
        std::cout << "Failed to open camera." << std::endl;
        return -1;
    }
    
    cv::Mat frame;
    while (true)
    {
        cap.read(frame); // 从相机中读取一帧图像
        cv::imshow("Camera", frame); // 显示图像
        if (cv::waitKey(30) == 27) // 按下ESC键退出
            break;
    }
    
    cap.release(); // 释放相机资源
    cv::destroyAllWindows(); // 关闭所有窗口
    
    return 0;
}
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;
int main()
{
    std::string image_path = "path/to/image";
    Mat img = imread(image_path, IMREAD_COLOR);

    imshow("Display window", img);
    int k = waitKey(0); // Wait for a keystroke in the window
    return 0;
}