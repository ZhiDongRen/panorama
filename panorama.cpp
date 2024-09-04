#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main() {
    // 设置摄像头参数
    int camera_width = 1920;
    int camera_height = 1080;
    int camera_fps = 30;

    // 创建4个摄像头捕捉对象
    cv::VideoCapture camera1, camera2, camera3, camera4;
    camera1.open(0);
    camera2.open(1);
    camera3.open(2);
    camera4.open(3);

    // 检查摄像头是否打开
    if (!camera1.isOpened() || !camera2.isOpened() || !camera3.isOpened() || !camera4.isOpened()) {
        std::cout << "Error: unable to open camera" << std::endl;
        return -1;
    }

    // 创建一个窗口来显示拼接后的图像
    cv::namedWindow("Panorama", cv::WINDOW_NORMAL);

    while (true) {
        // 读取4个摄像头的图像
        cv::Mat frame1, frame2, frame3, frame4;
        camera1 >> frame1;
        camera2 >> frame2;
        camera3 >> frame3;
        camera4 >> frame4;

        // 对图像进行裁剪和拼接
        cv::Mat panorama;
        cv::Mat frame1_cropped = frame1(cv::Rect(0, 0, camera_width, camera_height));
        cv::Mat frame2_cropped = frame2(cv::Rect(0, 0, camera_width, camera_height));
        cv::Mat frame3_cropped = frame3(cv::Rect(0, 0, camera_width, camera_height));
        cv::Mat frame4_cropped = frame4(cv::Rect(0, 0, camera_width, camera_height));
        cv::vconcat(&frame1_cropped, &frame2_cropped, &panorama);
        cv::vconcat(&panorama, &frame3_cropped, &panorama);
        cv::vconcat(&panorama, &frame4_cropped, &panorama);

        // 展示拼接后的图像
        cv::imshow("Panorama", panorama);

        // 等待键盘输入
        char c = cv::waitKey(1);
        if (c == 'q') {
            break;
        }
    }

    // 释放摄像头对象
    camera1.release();
    camera2.release();
    camera3.release();
    camera4.release();

    return 0;
}