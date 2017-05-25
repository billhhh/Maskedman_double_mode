//opencv2.0风格

//本程序有几个可调值
//1.背景更新 学习率 learningRate
//2.去掉小面积阈值 area_threshold

#include <cv.h>
#include <highgui.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include <iostream>
#include <string>
#include <cstdio>

using namespace std;
using namespace cv;


//函数声明

int myFaceDetect(String fileName); //主函数
void findBoundary(Rect r,Point &a,Point &c);//找到贴合矩形框
void biggerRect(Point &a,Point &c,Mat img);  //将矩形框适当放大
void hugeRect(Point &a,Point &c,Mat img);   //如果比例缩小太大，直接将矩形巨大化
void pedDetection(Mat& img);//行人检测
void detectAndDraw( Mat& img,
	CascadeClassifier& cascade, CascadeClassifier& nestedCascade,
	double scale);
void whThresholdOtsu(Mat &src, Mat &dst);
void cvSkinOtsu(Mat &src, Mat &dst);  //肤色检测
bool findMaskMan(Mat img); //真正找到是不是蒙面人（不用传地址过去）