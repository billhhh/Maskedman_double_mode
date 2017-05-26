//opencv2.0���

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


//��������

void findBoundary(Rect r,Point &a,Point &c,int &maxWidth,int &maxHeight);
void detectAndDraw( Mat& img,
	CascadeClassifier& cascade, CascadeClassifier& nestedCascade,
	double scale);


String cascadeName = "./haarcascades/haarcascade_frontalface_alt2.xml";//������ѵ������
String nestedCascadeName = "./haarcascades/haarcascade_eye.xml";//���۵�ѵ������

char* input_name = "003.avi";

//������

int main()
{
	CascadeClassifier cascade, nestedCascade;//������������������

	Mat frame;		//ÿһ֡ͼ��
	Mat gray;		//frameת�ɵĻҶ�ͼ
	Mat frame_copy_8U;	//copy������8Uͼ��
	Mat frame_copy;
	Mat img1;		//������
	Mat outBinary; //��ֵͼ���
	Mat outDilated;//�������

	double learningRate=0.6;    // ���Ʊ����ۻ�ѧϰ������


	//��ָ�����ļ�Ŀ¼�м��ؼ���������
	if( !cascade.load( cascadeName ) )
	{
		cerr << "ERROR: Could not load classifier cascade" << endl;
		return 0;
	}

	//���������û���������أ�����
	if( !nestedCascade.load( nestedCascadeName ) )
	{
		cerr << "WARNING: Could not load classifier cascade for nested objects" << endl;
		return 0;
	}

	int nThreshold; //��ֵ����ֵ


	//����Ƶ����
	VideoCapture capture(input_name);

	if(capture.isOpened()/*capture*/)	//��ȡ�ļ�����
	{
		//��ÿһ֡������

		for(;;)
		{

			//��֡����

			capture >> frame;
			if(!frame.empty())//�����׽����
			{
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
				nThreshold=30;
				threshold(img1, outBinary, nThreshold, 255, THRESH_BINARY);

				accumulateWeighted(gray, frame_copy,learningRate,outBinary);



				//��ʼ���߽缫ֵ������
				Point A,C;
				A.x=0x3f3f3f; A.y=0x3f3f3f;
				C.x=0; C.y=0;

				//������ο�����߿�
				int maxWidth=0,maxHeight=0;



				//�������
				vector<vector<Point>> _contours;//������������
				vector<Vec4i>hierarchy;

				Mat imageROI;;
				cv::findContours( outBinary, _contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

				double area_threshold = 50;
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

					//cout<<contArea<<endl;
					//cout<<"x == "<<r0.x<<endl;
					//cout<<"y == "<<r0.y<<endl;

					//�ҳ���߽�ĵ�
					findBoundary(r0,A,C,maxWidth,maxHeight);


					//ʵʱ����ÿ������
					//rectangle(outBinary,r0,cvScalar(255,255,255),1,8,0);
				}

				cout<<"A.x == "<<A.x<<endl;
				cout<<"A.y == "<<A.y<<endl;
				cout<<"C.x == "<<C.x<<endl;
				cout<<"C.y == "<<C.y<<endl;

				int a=A.x,b=A.y,c=maxWidth,d=maxHeight;


				//����һ����Ŀ��
				rectangle(outBinary,A,C,cvScalar(255,255,255),1,8,0);

				imshow("src", frame);
				imshow("outBinary", outBinary);


				cvWaitKey(1);
				
				if (c==0 || d==0)
					continue;

				//�õ�Ҫʶ��ľ��ο�
				Rect r=Rect(a,b,c,d);
				//��ȡframe�е�r���ο��С
				Mat src=frame(r);
				
				detectAndDraw(src,cascade, nestedCascade,1.3);

				cout<<"\n\n*************************************"<<endl;
			}

			else
			{ 
				printf(" --(!) No captured frame -- Break!");
				break;
			}

			//10ms�а�����������if��
			if( cvWaitKey( 10 ) >= 0 )
				break;
		}
	}

	return 0;
}


//��һ֡�����о��εı߽��ĵ�
void findBoundary(Rect r,Point &a,Point &c,int &maxWidth,int &maxHeight)
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


	//�õ����߿�
	if (r.width>maxWidth)
		maxWidth=r.width;

	if(r.height>maxHeight)
		maxHeight=r.height;
}


//������Ⲣ����
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
		CV_RGB(255,0,255)} ;//�ò�ͬ����ɫ��ʾ��ͬ������

	Mat gray, smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );//��ͼƬ��С���ӿ����ٶ�

	cvtColor( img, gray, CV_BGR2GRAY );//��Ϊ�õ�����haar���������Զ��ǻ��ڻҶ�ͼ��ģ�����Ҫת���ɻҶ�ͼ��
	resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );//���ߴ���С��1/scale,�����Բ�ֵ
	equalizeHist( smallImg, smallImg );//ֱ��ͼ����

	t = (double)cvGetTickCount();//���������㷨ִ��ʱ��


	//�������
	//detectMultiScale������smallImg��ʾ����Ҫ��������ͼ��ΪsmallImg��faces��ʾ��⵽������Ŀ�����У�1.1��ʾ
	//ÿ��ͼ��ߴ��С�ı���Ϊ1.1��2��ʾÿһ��Ŀ������Ҫ����⵽3�β��������Ŀ��(��Ϊ��Χ�����غͲ�ͬ�Ĵ��ڴ�
	//С�����Լ�⵽����),CV_HAAR_SCALE_IMAGE��ʾ�������ŷ���������⣬��������ͼ��Size(30, 30)ΪĿ���
	//��С���ߴ�
	cascade.detectMultiScale( smallImg, faces,
		1.1, 2, 0
		//|CV_HAAR_FIND_BIGGEST_OBJECT
		//|CV_HAAR_DO_ROUGH_SEARCH
		|CV_HAAR_SCALE_IMAGE
		,
		Size(30, 30) );

	t = (double)cvGetTickCount() - t;//���Ϊ�㷨ִ�е�ʱ��
	printf( "detection time = %g ms\n", t/((double)cvGetTickFrequency()*1000.) );
	for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++ )
	{
		Mat smallImgROI;
		vector<Rect> nestedObjects;
		Point center;
		Scalar color = colors[i%8];
		int radius;
		center.x = cvRound((r->x + r->width*0.5)*scale);//��ԭ��ԭ���Ĵ�С
		center.y = cvRound((r->y + r->height*0.5)*scale);
		radius = cvRound((r->width + r->height)*0.25*scale);
		circle( img, center, radius, color, 3, 8, 0 );

		//������ۣ���ÿ������ͼ�ϻ�������
		if( nestedCascade.empty() )
			continue;
		smallImgROI = smallImg(*r);

		//������ĺ�������һ��
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
			circle( img, center, radius, color, 3, 8, 0 );//���۾�Ҳ���������Ͷ�Ӧ������ͼ����һ����
		}
	}
	cv::imshow( "result", img );
}