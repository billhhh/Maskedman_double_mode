/********************************************************************************
** Form generated from reading UI file 'setting.ui'
**
** Created: Sat Oct 4 11:02:21 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTING_H
#define UI_SETTING_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_setting_ui
{
public:
    QPushButton *ok_pushbutton;
    QPushButton *cancel_pushbutton;
    QPushButton *default_pushbutton;
    QGroupBox *objectpramGroupBox;
    QLabel *label;
    QRadioButton *radiobutton100;
    QRadioButton *radiobutton75;
    QRadioButton *radiobutton50;
    QLineEdit *width_lineedit;
    QLineEdit *height_lineedit;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *min_area_lineedit;
    QLabel *label_4;
    QLineEdit *max_area_lineedit;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *jiange_lineedit;
    QGroupBox *groupBox;
    QLabel *label_7;
    QLineEdit *fps_lineedit;
    QLabel *label_8;
    QLineEdit *max_event_num_lineedit;

    void setupUi(QWidget *setting_ui)
    {
        if (setting_ui->objectName().isEmpty())
            setting_ui->setObjectName(QString::fromUtf8("setting_ui"));
        setting_ui->resize(389, 431);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(14);
        setting_ui->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/MainWindow/Resources/setting.png"), QSize(), QIcon::Normal, QIcon::Off);
        setting_ui->setWindowIcon(icon);
        ok_pushbutton = new QPushButton(setting_ui);
        ok_pushbutton->setObjectName(QString::fromUtf8("ok_pushbutton"));
        ok_pushbutton->setGeometry(QRect(30, 380, 71, 31));
        cancel_pushbutton = new QPushButton(setting_ui);
        cancel_pushbutton->setObjectName(QString::fromUtf8("cancel_pushbutton"));
        cancel_pushbutton->setGeometry(QRect(150, 380, 71, 31));
        default_pushbutton = new QPushButton(setting_ui);
        default_pushbutton->setObjectName(QString::fromUtf8("default_pushbutton"));
        default_pushbutton->setGeometry(QRect(270, 380, 91, 31));
        objectpramGroupBox = new QGroupBox(setting_ui);
        objectpramGroupBox->setObjectName(QString::fromUtf8("objectpramGroupBox"));
        objectpramGroupBox->setGeometry(QRect(10, 10, 371, 221));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font1.setPointSize(12);
        font1.setItalic(false);
        objectpramGroupBox->setFont(font1);
        label = new QLabel(objectpramGroupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 30, 91, 21));
        radiobutton100 = new QRadioButton(objectpramGroupBox);
        radiobutton100->setObjectName(QString::fromUtf8("radiobutton100"));
        radiobutton100->setGeometry(QRect(100, 30, 61, 21));
        radiobutton75 = new QRadioButton(objectpramGroupBox);
        radiobutton75->setObjectName(QString::fromUtf8("radiobutton75"));
        radiobutton75->setGeometry(QRect(190, 30, 51, 21));
        radiobutton50 = new QRadioButton(objectpramGroupBox);
        radiobutton50->setObjectName(QString::fromUtf8("radiobutton50"));
        radiobutton50->setGeometry(QRect(270, 30, 51, 21));
        width_lineedit = new QLineEdit(objectpramGroupBox);
        width_lineedit->setObjectName(QString::fromUtf8("width_lineedit"));
        width_lineedit->setGeometry(QRect(100, 80, 51, 21));
        height_lineedit = new QLineEdit(objectpramGroupBox);
        height_lineedit->setObjectName(QString::fromUtf8("height_lineedit"));
        height_lineedit->setGeometry(QRect(190, 80, 51, 20));
        label_2 = new QLabel(objectpramGroupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(170, 80, 16, 21));
        label_3 = new QLabel(objectpramGroupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 130, 101, 21));
        min_area_lineedit = new QLineEdit(objectpramGroupBox);
        min_area_lineedit->setObjectName(QString::fromUtf8("min_area_lineedit"));
        min_area_lineedit->setGeometry(QRect(110, 130, 71, 21));
        label_4 = new QLabel(objectpramGroupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(190, 130, 101, 21));
        max_area_lineedit = new QLineEdit(objectpramGroupBox);
        max_area_lineedit->setObjectName(QString::fromUtf8("max_area_lineedit"));
        max_area_lineedit->setGeometry(QRect(290, 130, 71, 21));
        label_5 = new QLabel(objectpramGroupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 80, 81, 21));
        label_6 = new QLabel(objectpramGroupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 180, 71, 16));
        jiange_lineedit = new QLineEdit(objectpramGroupBox);
        jiange_lineedit->setObjectName(QString::fromUtf8("jiange_lineedit"));
        jiange_lineedit->setGeometry(QRect(90, 180, 41, 21));
        groupBox = new QGroupBox(setting_ui);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 250, 371, 111));
        QFont font2;
        font2.setPointSize(12);
        groupBox->setFont(font2);
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 30, 71, 21));
        fps_lineedit = new QLineEdit(groupBox);
        fps_lineedit->setObjectName(QString::fromUtf8("fps_lineedit"));
        fps_lineedit->setGeometry(QRect(80, 30, 61, 21));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 70, 151, 21));
        max_event_num_lineedit = new QLineEdit(groupBox);
        max_event_num_lineedit->setObjectName(QString::fromUtf8("max_event_num_lineedit"));
        max_event_num_lineedit->setGeometry(QRect(160, 70, 61, 21));

        retranslateUi(setting_ui);

        QMetaObject::connectSlotsByName(setting_ui);
    } // setupUi

    void retranslateUi(QWidget *setting_ui)
    {
        setting_ui->setWindowTitle(QApplication::translate("setting_ui", "\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        ok_pushbutton->setText(QApplication::translate("setting_ui", "\347\241\256 \345\256\232", 0, QApplication::UnicodeUTF8));
        cancel_pushbutton->setText(QApplication::translate("setting_ui", "\345\217\226 \346\266\210", 0, QApplication::UnicodeUTF8));
        default_pushbutton->setText(QApplication::translate("setting_ui", "\351\273\230\350\256\244\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        objectpramGroupBox->setTitle(QApplication::translate("setting_ui", "\347\233\256\346\240\207\345\210\206\346\236\220\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("setting_ui", "\350\247\206\351\242\221\347\274\251\346\224\276", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        radiobutton100->setToolTip(QApplication::translate("setting_ui", "\344\273\245\345\216\237\345\260\272\345\257\270\345\257\271\350\247\206\351\242\221\350\277\233\350\241\214\345\210\206\346\236\220", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        radiobutton100->setText(QApplication::translate("setting_ui", "100%", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        radiobutton75->setToolTip(QApplication::translate("setting_ui", "\344\273\245\345\216\237\350\247\206\351\242\221\345\260\272\345\257\270\347\232\20475%\350\277\233\350\241\214\345\210\206\346\236\220\357\274\214\345\212\240\345\277\253\345\210\206\346\236\220\351\200\237\345\272\246", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        radiobutton75->setText(QApplication::translate("setting_ui", "75%", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        radiobutton50->setToolTip(QApplication::translate("setting_ui", "\344\273\245\345\216\237\350\247\206\351\242\221\345\260\272\345\257\270\347\232\20450%\350\277\233\350\241\214\345\210\206\346\236\220\357\274\214\350\277\233\344\270\200\346\255\245\345\212\240\345\277\253\345\210\206\346\236\220\351\200\237\345\272\246", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        radiobutton50->setText(QApplication::translate("setting_ui", "50%", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("setting_ui", "*", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("setting_ui", "\347\233\256\346\240\207\346\234\200\345\260\217\351\235\242\347\247\257", 0, QApplication::UnicodeUTF8));
        min_area_lineedit->setText(QString());
        label_4->setText(QApplication::translate("setting_ui", "\347\233\256\346\240\207\346\234\200\345\244\247\351\235\242\347\247\257", 0, QApplication::UnicodeUTF8));
        max_area_lineedit->setText(QString());
        label_5->setText(QApplication::translate("setting_ui", "\350\247\206\351\242\221\345\210\206\350\276\250\347\216\207", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("setting_ui", "\345\210\206\346\236\220\350\267\263\345\270\247", 0, QApplication::UnicodeUTF8));
        jiange_lineedit->setText(QString());
        groupBox->setTitle(QApplication::translate("setting_ui", "\345\205\250\346\221\230\350\246\201\350\247\206\351\242\221", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("setting_ui", "\350\247\206\351\242\221\345\270\247\347\216\207", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("setting_ui", "\345\220\214\344\270\200\346\227\266\351\227\264\346\234\200\345\244\247\346\221\230\350\246\201\346\225\260", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class setting_ui: public Ui_setting_ui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_H
