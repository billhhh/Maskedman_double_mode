//opencv2.0风格

//本程序有几个可调值
//1.背景更新 学习率 learningRate
//2.去掉小面积阈值 area_threshold

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


string cascadeName = "./cascades.xml";//人头检测训练数据
string thirdCascadeName = "./haarcascades/haarcascade_mcs_nose.xml"; //第3层训练数据
string secondCascadeName = "./haarcascades/haarcascade_frontalface_alt2.xml"; //第二层训练数据

string forthCascadeName = "./haarcascades/haarcascade_mcs_mouth.xml"; //嘴巴训练数据
CascadeClassifier cascade, nestedCascade,thirdCascade,mouthCascade;//创建级联分类器对象

vector<string> img_list_path;  //照片文件
int cnt=0;//输出视频特定特征的数量

//人脸检测并画出
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
	//Mat smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );//将图片缩小，加快检测速度
	if(img.channels() != 1)
 		cvtColor( img, gray, CV_BGR2GRAY );//因为用的是类haar特征，所以都是基于灰度图像的，这里要转换成灰度图像
	else
		gray = img.clone();
// 	resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );//将尺寸缩小到1/scale,用线性插值
// 	equalizeHist( smallImg, smallImg );//直方图均衡

// 	imshow("test",gray);
// 	waitKey();

	Mat smallImg_clone = gray.clone();//鼻子
	Mat smallImg_clone2 = gray.clone();//嘴巴
	Mat show = img_ori.clone();  //鼻子
	Mat show2 = img_ori.clone(); //嘴巴

	//鼻子判别【绿色】
	thirdCascade.detectMultiScale( smallImg_clone, thirdNestedObjects,
		1.01, 1, 0
		|CV_HAAR_SCALE_IMAGE
		,
		Size((int)smallImg_clone.cols/13, (int)smallImg_clone.rows/13)
		,Size((int)smallImg_clone.cols/3, (int)smallImg_clone.rows/3)
		);

	bool flag = false;

	cout<<"鼻子size："<<thirdNestedObjects.size()<<endl;
	for( vector<Rect>::const_iterator thirdr = thirdNestedObjects.begin(); thirdr != thirdNestedObjects.end(); thirdr++ )
	{
		isDetect=false;

		center.x = cvRound(( thirdr->x + thirdr->width*0.5)*scale);
		center.y = cvRound(( thirdr->y + thirdr->height*0.5)*scale);

		if (center.y < smallImg_clone.rows * 0.6 || center.y > smallImg_clone.rows *0.85 || //高度
			center.x < smallImg_clone.cols * 0.35 || center.x > smallImg_clone.cols * 0.65)  //宽度
		{
			//如果鼻子太偏
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

	//嘴巴判别【黄色】
	mouthCascade.detectMultiScale( smallImg_clone2, mouthNestedObjects,
		1.01, 1, 0
		//|CV_HAAR_FIND_BIGGEST_OBJECT	//只检测最大的物体
		//|CV_HAAR_DO_ROUGH_SEARCH	//只做初略检测
		|CV_HAAR_SCALE_IMAGE
		,
// 		Size(5,5)
// 		,Size(50,50)
		Size((int)smallImg_clone2.cols/13, (int)smallImg_clone2.rows/13)
		,Size((int)smallImg_clone2.cols*5/12, (int)smallImg_clone2.rows*5/12)
		);

	cout<<"嘴巴size："<<mouthNestedObjects.size()<<endl;
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
			//如果嘴巴检测位置太偏
			//waitKey();
			continue;
		}
		radius = cvRound((forthr->width + forthr->height)*0.25*scale);
		circle( show2, center, radius, CV_RGB(248,247,182), 1, 8, 0 );
		circle( show2, center, 1, CV_RGB(248,247,182), 1, 8, 0 ); //画点

		imshow("mouth",show2);
		imwrite(generateImgPath2(imgName,flag),show2);

		cnt++;
		//waitKey();
	}
}

//传入文件名和是否重复
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
		bResult =finder.FindNextFile();//读取下一个文件
		cout<<(LPCTSTR)finder.GetFileName()<<"\n";
	}
	finder.Close();
}


void batFindImgName(string path)
{
	string buf;
	//读入检测样本  
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
	//加载分类器
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

		//找文件名
		int startIndex = file.find_last_of('/');  //找不到返回-1
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
