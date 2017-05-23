/********************************************************************************
** Form generated from reading UI file 'drawform.ui'
**
** Created: Sat Oct 4 11:02:20 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRAWFORM_H
#define UI_DRAWFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QTimeEdit>

QT_BEGIN_NAMESPACE

class Ui_drawform
{
public:
    QLabel *image_label;
    QFrame *frame;
    QTimeEdit *timeEdit_end;
    QGroupBox *groupBox;
    QRadioButton *line_radiobutton;
    QRadioButton *rect_radiobutton;
    QLabel *label_2;
    QLabel *label;
    QTimeEdit *timeEdit_start;
    QPushButton *ok_button;
    QPushButton *clear_button;

    void setupUi(QDialog *drawform)
    {
        if (drawform->objectName().isEmpty())
            drawform->setObjectName(QString::fromUtf8("drawform"));
        drawform->resize(400, 400);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/MainWindow/Resources/windowIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        drawform->setWindowIcon(icon);
        image_label = new QLabel(drawform);
        image_label->setObjectName(QString::fromUtf8("image_label"));
        image_label->setGeometry(QRect(0, 0, 400, 300));
        frame = new QFrame(drawform);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 300, 401, 101));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        timeEdit_end = new QTimeEdit(frame);
        timeEdit_end->setObjectName(QString::fromUtf8("timeEdit_end"));
        timeEdit_end->setGeometry(QRect(230, 60, 81, 31));
        timeEdit_end->setTime(QTime(13, 50, 0));
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(110, 10, 75, 81));
        line_radiobutton = new QRadioButton(groupBox);
        line_radiobutton->setObjectName(QString::fromUtf8("line_radiobutton"));
        line_radiobutton->setGeometry(QRect(15, 15, 51, 16));
        rect_radiobutton = new QRadioButton(groupBox);
        rect_radiobutton->setObjectName(QString::fromUtf8("rect_radiobutton"));
        rect_radiobutton->setGeometry(QRect(15, 50, 51, 16));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(210, 60, 21, 31));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(210, 10, 21, 31));
        timeEdit_start = new QTimeEdit(frame);
        timeEdit_start->setObjectName(QString::fromUtf8("timeEdit_start"));
        timeEdit_start->setGeometry(QRect(230, 10, 81, 31));
        timeEdit_start->setTime(QTime(12, 20, 0));
        ok_button = new QPushButton(frame);
        ok_button->setObjectName(QString::fromUtf8("ok_button"));
        ok_button->setGeometry(QRect(10, 10, 75, 31));
        clear_button = new QPushButton(frame);
        clear_button->setObjectName(QString::fromUtf8("clear_button"));
        clear_button->setGeometry(QRect(10, 60, 75, 31));

        retranslateUi(drawform);

        QMetaObject::connectSlotsByName(drawform);
    } // setupUi

    void retranslateUi(QDialog *drawform)
    {
        drawform->setWindowTitle(QApplication::translate("drawform", "\346\221\230\350\246\201\346\243\200\347\264\242", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        image_label->setToolTip(QApplication::translate("drawform", "\345\234\250\350\247\206\351\242\221\344\270\212\347\224\273\347\272\277\350\277\233\350\241\214\346\221\230\350\246\201\346\243\200\347\264\242", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        image_label->setText(QString());
        groupBox->setTitle(QString());
#ifndef QT_NO_TOOLTIP
        line_radiobutton->setToolTip(QApplication::translate("drawform", "\347\224\273\344\270\200\346\235\241\345\270\246\347\256\255\345\244\264\347\232\204\347\233\264\347\272\277\357\274\214\346\243\200\347\264\242\346\214\211\347\205\247\347\233\264\347\272\277\346\226\271\345\220\221\350\277\220\345\212\250\347\232\204\350\247\206\351\242\221\346\221\230\350\246\201", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        line_radiobutton->setText(QApplication::translate("drawform", "\347\233\264\347\272\277", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        rect_radiobutton->setToolTip(QApplication::translate("drawform", "\345\234\250\350\247\206\351\242\221\344\270\255\347\224\273\344\270\200\344\270\252\347\237\251\345\275\242\357\274\214\346\243\200\347\264\242\350\277\233\345\205\245\350\277\231\344\270\252\347\237\251\345\275\242\347\232\204\350\247\206\351\242\221\346\221\230\350\246\201", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        rect_radiobutton->setText(QApplication::translate("drawform", "\347\237\251\345\275\242", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("drawform", "\345\210\260", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("drawform", "\344\273\216", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ok_button->setToolTip(QApplication::translate("drawform", "\347\202\271\345\207\273\347\241\256\345\256\232\344\277\235\345\255\230", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        ok_button->setText(QApplication::translate("drawform", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        clear_button->setToolTip(QApplication::translate("drawform", "\346\270\205\351\231\244\346\211\200\346\234\211\347\224\273\347\272\277", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        clear_button->setText(QApplication::translate("drawform", "\346\270\205\351\231\244", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class drawform: public Ui_drawform {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRAWFORM_H
