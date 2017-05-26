#include "cv.h"
#include "highgui.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <direct.h>
#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include<algorithm>

using namespace std;
using namespace cv;

string generateImgPath2(string imgName,bool flag);
vector<string> img_list_path;  //照片文件
vector<string> not_mouth_list;

void out_put_rate(string imgName , double rate)
{
	auto iter = find(not_mouth_list.begin(), not_mouth_list.end(), imgName);
	if (iter == not_mouth_list.end())//没找到
		printf("    %3s.jpg   %.2lf\n",imgName.c_str(),rate);
	else
		printf("%3s.jpg   %.2lf\n",imgName.c_str(),rate);
}

string DoubleToString(double d)
{
	char buffer[1024];
	sprintf(buffer,"%f\0",d);
	string str(buffer);
	return str;
}

void SobelDetect(string imgPath,string imgName)
{
	Mat src, src_gray;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;

	src = imread( imgPath );

	if( !src.data ){
		return ;
	}

	//高斯模糊
	GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

	//转成灰度图
	cvtColor( src, src_gray, CV_RGB2GRAY );

	Mat grad_y;
	Mat abs_grad_y;

	Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
	convertScaleAbs( grad_y, abs_grad_y );

	abs_grad_y *=1.5;
	threshold(abs_grad_y,abs_grad_y,30,255,THRESH_OTSU | THRESH_BINARY);
	dilate(abs_grad_y,abs_grad_y,Mat(2,14,CV_8U),Point(-1,-1),1);

	//medianBlur(abs_grad_y,abs_grad_y,3);
	//GaussianBlur( abs_grad_y, abs_grad_y, Size(3,3), 0, 0, BORDER_DEFAULT );

	//看白点数目
 	int count=countNonZero(abs_grad_y);
 	int area=abs_grad_y.rows*abs_grad_y.cols;
 	double rate=(double)count/area;
 	string words = DoubleToString(rate);
 	Mat rateImg = cv::Mat::zeros(abs_grad_y.rows*20,abs_grad_y.cols*20,CV_8U);
	putText( rateImg, words, Point( rateImg.rows/2,rateImg.cols/4),CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 0, 0) ); 

	out_put_rate(imgName,rate);
	imwrite(generateImgPath2(imgName,false),abs_grad_y);
	//imwrite(generateImgPath2(imgName,true),rateImg);
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

	ifstream file_stream( "f:\\notmouth.txt" );  
	while( file_stream )  
		if( getline( file_stream, buf ) )
			not_mouth_list.push_back( buf );
	file_stream.close();
}

int main(int argc, char **argv)
{
	freopen("f:\\output.txt", "w", stdout);

	system("rd /s /q f:\\mmr");
	_mkdir("f:\\mmr\\");

	batFindImgName(argv[1]);

	Mat src;
	//Mat src = imread("faceDetect.jpg");
	for(int i=0;i<img_list_path.size();i++)
	{
		string file = img_list_path[i];
		src = imread(file);
		//cout<<file<<"\n";

		//找文件名
		int startIndex = file.find_last_of('/');  //找不到返回-1
		int startIndex2 = file.find_last_of('\\');
		startIndex = startIndex>startIndex2?startIndex:startIndex2;
		int endIndex = file.find_last_of('.');
		string imgName = file.substr(startIndex+1,endIndex-startIndex-1);

		SobelDetect(file,imgName);
		//waitKey();
		destroyAllWindows();
	}
	src.release();

	//system("pause");

	return 0;
}
