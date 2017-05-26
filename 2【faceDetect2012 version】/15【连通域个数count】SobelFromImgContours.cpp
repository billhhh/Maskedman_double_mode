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

using namespace std;
using namespace cv;

string generateImgPath2(string imgName,bool flag);
vector<string> img_list_path;  //��Ƭ�ļ�
vector<string> not_mouth_list;

void out_put_rate(string imgName , int rate)
{
	auto iter = find(not_mouth_list.begin(), not_mouth_list.end(), imgName);
	if (iter == not_mouth_list.end())//û�ҵ�
		printf("    %3s.jpg   %d\n",imgName.c_str(),rate);
	else
		printf("%3s.jpg   %d\n",imgName.c_str(),rate);
}

string DoubleToString(double d)
{
	char buffer[1024];
	sprintf(buffer,"%f\0",d);
	string str(buffer);
	return str;
}

//src�Ǵ����ֵͼ��n�Ǳ���ǰN����ͨ��
bool keepSomeMaxCon(Mat &src, int n){
	///////// !!!findcontours���ܲ���λ��ͼ���Ե�ĵ㣬���±�Ե�ĵ�û�����
	for(int i=0;i<src.cols;i++)
		src.at<uchar>(0,i) = src.at<uchar>(src.rows -1,i) = 0;
	for(int j=0;j<src.rows;j++)
		src.at<uchar>(j,0) = src.at<uchar>(j,src.cols -1) = 0;

	//��ͨ��ȥ�룬ֻʣ��n��
	Mat temp = src.clone();
	vector<vector<Point> > contours;
	findContours(temp,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE); //����,������ı�temp

	//ԭͼ��ͨ������������Ҫ��������ͨ������
	if(contours.size() < n)	
		return false;

	Mat srt(Size(contours.size(),1),CV_32SC1);
	for(int c=0;c<(int)contours.size();c++)
		srt.at<int>(0,c) = (int)contourArea(contours[c]);

	cv::sortIdx(srt,srt,CV_SORT_EVERY_ROW + CV_SORT_DESCENDING);
	for(int i=n; i<(int)contours.size(); i++){ //ֻ����ǰn����ͨ��
		int idx = srt.at<int>(i);
		vector<Point> tmp = contours[idx];
		const Point* elementPoints[1] = { &tmp[0] };
		int numberOfPoints = (int)contours[idx].size();	
		fillPoly(src,elementPoints, &numberOfPoints ,1,Scalar(0,0,0));//��䵥����ͨ��		
	}

	return true;
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

	//��˹ģ��
	GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );

	//ת�ɻҶ�ͼ
	cvtColor( src, src_gray, CV_RGB2GRAY );

	Mat grad_y;
	Mat abs_grad_y;

	Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
	convertScaleAbs( grad_y, abs_grad_y );

	abs_grad_y *=1.5;
	threshold(abs_grad_y,abs_grad_y,30,255,THRESH_OTSU | THRESH_BINARY);

	//keepSomeMaxCon(abs_grad_y,1);

	Mat afterKeepCon = abs_grad_y.clone();
	//���׵���Ŀ
 	int count=countNonZero(abs_grad_y);

	//�������
	vector<vector<Point>> _contours;//������������
	vector<Vec4i>hierarchy;
	cv::findContours( abs_grad_y, _contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
//  	Rect r0 = boundingRect(Mat(_contours[0]));
// 
// 	Mat rateImg = cv::Mat::zeros(afterKeepCon.rows*20,afterKeepCon.cols*20,CV_8U);
// 	double rate=(double)count/(r0.width*r0.height);
// 	string words = DoubleToString( (double)count ) + "/" + DoubleToString(r0.width*r0.height) +" = ";
// 	putText( rateImg, words, Point( rateImg.rows/5,rateImg.cols/6),CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 0, 0) ); 
// 	words = DoubleToString(rate);
// 	putText( rateImg, words, Point( rateImg.rows*2/3,rateImg.cols/4),CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 0, 0) ); 

	out_put_rate(imgName,_contours.size());
	//imshow( "�ݶ�ͼ", afterKeepCon );
	imwrite(generateImgPath2(imgName,false),afterKeepCon);
	//imwrite(generateImgPath2(imgName,true),rateImg);
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

		//���ļ���
		int startIndex = file.find_last_of('/');  //�Ҳ�������-1
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
