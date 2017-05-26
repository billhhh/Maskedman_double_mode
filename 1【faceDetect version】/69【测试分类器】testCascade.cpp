#include "cv.h"
#include "highgui.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include <iostream>

using namespace std;
using namespace cv;

String cascadeName = "./cascades.xml";//��ͷ���ѵ������
String nestedCascadeName = "./haarcascades/haarcascade_frontalface_alt2.xml"; //�ڶ���ѵ������
String thirdCascadeName = "./haarcascades/haarcascade_mcs_nose.xml"; //��3��ѵ������
String mouthCascadeName = "./haarcascades/haarcascade_mcs_mouth.xml"; //���ѵ������
CascadeClassifier cascade, nestedCascade,thirdCascade,mouthCascade;//������������������

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

	double t = 0;
	vector<Rect> faces;

	Mat gray, smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );//��С���ӿ��ٶ�

	cvtColor( img, gray, CV_BGR2GRAY );//��haar������ת���ɻҶ�ͼ��
	resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );//��С��1/scale,���Բ�ֵ
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
	for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++ )
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
		waitKey();

		if( nestedCascade.empty() )//��2�������û�е����
			continue;

		smallImgROI = img_ori(*r);

		imshow("smallImgROI",smallImgROI);

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
			waitKey();

			//supSmallImg = smallImgROI(*nr);

			//�����б�
			thirdCascade.detectMultiScale( smallImgROI_clone, thirdNestedObjects,
				1.1, 2, 0
				|CV_HAAR_SCALE_IMAGE
				,
				Size(30, 30) );

			//���ӡ���ɫ��
			cout<<"����size��"<<thirdNestedObjects.size()<<endl;
			for( vector<Rect>::const_iterator thirdr = thirdNestedObjects.begin(); thirdr != thirdNestedObjects.end(); thirdr++ )
			{
				isDetect=false;

				center.x = cvRound((r->x + thirdr->x + thirdr->width*0.5)*scale);
				center.y = cvRound((r->y + thirdr->y + thirdr->height*0.5)*scale);
				radius = cvRound((thirdr->width + thirdr->height)*0.25*scale);
				circle( img, center, radius, CV_RGB(0,255,0), 1, 8, 0 );

				imshow("nose",img);

				waitKey();
			}

			//��͡�������ɫ��
			mouthCascade.detectMultiScale( smallImgROI_clone2, mouthNestedObjects,
				1.1, 2, 0
				|CV_HAAR_SCALE_IMAGE
				,
				Size(30, 30) );

			cout<<"���size��"<<mouthNestedObjects.size()<<endl;
			for( vector<Rect>::const_iterator forthr = mouthNestedObjects.begin(); forthr != mouthNestedObjects.end(); forthr++ )
			{
				isDetect=false;

				center.x = cvRound((r->x + forthr->x + forthr->width*0.5)*scale);
				center.y = cvRound((r->y + forthr->y + forthr->height*0.5)*scale);
				radius = cvRound((forthr->width + forthr->height)*0.25*scale);
				circle( img, center, radius, CV_RGB(128,128,0), 1, 8, 0 );

				imshow("mouth",img);

				waitKey();
			}
		}//����

// 		if (isDetect == true)
// 		{
// 			//��⵽������
// 			imshow("smallImgROI",smallImgROI);
// 			//cout<<path<<endl;
// 			waitKey();
// 		}
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
	
	Mat src = imread("faceDetect.jpg");
	detectAndDraw(src,cascade, nestedCascade , thirdCascade ,mouthCascade ,1.0);
	//imshow("src",src);
	//waitKey();

	return 0;
}