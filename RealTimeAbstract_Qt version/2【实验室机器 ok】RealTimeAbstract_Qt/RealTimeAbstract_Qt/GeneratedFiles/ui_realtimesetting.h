/********************************************************************************
** Form generated from reading UI file 'realtimesetting.ui'
**
** Created: Sat Oct 4 11:02:19 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REALTIMESETTING_H
#define UI_REALTIMESETTING_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_RealTimeSetting
{
public:
    QPushButton *pushButton_default;
    QPushButton *pushButton_cancel;
    QPushButton *pushButton_ok;
    QGroupBox *groupBox;
    QLabel *label_7;
    QLineEdit *lineEdit_fps;
    QLabel *label_8;
    QLineEdit *lineEdit_max_event_num;
    QLabel *label_9;
    QLineEdit *lineEdit_path;
    QPushButton *pushButton_path;
    QGroupBox *objectpramGroupBox;
    QLabel *label;
    QRadioButton *radioButton100;
    QRadioButton *radioButton75;
    QRadioButton *radioButton50;
    QLineEdit *lineEdit_width;
    QLineEdit *lineEdit_height;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_min_area;
    QLabel *label_4;
    QLineEdit *lineEdit_max_area;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *lineEdit_jiange;

    void setupUi(QDialog *RealTimeSetting)
    {
        if (RealTimeSetting->objectName().isEmpty())
            RealTimeSetting->setObjectName(QString::fromUtf8("RealTimeSetting"));
        RealTimeSetting->resize(506, 372);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/MainWindow/Resources/setting.png"), QSize(), QIcon::Normal, QIcon::Off);
        RealTimeSetting->setWindowIcon(icon);
        pushButton_default = new QPushButton(RealTimeSetting);
        pushButton_default->setObjectName(QString::fromUtf8("pushButton_default"));
        pushButton_default->setGeometry(QRect(340, 330, 91, 31));
        pushButton_cancel = new QPushButton(RealTimeSetting);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));
        pushButton_cancel->setGeometry(QRect(210, 330, 71, 31));
        pushButton_ok = new QPushButton(RealTimeSetting);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));
        pushButton_ok->setGeometry(QRect(70, 330, 71, 31));
        groupBox = new QGroupBox(RealTimeSetting);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 200, 481, 111));
        QFont font;
        font.setPointSize(12);
        groupBox->setFont(font);
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 30, 71, 21));
        lineEdit_fps = new QLineEdit(groupBox);
        lineEdit_fps->setObjectName(QString::fromUtf8("lineEdit_fps"));
        lineEdit_fps->setGeometry(QRect(80, 30, 61, 21));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(160, 30, 151, 21));
        lineEdit_max_event_num = new QLineEdit(groupBox);
        lineEdit_max_event_num->setObjectName(QString::fromUtf8("lineEdit_max_event_num"));
        lineEdit_max_event_num->setGeometry(QRect(310, 30, 61, 21));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 70, 101, 21));
        lineEdit_path = new QLineEdit(groupBox);
        lineEdit_path->setObjectName(QString::fromUtf8("lineEdit_path"));
        lineEdit_path->setGeometry(QRect(110, 70, 301, 21));
        pushButton_path = new QPushButton(groupBox);
        pushButton_path->setObjectName(QString::fromUtf8("pushButton_path"));
        pushButton_path->setGeometry(QRect(430, 70, 31, 23));
        objectpramGroupBox = new QGroupBox(RealTimeSetting);
        objectpramGroupBox->setObjectName(QString::fromUtf8("objectpramGroupBox"));
        objectpramGroupBox->setGeometry(QRect(10, 10, 481, 181));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(12);
        font1.setItalic(false);
        objectpramGroupBox->setFont(font1);
        label = new QLabel(objectpramGroupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 30, 91, 21));
        radioButton100 = new QRadioButton(objectpramGroupBox);
        radioButton100->setObjectName(QString::fromUtf8("radioButton100"));
        radioButton100->setGeometry(QRect(100, 30, 61, 21));
        radioButton75 = new QRadioButton(objectpramGroupBox);
        radioButton75->setObjectName(QString::fromUtf8("radioButton75"));
        radioButton75->setGeometry(QRect(190, 30, 51, 21));
        radioButton50 = new QRadioButton(objectpramGroupBox);
        radioButton50->setObjectName(QString::fromUtf8("radioButton50"));
        radioButton50->setGeometry(QRect(270, 30, 51, 21));
        lineEdit_width = new QLineEdit(objectpramGroupBox);
        lineEdit_width->setObjectName(QString::fromUtf8("lineEdit_width"));
        lineEdit_width->setGeometry(QRect(100, 70, 51, 21));
        lineEdit_height = new QLineEdit(objectpramGroupBox);
        lineEdit_height->setObjectName(QString::fromUtf8("lineEdit_height"));
        lineEdit_height->setGeometry(QRect(190, 70, 51, 20));
        label_2 = new QLabel(objectpramGroupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(170, 70, 16, 21));
        label_3 = new QLabel(objectpramGroupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 110, 101, 21));
        lineEdit_min_area = new QLineEdit(objectpramGroupBox);
        lineEdit_min_area->setObjectName(QString::fromUtf8("lineEdit_min_area"));
        lineEdit_min_area->setGeometry(QRect(110, 110, 71, 21));
        label_4 = new QLabel(objectpramGroupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(190, 110, 101, 21));
        lineEdit_max_area = new QLineEdit(objectpramGroupBox);
        lineEdit_max_area->setObjectName(QString::fromUtf8("lineEdit_max_area"));
        lineEdit_max_area->setGeometry(QRect(290, 110, 71, 21));
        label_5 = new QLabel(objectpramGroupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 70, 81, 21));
        label_6 = new QLabel(objectpramGroupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 150, 71, 16));
        lineEdit_jiange = new QLineEdit(objectpramGroupBox);
        lineEdit_jiange->setObjectName(QString::fromUtf8("lineEdit_jiange"));
        lineEdit_jiange->setGeometry(QRect(90, 150, 41, 21));

        retranslateUi(RealTimeSetting);

        QMetaObject::connectSlotsByName(RealTimeSetting);
    } // setupUi

    void retranslateUi(QDialog *RealTimeSetting)
    {
        RealTimeSetting->setWindowTitle(QApplication::translate("RealTimeSetting", "\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        pushButton_default->setText(QApplication::translate("RealTimeSetting", "\351\273\230\350\256\244\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        pushButton_cancel->setText(QApplication::translate("RealTimeSetting", "\345\217\226 \346\266\210", 0, QApplication::UnicodeUTF8));
        pushButton_ok->setText(QApplication::translate("RealTimeSetting", "\347\241\256 \345\256\232", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("RealTimeSetting", "\350\247\206\351\242\221\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("RealTimeSetting", "\350\247\206\351\242\221\345\270\247\347\216\207", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("RealTimeSetting", "\345\220\214\344\270\200\346\227\266\351\227\264\346\234\200\345\244\247\346\221\230\350\246\201\346\225\260", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("RealTimeSetting", "\350\247\206\351\242\221\344\277\235\345\255\230\350\267\257\345\276\204", 0, QApplication::UnicodeUTF8));
        pushButton_path->setText(QApplication::translate("RealTimeSetting", "...", 0, QApplication::UnicodeUTF8));
        objectpramGroupBox->setTitle(QApplication::translate("RealTimeSetting", "\347\233\256\346\240\207\345\210\206\346\236\220\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("RealTimeSetting", "\350\247\206\351\242\221\347\274\251\346\224\276", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        radioButton100->setToolTip(QApplication::translate("RealTimeSetting", "\344\273\245\345\216\237\345\260\272\345\257\270\345\257\271\350\247\206\351\242\221\350\277\233\350\241\214\345\210\206\346\236\220", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        radioButton100->setText(QApplication::translate("RealTimeSetting", "100%", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        radioButton75->setToolTip(QApplication::translate("RealTimeSetting", "\344\273\245\345\216\237\350\247\206\351\242\221\345\260\272\345\257\270\347\232\20475%\350\277\233\350\241\214\345\210\206\346\236\220\357\274\214\345\212\240\345\277\253\345\210\206\346\236\220\351\200\237\345\272\246", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        radioButton75->setText(QApplication::translate("RealTimeSetting", "75%", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        radioButton50->setToolTip(QApplication::translate("RealTimeSetting", "\344\273\245\345\216\237\350\247\206\351\242\221\345\260\272\345\257\270\347\232\20450%\350\277\233\350\241\214\345\210\206\346\236\220\357\274\214\350\277\233\344\270\200\346\255\245\345\212\240\345\277\253\345\210\206\346\236\220\351\200\237\345\272\246", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        radioButton50->setText(QApplication::translate("RealTimeSetting", "50%", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("RealTimeSetting", "*", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("RealTimeSetting", "\347\233\256\346\240\207\346\234\200\345\260\217\351\235\242\347\247\257", 0, QApplication::UnicodeUTF8));
        lineEdit_min_area->setText(QString());
        label_4->setText(QApplication::translate("RealTimeSetting", "\347\233\256\346\240\207\346\234\200\345\244\247\351\235\242\347\247\257", 0, QApplication::UnicodeUTF8));
        lineEdit_max_area->setText(QString());
        label_5->setText(QApplication::translate("RealTimeSetting", "\350\247\206\351\242\221\345\210\206\350\276\250\347\216\207", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("RealTimeSetting", "\345\210\206\346\236\220\350\267\263\345\270\247", 0, QApplication::UnicodeUTF8));
        lineEdit_jiange->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class RealTimeSetting: public Ui_RealTimeSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REALTIMESETTING_H
