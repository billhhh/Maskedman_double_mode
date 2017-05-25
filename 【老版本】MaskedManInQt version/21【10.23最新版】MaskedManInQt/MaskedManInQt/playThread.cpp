#include "playthread.h"
#include <iostream>
#include <QImage>

using namespace std;
using namespace  cv;


//ȫ�ֱ���

String cascadeName = "./cascades.xml";//��ͷ���ѵ������
String nestedCascadeName = "./haarcascades/haarcascade_frontalface_alt2.xml"; //����������

bool isDetect=false;
//cv::VideoCapture capture;

//int cnt=0;//�����Ƶ�ض�����������
//int nestedCnt=0;



//ԭ��д��main��������ı���
double fScale = 0.8;      //���ű���
double learningRate=0.5;    // ���Ʊ����ۻ�ѧϰ������
double area_threshold = 30;  //���������С��ֵ
int nThreshold=30; //��ֵ����ֵ



CascadeClassifier cascade, nestedCascade;//������������������
Mat frame_ori;		//ÿһ֡ԭͼ�񣬾�������
Mat frame;		//ÿһ֡ͼ����
Mat gray;		//frameת�ɵĻҶ�ͼ
Mat frame_copy_8U;	//copy������8Uͼ��
Mat frame_copy;
Mat img1;		//������
Mat outBinary; //��ֵͼ���
int lastRectHeight=0; //һ�㶼�Ǿ��εĸ߶ȱ仯���洢��һ�����θ߶�

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
				//����϶��˻�����
				capture.set(CV_CAP_PROP_POS_FRAMES, slidePos);
				pos = slidePos;
				slidePos = -1;
				emit sendSliderValue(pos);
			}


			capture>>frame_ori;

			//xxxx();
			//frame=myFaceDetect();


			//��ԭͼ������
			resize(frame_ori,frame,Size(frame_ori.cols * fScale,frame_ori.rows * fScale),0,0,CV_INTER_LINEAR);
			//frame=frame_ori;


			//frame->gray ��ͨ���Ҷ�ͼ
			cvtColor(frame, gray, CV_BGR2GRAY);

			//���д���
			if (frame_copy.empty())
			{
				//��¼��һ֡ gray->frame_copy
				gray.convertTo(frame_copy, CV_32F);
			}

			frame_copy.convertTo(frame_copy_8U, CV_8U);
			//���
			absdiff(frame_copy_8U, gray, img1);


			//��ֵ��
			threshold(img1, outBinary, nThreshold, 255, THRESH_BINARY);

			accumulateWeighted(gray, frame_copy,learningRate,outBinary);


			//��һ����ֵ�˲�������ٲ������
			cv::medianBlur(outBinary, outBinary,5);


			//��ʼ���߽缫ֵ������
			Point A,C;
			A.x=0x7fffffff; A.y=0x7fffffff;
			C.x=0; C.y=0;



			//�������
			vector<vector<Point>> _contours;//������������
			vector<Vec4i>hierarchy;

			cv::findContours( outBinary, _contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

			for(size_t i = 0; i< _contours.size(); ++i)
			{
				//������������

				//�����������
				double contArea =  fabs(contourArea(_contours[i]));

				//ȥ����С���������
				if( contArea < area_threshold)
					continue;

				//�����Ӿ���
				Rect r0 = boundingRect(Mat(_contours[i]));


				//�ҳ���߽�ĵ�
				findBoundary(r0,A,C);


				//ʵʱ����ÿ������
				//rectangle(outBinary,r0,cvScalar(255,255,255),1,8,0);
			}
			//cout<<"cnt == "<<cnt<<endl;
			//cout<<"nestedCnt == "<<nestedCnt<<endl;

			biggerRect(A,C,frame);

			int a=A.x,b=A.y,c=C.x-A.x,d=C.y-A.y;

			//���ο򲻴��ڣ���ⲻ��
			if (c<=0 || d<=0)
			{
				//cout<<"����ȥ"<<endl;

				//imshow("frame", frame);

				//waitKey(1);
				//continue;
			}

			else
			{
				//cout<<"����else"<<endl;

				if(d<lastRectHeight*0.7)
				hugeRect(A,C,frame);

				//�õ�Ҫʶ��ľ��ο�
				Rect r=Rect(a,b,c,d);

				//����һ����Ŀ��
				//rectangle(frame,r,cvScalar(255,255,255),1,8,0);

				//��ȡframe�е�r���ο��С
				Mat src=frame(r);


				//��ȥ�������
				isPedestrian=false;
				detectAndDraw(src,cascade, nestedCascade,1.0);

				//������ͷ
				if(isDetect==false && isPedestrian==true)
					emit sendMmrInfo(1);

				//ɶ��û��
				else if(isDetect==false && isPedestrian==false)
					emit sendMmrInfo(0);

				//imshow("frame", frame);
				//waitKey(50);


				if(isDetect==true)
				{
					emit sendMmrInfo(2);
					//cout<<"isDetected"<<endl;
					imshow("��⵽�����ˣ������������", src);
					waitKey(0);
					destroyWindow("��⵽�����ˣ������������");
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







//��һ֡�����о��εı߽��ĵ�
void findBoundary(Rect r,Point &a,Point &c)
{
	//a�Ǿ���ԭ��
	//c��ԭ��Խ��ߵ�

	//r.x����a.x�����
	if (r.x < a.x)
		a.x = r.x;

	//r.y ���� a.y ����
	if(r.y < a.y)
		a.y = r.y;

	//r.x+r.width ����c.x���ұ�
	if ((r.x+r.width) > c.x)
		c.x = r.x+r.width;

	//(r.y+r.height) ���� c.y ����
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



//������Ⲣ����
void detectAndDraw( Mat& img,
	CascadeClassifier& cascade, CascadeClassifier& nestedCascade,
	double scale)
{
	//cout<<"����detectAndDraw"<<endl;

	Mat img_ori=img.clone();

	//��ͼ���ֶ�����
	//ע�͵���һ������Ƕ�������ļ��
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
		CV_RGB(255,0,255)} ;//�ò�ͬ����ɫ��ʾ��ͬ������

	Mat gray, smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );//��ͼƬ��С���ӿ����ٶ�

	cvtColor( img, gray, CV_BGR2GRAY );//��Ϊ�õ�����haar���������Զ��ǻ��ڻҶ�ͼ��ģ�����Ҫת���ɻҶ�ͼ��
	resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );//���ߴ���С��1/scale,�����Բ�ֵ
	equalizeHist( smallImg, smallImg );//ֱ��ͼ����

	//t = (double)cvGetTickCount();//���������㷨ִ��ʱ��








	//��⵽��ͷ����
	cascade.detectMultiScale( smallImg, faces,
		1.1, 2, 0
		//|CV_HAAR_FIND_BIGGEST_OBJECT
		//|CV_HAAR_DO_ROUGH_SEARCH
		|CV_HAAR_SCALE_IMAGE
		,
		Size(30, 30) );

	//t = (double)cvGetTickCount() - t;//���Ϊ�㷨ִ�е�ʱ��
	//printf( "detection time = %g ms\n", t/((double)cvGetTickFrequency()*1000.) );

	for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++ )
	{
		//cout<<"��⵽��ͷ"<<endl;
		isPedestrian=true;

		Mat smallImgROI;
		vector<Rect> nestedObjects;
		Point center;
		Scalar color = colors[i%8];
		int radius;
		center.x = cvRound((r->x + r->width*0.5)*scale);//��ԭ��ԭ���Ĵ�С
		center.y = cvRound((r->y + r->height*0.5)*scale);
		radius = cvRound((r->width + r->height)*0.25*scale);
		//circle( img, center, radius, color, 3, 8, 0 );
		
		//cnt++;

		//�����ͣ���ÿ������ͼ�ϻ���Ƕ������
		if( nestedCascade.empty() )
			continue;



		smallImgROI = img_ori(*r);

		//������ĺ�������һ��
		nestedCascade.detectMultiScale( smallImgROI, nestedObjects,
			1.1, 2, 0
			//|CV_HAAR_FIND_BIGGEST_OBJECT
			//|CV_HAAR_DO_ROUGH_SEARCH
			//|CV_HAAR_DO_CANNY_PRUNING
			|CV_HAAR_SCALE_IMAGE
			,
			Size(30, 30) );









		//��⵽��������
		for( vector<Rect>::const_iterator nr = nestedObjects.begin(); nr != nestedObjects.end(); nr++ )
		{
			Mat supSmallImg;
			Mat ssimgResult;

			center.x = cvRound((r->x + nr->x + nr->width*0.5)*scale);
			center.y = cvRound((r->y + nr->y + nr->height*0.5)*scale);
			radius = cvRound((nr->width + nr->height)*0.25*scale);
			//circle( img, center, radius, color, 3, 8, 0 );//�����Ҳ���������Ͷ�Ӧ������ͼ����һ����

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
	//cout<<"����findMaskMan"<<endl;

	double scale=0.3;

	int width = img.cols;
	int height = img.rows;

	//�����ο�λ���°벿��
	Rect r=Rect(0,height*(1-scale),width,height*scale);
	img=img(r);

	int count=countNonZero(img);

	int area=width*height*scale;
	double rate=(double)count/area;

	/*cout<<"�� == "<<width<<" �� == "<<height*scale<<endl;
	cout<<"��� == "<<area<<endl;
	cout<<"count == "<<count<<endl;
	cout<<"ռ�� == "<<rate<<endl;*/

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

	//��ָ�����ļ�Ŀ¼�м��ؼ���������
	if( !cascade.load( cascadeName ) )
	{
		cerr << "ERROR: Could not load classifier cascade" << endl;
		return false;
	}

	//���������û���������أ�����
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
	
	cout<<"����getFrameByPos()����"<<endl;
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
