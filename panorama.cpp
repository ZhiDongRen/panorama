#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main() {
  
    int camera_width = 1920;
    int camera_height = 1080;
    int camera_fps = 30;


    cv::VideoCapture camera1, camera2, camera3, camera4;
    camera1.open(0);
    camera2.open(1);
    camera3.open(2);
    camera4.open(3);

    
    if (!camera1.isOpened() || !camera2.isOpened() || !camera3.isOpened() || !camera4.isOpened()) {
        std::cout << "Error: unable to open camera" << std::endl;
        return -1;
    }

    
    cv::namedWindow("Panorama", cv::WINDOW_NORMAL);

    while (true) {
     
        cv::Mat frame1, frame2, frame3, frame4;
        camera1 >> frame1;
        camera2 >> frame2;
        camera3 >> frame3;
        camera4 >> frame4;

        /*
        * 帧拼接
        * 打开4个摄像头，并从每个摄像头中读取帧。然后我们将这4个帧按照顶部两个和底部两个的方式拼接在一起，最终得到一个完整的鸟瞰图像。
        */
        cv::Mat topview, bottomRow;
        cv::Mat panorama;
        cv::Mat frame1_cropped = frame1(cv::Rect(0, 0, camera_width, camera_height));
        cv::Mat frame2_cropped = frame2(cv::Rect(0, 0, camera_width, camera_height));
        cv::Mat frame3_cropped = frame3(cv::Rect(0, 0, camera_width, camera_height));
        cv::Mat frame4_cropped = frame4(cv::Rect(0, 0, camera_width, camera_height));
        cv::hconcat(frame1_cropped, frame2_cropped, topview);
        cv::hconcat(frame3_cropped, frame4_cropped, bottomRow);
        cv::vconcat(topview, bottomRow, panorama);

    
        cv::imshow("Panorama", panorama);

       
        char c = cv::waitKey(1);
        if (c == 'q') {
            break;
        }
    }

    
    camera1.release();
    camera2.release();
    camera3.release();
    camera4.release();

    return 0;
}