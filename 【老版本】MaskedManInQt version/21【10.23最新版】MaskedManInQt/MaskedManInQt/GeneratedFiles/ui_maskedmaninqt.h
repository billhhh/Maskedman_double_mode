/********************************************************************************
** Form generated from reading UI file 'maskedmaninqt.ui'
**
** Created: Tue Sep 16 11:12:22 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MASKEDMANINQT_H
#define UI_MASKEDMANINQT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_MaskedManInQtClass
{
public:
    QLabel *image_label;
    QPushButton *exit_button;
    QPushButton *play_button;
    QSlider *play_slider;
    QPushButton *pBtn_openVideo;
    QLabel *label;
    QLabel *label2;
    QTextEdit *info_text;

    void setupUi(QDialog *MaskedManInQtClass)
    {
        if (MaskedManInQtClass->objectName().isEmpty())
            MaskedManInQtClass->setObjectName(QString::fromUtf8("MaskedManInQtClass"));
        MaskedManInQtClass->resize(698, 515);
        image_label = new QLabel(MaskedManInQtClass);
        image_label->setObjectName(QString::fromUtf8("image_label"));
        image_label->setGeometry(QRect(30, 70, 421, 291));
        exit_button = new QPushButton(MaskedManInQtClass);
        exit_button->setObjectName(QString::fromUtf8("exit_button"));
        exit_button->setGeometry(QRect(310, 430, 51, 41));
        play_button = new QPushButton(MaskedManInQtClass);
        play_button->setObjectName(QString::fromUtf8("play_button"));
        play_button->setGeometry(QRect(190, 430, 51, 41));
        play_slider = new QSlider(MaskedManInQtClass);
        play_slider->setObjectName(QString::fromUtf8("play_slider"));
        play_slider->setGeometry(QRect(50, 390, 321, 19));
        play_slider->setOrientation(Qt::Horizontal);
        pBtn_openVideo = new QPushButton(MaskedManInQtClass);
        pBtn_openVideo->setObjectName(QString::fromUtf8("pBtn_openVideo"));
        pBtn_openVideo->setGeometry(QRect(50, 430, 71, 41));
        label = new QLabel(MaskedManInQtClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 20, 111, 31));
        label2 = new QLabel(MaskedManInQtClass);
        label2->setObjectName(QString::fromUtf8("label2"));
        label2->setGeometry(QRect(510, 20, 71, 31));
        info_text = new QTextEdit(MaskedManInQtClass);
        info_text->setObjectName(QString::fromUtf8("info_text"));
        info_text->setGeometry(QRect(500, 70, 151, 151));

        retranslateUi(MaskedManInQtClass);

        QMetaObject::connectSlotsByName(MaskedManInQtClass);
    } // setupUi

    void retranslateUi(QDialog *MaskedManInQtClass)
    {
        MaskedManInQtClass->setWindowTitle(QApplication::translate("MaskedManInQtClass", "MaskedManInQt", 0, QApplication::UnicodeUTF8));
        image_label->setText(QString());
        exit_button->setText(QApplication::translate("MaskedManInQtClass", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
        play_button->setText(QApplication::translate("MaskedManInQtClass", "\346\222\255\346\224\276", 0, QApplication::UnicodeUTF8));
        pBtn_openVideo->setText(QApplication::translate("MaskedManInQtClass", "\346\211\223\345\274\200\350\247\206\351\242\221", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MaskedManInQtClass", "\350\222\231\351\235\242\344\272\272\346\231\272\350\203\275\350\257\206\345\210\253\347\263\273\347\273\237", 0, QApplication::UnicodeUTF8));
        label2->setText(QApplication::translate("MaskedManInQtClass", "\344\277\241\346\201\257\346\243\200\346\265\213\346\241\206", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MaskedManInQtClass: public Ui_MaskedManInQtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MASKEDMANINQT_H
