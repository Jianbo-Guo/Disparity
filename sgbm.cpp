#include <iostream>
#include <chrono>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/calib3d/calib3d.hpp>

using namespace std;
using namespace cv;


int main ( int argc, char** argv )
{
    double fx = 718.856, fy = 718.856, cx = 607.1928, cy = 185.2157;// 内参
    double b = 0.573;// 基线
        
    cout << "OpenCV version : " << CV_VERSION << endl;
   
    Mat leftImg=imread("../Left.png",0);
    Mat rightImg=imread("../Right.png",0);
  
    imshow ( "leftImg", leftImg);
    imshow ( "rightImg", rightImg);
    waitKey ( 0 );
    
    //OpenCV实现的SGBM立体匹配算法
    Ptr<StereoSGBM> sgbm = StereoSGBM::create(
        0,//minDisparity 最小视差
        96, //numDisparities 视差搜索范围，值必需为16的整数倍。最大搜索边界=最小视差+视差搜索范围
        9, //blockSize 块大小
        //8*cn*sgbm.SADWindowSize*sgbm.SADWindowSize;
        8 * 9 * 9, //P1 控制视差变化平滑性的参数。P1、P2的值越大，视差越平滑。P1是相邻像素点视差增/减 1 时的惩罚系数；P2是相邻像素点视差变化值大于1时的惩罚系数。P2必须大于P1。
        //32*cn*sgbm.SADWindowSize*sgbm.SADWindowSize
        32 * 9 * 9, //P2
        1, //disp12MaxDiff 左右一致性检测最大容许误差阈值。
        63, //preFilterCap,预处理时映射参数
        10, //uniquenessRatio 唯一性检测参数，
        100, //speckleWindowSize 视差连通区域像素点个数的大小。对于每一个视差点，当其连通区域的像素点个数小于speckleWindowSize时，认为该视差值无效，是噪点。
        32//speckleRange 视差连通条件，在计算一个视差点的连通区域时，当下一个像素点视差变化绝对值大于speckleRange就认为下一个视差像素点和当前视差像素点是不连通的。
    );
    
    Mat disparity_sgbm, disparity;
    sgbm->compute(leftImg, rightImg, disparity_sgbm); //计算视差图
    disparity_sgbm.convertTo(disparity, CV_32F, 1.0 / 16.0f);//得到视差图
    
    cv::imshow("disparity", disparity / 96.0);
    cv::waitKey(0);
    
    return 0;
}



