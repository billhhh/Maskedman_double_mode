#ifndef PLAYTHREAD_H
#define PLAYTHREAD_H

#include <QThread>
#include <cv.h>
#include <highgui.h>
#include <qimage.h>
//#include "EventNode.h"

class PlayThread : public QThread
{
	Q_OBJECT

public:
	bool init(QString);
	//bool init(QString,EventNode,int);
	void getFrameByPos(int);
	PlayThread(QObject *parent);
	~PlayThread();
	cv::VideoCapture capture;

signals:
	void sendPlayImage(QImage);
	void sendSliderRange(int,int);
	void sendSliderValue(int);
	void sendMmrInfo(int);
	void playEnd();
	void threadEnd();   //������Ϻ��ʹ���Ϣ���ð�ť״̬�ı�
protected:
	void run();
private:


public:
	QString filePath;
	cv::Mat iplImg;
	cv::Mat frame;
	QImage *qImg;
	cv::Size captureSize;
	int fps;
	int interval;
	int frameCount;
	//EventNode node;
	bool isPlaying;
	int pos;
	bool isAllAbstract;
	int slidePos;
};

#endif // PLAYTHREAD_H



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
