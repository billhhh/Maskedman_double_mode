//opencv2.0���

//�������м����ɵ�ֵ
//1.�������� ѧϰ�� learningRate
//2.ȥ��С�����ֵ area_threshold

#include <cv.h>
#include <highgui.h>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include <iostream>
#include <string>
#include <cstdio>

using namespace std;
using namespace cv;


//��������

int myFaceDetect(String fileName); //������
void findBoundary(Rect r,Point &a,Point &c);//�ҵ����Ͼ��ο�
void biggerRect(Point &a,Point &c,Mat img);  //�����ο��ʵ��Ŵ�
void hugeRect(Point &a,Point &c,Mat img);   //���������С̫��ֱ�ӽ����ξ޴�
void pedDetection(Mat& img);//���˼��
void detectAndDraw( Mat& img,
	CascadeClassifier& cascade, CascadeClassifier& nestedCascade,
	double scale);
void whThresholdOtsu(Mat &src, Mat &dst);
void cvSkinOtsu(Mat &src, Mat &dst);  //��ɫ���
bool findMaskMan(Mat img); //�����ҵ��ǲ��������ˣ����ô���ַ��ȥ��