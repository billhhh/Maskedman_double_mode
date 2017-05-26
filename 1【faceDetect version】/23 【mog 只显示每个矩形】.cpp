//opencv2.0风格

//本程序有2个可调值
//1.背景更新 学习率 learningRate
//2.去掉小面积阈值 area_threshold

#include "cv.h"
#include "highgui.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/video/video.hpp>

#include <iostream>
#include <string>
#include <cstdio>

using namespace std;
using namespace cv;


//函数声明



//主函数
int main()
{
	/*可调参数*/
	char* input_name = "003.avi";
	double learningRate=0.01;    // 控制背景累积学习的速率
	double area_threshold =50;  //区域面积大小阈值
	double binThreshold=128;     //二值化阈值

	// 混合高斯物体
	BackgroundSubtractorMOG mog;

	Mat frame;		//每一帧图像
	Mat foreground;	// 前景图片

	//从视频读入
	VideoCapture capture(input_name);

	bool stop(false);
	while (!stop)
	{
		if (!capture.read(frame))
		{
			break;
		}

		// 更新背景图片并且输出前景
		mog(frame, foreground, learningRate);
		// 输出的前景图片并不是2值图片，要处理一下显示
		threshold(foreground, foreground, binThreshold, 255, THRESH_BINARY);
		

		//imshow("outBinary", foreground);


		//轮廓检测
		vector<vector<Point>> _contours;//储存所有轮廓
		vector<Vec4i>hierarchy;

		Mat imageROI;;
		cv::findContours(foreground, _contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

		for(size_t i = 0; i< _contours.size(); ++i)
		{
			//遍历所有轮廓

			//计算轮廓面积
			double contArea =  fabs(contourArea(_contours[i]));

			//去除较小面积的轮廓
			if( contArea < area_threshold)
				continue;

			//获得外接矩形
			Rect r0 = boundingRect(Mat(_contours[i]));


			//实时画出每个矩形
			rectangle(foreground,r0,cvScalar(255,255,255),1,8,0);
		}

		
		imshow("result", foreground);
		imshow("src", frame);
		
		//10ms中按任意键进入此if块
		if( cvWaitKey( 10 ) >= 0 )
			break;

		cout<<"\n\n*************************************"<<endl;
	}

	return 0;
}


//找一帧中所有矩形的边界四点
void findBoundary(Rect r,Point &a,Point &c)
{
	//a是矩形原点
	//c是原点对角线点

	//r.x还在a.x的左边
	if (r.x < a.x)
		a.x = r.x;

	//r.y 还在 a.y 上面
	if(r.y < a.y)
		a.y = r.y;

	//r.x+r.width 还在c.x的右边
	if ((r.x+r.width) > c.x)
		c.x = r.x+r.width;

	//(r.y+r.height) 还在 c.y 下面
	if((r.y+r.height) > c.y)
		c.y = r.y+r.height;
}


//适当扩大矩形框
void biggerRect(Point &a,Point &c)
{

}
