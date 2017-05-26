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



//������
int main()
{
	/*�ɵ�����*/
	char* input_name = "003.avi";
	double learningRate=0.01;    // ���Ʊ����ۻ�ѧϰ������
	double area_threshold =50;  //���������С��ֵ
	double binThreshold=128;     //��ֵ����ֵ

	// ��ϸ�˹����
	BackgroundSubtractorMOG mog;

	Mat frame;		//ÿһ֡ͼ��
	Mat foreground;	// ǰ��ͼƬ

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


			//ʵʱ����ÿ������
			rectangle(foreground,r0,cvScalar(255,255,255),1,8,0);
		}

		
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
