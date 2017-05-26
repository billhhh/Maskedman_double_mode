//opencv2.0风格

#include "cv.h"
#include "highgui.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include <iostream>
#include <cstdio>

using namespace std;
using namespace cv;


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







int main()
{
	Mat frame;		//每一帧图像
	Mat gray;		//frame转成的灰度图
	Mat frame_copy_8U;	//copy过来的8U图像
	Mat img1;		//差分输出
	Mat outBinary; //二值图输出
	Mat outDilated;//膨胀输出

	//获取自定义核
	Mat elementDilated = getStructuringElement(MORPH_RECT, Size(200, 200));

	int nThreshold; //二值化阈值
	char* input_name = "001.avi";


	//从视频读入
	VideoCapture capture(input_name);

	cvNamedWindow( "result", 1 );

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
				if (frame_copy_8U.empty())
				{
					//记录第一帧 gray->frame_copy
					gray.convertTo(frame_copy_8U, CV_8U);
				}

				//差分
				absdiff(frame_copy_8U, gray, img1);

				
				//二值化
				nThreshold=30;
				threshold(img1, outBinary, nThreshold, 255, THRESH_BINARY);



				//初始化边界极值点坐标
				Point A,C;
				A.x=0x3f3f3f; A.y=0x3f3f3f;
				C.x=0; C.y=0;



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
					findBoundary(r0,A,C);

					cout<<"A.x == "<<A.x<<endl;
					cout<<"A.y == "<<A.y<<endl;
					cout<<"C.x == "<<C.x<<endl;
					cout<<"C.y == "<<C.y<<endl;


					//实时画出每个矩形
					//rectangle(outBinary,r0,cvScalar(255,255,255),1,8,0);
				}

				//画出一个大的框架
				rectangle(outBinary,A,C,cvScalar(255,255,255),1,8,0);

				cout<<"\n\n*************************************"<<endl;

				imshow("src", frame);
				imshow("result", outBinary);

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
