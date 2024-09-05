#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

// 函数：四路摄像头鸟瞰拼接算法
void stitchFourCameras(Mat& img1, Mat& img2, Mat& img3, Mat& img4, Mat& stitchedImg) {
    // Step 1：检测四个摄像头的角点

    vector<Point3f> ObjectPoints; //世界坐标系三维点
    vector<Point2f> ImgPoint;  //图像二维点
  
    vector<Point2f> corners1, corners2, corners3, corners4;
    goodFeaturesToTrack(img1, corners1, 100, 0.01, 10);
    goodFeaturesToTrack(img2, corners2, 100, 0.01, 10);
    goodFeaturesToTrack(img3, corners3, 100, 0.01, 10);
    goodFeaturesToTrack(img4, corners4, 100, 0.01, 10);

    // Step 2：计算四个摄像头之间的相对位移
    Mat distCoeffs;
    Mat Rvect1, Rvect2, Rvect3, Rvect4;
    Mat Tvect1, Tvect2, Tvect3, Tvect4;
    solvePnP(ObjectPoints, corners1, Mat::eye(3, 3, CV_32F), distCoeffs, Rvect1, Tvect1);  //  Mat::eye(3, 3, CV_32F)  = = cameraMatrix  
    solvePnP(ObjectPoints, corners2, Mat::eye(3, 3, CV_32F), distCoeffs, Rvect2, Tvect2);
    solvePnP(ObjectPoints, corners3, Mat::eye(3, 3, CV_32F), distCoeffs,Rvect3, Tvect3);
    solvePnP(ObjectPoints, corners4, Mat::eye(3, 3, CV_32F), distCoeffs, Rvect4, Tvect4);
    // Step 3：计算四个摄像头之间的相对平???
    Mat rotationMat1, rotationMat2, rotationMat3, rotationMat4;
    Rodrigues(Rvect1, rotationMat1);
    Rodrigues(Rvect2, rotationMat2);
    Rodrigues(Rvect3, rotationMat3);
    Rodrigues(Rvect4, rotationMat4);

    // Step 4：计算四个摄像头之间的相对变换
    Mat H1, H2, H3, H4;
    H1 = Mat::eye(3, 4, CV_32F);
    H1.at<float>(0, 3) = rotationMat1.at<float>(0, 0);
    H1.at<float>(1, 3) = rotationMat1.at<float>(1, 0);
    H1.at<float>(2, 3) = rotationMat1.at<float>(2, 0);

    H2 = Mat::eye(3, 4, CV_32F);
    H2.at<float>(0, 3) = rotationMat2.at<float>(0, 0);
    H2.at<float>(1, 3) = rotationMat2.at<float>(1, 0);
    H2.at<float>(2, 3) = rotationMat2.at<float>(2, 0);

    H3 = Mat::eye(3, 4, CV_32F);
    H3.at<float>(0, 3) = rotationMat3.at<float>(0, 0);
    H3.at<float>(1, 3) = rotationMat3.at<float>(1, 0);
    H3.at<float>(2, 3) = rotationMat3.at<float>(2, 0);

    H4 = Mat::eye(3, 4, CV_32F);
    H4.at<float>(0, 3) = rotationMat4.at<float>(0, 0);
    H4.at<float>(1, 3) = rotationMat4.at<float>(1, 0);
    H4.at<float>(2, 3) = rotationMat4.at<float>(2, 0);

    // Step 5：使用四个摄像头之间的相对变换进行拼接
    Mat stitchedImg1, stitchedImg2;
    warpPerspective(img1, stitchedImg1, H1, img1.size());
    warpPerspective(img2, stitchedImg2, H2, img2.size());

    Mat stitchedImg3, stitchedImg4;
    warpPerspective(img3, stitchedImg3, H3, img3.size());
    warpPerspective(img4, stitchedImg4, H4, img4.size());

    // Step 6：将四个摄像头拼接成一个图像
    stitchedImg = Mat::zeros(img1.size(), CV_8UC3);
    stitchedImg1.copyTo(stitchedImg(Rect(0, 0, stitchedImg1.cols, stitchedImg1.rows)));
    stitchedImg2.copyTo(stitchedImg(Rect(stitchedImg1.cols, 0, stitchedImg2.cols, stitchedImg2.rows)));
    stitchedImg3.copyTo(stitchedImg(Rect(0, stitchedImg1.rows, stitchedImg3.cols, stitchedImg3.rows)));
    stitchedImg4.copyTo(stitchedImg(Rect(stitchedImg3.cols, stitchedImg1.rows, stitchedImg4.cols, stitchedImg4.rows)));
}

int main() {
    // 加载四个摄像头图像
    try {
        Mat img1 = imread("img1.jpg");
        Mat img2 = imread("img2.jpg");
        Mat img3 = imread("img3.jpg");
        Mat img4 = imread("img4.jpg");
        
        Mat stitchedImg;
        stitchFourCameras(img1, img2, img3, img4, stitchedImg);
        // 显示拼接后的图像
        imshow("Stitched Image", stitchedImg);
        waitKey(0);
        return 0;
    }

    catch(double){
        cerr << "cant open img. \n";
    }


}

