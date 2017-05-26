//opencv2.0���

//��������2���ɵ�ֵ
//1.�������� ѧϰ�� learningRate
//2.ȥ��С�����ֵ area_threshold

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


//��������

void findBoundary(Rect r,Point &a,Point &c);
void biggerRect(Point &a,Point &c);


String cascadeName = "./haarcascades/haarcascade_frontalface_alt2.xml";//������ѵ������
//String nestedCascadeName = "./haarcascades/haarcascade_eye.xml";//���۵�ѵ�����ݣ�ͬ�����Լ��ر������
String nestedCascadeName = "./haarcascades/haarcascade_mcs_mouth.xml";//��͵�ѵ������


//������
int main()
{
	/*�ɵ�����*/
	char* input_name = "0010.mp4";
	double learningRate=0.01;    // ���Ʊ����ۻ�ѧϰ������
	double binThreshold=128;     //��ֵ����ֵ
	double area_threshold =50;  //���������С��ֵ

	// ��ϸ�˹����
	BackgroundSubtractorMOG mog;

	CascadeClassifier cascade, nestedCascade;//������������������
	Mat frame;		//ÿһ֡ͼ��
	Mat foreground;	// ǰ��ͼƬ

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


	//����Ƶ����
	VideoCapture capture(input_name);

	bool stop(false);
	while (!stop)
	{
		if (!capture.read(frame))
		{
			break;
		}

		// ���±���ͼƬ�������ǰ��
		mog(frame, foreground, learningRate);
		// �����ǰ��ͼƬ������2ֵͼƬ��Ҫ����һ����ʾ
		threshold(foreground, foreground, binThreshold, 255, THRESH_BINARY);
		
		//��ʼ���߽缫ֵ������
		Point A,C;
		A.x=0x7fffffff; A.y=0x7fffffff;
		C.x=0; C.y=0;

		//imshow("outBinary", foreground);


		//�������
		vector<vector<Point>> _contours;//������������
		vector<Vec4i>hierarchy;

		Mat imageROI;;
		cv::findContours(foreground, _contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

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
			rectangle(foreground,r0,cvScalar(255,255,255),1,8,0);
		}

		cout<<"A.x == "<<A.x<<endl;
		cout<<"A.y == "<<A.y<<endl;
		cout<<"C.x == "<<C.x<<endl;
		cout<<"C.y == "<<C.y<<endl;

		//�ʵ�������ο�
		//biggerRect(A,C);

		int a=A.x,b=A.y,c=C.x-A.x,d=C.y-A.y;

		if (c<0 || d<0)
		{
			c=0;
			d=0;
		}

		//�õ�Ҫʶ��ľ��ο�
		Rect r=Rect(a,b,c,d);

		//����һ����Ŀ��
		rectangle(foreground,r,cvScalar(255,255,255),1,8,0);
		//rectangle(frame,r,cvScalar(255,255,255),1,8,0);

		//���ο򲻴��ڣ���ⲻ��
		if (c==0 || d==0)
		{
			imshow("src", frame);
			imshow("result", foreground);

			cvWaitKey(1);
			continue;
		}

		//��ȡframe�е�r���ο��С
		Mat src=frame(r);

		imshow("result", foreground);
		imshow("src", frame);
		
		//10ms�а�����������if��
		if( cvWaitKey( 10 ) >= 0 )
			break;

		cout<<"\n\n*************************************"<<endl;
	}

	return 0;
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


//�ʵ�������ο�
void biggerRect(Point &a,Point &c)
{

}
