#include <iostream>
#include <chrono>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<opencv2/calib3d/calib3d.hpp>

enum { STEREO_BM = 0, STEREO_SGBM = 1, STEREO_HH = 2, STEREO_VAR = 3, STEREO_3WAY = 4 };
 
void calDispWithSGBM(cv::Mat imgL, cv::Mat imgR, cv::Mat &imgDisparity8U)
{
	cv::Size imgSize = imgL.size();
	int numberOfDisparities = ((imgSize.width / 8) + 15) & -16;
	cv::Ptr<cv::StereoSGBM> sgbm = cv::StereoSGBM::create(0, 16, 3);
 
	sgbm->setPreFilterCap(63);
 
	int SADWindowSize = 9;
	int sgbmWinSize = SADWindowSize > 0 ? SADWindowSize : 3;
	sgbm->setBlockSize(sgbmWinSize);
 
	int cn = imgL.channels();
	sgbm->setP1(8 * cn*sgbmWinSize*sgbmWinSize);
	sgbm->setP2(32 * cn*sgbmWinSize*sgbmWinSize);
 
	sgbm->setMinDisparity(0);
	sgbm->setNumDisparities(numberOfDisparities);
	sgbm->setUniquenessRatio(10);
	sgbm->setSpeckleWindowSize(100);
	sgbm->setSpeckleRange(32);
	sgbm->setDisp12MaxDiff(1);
 
	int alg = STEREO_SGBM;
	if (alg == STEREO_HH)
		sgbm->setMode(cv::StereoSGBM::MODE_HH);
	else if (alg == STEREO_SGBM)
		sgbm->setMode(cv::StereoSGBM::MODE_SGBM);
	else if (alg == STEREO_3WAY)
		sgbm->setMode(cv::StereoSGBM::MODE_SGBM_3WAY);
 
	cv::Mat imgDisparity16S = cv::Mat(imgL.rows, imgL.cols, CV_16S);
	sgbm->compute(imgL, imgR, imgDisparity16S);
 
	//--Display it as a CV_8UC1 image：16位有符号转为8位无符号
	imgDisparity16S.convertTo(imgDisparity8U, CV_8U, 255 / (numberOfDisparities*16.));
    
}
 
int main()
{
	//--读取图像
	cv::Mat imgL = cv::imread("../Left.png", 0);
	cv::Mat imgR = cv::imread("../Right.png", 0);
 
	//--And create the image in which we will save our disparities
	cv::Mat imgDisparity8U = cv::Mat(imgL.rows, imgL.cols, CV_8UC1);
 
	//calDispWithBM(imgL, imgR, imgDisparity8U);
	calDispWithSGBM(imgL, imgR, imgDisparity8U);
    cv::imshow("imgDisparity16S",imgDisparity16S);
}
