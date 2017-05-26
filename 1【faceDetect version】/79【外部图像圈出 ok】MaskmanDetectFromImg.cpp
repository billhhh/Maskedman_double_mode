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

string generateImgPath2(string,bool);
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
	double scale,string imgName)
{
	bool isDetect=false;
	Mat img_ori=img.clone();
	Point center;
	int radius;
	vector<Rect> thirdNestedObjects;
	vector<Rect> mouthNestedObjects;


	//Ԥ����
	Mat gray, smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );//��ͼƬ��С���ӿ����ٶ�
	cvtColor( img, gray, CV_BGR2GRAY );//��Ϊ�õ�����haar���������Զ��ǻ��ڻҶ�ͼ��ģ�����Ҫת���ɻҶ�ͼ��
	resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );//���ߴ���С��1/scale,�����Բ�ֵ
	equalizeHist( smallImg, smallImg );//ֱ��ͼ����

	Mat smallImg_clone = img_ori.clone();
	Mat smallImg_clone2 = img_ori.clone();

	//�����б�
	thirdCascade.detectMultiScale( smallImg_clone, thirdNestedObjects,
		1.1, 2, 0
		|CV_HAAR_SCALE_IMAGE
		,
		Size(30, 30) );

	bool flag = false;
	//���ӡ���ɫ��
	cout<<"����size��"<<thirdNestedObjects.size()<<endl;
	for( vector<Rect>::const_iterator thirdr = thirdNestedObjects.begin(); thirdr != thirdNestedObjects.end(); thirdr++ )
	{
		isDetect=false;

		center.x = cvRound(( thirdr->x + thirdr->width*0.5)*scale);
		center.y = cvRound(( thirdr->y + thirdr->height*0.5)*scale);
		radius = cvRound((thirdr->width + thirdr->height)*0.25*scale);

		circle( smallImg_clone, center, radius, CV_RGB(0,255,0), 1, 8, 0 );
		imshow("nose",smallImg_clone);
		imwrite(generateImgPath2(imgName,flag),smallImg_clone);

		cnt++;
		flag = true;
		//waitKey();
	}

	//����б�
	mouthCascade.detectMultiScale( smallImg_clone2, mouthNestedObjects,
		1.1, 2, 0
		|CV_HAAR_SCALE_IMAGE
		,
		Size(30, 30) );

	cout<<"���size��"<<mouthNestedObjects.size()<<endl;
	for( vector<Rect>::const_iterator forthr = mouthNestedObjects.begin(); forthr != mouthNestedObjects.end(); forthr++ )
	{
		isDetect=false;

		center.x = cvRound((forthr->x + forthr->width*0.5)*scale);
		center.y = cvRound((forthr->y + forthr->height*0.5)*scale);

		if (center.y < smallImg_clone2.rows * 0.5)
		{
			//waitKey();
			continue;
		}
		radius = cvRound((forthr->width + forthr->height)*0.25*scale);
		circle( smallImg_clone2, center, radius, CV_RGB(248,247,182), 1, 8, 0 );

		imshow("mouth",smallImg_clone2);
		imwrite(generateImgPath2(imgName,flag),smallImg_clone2);

		cnt++;
		//waitKey();
	}
}

//�����ļ������Ƿ��ظ�
string generateImgPath2(string imgName,bool flag)
{
	string path = "f:\\mmr\\";
	path.append(imgName);
	if (flag == true)
		path.append("(2)");
	path.append(".jpg");

	return path;
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
	batFindImgName("F:\\������\\5.mp4\\train_list.txt");

	Mat src;
	//Mat src = imread("faceDetect.jpg");
	for(int i=0;i<img_list_path.size();i++)
	{
		string file = img_list_path[i];
		src = imread(file);
		cout<<file<<"\n";

		//���ļ���
		int startIndex = file.find_last_of('/');  //�Ҳ�������-1
		int startIndex2 = file.find_last_of('\\');
		startIndex = startIndex>startIndex2?startIndex:startIndex2;
		int endIndex = file.find_last_of('.');
		string imgName = file.substr(startIndex+1,endIndex-startIndex-1);

		detectAndDraw(src,cascade, nestedCascade , thirdCascade ,mouthCascade ,1.0,imgName);
		//waitKey();
		destroyAllWindows();
	}
	src.release();

	system("pause");

	return 0;
}
