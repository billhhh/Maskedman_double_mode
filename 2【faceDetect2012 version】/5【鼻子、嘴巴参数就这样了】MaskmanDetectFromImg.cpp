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


string cascadeName = "./cascades.xml";//��ͷ���ѵ������
string thirdCascadeName = "./haarcascades/haarcascade_mcs_nose.xml"; //��3��ѵ������
string secondCascadeName = "./haarcascades/haarcascade_frontalface_alt2.xml"; //�ڶ���ѵ������

string forthCascadeName = "./haarcascades/haarcascade_mcs_mouth.xml"; //���ѵ������
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

	//pre_process
	Mat gray;
	//Mat smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );//��ͼƬ��С���ӿ����ٶ�
	if(img.channels() != 1)
 		cvtColor( img, gray, CV_BGR2GRAY );//��Ϊ�õ�����haar���������Զ��ǻ��ڻҶ�ͼ��ģ�����Ҫת���ɻҶ�ͼ��
	else
		gray = img.clone();
// 	resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );//���ߴ���С��1/scale,�����Բ�ֵ
// 	equalizeHist( smallImg, smallImg );//ֱ��ͼ����

// 	imshow("test",gray);
// 	waitKey();

	Mat smallImg_clone = gray.clone();//����
	Mat smallImg_clone2 = gray.clone();//���
	Mat show = img_ori.clone();  //����
	Mat show2 = img_ori.clone(); //���

	//�����б���ɫ��
	thirdCascade.detectMultiScale( smallImg_clone, thirdNestedObjects,
		1.01, 1, 0
		|CV_HAAR_SCALE_IMAGE
		,
		Size((int)smallImg_clone.cols/13, (int)smallImg_clone.rows/13)
		,Size((int)smallImg_clone.cols/3, (int)smallImg_clone.rows/3)
		);

	bool flag = false;

	cout<<"����size��"<<thirdNestedObjects.size()<<endl;
	for( vector<Rect>::const_iterator thirdr = thirdNestedObjects.begin(); thirdr != thirdNestedObjects.end(); thirdr++ )
	{
		isDetect=false;

		center.x = cvRound(( thirdr->x + thirdr->width*0.5)*scale);
		center.y = cvRound(( thirdr->y + thirdr->height*0.5)*scale);

		if (center.y < smallImg_clone.rows * 0.6 || center.y > smallImg_clone.rows *0.85 || //�߶�
			center.x < smallImg_clone.cols * 0.35 || center.x > smallImg_clone.cols * 0.65)  //���
		{
			//�������̫ƫ
			//waitKey();
			continue;
		}

		radius = cvRound((thirdr->width + thirdr->height)*0.25*scale);

		//circle( smallImg_clone, center, radius, CV_RGB(0,255,0), 1, 8, 0 );
		circle( show, center, radius, CV_RGB(0,255,0), 1, 8, 0 );
		circle( show, center, 1, CV_RGB(0,255,0), 1, 8, 0 );
		imshow("nose",show);
		//imwrite(generateImgPath2(imgName,flag),smallImg_clone);
		imwrite(generateImgPath2(imgName,flag),show);

		cnt++;
		flag = true;
		//waitKey();
	}

	//����б𡾻�ɫ��
	mouthCascade.detectMultiScale( smallImg_clone2, mouthNestedObjects,
		1.01, 1, 0
		//|CV_HAAR_FIND_BIGGEST_OBJECT	//ֻ�����������
		//|CV_HAAR_DO_ROUGH_SEARCH	//ֻ�����Լ��
		|CV_HAAR_SCALE_IMAGE
		,
// 		Size(5,5)
// 		,Size(50,50)
		Size((int)smallImg_clone2.cols/13, (int)smallImg_clone2.rows/13)
		,Size((int)smallImg_clone2.cols*5/12, (int)smallImg_clone2.rows*5/12)
		);

	cout<<"���size��"<<mouthNestedObjects.size()<<endl;
	for( vector<Rect>::const_iterator forthr = mouthNestedObjects.begin(); forthr != mouthNestedObjects.end(); forthr++ )
	{
		isDetect=false;

		center.x = cvRound((forthr->x + forthr->width*0.5)*scale);
		center.y = cvRound((forthr->y + forthr->height*0.5)*scale);

		if (center.y < smallImg_clone2.rows * 0.68
			|| center.y > smallImg_clone2.rows * 0.89
			||center.x < smallImg_clone.cols * 0.2 || center.x > smallImg_clone.cols * 0.8
			)
		{
			//�����ͼ��λ��̫ƫ
			//waitKey();
			continue;
		}
		radius = cvRound((forthr->width + forthr->height)*0.25*scale);
		circle( show2, center, radius, CV_RGB(248,247,182), 1, 8, 0 );
		circle( show2, center, 1, CV_RGB(248,247,182), 1, 8, 0 ); //����

		imshow("mouth",show2);
		imwrite(generateImgPath2(imgName,flag),show2);

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

int main(int argc, char **argv)
{
	//���ط�����
	if( !cascade.load( cascadeName ) )
		cerr << "ERROR: Could not load classifier cascade" << endl;
	cout<<secondCascadeName<<endl;
	if( !nestedCascade.load( secondCascadeName ) )
		cerr << "WARNING: Could not load classifier cascade for nested objects" << endl;
	if( !thirdCascade.load( thirdCascadeName ) )
		cerr << "WARNING: Could not load classifier cascade for thirdCascade objects" << endl;
	if( !mouthCascade.load( forthCascadeName ) )
		cerr << "WARNING: Could not load classifier cascade for mouthCascade objects" << endl;

	batFindImgName(argv[1]);

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

	//system("pause");

	return 0;
}
