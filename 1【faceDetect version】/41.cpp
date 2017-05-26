//opencv2.0���

//�������м����ɵ�ֵ
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

void findBoundary(Rect r,Point &a,Point &c);//�ҵ����Ͼ��ο�
void biggerRect(Point &a,Point &c,Mat img);  //�����ο��ʵ��Ŵ�
void hugeRect(Point &a,Point &c,Mat img);   //���������С̫��ֱ�ӽ����ξ޴�
void pedDetection(Mat& img);//���˼��
void detectAndDraw( Mat& img,
	CascadeClassifier& cascade, CascadeClassifier& nestedCascade,
	double scale);
void whThresholdOtsu(Mat &src, Mat &dst);
void cvSkinOtsu(Mat &src, Mat &dst);  //��ɫ���
void findMaskMan(Mat img); //�����ҵ��ǲ��������ˣ����ô���ַ��ȥ��



//String cascadeName = "./haarcascades/haarcascade_frontalface_alt2.xml";//������ѵ������
String cascadeName = "./cascades.xml";//��ͷ���ѵ������
//String cascadeName = "./mmr_cascade9.xml";

//String nestedCascadeName = "./haarcascades/haarcascade_eye.xml";//���۵�ѵ�����ݣ�ͬ�����Լ��ر������
//String nestedCascadeName = "./haarcascades/haarcascade_mcs_mouth.xml";//��͵�ѵ������
//String nestedCascadeName = "./mmr_cascade9.xml";
String nestedCascadeName = "./haarcascades/haarcascade_frontalface_alt2.xml";

int cnt=0;//�����Ƶ�ض�����������
int nestedCnt=0;


//������
int main()
{
	//�ɵ�����
	char* input_name = "1.mp4";
	//char* input_name = "E:\\������\\������ʶ��1.avi";
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

	if(capture.isOpened()/*capture*/)	//��ȡ�ļ�����
	{
		//��ÿһ֡������

		for(;;)
		{

			//��֡����

			capture >> frame_ori;
			if(!frame_ori.empty())//�����׽����
			{
				cout<<"\n\n***************New Start********************"<<endl;


				//��ԭͼ������
				resize(frame_ori,frame,Size(frame_ori.cols * fScale,frame_ori.rows * fScale),0,0,CV_INTER_LINEAR);
				//frame=frame_ori;


				//��ȥ���˼��
				//pedDetection(frame);

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
					rectangle(outBinary,r0,cvScalar(255,255,255),1,8,0);
				}
				cout<<"cnt == "<<cnt<<endl;
				cout<<"nestedCnt == "<<nestedCnt<<endl;

				biggerRect(A,C,frame);

				/*cout<<"A.x == "<<A.x<<endl;
				cout<<"A.y == "<<A.y<<endl;
				cout<<"C.x == "<<C.x<<endl;
				cout<<"C.y == "<<C.y<<endl;*/

				int a=A.x,b=A.y,c=C.x-A.x,d=C.y-A.y;

				//���ο򲻴��ڣ���ⲻ��
				if (c<=0 || d<=0)
				{
					//cout<<"����ȥ"<<endl;

					imshow("src", frame);
					imshow("outBinary", outBinary);

					cvWaitKey(1);
					continue;
				}

				if(d<lastRectHeight*0.7)
					hugeRect(A,C,frame);

				//�õ�Ҫʶ��ľ��ο�
				Rect r=Rect(a,b,c,d);

				//����һ����Ŀ��
				rectangle(outBinary,r,cvScalar(255,255,255),1,8,0);
				rectangle(frame,r,cvScalar(255,255,255),1,8,0);

				/*cout<<"r.x "<<r.x<<endl;
				cout<<"r.y "<<r.y<<endl;
				cout<<"r.width "<<r.width<<endl;
				cout<<"r.height "<<r.height<<endl;
				cout<<"frame.cols "<<frame.cols<<endl;
				cout<<"frame.rows "<<frame.rows<<endl;*/

				//��ȡframe�е�r���ο��С
				Mat src=frame(r);

				//��ȥ���˼��
				//pedDetection(src);

				//��ȥ�������			
				detectAndDraw(src,cascade, nestedCascade,1.0);

				imshow("src", frame);
				imshow("outBinary", outBinary);

				lastRectHeight=d;
			}

			else
			{ 
				printf(" --(!) No captured frame -- Break!");
				break;
			}

			//10ms�а�����������if��
			if( cvWaitKey( 10 ) == 27 )
				break;
		}
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



//���˼��
void pedDetection(Mat& image)
{
	// 1. ����HOG����
	cv::HOGDescriptor hog; // ����Ĭ�ϲ��� 64*128 ������Ϊ��λ��


	// 2. ����SVM������
	hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());   // �����Ѿ�ѵ���õ����˼�������

	// 3. �ڲ���ͼ���ϼ����������
	std::vector<cv::Rect> regions;
	hog.detectMultiScale(image, regions, 0, cv::Size(8,8), cv::Size(32,32), 1.05, 1);

	if(regions.size()>0)
	{
		printf("��һ����!!!!!!!!!!!!!!!!\n");
		printf("��һ����!!!!!!!!!!!!!!!!\n");
		printf("��һ����!!!!!!!!!!!!!!!!\n");
		printf("��һ����!!!!!!!!!!!!!!!!\n");
		printf("��һ����!!!!!!!!!!!!!!!!\n");
		printf("��һ����!!!!!!!!!!!!!!!!\n");
	}
	

	// ��ʾ
	for (size_t i = 0; i < regions.size(); i++)
	{
		cv::rectangle(image, regions[i], cv::Scalar(0,0,255), 2);
	} 

	cv::imshow("hog", image);
}



//������Ⲣ����
void detectAndDraw( Mat& img,
	CascadeClassifier& cascade, CascadeClassifier& nestedCascade,
	double scale)
{
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
		
		cnt++;

		//�����ͣ���ÿ������ͼ�ϻ���Ƕ������
		if( nestedCascade.empty() )
			continue;

		/*printf("down here!!!!!!!!!!!!!!!!\n");
		printf("down here!!!!!!!!!!!!!!!!\n");
		printf("down here!!!!!!!!!!!!!!!!\n");
		printf("down here!!!!!!!!!!!!!!!!\n");
		printf("down here!!!!!!!!!!!!!!!!\n");*/

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
		for( vector<Rect>::const_iterator nr = nestedObjects.begin(); nr != nestedObjects.end(); nr++ )
		{
			Mat supSmallImg;
			Mat ssimgResult;

			center.x = cvRound((r->x + nr->x + nr->width*0.5)*scale);
			center.y = cvRound((r->y + nr->y + nr->height*0.5)*scale);
			radius = cvRound((nr->width + nr->height)*0.25*scale);
			circle( img, center, radius, color, 3, 8, 0 );//�����Ҳ���������Ͷ�Ӧ������ͼ����һ����

			nestedCnt++;

			supSmallImg = smallImgROI(*nr);

			imshow("supSmallImg",supSmallImg);

			cvSkinOtsu(supSmallImg, ssimgResult);

			imshow("supSmallImg",ssimgResult);

			findMaskMan(ssimgResult);
		}
	}

	//������һ����ʱ����Ӧ
	//cvWaitKey(10);

	//cv::imshow( "result", img );
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

	//show ycrcb, test
	//imshow("ycrcb",ycrcb);

	vector<Mat> mv;
	split(ycrcb,mv);

	whThresholdOtsu(mv[1],cr);
	imshow("out2",cr);

	//cvWaitKey(0);

	dst = cr.clone();
}


void findMaskMan(Mat img)
{
	int area_threshold=1;
	//�������
	vector<vector<Point>> _contours;//������������
	vector<Vec4i>hierarchy;

	cv::findContours( img, _contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	cout<<"contours.size == "<<_contours.size()<<endl;
	int count=_contours.size();

	for(size_t i = 0; i< _contours.size(); ++i)
	{
		//������������

		//�����������
		double contArea =  fabs(contourArea(_contours[i]));
		//cout<<"contArea == "<<contArea<<endl;

		//ȥ����С���������
		if( contArea < area_threshold)
		{
			count--;
			continue;
		}

		//�����Ӿ���
		Rect r0 = boundingRect(Mat(_contours[i]));


		//ʵʱ����ÿ������
		rectangle(img,r0,cvScalar(255,255,255),1,8,0);
	}

	imshow("rectangle",img);

	if(count>1)
	{
		//rectangle(img,r0,cvScalar(255,255,255),1,8,0);
		cvWaitKey(0);
	}
}
