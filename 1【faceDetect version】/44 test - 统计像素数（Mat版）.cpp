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

using namespace std;

void Image_Stat(Mat img)
{
	double scale=0.3;

	int width = img.cols;
	int height = img.rows;

	//�����ο�λ���°벿��
	Rect r=Rect(0,height*(1-scale),width,height*scale);
	img=img(r);

	imshow("mid_img",img);
	//waitKey(0);

	cvtColor(img, img, CV_BGR2GRAY);
	int count=countNonZero(img);

	int area=width*height*scale;
	double rate=(double)count/area;

	cout<<"�� == "<<width<<" �� == "<<height*scale<<endl;
	cout<<"��� == "<<area<<endl;
	cout<<"count == "<<count<<endl;
	cout<<"ռ�� == "<<rate<<endl;

	waitKey(0);
}


int main()
{
	Mat img;
	//img = imread("mmr_out.jpg");
	img = imread("zcr_out.jpg");


	//ͼ���֣�����ؼ���һ��
	Image_Stat(img);

	//imshow("img",img);
	
	//cvWaitKey(0);
	
	return 0;
}