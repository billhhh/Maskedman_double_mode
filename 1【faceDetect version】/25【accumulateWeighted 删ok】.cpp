//opencv2.0���

//��������2���ɵ�ֵ
//1.�������� ѧϰ�� learningRate
//2.ȥ��С�����ֵ area_threshold

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


//������
int main()
{
	/*�ɵ�����*/
	char* input_name = "003.avi";
	double learningRate=0.1;    // ���Ʊ����ۻ�ѧϰ������
	double area_threshold = 50;  //���������С��ֵ
	int nThreshold=30; //��ֵ����ֵ


	Mat frame;		//ÿһ֡ͼ��
	Mat gray;		//frameת�ɵĻҶ�ͼ
	Mat frame_copy_8U;	//copy������8Uͼ��
	Mat frame_copy;
	Mat img1;		//������
	Mat outBinary; //��ֵͼ���


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
				threshold(img1, outBinary, nThreshold, 255, THRESH_BINARY);

				accumulateWeighted(gray, frame_copy,learningRate,outBinary);


				//��ֵ�˲�
				//cv::medianBlur(outBinary, outBinary, 5);





				//�������
				vector<vector<Point>> _contours;//������������
				vector<Vec4i>hierarchy;

				Mat imageROI;;
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


					//ʵʱ����ÿ������
					rectangle(outBinary,r0,cvScalar(255,255,255),1,8,0);
				}

				imshow("src", frame);
				imshow("outBinary", outBinary);

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
