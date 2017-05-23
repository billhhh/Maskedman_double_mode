/********************************************************************************
** Form generated from reading UI file 'videoabstract_qtver.ui'
**
** Created: Sat Oct 4 11:02:21 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOABSTRACT_QTVER_H
#define UI_VIDEOABSTRACT_QTVER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QTextBrowser>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VideoAbstract_QTverClass
{
public:
    QWidget *left_widget_down;
    QPushButton *open_file_button;
    QPushButton *setting_button;
    QPushButton *analysis_button;
    QProgressBar *progress_bar;
    QLabel *progress_label;
    QPushButton *search_button;
    QTextBrowser *progress_info;
    QCheckBox *show_video_check_box;
    QLabel *event_count_label;
    QWidget *left_widget_up;
    QLabel *video_label;
    QWidget *right_widget;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QLabel *label_2;
    QPushButton *pushButton_switch;
    QPushButton *pushButton_playAll;
    QFrame *line_h;
    QFrame *line_v;

    void setupUi(QWidget *VideoAbstract_QTverClass)
    {
        if (VideoAbstract_QTverClass->objectName().isEmpty())
            VideoAbstract_QTverClass->setObjectName(QString::fromUtf8("VideoAbstract_QTverClass"));
        VideoAbstract_QTverClass->resize(1020, 680);
        VideoAbstract_QTverClass->setMinimumSize(QSize(900, 600));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/MainWindow/Resources/windowIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        VideoAbstract_QTverClass->setWindowIcon(icon);
        VideoAbstract_QTverClass->setStyleSheet(QString::fromUtf8("border-color: rgb(255, 19, 125);"));
        left_widget_down = new QWidget(VideoAbstract_QTverClass);
        left_widget_down->setObjectName(QString::fromUtf8("left_widget_down"));
        left_widget_down->setGeometry(QRect(0, 300, 400, 380));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(11);
        left_widget_down->setFont(font);
        left_widget_down->setStyleSheet(QString::fromUtf8("border-color: rgb(158, 151, 255);"));
        open_file_button = new QPushButton(left_widget_down);
        open_file_button->setObjectName(QString::fromUtf8("open_file_button"));
        open_file_button->setGeometry(QRect(70, 160, 90, 90));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/MainWindow/Resources/openvideo.png"), QSize(), QIcon::Normal, QIcon::Off);
        open_file_button->setIcon(icon1);
        open_file_button->setIconSize(QSize(75, 75));
        setting_button = new QPushButton(left_widget_down);
        setting_button->setObjectName(QString::fromUtf8("setting_button"));
        setting_button->setGeometry(QRect(240, 270, 90, 90));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/MainWindow/Resources/setting.png"), QSize(), QIcon::Normal, QIcon::Off);
        setting_button->setIcon(icon2);
        setting_button->setIconSize(QSize(75, 75));
        analysis_button = new QPushButton(left_widget_down);
        analysis_button->setObjectName(QString::fromUtf8("analysis_button"));
        analysis_button->setGeometry(QRect(240, 160, 90, 90));
        analysis_button->setStyleSheet(QString::fromUtf8("border-color: rgb(255, 0, 0);"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/MainWindow/Resources/startanalyze.png"), QSize(), QIcon::Normal, QIcon::Off);
        analysis_button->setIcon(icon3);
        analysis_button->setIconSize(QSize(75, 75));
        progress_bar = new QProgressBar(left_widget_down);
        progress_bar->setObjectName(QString::fromUtf8("progress_bar"));
        progress_bar->setGeometry(QRect(10, 10, 381, 30));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Agency FB"));
        font1.setPointSize(11);
        progress_bar->setFont(font1);
        progress_bar->setValue(0);
        progress_bar->setAlignment(Qt::AlignCenter);
        progress_label = new QLabel(left_widget_down);
        progress_label->setObjectName(QString::fromUtf8("progress_label"));
        progress_label->setGeometry(QRect(260, 40, 100, 30));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(9);
        progress_label->setFont(font2);
        progress_label->setAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        search_button = new QPushButton(left_widget_down);
        search_button->setObjectName(QString::fromUtf8("search_button"));
        search_button->setGeometry(QRect(70, 270, 90, 90));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/MainWindow/Resources/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        search_button->setIcon(icon4);
        search_button->setIconSize(QSize(90, 90));
        progress_info = new QTextBrowser(left_widget_down);
        progress_info->setObjectName(QString::fromUtf8("progress_info"));
        progress_info->setGeometry(QRect(5, 70, 390, 65));
        progress_info->setFont(font);
        progress_info->setFrameShadow(QFrame::Sunken);
        show_video_check_box = new QCheckBox(left_widget_down);
        show_video_check_box->setObjectName(QString::fromUtf8("show_video_check_box"));
        show_video_check_box->setGeometry(QRect(20, 40, 91, 30));
        event_count_label = new QLabel(left_widget_down);
        event_count_label->setObjectName(QString::fromUtf8("event_count_label"));
        event_count_label->setGeometry(QRect(140, 40, 91, 30));
        left_widget_up = new QWidget(VideoAbstract_QTverClass);
        left_widget_up->setObjectName(QString::fromUtf8("left_widget_up"));
        left_widget_up->setGeometry(QRect(0, 0, 400, 300));
        video_label = new QLabel(left_widget_up);
        video_label->setObjectName(QString::fromUtf8("video_label"));
        video_label->setGeometry(QRect(0, 0, 400, 300));
        video_label->setPixmap(QPixmap(QString::fromUtf8(":/MainWindow/Resources/nocapture.png")));
        right_widget = new QWidget(VideoAbstract_QTverClass);
        right_widget->setObjectName(QString::fromUtf8("right_widget"));
        right_widget->setGeometry(QRect(400, 0, 620, 680));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(right_widget->sizePolicy().hasHeightForWidth());
        right_widget->setSizePolicy(sizePolicy);
        scrollArea = new QScrollArea(right_widget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(0, 30, 620, 650));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy1);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 601, 648));
        scrollArea->setWidget(scrollAreaWidgetContents);
        label_2 = new QLabel(right_widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 0, 111, 30));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font3.setPointSize(12);
        label_2->setFont(font3);
        pushButton_switch = new QPushButton(right_widget);
        pushButton_switch->setObjectName(QString::fromUtf8("pushButton_switch"));
        pushButton_switch->setGeometry(QRect(520, 0, 81, 23));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/MainWindow/Resources/switch.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_switch->setIcon(icon5);
        pushButton_playAll = new QPushButton(right_widget);
        pushButton_playAll->setObjectName(QString::fromUtf8("pushButton_playAll"));
        pushButton_playAll->setGeometry(QRect(130, 0, 81, 23));
        line_h = new QFrame(VideoAbstract_QTverClass);
        line_h->setObjectName(QString::fromUtf8("line_h"));
        line_h->setGeometry(QRect(0, 300, 400, 3));
        line_h->setFrameShape(QFrame::HLine);
        line_h->setFrameShadow(QFrame::Sunken);
        line_v = new QFrame(VideoAbstract_QTverClass);
        line_v->setObjectName(QString::fromUtf8("line_v"));
        line_v->setGeometry(QRect(400, 0, 3, 600));
        line_v->setFrameShape(QFrame::VLine);
        line_v->setFrameShadow(QFrame::Sunken);

        retranslateUi(VideoAbstract_QTverClass);

        QMetaObject::connectSlotsByName(VideoAbstract_QTverClass);
    } // setupUi

    void retranslateUi(QWidget *VideoAbstract_QTverClass)
    {
        VideoAbstract_QTverClass->setWindowTitle(QApplication::translate("VideoAbstract_QTverClass", "\346\231\272\350\203\275\350\247\206\351\242\221\346\221\230\350\246\201\350\275\257\344\273\266", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        open_file_button->setToolTip(QApplication::translate("VideoAbstract_QTverClass", "\346\211\223\345\274\200\350\247\206\351\242\221", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        open_file_button->setText(QString());
#ifndef QT_NO_TOOLTIP
        setting_button->setToolTip(QApplication::translate("VideoAbstract_QTverClass", "\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        setting_button->setText(QString());
#ifndef QT_NO_TOOLTIP
        analysis_button->setToolTip(QApplication::translate("VideoAbstract_QTverClass", "\345\274\200\345\247\213\345\210\206\346\236\220", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        analysis_button->setText(QString());
        progress_label->setText(QApplication::translate("VideoAbstract_QTverClass", "\350\200\227\346\227\266:0\346\227\2660\345\210\2060\347\247\222", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        search_button->setToolTip(QApplication::translate("VideoAbstract_QTverClass", "\346\221\230\350\246\201\346\243\200\347\264\242", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        search_button->setText(QString());
        progress_info->setHtml(QApplication::translate("VideoAbstract_QTverClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\256\213\344\275\223'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\350\257\267\351\200\211\346\213\251\344\270\200\344\270\252\346\226\207\344\273\266</p></body></html>", 0, QApplication::UnicodeUTF8));
        show_video_check_box->setText(QApplication::translate("VideoAbstract_QTverClass", "\346\230\276\347\244\272\345\210\206\346\236\220\350\247\206\351\242\221", 0, QApplication::UnicodeUTF8));
        event_count_label->setText(QApplication::translate("VideoAbstract_QTverClass", "\344\272\213\344\273\266\346\225\260\351\207\217:0", 0, QApplication::UnicodeUTF8));
        video_label->setText(QString());
        label_2->setText(QApplication::translate("VideoAbstract_QTverClass", " \350\247\206\351\242\221\346\221\230\350\246\201\345\210\227\350\241\250\357\274\232", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pushButton_switch->setToolTip(QApplication::translate("VideoAbstract_QTverClass", "\345\210\207\346\215\242\345\210\260\345\256\236\346\227\266\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButton_switch->setText(QApplication::translate("VideoAbstract_QTverClass", "\345\256\236\346\227\266\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8));
        pushButton_playAll->setText(QApplication::translate("VideoAbstract_QTverClass", "\346\222\255\346\224\276\346\211\200\346\234\211\344\272\213\344\273\266", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class VideoAbstract_QTverClass: public Ui_VideoAbstract_QTverClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOABSTRACT_QTVER_H
