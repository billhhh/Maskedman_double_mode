#include "cv.h"
#include "highgui.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include <iostream>

using namespace std;
using namespace cv;

String cascadeName = "./cascades.xml";//人头检测训练数据
String nestedCascadeName = "./haarcascades/haarcascade_frontalface_alt2.xml"; //第二层训练数据
String thirdCascadeName = "./haarcascades/haarcascade_mcs_nose.xml"; //第3层训练数据
String mouthCascadeName = "./haarcascades/haarcascade_mcs_mouth.xml"; //嘴巴训练数据
CascadeClassifier cascade, nestedCascade,thirdCascade,mouthCascade;//创建级联分类器对象

//人脸检测并画出
void detectAndDraw( Mat& img,
	CascadeClassifier& cascade, CascadeClassifier& nestedCascade,
	CascadeClassifier& thirdCascade,CascadeClassifier& mouthCascade ,
	double scale)
{
	bool isDetect=false;
	Mat img_ori=img.clone();

	//注释掉下一行语句打开嵌套特征的检测
	//nestedCascade.~CascadeClassifier() ;

	double t = 0;
	vector<Rect> faces;

	Mat gray, smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );//缩小，加快速度

	cvtColor( img, gray, CV_BGR2GRAY );//类haar特征，转换成灰度图像
	resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );//缩小到1/scale,线性插值
	equalizeHist( smallImg, smallImg );//直方图均衡

	t = (double)cvGetTickCount();


	//detectMultiScale函数中smallImg表示的是要检测的输入图像为smallImg，faces表示检测到的人脸目标序列，1.1表示
	//每次图像尺寸减小的比例为1.1，2表示每一个目标至少要被检测到3次才算是真的目标(因为周围的像素和不同的窗口大
	//小都可以检测到人脸),CV_HAAR_SCALE_IMAGE表示不是缩放分类器来检测，而是缩放图像，Size(30, 30)为目标的
	//最小最大尺寸
	cascade.detectMultiScale( smallImg, faces,
		1.1, 2, 0
		//|CV_HAAR_FIND_BIGGEST_OBJECT
		//|CV_HAAR_DO_ROUGH_SEARCH
		|CV_HAAR_SCALE_IMAGE
		,
		Size(30, 30) );

	t = (double)cvGetTickCount() - t;
	printf( "detection time = %g ms\n", t/((double)cvGetTickFrequency()*1000.) );

	//人头【红色】
	for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++ )
	{
		Mat smallImgROI;
		vector<Rect> nestedObjects;
		Point center;
		int radius;
		center.x = cvRound((r->x + r->width*0.5)*scale);//还原成原来的大小
		center.y = cvRound((r->y + r->height*0.5)*scale);
		radius = cvRound((r->width + r->height)*0.25*scale);
		circle( img, center, radius, CV_RGB(255,0,0), 1, 8, 0 );

		imshow("head",img);
		waitKey();

		if( nestedCascade.empty() )//第2层分类器没有的情况
			continue;

		smallImgROI = img_ori(*r);

		imshow("smallImgROI",smallImgROI);

		Mat smallImgROI_clone = smallImgROI.clone();
		Mat smallImgROI_clone2 = smallImgROI.clone();

		//和上面的函数功能一样
		nestedCascade.detectMultiScale( smallImgROI, nestedObjects,
			1.1, 2, 0
			//|CV_HAAR_FIND_BIGGEST_OBJECT
			//|CV_HAAR_DO_ROUGH_SEARCH
			//|CV_HAAR_DO_CANNY_PRUNING
			|CV_HAAR_SCALE_IMAGE
			,
			Size(30, 30) );

		//人脸，用蓝色标识
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

			//鼻子判别
			thirdCascade.detectMultiScale( smallImgROI_clone, thirdNestedObjects,
				1.1, 2, 0
				|CV_HAAR_SCALE_IMAGE
				,
				Size(30, 30) );

			//鼻子【绿色】
			cout<<"鼻子size："<<thirdNestedObjects.size()<<endl;
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

			//嘴巴【其他颜色】
			mouthCascade.detectMultiScale( smallImgROI_clone2, mouthNestedObjects,
				1.1, 2, 0
				|CV_HAAR_SCALE_IMAGE
				,
				Size(30, 30) );

			cout<<"嘴巴size："<<mouthNestedObjects.size()<<endl;
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
		}//人脸

// 		if (isDetect == true)
// 		{
// 			//检测到蒙面人
// 			imshow("smallImgROI",smallImgROI);
// 			//cout<<path<<endl;
// 			waitKey();
// 		}
	}//人头

}


int main()
{
	//从指定的文件目录中加载级联分类器
	if( !cascade.load( cascadeName ) )
	{
		cerr << "ERROR: Could not load classifier cascade" << endl;
		//return 0;
	}

	//如果分类器没有正常加载，报错
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