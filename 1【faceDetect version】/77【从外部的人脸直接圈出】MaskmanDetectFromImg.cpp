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
#include <afx.h>
#include <fstream>

using namespace std;
using namespace cv;

string generateImgPath();
void detectAndDraw( Mat& img,
	CascadeClassifier& cascade, CascadeClassifier& nestedCascade,
	CascadeClassifier& thirdCascade,CascadeClassifier& mouthCascade,
	double scale);


String cascadeName = "./cascades.xml";//��ͷ���ѵ������
String nestedCascadeName = "./haarcascades/haarcascade_frontalface_alt2.xml"; //�ڶ���ѵ������
String thirdCascadeName = "./haarcascades/haarcascade_mcs_nose.xml"; //��3��ѵ������
String mouthCascadeName = "./haarcascades/haarcascade_mcs_mouth.xml"; //���ѵ������
CascadeClassifier cascade, nestedCascade,thirdCascade,mouthCascade;//������������������

vector<string> img_list_path;  //��Ƭ�ļ�
int cnt=0;//�����Ƶ�ض�����������

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

	Mat gray, smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );//��ͼƬ��С���ӿ����ٶ�

	cvtColor( img, gray, CV_BGR2GRAY );//��Ϊ�õ�����haar���������Զ��ǻ��ڻҶ�ͼ��ģ�����Ҫת���ɻҶ�ͼ��
	resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );//���ߴ���С��1/scale,�����Բ�ֵ
	equalizeHist( smallImg, smallImg );//ֱ��ͼ����

	t = (double)cvGetTickCount();

	imshow("test",smallImg);


	//detectMultiScale������smallImg��ʾ����Ҫ��������ͼ��ΪsmallImg��faces��ʾ��⵽������Ŀ�����У�1.1��ʾ
	//ÿ��ͼ��ߴ��С�ı���Ϊ1.1��2��ʾÿһ��Ŀ������Ҫ����⵽3�β��������Ŀ��(��Ϊ��Χ�����غͲ�ͬ�Ĵ��ڴ�
	//С�����Լ�⵽����),CV_HAAR_SCALE_IMAGE��ʾ�������ŷ���������⣬��������ͼ��Size(30, 30)ΪĿ���
	//��С���ߴ�
	cascade.detectMultiScale( smallImg, faces,
		1.1, 2, 0
		//|CV_HAAR_FIND_BIGGEST_OBJECT	//ֻ�����������
		//|CV_HAAR_DO_ROUGH_SEARCH	//ֻ�����Լ��
		|CV_HAAR_SCALE_IMAGE	//�������������
		,
		Size(30, 30) );

	t = (double)cvGetTickCount() - t;
	printf( "detection time = %g ms\n", t/((double)cvGetTickFrequency()*1000.) );

	//��ͷ����ɫ��
	for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++)
	{
		cout<<"�ҵ���ͷ\n";
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

			imshow("face",smallImgROI);
			//imwrite(generateImgPath(),smallImgROI);
			cnt++;
			//waitKey();
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

				center.x = cvRound(( thirdr->x + thirdr->width*0.5)*scale);
				center.y = cvRound(( thirdr->y + thirdr->height*0.5)*scale);
				circle( smallImgROI_clone, center, radius, CV_RGB(0,255,0), 1, 8, 0 );
				imshow("nose",smallImgROI_clone);
				//imwrite(generateImgPath(),smallImgROI_clone);

				cnt++;
				//waitKey();
			}

			//����б�
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
				circle( img, center, radius, CV_RGB(248,247,182), 1, 8, 0 );

				center.x = cvRound((forthr->x + forthr->width*0.5)*scale);
				center.y = cvRound((forthr->y + forthr->height*0.5)*scale);

				if (center.y < smallImgROI_clone2.rows * 0.5)
				{
					//waitKey();
					continue;
				}

				circle( smallImgROI_clone2, center, radius, CV_RGB(248,247,182), 1, 8, 0 );

				imshow("mouth",smallImgROI_clone2);
				//imwrite(generateImgPath(),smallImgROI_clone2);

				cnt++;
				//waitKey();
			}
		}

	}//��ͷ
}


string generateImgPath()
{
	std::stringstream ss;
	std::string str;
	ss<<cnt;
	ss>>str;
	string path = "f:\\mmr\\";
	path.append(str);
	path.append(".jpg");

	return path;
}

void findImgName(CString path)
{
	CFileFind finder;
	bool bResult =finder.FindFile(path+"\\*.*");
	while(bResult ){
		bResult =finder.FindNextFile();//��ȡ��һ���ļ�
		cout<<(LPCTSTR)finder.GetFileName()<<"\n";
	}
	finder.Close();
}


void batFindImgName(string path)
{
	string buf;
	//����������  
	ifstream img_stream( path );  
	while( img_stream ){  
		if( getline( img_stream, buf ) ){  
			img_list_path.push_back( buf );
		}  
	}
	img_stream.close(); 

}

int main()
{
	//���ط�����
	if( !cascade.load( cascadeName ) )
		cerr << "ERROR: Could not load classifier cascade" << endl;
	if( !nestedCascade.load( nestedCascadeName ) )
		cerr << "WARNING: Could not load classifier cascade for nested objects" << endl;
	if( !thirdCascade.load( thirdCascadeName ) )
		cerr << "WARNING: Could not load classifier cascade for thirdCascade objects" << endl;
	if( !mouthCascade.load( mouthCascadeName ) )
		cerr << "WARNING: Could not load classifier cascade for mouthCascade objects" << endl;

	//findImgName("F:\\������ ����+��Ǳ��졾��Ƭ��\\����\\�ڶ��� mp4\\5.mp4��һ������������+2�������ˡ�");
	batFindImgName("F:\\mmr_test\\train_list.txt");

	Mat src;
	//Mat src = imread("faceDetect.jpg");
	for(int i=0;i<img_list_path.size();i++)
	{
		string file = img_list_path[i];
		src = imread(file);
		cout<<file<<"\n";
		detectAndDraw(src,cascade, nestedCascade , thirdCascade ,mouthCascade ,1.0);
		waitKey();
		destroyAllWindows();
	}
	src.release();

	system("pause");

	return 0;
}
