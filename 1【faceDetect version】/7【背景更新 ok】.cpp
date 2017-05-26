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


static CvMemStorage* storage = 0;
static CvHaarClassifierCascade* cascade = 0;
const char* cascade_name = NULL;


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




//������Ⲣ����
void detect_and_draw( IplImage* img )
{
	//����Ҫ�Ŀ������ĺ���
	static CvScalar colors[] = 
	{//�������Ĳ�ͬ�ֺ���
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
		//cascade�Ƿ�������ȫ�ֱ���
		double t = (double)cvGetTickCount();

		//�������
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
	Mat frame;		//ÿһ֡ͼ��
	Mat gray;		//frameת�ɵĻҶ�ͼ
	Mat frame_copy_8U;	//copy������8Uͼ��
	Mat frame_copy;
	Mat img1;		//������
	Mat outBinary; //��ֵͼ���
	Mat outDilated;//�������

	double learningRate=0.01;    // ���Ʊ����ۻ�ѧϰ������


	//��ȡ�Զ����
	//Mat elementDilated = getStructuringElement(MORPH_RECT, Size(200, 200));




	//��ʼ��������
	cascade_name = "E:/Project/faceDetect/faceDetect/haarcascade_frontalface_alt2.xml";
	//���ط�����
	cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );

	//���������û���������أ�����
	if( !cascade )
	{
		fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
		return -1;
	}
	storage = cvCreateMemStorage(0);

	int nThreshold; //��ֵ����ֵ
	char* input_name = "004.avi";


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

// 					cout<<"A.x == "<<A.x<<endl;
// 					cout<<"A.y == "<<A.y<<endl;
// 					cout<<"C.x == "<<C.x<<endl;
// 					cout<<"C.y == "<<C.y<<endl;


					//ʵʱ����ÿ������
					//rectangle(outBinary,r0,cvScalar(255,255,255),1,8,0);
				}

				cout<<"A.x == "<<A.x<<endl;
				cout<<"A.y == "<<A.y<<endl;
				cout<<"C.x == "<<C.x<<endl;
				cout<<"C.y == "<<C.y<<endl;

				int a=A.x,b=A.y,c=C.x-A.x,d=C.y-A.y;

				if (c<0 || d<0)
					continue;

				//����һ����Ŀ��
				rectangle(outBinary,A,C,cvScalar(255,255,255),1,8,0);






				//��ԭͼƬת��iplimg��
				IplImage * src=&(IplImage)frame;

				//ԭ��cvSetImageROI(src , cvRect(x,y,width,height));
				cvSetImageROI(src,cvRect(a,b,c,d));

				IplImage * dst = cvCreateImage(cvSize(c,d),
					src->depth,
					src->nChannels);

				cvCopy(src,dst,0);
				cvResetImageROI(src);

				detect_and_draw(dst);

				//�ͷ���ʾ����ռ��dst
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

			//10ms�а�����������if��
			if( cvWaitKey( 10 ) >= 0 )
				break;
		}
	}

	return 0;
}
