/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sat Oct 4 11:02:02 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QLabel *label_cam0;
    QLabel *label_cam1;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QCheckBox *checkBox_cam0;
    QCheckBox *checkBox_cam1;
    QLabel *label_5;
    QPushButton *pushButton_setting;
    QPushButton *pushButton_localModel;
    QPushButton *pushButton_start;
    QLabel *label_time;
    QLabel *label_abstract_num_1;
    QLabel *label_abstract_num_0;

    void setupUi(QWidget *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->resize(800, 400);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/MainWindow/Resources/windowIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindowClass->setWindowIcon(icon);
        label_cam0 = new QLabel(MainWindowClass);
        label_cam0->setObjectName(QString::fromUtf8("label_cam0"));
        label_cam0->setGeometry(QRect(0, 0, 400, 300));
        label_cam0->setPixmap(QPixmap(QString::fromUtf8(":/MainWindow/Resources/nocapture.png")));
        label_cam1 = new QLabel(MainWindowClass);
        label_cam1->setObjectName(QString::fromUtf8("label_cam1"));
        label_cam1->setGeometry(QRect(400, 0, 400, 300));
        label_cam1->setPixmap(QPixmap(QString::fromUtf8(":/MainWindow/Resources/nocapture.png")));
        line = new QFrame(MainWindowClass);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 301, 800, 2));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(MainWindowClass);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(400, 0, 2, 301));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(MainWindowClass);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(801, 0, 2, 301));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);
        checkBox_cam0 = new QCheckBox(MainWindowClass);
        checkBox_cam0->setObjectName(QString::fromUtf8("checkBox_cam0"));
        checkBox_cam0->setGeometry(QRect(30, 340, 71, 16));
        checkBox_cam1 = new QCheckBox(MainWindowClass);
        checkBox_cam1->setObjectName(QString::fromUtf8("checkBox_cam1"));
        checkBox_cam1->setGeometry(QRect(30, 370, 71, 16));
        label_5 = new QLabel(MainWindowClass);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 310, 81, 21));
        pushButton_setting = new QPushButton(MainWindowClass);
        pushButton_setting->setObjectName(QString::fromUtf8("pushButton_setting"));
        pushButton_setting->setGeometry(QRect(280, 310, 81, 81));
        pushButton_setting->setLayoutDirection(Qt::LeftToRight);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/MainWindow/Resources/setting.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_setting->setIcon(icon1);
        pushButton_setting->setIconSize(QSize(60, 60));
        pushButton_localModel = new QPushButton(MainWindowClass);
        pushButton_localModel->setObjectName(QString::fromUtf8("pushButton_localModel"));
        pushButton_localModel->setGeometry(QRect(710, 310, 81, 21));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/MainWindow/Resources/switch.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_localModel->setIcon(icon2);
        pushButton_start = new QPushButton(MainWindowClass);
        pushButton_start->setObjectName(QString::fromUtf8("pushButton_start"));
        pushButton_start->setGeometry(QRect(160, 310, 81, 81));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/MainWindow/Resources/startanalyze.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_start->setIcon(icon3);
        pushButton_start->setIconSize(QSize(60, 60));
        label_time = new QLabel(MainWindowClass);
        label_time->setObjectName(QString::fromUtf8("label_time"));
        label_time->setGeometry(QRect(480, 370, 201, 21));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        label_time->setFont(font);
        label_abstract_num_1 = new QLabel(MainWindowClass);
        label_abstract_num_1->setObjectName(QString::fromUtf8("label_abstract_num_1"));
        label_abstract_num_1->setGeometry(QRect(480, 350, 161, 21));
        label_abstract_num_1->setFont(font);
        label_abstract_num_0 = new QLabel(MainWindowClass);
        label_abstract_num_0->setObjectName(QString::fromUtf8("label_abstract_num_0"));
        label_abstract_num_0->setGeometry(QRect(480, 330, 161, 21));
        label_abstract_num_0->setFont(font);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QWidget *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "\345\256\236\346\227\266\350\247\206\351\242\221\346\221\230\350\246\201", 0, QApplication::UnicodeUTF8));
        label_cam0->setText(QString());
        label_cam1->setText(QString());
        checkBox_cam0->setText(QApplication::translate("MainWindowClass", "\346\221\204\345\203\217\345\244\2641", 0, QApplication::UnicodeUTF8));
        checkBox_cam1->setText(QApplication::translate("MainWindowClass", "\346\221\204\345\203\217\345\244\2642", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindowClass", "\346\221\204\345\203\217\345\244\264\351\200\211\346\213\251\357\274\232", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_setting->setToolTip(QApplication::translate("MainWindowClass", "\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_setting->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButton_localModel->setToolTip(QApplication::translate("MainWindowClass", "\345\210\207\346\215\242\345\210\260\346\234\254\345\234\260\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_localModel->setText(QApplication::translate("MainWindowClass", "\346\234\254\345\234\260\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_start->setToolTip(QApplication::translate("MainWindowClass", "\345\274\200\345\247\213\347\233\221\346\216\247", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_start->setText(QString());
        label_time->setText(QApplication::translate("MainWindowClass", "\346\227\266\351\227\264:", 0, QApplication::UnicodeUTF8));
        label_abstract_num_1->setText(QApplication::translate("MainWindowClass", "\346\221\204\345\203\217\345\244\2642\344\272\272\347\211\251\346\225\260\351\207\217:", 0, QApplication::UnicodeUTF8));
        label_abstract_num_0->setText(QApplication::translate("MainWindowClass", "\346\221\204\345\203\217\345\244\2641\344\272\272\347\211\251\346\225\260\351\207\217:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
