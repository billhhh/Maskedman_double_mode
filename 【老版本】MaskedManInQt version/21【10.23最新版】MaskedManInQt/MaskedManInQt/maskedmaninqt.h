#ifndef MASKEDMANINQT_H
#define MASKEDMANINQT_H

#include <QtGui/QDialog>
#include <cv.h>
#include "highgui.h"
#include "ui_maskedmaninqt.h"
#include "playThread.h"

class MaskedManInQt : public QDialog
{
	Q_OBJECT

public:
	MaskedManInQt(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MaskedManInQt();

private:
	Ui::MaskedManInQtClass ui;

public:
	QString filePath;
	cv::VideoCapture capture;
	cv::Mat iplImg;
	cv::Mat frame;
	QImage *qImg;
	cv::Size captureSize;
	int fps;

	PlayThread*  thread;
public:
	void init(QString filePath);

	private slots:
		void on_play_button_clicked();
		void on_exit_button_clicked();
		void showImage(QImage image);
		void getSliderMoved(int);
		void setSliderValue(int value);
		void setSliderRange(int min, int max);
		void getThreadEnd();
		void showMmrInfo(int isDetect);

		void on_pBtn_openVideo_clicked();
};

#endif // MASKEDMANINQT_H
