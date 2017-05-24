/********************************************************************************
** Form generated from reading UI file 'playform.ui'
**
** Created: Sat Oct 4 11:02:21 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYFORM_H
#define UI_PLAYFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayForm
{
public:
    QSlider *play_slider;
    QLabel *image_label;
    QPushButton *play_button;
    QCheckBox *loop_checkbox;
    QPushButton *exit_button;

    void setupUi(QWidget *PlayForm)
    {
        if (PlayForm->objectName().isEmpty())
            PlayForm->setObjectName(QString::fromUtf8("PlayForm"));
        PlayForm->resize(404, 400);
        play_slider = new QSlider(PlayForm);
        play_slider->setObjectName(QString::fromUtf8("play_slider"));
        play_slider->setGeometry(QRect(0, 310, 321, 19));
        play_slider->setOrientation(Qt::Horizontal);
        image_label = new QLabel(PlayForm);
        image_label->setObjectName(QString::fromUtf8("image_label"));
        image_label->setGeometry(QRect(0, 0, 400, 300));
        play_button = new QPushButton(PlayForm);
        play_button->setObjectName(QString::fromUtf8("play_button"));
        play_button->setGeometry(QRect(110, 340, 51, 41));
        loop_checkbox = new QCheckBox(PlayForm);
        loop_checkbox->setObjectName(QString::fromUtf8("loop_checkbox"));
        loop_checkbox->setGeometry(QRect(330, 310, 71, 16));
        exit_button = new QPushButton(PlayForm);
        exit_button->setObjectName(QString::fromUtf8("exit_button"));
        exit_button->setGeometry(QRect(250, 340, 51, 41));

        retranslateUi(PlayForm);

        QMetaObject::connectSlotsByName(PlayForm);
    } // setupUi

    void retranslateUi(QWidget *PlayForm)
    {
        PlayForm->setWindowTitle(QApplication::translate("PlayForm", "Form", 0, QApplication::UnicodeUTF8));
        image_label->setText(QApplication::translate("PlayForm", "TextLabel", 0, QApplication::UnicodeUTF8));
        play_button->setText(QApplication::translate("PlayForm", "\346\222\255\346\224\276", 0, QApplication::UnicodeUTF8));
        loop_checkbox->setText(QApplication::translate("PlayForm", "\345\276\252\347\216\257\346\222\255\346\224\276", 0, QApplication::UnicodeUTF8));
        exit_button->setText(QApplication::translate("PlayForm", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PlayForm: public Ui_PlayForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYFORM_H
