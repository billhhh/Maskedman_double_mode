//opencv2.0风格

#include "cv.h"
#include "highgui.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include <iostream>
#include <string>
#include <cstdio>

using namespace std;
using namespace cv;


//函数声明

void findBoundary(Rect r,Point &a,Point &c,int &maxWidth,int &maxHeight);
void detectAndDraw( Mat& img,
	CascadeClassifier& cascade, CascadeClassifier& nestedCascade,
	double scale);


String cascadeName = "./haarcascades/haarcascade_frontalface_alt2.xml";//人脸的训练数据
String nestedCascadeName = "./haarcascades/haarcascade_eye.xml";//人眼的训练数据

char* input_name = "003.avi";

//主函数

int main()
{
	CascadeClassifier cascade, nestedCascade;//创建级联分类器对象

	Mat frame;		//每一帧图像
	Mat gray;		//frame转成的灰度图
	Mat frame_copy_8U;	//copy过来的8U图像
	Mat frame_copy;
	Mat img1;		//差分输出
	Mat outBinary; //二值图输出
	Mat outDilated;//膨胀输出

	double learningRate=0.6;    // 控制背景累积学习的速率


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

	int nThreshold; //二值化阈值


	//从视频读入
	VideoCapture capture(input_name);

	if(capture.isOpened()/*capture*/)	//读取文件开关
	{
		//对每一帧做处理

		for(;;)
		{

			//单帧处理

			capture >> frame;
			if(!frame.empty())//如果捕捉到了
			{
				//frame->gray 单通道灰度图
				cvtColor(frame, gray, CV_BGR2GRAY);

				//进行处理
				if (frame_copy.empty())
				{
					//记录第一帧 gray->frame_copy
					gray.convertTo(frame_copy, CV_32F);
				}

				frame_copy.convertTo(frame_copy_8U, CV_8U);
				//差分
				absdiff(frame_copy_8U, gray, img1);


				//二值化
				nThreshold=30;
				threshold(img1, outBinary, nThreshold, 255, THRESH_BINARY);

				accumulateWeighted(gray, frame_copy,learningRate,outBinary);



				//初始化边界极值点坐标
				Point A,C;
				A.x=0x3f3f3f; A.y=0x3f3f3f;
				C.x=0; C.y=0;

				//保存矩形框的最大高宽
				int maxWidth=0,maxHeight=0;



				//轮廓检测
				vector<vector<Point>> _contours;//储存所有轮廓
				vector<Vec4i>hierarchy;

				Mat imageROI;;
				cv::findContours( outBinary, _contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

				double area_threshold = 50;
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

					//cout<<contArea<<endl;
					//cout<<"x == "<<r0.x<<endl;
					//cout<<"y == "<<r0.y<<endl;

					//找出最边界的点
					findBoundary(r0,A,C,maxWidth,maxHeight);


					//实时画出每个矩形
					//rectangle(outBinary,r0,cvScalar(255,255,255),1,8,0);
				}

				cout<<"A.x == "<<A.x<<endl;
				cout<<"A.y == "<<A.y<<endl;
				cout<<"C.x == "<<C.x<<endl;
				cout<<"C.y == "<<C.y<<endl;

				int a=A.x,b=A.y,c=maxWidth,d=maxHeight;


				//画出一个大的框架
				rectangle(outBinary,A,C,cvScalar(255,255,255),1,8,0);

				imshow("src", frame);
				imshow("outBinary", outBinary);


				cvWaitKey(1);
				
				if (c==0 || d==0)
					continue;

				//得到要识别的矩形框
				Rect r=Rect(a,b,c,d);
				//截取frame中的r矩形框大小
				Mat src=frame(r);
				
				detectAndDraw(src,cascade, nestedCascade,1.3);

				cout<<"\n\n*************************************"<<endl;
			}

			else
			{ 
				printf(" --(!) No captured frame -- Break!");
				break;
			}

			//10ms中按任意键进入此if块
			if( cvWaitKey( 10 ) >= 0 )
				break;
		}
	}

	return 0;
}


//找一帧中所有矩形的边界四点
void findBoundary(Rect r,Point &a,Point &c,int &maxWidth,int &maxHeight)
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


	//得到最大高宽
	if (r.width>maxWidth)
		maxWidth=r.width;

	if(r.height>maxHeight)
		maxHeight=r.height;
}


//人脸检测并画出
void detectAndDraw( Mat& img,
	CascadeClassifier& cascade, CascadeClassifier& nestedCascade,
	double scale)
{
	int i = 0;
	double t = 0;
	vector<Rect> faces;
	const static Scalar colors[] =  { CV_RGB(0,0,255),
		CV_RGB(0,128,255),
		CV_RGB(0,255,255),
		CV_RGB(0,255,0),
		CV_RGB(255,128,0),
		CV_RGB(255,255,0),
		CV_RGB(255,0,0),
		CV_RGB(255,0,255)} ;//用不同的颜色表示不同的人脸

	Mat gray, smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );//将图片缩小，加快检测速度

	cvtColor( img, gray, CV_BGR2GRAY );//因为用的是类haar特征，所以都是基于灰度图像的，这里要转换成灰度图像
	resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );//将尺寸缩小到1/scale,用线性插值
	equalizeHist( smallImg, smallImg );//直方图均衡

	t = (double)cvGetTickCount();//用来计算算法执行时间


	//检测人脸
	//detectMultiScale函数中smallImg表示的是要检测的输入图像为smallImg，faces表示检测到的人脸目标序列，1.1表示
	//每次图像尺寸减小的比例为1.1，2表示每一个目标至少要被检测到3次才算是真的目标(因为周围的像素和不同的窗口大
	//小都可以检测到人脸),CV_HAAR_SCALE_IMAGE表示不是缩放分类器来检测，而是缩放图像，Size(30, 30)为目标的
	//最小最大尺寸
	cascade.detectMultiScale( smallImg, faces,
		1.1, 2, 0
		//|CV_HAAR_FIND_BIGGEST_OBJECT
		//|CV_HAAR_DO_ROUGH_SEARCH
		|CV_HAAR_SCALE_IMAGE
		,
		Size(30, 30) );

	t = (double)cvGetTickCount() - t;//相减为算法执行的时间
	printf( "detection time = %g ms\n", t/((double)cvGetTickFrequency()*1000.) );
	for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++ )
	{
		Mat smallImgROI;
		vector<Rect> nestedObjects;
		Point center;
		Scalar color = colors[i%8];
		int radius;
		center.x = cvRound((r->x + r->width*0.5)*scale);//还原成原来的大小
		center.y = cvRound((r->y + r->height*0.5)*scale);
		radius = cvRound((r->width + r->height)*0.25*scale);
		circle( img, center, radius, color, 3, 8, 0 );

		//检测人眼，在每幅人脸图上画出人眼
		if( nestedCascade.empty() )
			continue;
		smallImgROI = smallImg(*r);

		//和上面的函数功能一样
		nestedCascade.detectMultiScale( smallImgROI, nestedObjects,
			1.1, 2, 0
			//|CV_HAAR_FIND_BIGGEST_OBJECT
			//|CV_HAAR_DO_ROUGH_SEARCH
			//|CV_HAAR_DO_CANNY_PRUNING
			|CV_HAAR_SCALE_IMAGE
			,
			Size(30, 30) );
		for( vector<Rect>::const_iterator nr = nestedObjects.begin(); nr != nestedObjects.end(); nr++ )
		{
			center.x = cvRound((r->x + nr->x + nr->width*0.5)*scale);
			center.y = cvRound((r->y + nr->y + nr->height*0.5)*scale);
			radius = cvRound((nr->width + nr->height)*0.25*scale);
			circle( img, center, radius, color, 3, 8, 0 );//将眼睛也画出来，和对应人脸的图形是一样的
		}
	}
	cv::imshow( "result", img );
}