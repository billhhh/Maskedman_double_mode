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


static CvMemStorage* storage = 0;
static CvHaarClassifierCascade* cascade = 0;
const char* cascade_name = NULL;


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




//人脸检测并画出
void detect_and_draw( IplImage* img )
{
	//最主要的框人脸的函数
	static CvScalar colors[] = 
	{//框人脸的不同种函数
		{{0,0,255}},
		{{0,128,255}},
		{{0,255,255}},
		{{0,255,0}},
		{{255,128,0}},
		{{255,255,0}},
		{{255,0,0}},
		{{255,0,255}}
	};

	double scale = 1.3;
	IplImage* gray = cvCreateImage( cvSize(img->width,img->height), 8, 1 );
	IplImage* small_img = cvCreateImage( cvSize( cvRound (img->width/scale),
		cvRound (img->height/scale)),
		8, 1 );
	int i;

	cvCvtColor( img, gray, CV_BGR2GRAY );
	cvResize( gray, small_img, CV_INTER_LINEAR );
	cvEqualizeHist( small_img, small_img );
	cvClearMemStorage( storage );


	if( cascade )
	{
		//cascade是分类器，全局变量
		double t = (double)cvGetTickCount();

		//检测脸部
		CvSeq* faces = cvHaarDetectObjects( small_img, cascade, storage,
			1.1, 2, 0/*CV_HAAR_DO_CANNY_PRUNING*/,
			cvSize(30, 30) );
		t = (double)cvGetTickCount() - t;
		printf( "detection time = %gms\n", t/((double)cvGetTickFrequency()*1000.) );
		for( i = 0; i < (faces ? faces->total : 0); i++ )
		{
			CvRect* r = (CvRect*)cvGetSeqElem( faces, i );
			CvPoint center;
			int radius;
			center.x = cvRound((r->x + r->width*0.5)*scale);
			center.y = cvRound((r->y + r->height*0.5)*scale);
			radius = cvRound((r->width + r->height)*0.25*scale);
			cvCircle( img, center, radius, colors[i%8], 3, 8, 0 );
		}
	}

	cvShowImage( "result", img );

	//cvWaitKey(0);
	cvReleaseImage( &gray );
	cvReleaseImage( &small_img );
}







int main()
{
	Mat frame;		//每一帧图像
	Mat gray;		//frame转成的灰度图
	Mat frame_copy_8U;	//copy过来的8U图像
	Mat frame_copy;
	Mat img1;		//差分输出
	Mat outBinary; //二值图输出
	Mat outDilated;//膨胀输出

	double learningRate=0.01;    // 控制背景累积学习的速率


	//获取自定义核
	//Mat elementDilated = getStructuringElement(MORPH_RECT, Size(200, 200));




	//初始化分类器
	cascade_name = "E:/Project/faceDetect/faceDetect/haarcascade_frontalface_alt2.xml";
	//加载分类器
	cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );

	//如果分类器没有正常加载，报错
	if( !cascade )
	{
		fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
		return -1;
	}
	storage = cvCreateMemStorage(0);

	int nThreshold; //二值化阈值
	char* input_name = "004.avi";


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

// 					cout<<"A.x == "<<A.x<<endl;
// 					cout<<"A.y == "<<A.y<<endl;
// 					cout<<"C.x == "<<C.x<<endl;
// 					cout<<"C.y == "<<C.y<<endl;


					//实时画出每个矩形
					//rectangle(outBinary,r0,cvScalar(255,255,255),1,8,0);
				}

				cout<<"A.x == "<<A.x<<endl;
				cout<<"A.y == "<<A.y<<endl;
				cout<<"C.x == "<<C.x<<endl;
				cout<<"C.y == "<<C.y<<endl;

				int a=A.x,b=A.y,c=C.x-A.x,d=C.y-A.y;

				if (c<0 || d<0)
					continue;

				//画出一个大的框架
				rectangle(outBinary,A,C,cvScalar(255,255,255),1,8,0);






				//将原图片转成iplimg型
				IplImage * src=&(IplImage)frame;

				//原型cvSetImageROI(src , cvRect(x,y,width,height));
				cvSetImageROI(src,cvRect(a,b,c,d));

				IplImage * dst = cvCreateImage(cvSize(c,d),
					src->depth,
					src->nChannels);

				cvCopy(src,dst,0);
				cvResetImageROI(src);

				detect_and_draw(dst);

				//释放显示分配空间的dst
				cvReleaseImage(&dst);





				cout<<"\n\n*************************************"<<endl;

				imshow("src", frame);
				imshow("outBinary", outBinary);

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
