//opencv2.0���

#include "cv.h"
#include "highgui.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include <iostream>
#include <cstdio>

using namespace std;
using namespace cv;


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







int main()
{
	Mat frame;		//ÿһ֡ͼ��
	Mat gray;		//frameת�ɵĻҶ�ͼ
	Mat frame_copy_8U;	//copy������8Uͼ��
	Mat img1;		//������
	Mat outBinary; //��ֵͼ���
	Mat outDilated;//�������

	//��ȡ�Զ����
	Mat elementDilated = getStructuringElement(MORPH_RECT, Size(200, 200));

	int nThreshold; //��ֵ����ֵ
	char* input_name = "001.avi";


	//����Ƶ����
	VideoCapture capture(input_name);

	cvNamedWindow( "result", 1 );

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
				if (frame_copy_8U.empty())
				{
					//��¼��һ֡ gray->frame_copy
					gray.convertTo(frame_copy_8U, CV_8U);
				}

				//���
				absdiff(frame_copy_8U, gray, img1);

				
				//��ֵ��
				nThreshold=30;
				threshold(img1, outBinary, nThreshold, 255, THRESH_BINARY);



				//��ʼ���߽缫ֵ������
				Point A,C;
				A.x=0x3f3f3f; A.y=0x3f3f3f;
				C.x=0; C.y=0;



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
					findBoundary(r0,A,C);

					cout<<"A.x == "<<A.x<<endl;
					cout<<"A.y == "<<A.y<<endl;
					cout<<"C.x == "<<C.x<<endl;
					cout<<"C.y == "<<C.y<<endl;


					//ʵʱ����ÿ������
					//rectangle(outBinary,r0,cvScalar(255,255,255),1,8,0);
				}

				//����һ����Ŀ��
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

			//10ms�а�����������if��
			if( cvWaitKey( 10 ) >= 0 )
				break;
		}
	}

	return 0;
}
