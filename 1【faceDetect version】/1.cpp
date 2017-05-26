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

	if(capture.isOpened()/*capture*/)	// 摄像头读取文件开关
	{
		//对每一帧做处理

		for(;;)
		{
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

				//轮廓检测
				vector<vector<Point>> _contours;//储存所有轮廓
				vector<Vec4i>hierarchy;
				vector<Rect> rectSeries;

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

					cout<<contArea<<endl;
					//cout<<"x == "<<r0.x<<endl;
					//cout<<"y == "<<r0.y<<endl;

					rectangle(outBinary,r0,cvScalar(255,255,255),1,8,0);
				}

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
