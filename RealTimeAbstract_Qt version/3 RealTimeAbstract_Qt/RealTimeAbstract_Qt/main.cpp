#include "mainwindow.h"
#include <QtGui/QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
	QTextCodec::setCodecForTr( QTextCodec::codecForName("System") );
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
