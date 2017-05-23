/********************************************************************************
** Form generated from reading UI file 'abstract.ui'
**
** Created: Sat Oct 4 11:02:20 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABSTRACT_H
#define UI_ABSTRACT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AbstrctForm
{
public:
    QLabel *image_label;
    QLabel *start_time_label;
    QLabel *end_time_label;
    QPushButton *play_button;
    QLabel *label_abstract_index;

    void setupUi(QWidget *AbstrctForm)
    {
        if (AbstrctForm->objectName().isEmpty())
            AbstrctForm->setObjectName(QString::fromUtf8("AbstrctForm"));
        AbstrctForm->resize(300, 255);
        image_label = new QLabel(AbstrctForm);
        image_label->setObjectName(QString::fromUtf8("image_label"));
        image_label->setGeometry(QRect(0, 0, 300, 225));
        start_time_label = new QLabel(AbstrctForm);
        start_time_label->setObjectName(QString::fromUtf8("start_time_label"));
        start_time_label->setGeometry(QRect(0, 225, 150, 15));
        end_time_label = new QLabel(AbstrctForm);
        end_time_label->setObjectName(QString::fromUtf8("end_time_label"));
        end_time_label->setGeometry(QRect(0, 240, 150, 15));
        play_button = new QPushButton(AbstrctForm);
        play_button->setObjectName(QString::fromUtf8("play_button"));
        play_button->setGeometry(QRect(150, 225, 40, 30));
        label_abstract_index = new QLabel(AbstrctForm);
        label_abstract_index->setObjectName(QString::fromUtf8("label_abstract_index"));
        label_abstract_index->setGeometry(QRect(200, 230, 54, 21));

        retranslateUi(AbstrctForm);

        QMetaObject::connectSlotsByName(AbstrctForm);
    } // setupUi

    void retranslateUi(QWidget *AbstrctForm)
    {
        AbstrctForm->setWindowTitle(QApplication::translate("AbstrctForm", "Form", 0, QApplication::UnicodeUTF8));
        image_label->setText(QApplication::translate("AbstrctForm", "\345\233\276\347\211\207\346\230\276\347\244\272", 0, QApplication::UnicodeUTF8));
        start_time_label->setText(QApplication::translate("AbstrctForm", "\345\274\200\345\247\213\346\227\266\351\227\264:", 0, QApplication::UnicodeUTF8));
        end_time_label->setText(QApplication::translate("AbstrctForm", "\347\273\223\346\235\237\346\227\266\351\227\264:", 0, QApplication::UnicodeUTF8));
        play_button->setText(QApplication::translate("AbstrctForm", "\346\222\255\346\224\276", 0, QApplication::UnicodeUTF8));
        label_abstract_index->setText(QApplication::translate("AbstrctForm", "\346\221\230\350\246\201", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AbstrctForm: public Ui_AbstrctForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABSTRACT_H
