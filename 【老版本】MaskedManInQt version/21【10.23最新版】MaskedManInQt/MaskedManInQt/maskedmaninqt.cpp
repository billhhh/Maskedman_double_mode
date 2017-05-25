#include "maskedmaninqt.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QProcess>

using namespace cv;

QString fileName;

MaskedManInQt::MaskedManInQt(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);

	thread = new PlayThread(this);
	connect(thread, SIGNAL(sendPlayImage(QImage)), this,SLOT(showImage(QImage)));
	connect(thread, SIGNAL(sendSliderRange(int,int)), this, SLOT(setSliderRange(int,int)));
	connect(thread, SIGNAL(sendSliderValue(int)), this, SLOT(setSliderValue(int)));
	connect(thread, SIGNAL(threadEnd()), this, SLOT(getThreadEnd()));
	connect(ui.play_slider, SIGNAL(sliderMoved(int)), this, SLOT(getSliderMoved(int)));

	connect( ui.exit_button, SIGNAL(clicked()), this, SLOT( on_exit_button_clicked() ) );
	connect( thread, SIGNAL(playEnd()), this, SLOT( on_exit_button_clicked() ) );
	connect( thread, SIGNAL(sendMmrInfo(int)), this, SLOT( showMmrInfo(int ) ) );
}

MaskedManInQt::~MaskedManInQt()
{
	if( thread != NULL){
		delete thread;
		thread = NULL;
	}
}

void MaskedManInQt::init(QString filePath){
	thread->init(filePath);

	this->filePath = filePath;
	//QByteArray ba = filePath.toLocal8Bit();
	//const char *file = ba.data();
	if( capture.isOpened())
		capture.release();

	capture.open(filePath.toStdString().c_str());
	if(!capture.isOpened())
		return;
	captureSize = Size((int)capture.get(CV_CAP_PROP_FRAME_WIDTH),
		(int)capture.get(CV_CAP_PROP_FRAME_HEIGHT));
	fps = (int)capture.get(CV_CAP_PROP_FPS);
	qImg = new QImage(QSize(captureSize.width,captureSize.height), QImage::Format_RGB888);
	iplImg.create(captureSize,  CV_8UC3);
	iplImg.data = qImg->bits();
}

void MaskedManInQt::on_play_button_clicked(){
	if(!thread->isPlaying){
		thread->isPlaying = true;
		ui.play_button->setText(QString::fromLocal8Bit("暂停"));
		thread->start();
	}else{
		thread->isPlaying = false;
		ui.play_button->setText(QString::fromLocal8Bit("开始"));
	}
}

void MaskedManInQt::on_exit_button_clicked(){
	getThreadEnd();
	exit(0);
}

void MaskedManInQt::showImage(QImage image){
	//cout<<"getImg"<<endl;
	//QImage* q = &image;
	//iplImg.data = q->bits();
	//imshow("img", iplImg);
	//waitKey(0);
	QImage newImg = image.scaled(ui.image_label->width(), ui.image_label->height());
	ui.image_label->setPixmap(QPixmap::fromImage(newImg));
}

void MaskedManInQt::getSliderMoved(int value){
	thread->getFrameByPos(value);
}

void MaskedManInQt::setSliderValue(int value){
	ui.play_slider->setValue(value);
}

void MaskedManInQt::setSliderRange(int min, int max){
	ui.play_slider->setRange(min, max);
}

void MaskedManInQt::getThreadEnd(){
	thread->isPlaying = false;
	//ui.play_button->setText(tr("开始"));
	//重置进度条和pos
	//ui.play_slider->setValue(0);
	//thread->pos = 0;
}


void MaskedManInQt::on_pBtn_openVideo_clicked(){
	fileName = QFileDialog::getOpenFileName(
		this, QString::fromLocal8Bit("选择打开的视频"), ".",
		tr("Video Files (*.avi *.wmv *.3gp *.mp4 *.flv)"));
	if( fileName.size() == 0)
		return;

	init( fileName);
}


//显示蒙面人信息
void MaskedManInQt::showMmrInfo(int isDetect)
{
	if(isDetect==0)
		ui.info_text->setText(QString::fromLocal8Bit(""));

	else if(isDetect==1)
	{
		ui.info_text->setTextColor(Qt::green);
		ui.info_text->setText(QString::fromLocal8Bit("有行人经过"));
	}

	else if(isDetect==2)
	{
		ui.info_text->setTextColor(Qt::red);
		ui.info_text->setText(QString::fromLocal8Bit("蒙面人出现！！！！！\n拉响警报！！！！！"));
	}
}
