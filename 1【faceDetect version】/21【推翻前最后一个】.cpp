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

void findBoundary(Rect r,Point &a,Point &c);
void biggerRect(Point &a,Point &c);


String cascadeName = "./haarcascades/haarcascade_frontalface_alt2.xml";//人脸的训练数据
//String nestedCascadeName = "./haarcascades/haarcascade_eye.xml";//人眼的训练数据，同样可以加载别的数据
String nestedCascadeName = "./haarcascades/haarcascade_mcs_mouth.xml";//嘴巴的训练数据


//主函数
int main()
{
	/*可调参数*/
	char* input_name = "0010.mp4";
	double learningRate=0.01;    // 控制背景累积学习的速率
	double binThreshold=128;     //二值化阈值
	double area_threshold =50;  //区域面积大小阈值

	// 混合高斯物体
	BackgroundSubtractorMOG mog;

	CascadeClassifier cascade, nestedCascade;//创建级联分类器对象
	Mat frame;		//每一帧图像
	Mat foreground;	// 前景图片

	//从指定的文件目录中加载级联分类器
	if( !cascade.load( cascadeName ) )
	{
		cerr << "ERROR: Could not load classifier cascade" << endl;
		return 0;
	}

	//如果分类器没有正常加载，报错
	if( !nestedCascade.load( nestedCascadeName ) )
	{
		cerr << "WARNING: Could not load classifier cascade for nested objects" << endl;
		return 0;
	}


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
		
		//初始化边界极值点坐标
		Point A,C;
		A.x=0x7fffffff; A.y=0x7fffffff;
		C.x=0; C.y=0;

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

			//找出最边界的点
			findBoundary(r0,A,C);


			//实时画出每个矩形
			rectangle(foreground,r0,cvScalar(255,255,255),1,8,0);
		}

		cout<<"A.x == "<<A.x<<endl;
		cout<<"A.y == "<<A.y<<endl;
		cout<<"C.x == "<<C.x<<endl;
		cout<<"C.y == "<<C.y<<endl;

		//适当扩大矩形框
		//biggerRect(A,C);

		int a=A.x,b=A.y,c=C.x-A.x,d=C.y-A.y;

		if (c<0 || d<0)
		{
			c=0;
			d=0;
		}

		//得到要识别的矩形框
		Rect r=Rect(a,b,c,d);

		//画出一个大的框架
		rectangle(foreground,r,cvScalar(255,255,255),1,8,0);
		//rectangle(frame,r,cvScalar(255,255,255),1,8,0);

		//矩形框不存在，检测不了
		if (c==0 || d==0)
		{
			imshow("src", frame);
			imshow("result", foreground);

			cvWaitKey(1);
			continue;
		}

		//截取frame中的r矩形框大小
		Mat src=frame(r);

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
