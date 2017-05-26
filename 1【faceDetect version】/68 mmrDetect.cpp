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
void detectAndDraw( Mat& img,
	CascadeClassifier& cascade, CascadeClassifier& nestedCascade,
	CascadeClassifier& thirdCascade,CascadeClassifier& mouthCascade,
	double scale);
void whThresholdOtsu(Mat &src, Mat &dst);
void cvSkinOtsu(Mat &src, Mat &dst);  //��ɫ���
bool findMaskMan(Mat img); //�����ҵ��ǲ��������ˣ����ô���ַ��ȥ��


String cascadeName = "./cascades.xml";//��ͷ���ѵ������
String nestedCascadeName = "./haarcascades/haarcascade_frontalface_alt2.xml"; //�ڶ���ѵ������
String thirdCascadeName = "./haarcascades/haarcascade_mcs_nose.xml"; //��3��ѵ������
String mouthCascadeName = "./haarcascades/haarcascade_mcs_mouth.xml"; //���ѵ������
CascadeClassifier cascade, nestedCascade,thirdCascade,mouthCascade;//������������������

int cnt=0;//�����Ƶ�ض�����������
int nestedCnt=0;

VideoCapture capture;
int g_slider_position=0;


void onTrackbarSlide(int pos,void *)
{
	capture.set(CV_CAP_PROP_POS_FRAMES,pos);
}


//��⺯��
int faceDetect()
{
	/*char input_name[50];
	cout<<"�롾���롿Ҫ��������Ƶ��"<<endl;
	cin>>input_name;*/
	//�ɵ�����
	char* input_name = "4.mp4";
	//char* input_name = "E:\\������\\������ʶ��1.avi";
	double fScale = 0.8;      //���ű���
	double learningRate=0.5;    // ���Ʊ����ۻ�ѧϰ������
	double area_threshold = 30;  //���������С��ֵ
	int nThreshold=30; //��ֵ����ֵ

	Mat frame_ori;		//ÿһ֡ԭͼ�񣬾�������
	Mat frame;		//ÿһ֡ͼ����
	Mat gray;		//frameת�ɵĻҶ�ͼ
	Mat frame_copy_8U;	//copy������8Uͼ��
	Mat frame_copy;
	Mat img1;		//������
	Mat outBinary; //��ֵͼ���
	int lastRectHeight=0; //һ�㶼�Ǿ��εĸ߶ȱ仯���洢��һ�����θ߶�


	//����Ƶ����
	capture.open(input_name);
	

	int frameCount=(int) capture.get(CV_CAP_PROP_FRAME_COUNT);

	if(capture.isOpened()/*capture*/)	//��ȡ�ļ�����
	{
		//��ÿһ֡������

		for(;;)
		{

			//������
			createTrackbar("Position","frame",&g_slider_position,frameCount,onTrackbarSlide);

			//��֡����

			capture >> frame_ori;
			if(!frame_ori.empty())//�����׽����
			{
				//10ms�а�����������if��
				if( cvWaitKey( 1 ) == 27 )
					waitKey();

				cout<<"\n\n***************New Start********************"<<endl;


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
				cout<<"cnt == "<<cnt<<endl;
				cout<<"nestedCnt == "<<nestedCnt<<endl;

				biggerRect(A,C,frame);

				int a=A.x,b=A.y,c=C.x-A.x,d=C.y-A.y;

				//���ο򲻴��ڣ���ⲻ��
				if (c<=0 || d<=0)
				{
					//cout<<"����ȥ"<<endl;

					imshow("frame", frame);
					//imshow("outBinary", outBinary);

					cvWaitKey(1);
					continue;
				}

				if(d<lastRectHeight*0.7)
					hugeRect(A,C,frame);

				//�õ�Ҫʶ��ľ��ο�
				Rect r=Rect(a,b,c,d);

				//����һ����Ŀ��
				//rectangle(outBinary,r,cvScalar(255,255,255),1,8,0);
				//rectangle(frame,r,cvScalar(255,255,255),1,8,0);

				//��ȡframe�е�r���ο��С
				Mat src=frame(r);

				//��ȥ�������			
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
	CascadeClassifier& thirdCascade,CascadeClassifier& mouthCascade ,
	double scale)
{
	bool isDetect=false;
	Mat img_ori=img.clone();

	//ע�͵���һ������Ƕ�������ļ��
	//nestedCascade.~CascadeClassifier() ;


	int i = 0;
	double t = 0;
	vector<Rect> faces;

	Mat gray, smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );//��ͼƬ��С���ӿ����ٶ�

	cvtColor( img, gray, CV_BGR2GRAY );//��Ϊ�õ�����haar���������Զ��ǻ��ڻҶ�ͼ��ģ�����Ҫת���ɻҶ�ͼ��
	resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );//���ߴ���С��1/scale,�����Բ�ֵ
	equalizeHist( smallImg, smallImg );//ֱ��ͼ����

	t = (double)cvGetTickCount();


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

	t = (double)cvGetTickCount() - t;
	printf( "detection time = %g ms\n", t/((double)cvGetTickFrequency()*1000.) );

	//��ͷ����ɫ��
	for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++ )
	{
		Mat smallImgROI;
		vector<Rect> nestedObjects;
		Point center;
		int radius;
		center.x = cvRound((r->x + r->width*0.5)*scale);//��ԭ��ԭ���Ĵ�С
		center.y = cvRound((r->y + r->height*0.5)*scale);
		radius = cvRound((r->width + r->height)*0.25*scale);
		circle( img, center, radius, CV_RGB(255,0,0), 1, 8, 0 );

		imshow("head",img);
		//waitKey();
		
		cnt++;

		if( nestedCascade.empty() )//��2�������û�е����
			continue;

		smallImgROI = img_ori(*r);
		Mat smallImgROI_clone = smallImgROI.clone();
		Mat smallImgROI_clone2 = smallImgROI.clone();

		//������ĺ�������һ��
		nestedCascade.detectMultiScale( smallImgROI, nestedObjects,
			1.1, 2, 0
			//|CV_HAAR_FIND_BIGGEST_OBJECT
			//|CV_HAAR_DO_ROUGH_SEARCH
			//|CV_HAAR_DO_CANNY_PRUNING
			|CV_HAAR_SCALE_IMAGE
			,
			Size(30, 30) );

		//����������ɫ��ʶ
		for( vector<Rect>::const_iterator nr = nestedObjects.begin(); nr != nestedObjects.end(); nr++ )
		{
			isDetect=true;

			//Mat supSmallImg;
			vector<Rect> thirdNestedObjects;
			vector<Rect> mouthNestedObjects;

			center.x = cvRound((r->x + nr->x + nr->width*0.5)*scale);
			center.y = cvRound((r->y + nr->y + nr->height*0.5)*scale);
			radius = cvRound((nr->width + nr->height)*0.25*scale);
			circle( img, center, radius, CV_RGB(0,0,255), 1, 8, 0 );

			imshow("face",img);
			//waitKey();

			nestedCnt++;

			//supSmallImg = smallImgROI(*nr);

			//�����б�
			thirdCascade.detectMultiScale( smallImgROI_clone, thirdNestedObjects,
				1.1, 2, 0
				|CV_HAAR_SCALE_IMAGE
				,
				Size(30, 30) );

			//���ӡ���ɫ��
			if (thirdNestedObjects.size()>0)
			{
				isDetect=false;

				center.x = cvRound((r->x + thirdNestedObjects.begin()->x + thirdNestedObjects.begin()->width*0.5)*scale);
				center.y = cvRound((r->y + thirdNestedObjects.begin()->y + thirdNestedObjects.begin()->height*0.5)*scale);
				radius = cvRound((thirdNestedObjects.begin()->width + thirdNestedObjects.begin()->height)*0.25*scale);
				circle( img, center, radius, CV_RGB(0,255,0), 1, 8, 0 );

				imshow("nose",img);

				cout<<"����size��"<<thirdNestedObjects.size()<<endl;
				waitKey();
			}

			//����б�
			thirdCascade.detectMultiScale( smallImgROI_clone2, mouthNestedObjects,
				1.1, 2, 0
				|CV_HAAR_SCALE_IMAGE
				,
				Size(30, 30) );

			if (mouthNestedObjects.size()>0)
			{
				isDetect=false;

				center.x = cvRound((r->x + mouthNestedObjects.begin()->x + mouthNestedObjects.begin()->width*0.5)*scale);
				center.y = cvRound((r->y + mouthNestedObjects.begin()->y + mouthNestedObjects.begin()->height*0.5)*scale);
				radius = cvRound((mouthNestedObjects.begin()->width + mouthNestedObjects.begin()->height)*0.25*scale);
				circle( img, center, radius, CV_RGB(128,128,0), 1, 8, 0 );

				imshow("mouth",img);

				cout<<"���size��"<<mouthNestedObjects.size()<<endl;
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
			//��⵽������
			imshow("smallImgROI",smallImgROI);
			imwrite(path,smallImgROI);
			//cout<<path<<endl;
			//waitKey();
		}
	}//��ͷ

}

int main()
{
	//��ָ�����ļ�Ŀ¼�м��ؼ���������
	if( !cascade.load( cascadeName ) )
	{
		cerr << "ERROR: Could not load classifier cascade" << endl;
		//return 0;
	}

	//���������û���������أ�����
	if( !nestedCascade.load( nestedCascadeName ) )
	{
		cerr << "WARNING: Could not load classifier cascade for nested objects" << endl;
		//return 0;
	}

	if( !thirdCascade.load( thirdCascadeName ) )
	{
		cerr << "WARNING: Could not load classifier cascade for thirdCascade objects" << endl;
		//return 0;
	}

	if( !mouthCascade.load( mouthCascadeName ) )
	{
		cerr << "WARNING: Could not load classifier cascade for mouthCascade objects" << endl;
		//return 0;
	}
	faceDetect();

	return 0;
}
