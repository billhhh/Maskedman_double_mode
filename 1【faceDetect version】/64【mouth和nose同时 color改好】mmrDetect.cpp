//opencv2.0风格

//本程序有几个可调值
//1.背景更新 学习率 learningRate
//2.去掉小面积阈值 area_threshold

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

void findBoundary(Rect r,Point &a,Point &c);//找到贴合矩形框
void biggerRect(Point &a,Point &c,Mat img);  //将矩形框适当放大
void hugeRect(Point &a,Point &c,Mat img);   //如果比例缩小太大，直接将矩形巨大化
void detectAndDraw( Mat& img,
	CascadeClassifier& cascade, CascadeClassifier& nestedCascade,CascadeClassifier& thirdCascade,CascadeClassifier& mouthCascade,
	double scale);
void whThresholdOtsu(Mat &src, Mat &dst);
void cvSkinOtsu(Mat &src, Mat &dst);  //肤色检测
bool findMaskMan(Mat img); //真正找到是不是蒙面人（不用传地址过去）


String cascadeName = "./cascades.xml";//人头检测训练数据
String nestedCascadeName = "./haarcascades/haarcascade_frontalface_alt2.xml"; //第二层训练数据
String thirdCascadeName = "./haarcascades/haarcascade_mcs_nose.xml"; //第3层训练数据
String mouthCascadeName = "./haarcascades/haarcascade_mcs_mouth.xml"; //嘴巴训练数据

int cnt=0;//输出视频特定特征的数量
int nestedCnt=0;

VideoCapture capture;
int g_slider_position=0;


void onTrackbarSlide(int pos,void *)
{
	capture.set(CV_CAP_PROP_POS_FRAMES,pos);
}


//主函数
int main()
{
	/*char input_name[50];
	cout<<"请【拖入】要分析的视频："<<endl;
	cin>>input_name;*/
	//可调参数
	char* input_name = "4.mp4";
	//char* input_name = "E:\\蒙面人\\蒙面人识别1.avi";
	double fScale = 0.8;      //缩放倍数
	double learningRate=0.5;    // 控制背景累积学习的速率
	double area_threshold = 30;  //区域面积大小阈值
	int nThreshold=30; //二值化阈值



	CascadeClassifier cascade, nestedCascade,thirdCascade,mouthCascade;//创建级联分类器对象
	Mat frame_ori;		//每一帧原图像，绝不处理
	Mat frame;		//每一帧图像处理
	Mat gray;		//frame转成的灰度图
	Mat frame_copy_8U;	//copy过来的8U图像
	Mat frame_copy;
	Mat img1;		//差分输出
	Mat outBinary; //二值图输出
	int lastRectHeight=0; //一般都是矩形的高度变化，存储上一个矩形高度


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

	if( !thirdCascade.load( thirdCascadeName ) )
	{
		cerr << "WARNING: Could not load classifier cascade for thirdCascade objects" << endl;
		return 0;
	}

	if( !mouthCascade.load( mouthCascadeName ) )
	{
		cerr << "WARNING: Could not load classifier cascade for mouthCascade objects" << endl;
		return 0;
	}


	//从视频读入
	capture.open(input_name);
	

	int frameCount=(int) capture.get(CV_CAP_PROP_FRAME_COUNT);

	if(capture.isOpened()/*capture*/)	//读取文件开关
	{
		//对每一帧做处理

		for(;;)
		{

			//滑动条
			createTrackbar("Position","frame",&g_slider_position,frameCount,onTrackbarSlide);

			//单帧处理

			capture >> frame_ori;
			if(!frame_ori.empty())//如果捕捉到了
			{
				//10ms中按任意键进入此if块
				if( cvWaitKey( 10 ) == 27 )
					waitKey();

				cout<<"\n\n***************New Start********************"<<endl;


				//将原图像缩放
				resize(frame_ori,frame,Size(frame_ori.cols * fScale,frame_ori.rows * fScale),0,0,CV_INTER_LINEAR);
				//frame=frame_ori;

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
				threshold(img1, outBinary, nThreshold, 255, THRESH_BINARY);

				accumulateWeighted(gray, frame_copy,learningRate,outBinary);


				//加一个中值滤波，会减少不少误差
				cv::medianBlur(outBinary, outBinary,5);


				//初始化边界极值点坐标
				Point A,C;
				A.x=0x7fffffff; A.y=0x7fffffff;
				C.x=0; C.y=0;



				//轮廓检测
				vector<vector<Point>> _contours;//储存所有轮廓
				vector<Vec4i>hierarchy;

				cv::findContours( outBinary, _contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

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
					//rectangle(outBinary,r0,cvScalar(255,255,255),1,8,0);
				}
				cout<<"cnt == "<<cnt<<endl;
				cout<<"nestedCnt == "<<nestedCnt<<endl;

				biggerRect(A,C,frame);

				int a=A.x,b=A.y,c=C.x-A.x,d=C.y-A.y;

				//矩形框不存在，检测不了
				if (c<=0 || d<=0)
				{
					//cout<<"弹回去"<<endl;

					imshow("frame", frame);
					//imshow("outBinary", outBinary);

					cvWaitKey(1);
					continue;
				}

				if(d<lastRectHeight*0.7)
					hugeRect(A,C,frame);

				//得到要识别的矩形框
				Rect r=Rect(a,b,c,d);

				//画出一个大的框架
				//rectangle(outBinary,r,cvScalar(255,255,255),1,8,0);
				//rectangle(frame,r,cvScalar(255,255,255),1,8,0);

				//截取frame中的r矩形框大小
				Mat src=frame(r);

				//送去人脸检测			
				detectAndDraw(src,cascade, nestedCascade , thirdCascade ,mouthCascade ,1.0);

				imshow("frame", frame);
				//imshow("outBinary", outBinary);

				lastRectHeight=d;
			}

			else
			{ 
				printf(" --(!) No captured frame -- Break!");
				break;
			}


		}
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


void biggerRect(Point &a,Point &c,Mat img)
{
	if (c.x-a.x<0 || c.y-a.y<0)
		return;

	a.x -= 30;
	a.y -= 100;
	c.x += 30;
	c.y += 100;

	if(a.x<0)
		a.x=0;

	if(a.y<0)
		a.y=0;

	if(c.x>img.cols)
		c.x=img.cols;

	if(c.y>img.rows)
		c.y=img.rows;
}


void hugeRect(Point &a,Point &c,Mat img)
{
	a.y = 0;
	c.y = img.rows;
}


//人脸检测并画出
void detectAndDraw( Mat& img,
	CascadeClassifier& cascade, CascadeClassifier& nestedCascade,CascadeClassifier& thirdCascade,CascadeClassifier& mouthCascade ,
	double scale)
{
	bool isDetect=false;
	Mat img_ori=img.clone();

	//嘴巴检测手动开关
	//注释掉下一行语句打开嵌套特征的检测
	//nestedCascade.~CascadeClassifier() ;


	int i = 0;
	double t = 0;
	vector<Rect> faces;

	Mat gray, smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );//将图片缩小，加快检测速度

	cvtColor( img, gray, CV_BGR2GRAY );//因为用的是类haar特征，所以都是基于灰度图像的，这里要转换成灰度图像
	resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );//将尺寸缩小到1/scale,用线性插值
	equalizeHist( smallImg, smallImg );//直方图均衡

	t = (double)cvGetTickCount();//用来计算算法执行时间


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

	//检测人头，用红色标识
	for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++ )
	{
		Mat smallImgROI;
		vector<Rect> nestedObjects;
		Point center;
		Scalar headColor = CV_RGB(255,0,0);  //红色
		int radius;
		center.x = cvRound((r->x + r->width*0.5)*scale);//还原成原来的大小
		center.y = cvRound((r->y + r->height*0.5)*scale);
		radius = cvRound((r->width + r->height)*0.25*scale);
		circle( img, center, radius, headColor, 1, 8, 0 );
		
		cnt++;

		//检测嘴巴，在每幅人脸图上画出嵌套特征
		if( nestedCascade.empty() )
			continue;

		smallImgROI = img_ori(*r);

		//和上面的函数功能一样
		nestedCascade.detectMultiScale( smallImgROI, nestedObjects,
			1.1, 2, 0
			//|CV_HAAR_FIND_BIGGEST_OBJECT
			//|CV_HAAR_DO_ROUGH_SEARCH
			//|CV_HAAR_DO_CANNY_PRUNING
			|CV_HAAR_SCALE_IMAGE
			,
			Size(30, 30) );

		//人脸，用蓝色标识
		for( vector<Rect>::const_iterator nr = nestedObjects.begin(); nr != nestedObjects.end(); nr++ )
		{
			isDetect=true;

			Mat supSmallImg;
			vector<Rect> thirdNestedObjects;
			vector<Rect> mouthNestedObjects;

			Scalar faceColor = CV_RGB(0,0,255);  //蓝色
			center.x = cvRound((r->x + nr->x + nr->width*0.5)*scale);
			center.y = cvRound((r->y + nr->y + nr->height*0.5)*scale);
			radius = cvRound((nr->width + nr->height)*0.25*scale);
			circle( img, center, radius, faceColor, 1, 8, 0 );//将嘴巴也画出来，和对应人脸的图形是一样的

			nestedCnt++;

			supSmallImg = smallImgROI(*nr);

			//鼻子判别
			thirdCascade.detectMultiScale( supSmallImg, thirdNestedObjects,
				1.1, 2, 0
				|CV_HAAR_SCALE_IMAGE
				,
				Size(30, 30) );

			if (thirdNestedObjects.size()>0)
			{
				isDetect=false;
				cout<<"鼻子size："<<thirdNestedObjects.size()<<endl;
				waitKey();
			}

			//嘴巴判别
			thirdCascade.detectMultiScale( supSmallImg, mouthNestedObjects,
				1.1, 2, 0
				|CV_HAAR_SCALE_IMAGE
				,
				Size(30, 30) );

			if (mouthNestedObjects.size()>0)
			{
				isDetect=false;
				cout<<"嘴巴size："<<mouthNestedObjects.size()<<endl;
				waitKey();
			}
		}
		std::stringstream ss;
		std::string str;
		ss<<cnt;
		ss>>str;
		string path = "f:\\mmr\\";
		path.append(str);
		path.append(".jpg");

		if (isDetect == true)
		{
			//检测到蒙面人
			imshow("smallImgROI",smallImgROI);
			imwrite(path,smallImgROI);
			//cout<<path<<endl;
			//waitKey();
		}
	}//人头

}


