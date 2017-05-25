#include "playthread.h"
#include <iostream>
#include <QImage>

using namespace std;
using namespace  cv;


//全局变量

String cascadeName = "./cascades.xml";//人头检测训练数据
String nestedCascadeName = "./haarcascades/haarcascade_frontalface_alt2.xml"; //正脸分类器

bool isDetect=false;
//cv::VideoCapture capture;

//int cnt=0;//输出视频特定特征的数量
//int nestedCnt=0;



//原来写在main函数里面的变量
double fScale = 0.8;      //缩放倍数
double learningRate=0.5;    // 控制背景累积学习的速率
double area_threshold = 30;  //区域面积大小阈值
int nThreshold=30; //二值化阈值



CascadeClassifier cascade, nestedCascade;//创建级联分类器对象
Mat frame_ori;		//每一帧原图像，绝不处理
Mat frame;		//每一帧图像处理
Mat gray;		//frame转成的灰度图
Mat frame_copy_8U;	//copy过来的8U图像
Mat frame_copy;
Mat img1;		//差分输出
Mat outBinary; //二值图输出
int lastRectHeight=0; //一般都是矩形的高度变化，存储上一个矩形高度

bool isPedestrian=false;




PlayThread::PlayThread(QObject *parent=0)
	: QThread(parent)
{
	isPlaying = false;
	slidePos = -1;
	pos = 0;
}

PlayThread::~PlayThread(){
}

void PlayThread::run()
{
	if(isAllAbstract){
		//cout<<capture.get(CV_CAP_PROP_FRAME_COUNT)<<endl;
		capture.set(CV_CAP_PROP_POS_FRAMES, pos);
		for(; isPlaying; pos++){
			if(pos >= frameCount){
					break;
			}


			if (slidePos>=0)
			{
				//如果拖动了滑动条
				capture.set(CV_CAP_PROP_POS_FRAMES, slidePos);
				pos = slidePos;
				slidePos = -1;
				emit sendSliderValue(pos);
			}


			capture>>frame_ori;

			//xxxx();
			//frame=myFaceDetect();


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
			//cout<<"cnt == "<<cnt<<endl;
			//cout<<"nestedCnt == "<<nestedCnt<<endl;

			biggerRect(A,C,frame);

			int a=A.x,b=A.y,c=C.x-A.x,d=C.y-A.y;

			//矩形框不存在，检测不了
			if (c<=0 || d<=0)
			{
				//cout<<"弹回去"<<endl;

				//imshow("frame", frame);

				//waitKey(1);
				//continue;
			}

			else
			{
				//cout<<"进入else"<<endl;

				if(d<lastRectHeight*0.7)
				hugeRect(A,C,frame);

				//得到要识别的矩形框
				Rect r=Rect(a,b,c,d);

				//画出一个大的框架
				//rectangle(frame,r,cvScalar(255,255,255),1,8,0);

				//截取frame中的r矩形框大小
				Mat src=frame(r);


				//送去人脸检测
				isPedestrian=false;
				detectAndDraw(src,cascade, nestedCascade,1.0);

				//检测出人头
				if(isDetect==false && isPedestrian==true)
					emit sendMmrInfo(1);

				//啥都没有
				else if(isDetect==false && isPedestrian==false)
					emit sendMmrInfo(0);

				//imshow("frame", frame);
				//waitKey(50);


				if(isDetect==true)
				{
					emit sendMmrInfo(2);
					//cout<<"isDetected"<<endl;
					imshow("检测到蒙面人，按任意键继续", src);
					waitKey(0);
					destroyWindow("检测到蒙面人，按任意键继续");
					isDetect=false;
				}

				lastRectHeight=d;
			}

			//resize(frame,iplImg,Size(frame_ori.cols / fScale,frame_ori.rows / fScale),0,0,CV_INTER_LINEAR);
			//iplImg=frame;
			//imshow("frame", frame);
			//waitKey(20);
			cvtColor(frame,iplImg,CV_BGR2RGB);

			*qImg = QImage(iplImg.data, iplImg.cols, iplImg.rows, QImage::Format_RGB888);
			emit sendPlayImage(*qImg);
			emit sendSliderValue(pos);
			msleep(10);
		}
		if(isPlaying){
			emit threadEnd();
		}
		//emit playEnd();
	}
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
	CascadeClassifier& cascade, CascadeClassifier& nestedCascade,
	double scale)
{
	//cout<<"进入detectAndDraw"<<endl;

	Mat img_ori=img.clone();

	//嘴巴检测手动开关
	//注释掉下一行语句打开嵌套特征的检测
	//nestedCascade.~CascadeClassifier() ;


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

	//t = (double)cvGetTickCount();//用来计算算法执行时间








	//检测到人头进入
	cascade.detectMultiScale( smallImg, faces,
		1.1, 2, 0
		//|CV_HAAR_FIND_BIGGEST_OBJECT
		//|CV_HAAR_DO_ROUGH_SEARCH
		|CV_HAAR_SCALE_IMAGE
		,
		Size(30, 30) );

	//t = (double)cvGetTickCount() - t;//相减为算法执行的时间
	//printf( "detection time = %g ms\n", t/((double)cvGetTickFrequency()*1000.) );

	for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++ )
	{
		//cout<<"检测到人头"<<endl;
		isPedestrian=true;

		Mat smallImgROI;
		vector<Rect> nestedObjects;
		Point center;
		Scalar color = colors[i%8];
		int radius;
		center.x = cvRound((r->x + r->width*0.5)*scale);//还原成原来的大小
		center.y = cvRound((r->y + r->height*0.5)*scale);
		radius = cvRound((r->width + r->height)*0.25*scale);
		//circle( img, center, radius, color, 3, 8, 0 );
		
		//cnt++;

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









		//检测到正脸进入
		for( vector<Rect>::const_iterator nr = nestedObjects.begin(); nr != nestedObjects.end(); nr++ )
		{
			Mat supSmallImg;
			Mat ssimgResult;

			center.x = cvRound((r->x + nr->x + nr->width*0.5)*scale);
			center.y = cvRound((r->y + nr->y + nr->height*0.5)*scale);
			radius = cvRound((nr->width + nr->height)*0.25*scale);
			//circle( img, center, radius, color, 3, 8, 0 );//将嘴巴也画出来，和对应人脸的图形是一样的

			//nestedCnt++;

			supSmallImg = smallImgROI(*nr);

			//imshow("supSmallImg",supSmallImg);
			cvSkinOtsu(supSmallImg, ssimgResult);
			//imshow("ssimgResult",ssimgResult);

			//findMaskMan(ssimgResult);

			if(findMaskMan(ssimgResult) == true)
			{
				isDetect=true;
				circle( img, center, radius, color, 3, 8, 0 );
			}
		}
	}


}

void whThresholdOtsu(Mat &src, Mat &dst)
{
	int height=src.rows;
	int width=src.cols;

	//histogram
	float histogram[256]={0};
	for(int i=0;i<height;i++) {
		unsigned char* p=(unsigned char*)src.data+src.step*i;
		for(int j=0;j<width;j++) {
			histogram[*p++]++;
		}
	}
	//normalize histogram
	int size=height*width;
	for(int i=0;i<256;i++) {
		histogram[i]=histogram[i]/size;
	}

	//average pixel value
	float avgValue=0;
	for(int i=0;i<256;i++) {
		avgValue+=i*histogram[i];
	}

	int threshold;	
	float maxVariance=0;
	float w=0,u=0;
	for(int i=0;i<256;i++) {
		w+=histogram[i];
		u+=i*histogram[i];

		float t=avgValue*w-u;
		float variance=t*t/(w*(1-w));
		if(variance>maxVariance) {
			maxVariance=variance;
			threshold=i;
		}
	}

	cv::threshold( src, dst, threshold, 255, THRESH_BINARY);
}

void cvSkinOtsu(Mat &src, Mat &dst)
{
	Mat ycrcb;
	Mat cr;
	cvtColor(src,ycrcb,CV_BGR2YCrCb);


	vector<Mat> mv;
	split(ycrcb,mv);

	whThresholdOtsu(mv[1],cr);

	dst = cr.clone();
}


bool findMaskMan(Mat img)
{
	//cout<<"进入findMaskMan"<<endl;

	double scale=0.3;

	int width = img.cols;
	int height = img.rows;

	//将矩形框定位在下半部分
	Rect r=Rect(0,height*(1-scale),width,height*scale);
	img=img(r);

	int count=countNonZero(img);

	int area=width*height*scale;
	double rate=(double)count/area;

	/*cout<<"长 == "<<width<<" 宽 == "<<height*scale<<endl;
	cout<<"面积 == "<<area<<endl;
	cout<<"count == "<<count<<endl;
	cout<<"占比 == "<<rate<<endl;*/

	if(rate<0.3)
	{
		//rectangle(img,r0,cvScalar(255,255,255),1,8,0);
		//cvWaitKey(0);

		return true;
	}

	return false;
}




bool PlayThread::init(QString filePath)
{
	this->filePath = filePath;
	//QByteArray ba = filePath.toLocal8Bit();
	//const char *file = ba.data();

	cout<<filePath.toStdString()<<endl;

	//	printf("filepath == %s\n",filePath);
	capture.open(filePath.toStdString());
	if(!capture.isOpened())
		return false;
	interval= 1;
	captureSize = Size((int)capture.get(CV_CAP_PROP_FRAME_WIDTH),
		(int)capture.get(CV_CAP_PROP_FRAME_HEIGHT));
	fps = (int)capture.get(CV_CAP_PROP_FPS);
	frameCount = (int)capture.get(CV_CAP_PROP_FRAME_COUNT);
	qImg = new QImage(QSize(captureSize.width,captureSize.height), QImage::Format_RGB888);
	iplImg.create(captureSize,  CV_8UC3);
	iplImg.data = qImg->bits();
	emit sendSliderRange(0, frameCount-1);
	isAllAbstract = true;

	//从指定的文件目录中加载级联分类器
	if( !cascade.load( cascadeName ) )
	{
		cerr << "ERROR: Could not load classifier cascade" << endl;
		return false;
	}

	//如果分类器没有正常加载，报错
	if( !nestedCascade.load( nestedCascadeName ) )
	{
		cerr << "WARNING: Could not load classifier cascade for nested objects" << endl;
		return false;
	}

	return true;
}

void PlayThread::getFrameByPos(int value){
	//capture.set(CV_CAP_PROP_POS_FRAMES, 50);

	this->slidePos = value;
	return;

	/*pos = value;
	
	cout<<"进入getFrameByPos()函数"<<endl;
	cout<<pos<<endl;

	cout<<capture.get(CV_CAP_PROP_FRAME_COUNT)<<endl;
	capture.set(CV_CAP_PROP_POS_FRAMES, pos);
	cout<<"1"<<endl;


	capture>> frame;

	cout<<"2"<<endl;

	cvtColor(frame,iplImg,CV_BGR2RGB);
	*qImg = QImage(iplImg.data, iplImg.cols, iplImg.rows, QImage::Format_RGB888);

	emit sendPlayImage(*qImg);*/
	//emit sendSliderValue(pos);
}
