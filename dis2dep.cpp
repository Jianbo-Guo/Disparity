#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

const double fx = 4152.073;
const double baseline = 176.252;


int main(int argc, char** argv)
{
        Mat img = imread("/home/jianbo/progress/build/Disparity.png",0);
    cout << img.type();

   // Mat img = imread("E:\\intern\\depth\\disp0.png");
    Mat depth(img.rows, img.cols, CV_16UC1);  //深度图
    cout<< depth.type()<<endl;//https://blog.csdn.net/sysleo/article/details/96445786   查看图像类型，输出的数值去网站查表
    //视差图转深度图
    for (int row = 0; row < depth.rows; row++)
    {
        for (int col = 0; col < depth.cols; col++)
        {
            short d = img.ptr<uchar>(row)[col];


            if (d == 0)
                continue;

            depth.ptr<short>(row)[col] = fx * baseline / d;
        }
    }
    namedWindow("img", 0);
    namedWindow("depth", 0);
    imshow("img", img);
    imshow("depth", depth);
    imwrite("depth.png",depth);
    waitKey(0);
}

