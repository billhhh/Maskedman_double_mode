/********************************************************************************
** Form generated from reading UI file 'abstractsearchform.ui'
**
** Created: Sat Oct 4 11:02:20 2014
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABSTRACTSEARCHFORM_H
#define UI_ABSTRACTSEARCHFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AbstractSearchForm
{
public:
    QPushButton *pushButton;
    QLineEdit *min_area_lineedit1;
    QCheckBox *limit_area_checkbox;
    QLineEdit *max_area_lineedit1;
    QLabel *label_10;
    QLabel *label_9;
    QCheckBox *checkBox_3;
    QCheckBox *limit_content_checkbox;
    QCheckBox *enter_checkbox;
    QCheckBox *checkBox_5;

    void setupUi(QDialog *AbstractSearchForm)
    {
        if (AbstractSearchForm->objectName().isEmpty())
            AbstractSearchForm->setObjectName(QString::fromUtf8("AbstractSearchForm"));
        AbstractSearchForm->resize(586, 376);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(12);
        AbstractSearchForm->setFont(font);
        pushButton = new QPushButton(AbstractSearchForm);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(90, 260, 75, 23));
        min_area_lineedit1 = new QLineEdit(AbstractSearchForm);
        min_area_lineedit1->setObjectName(QString::fromUtf8("min_area_lineedit1"));
        min_area_lineedit1->setGeometry(QRect(70, 70, 91, 21));
        limit_area_checkbox = new QCheckBox(AbstractSearchForm);
        limit_area_checkbox->setObjectName(QString::fromUtf8("limit_area_checkbox"));
        limit_area_checkbox->setGeometry(QRect(20, 20, 201, 21));
        max_area_lineedit1 = new QLineEdit(AbstractSearchForm);
        max_area_lineedit1->setObjectName(QString::fromUtf8("max_area_lineedit1"));
        max_area_lineedit1->setGeometry(QRect(70, 120, 91, 21));
        label_10 = new QLabel(AbstractSearchForm);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(30, 120, 41, 21));
        label_9 = new QLabel(AbstractSearchForm);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(30, 70, 41, 21));
        checkBox_3 = new QCheckBox(AbstractSearchForm);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setGeometry(QRect(330, 50, 61, 21));
        limit_content_checkbox = new QCheckBox(AbstractSearchForm);
        limit_content_checkbox->setObjectName(QString::fromUtf8("limit_content_checkbox"));
        limit_content_checkbox->setGeometry(QRect(300, 20, 121, 21));
        enter_checkbox = new QCheckBox(AbstractSearchForm);
        enter_checkbox->setObjectName(QString::fromUtf8("enter_checkbox"));
        enter_checkbox->setGeometry(QRect(330, 110, 61, 21));
        checkBox_5 = new QCheckBox(AbstractSearchForm);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));
        checkBox_5->setGeometry(QRect(330, 80, 51, 21));

        retranslateUi(AbstractSearchForm);

        QMetaObject::connectSlotsByName(AbstractSearchForm);
    } // setupUi

    void retranslateUi(QDialog *AbstractSearchForm)
    {
        AbstractSearchForm->setWindowTitle(QApplication::translate("AbstractSearchForm", "AbstractSearchForm", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("AbstractSearchForm", "PushButton", 0, QApplication::UnicodeUTF8));
        min_area_lineedit1->setText(QApplication::translate("AbstractSearchForm", "1000", 0, QApplication::UnicodeUTF8));
        limit_area_checkbox->setText(QApplication::translate("AbstractSearchForm", "\351\231\220\345\210\266\347\233\256\346\240\207\351\235\242\347\247\257\345\244\247\345\260\217(\345\203\217\347\264\240):", 0, QApplication::UnicodeUTF8));
        max_area_lineedit1->setText(QApplication::translate("AbstractSearchForm", "1000000", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("AbstractSearchForm", "\346\234\200\345\244\247", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("AbstractSearchForm", "\346\234\200\345\260\217", 0, QApplication::UnicodeUTF8));
        checkBox_3->setText(QApplication::translate("AbstractSearchForm", "\347\273\212\347\272\277", 0, QApplication::UnicodeUTF8));
        limit_content_checkbox->setText(QApplication::translate("AbstractSearchForm", "\351\231\220\345\210\266\346\243\200\347\264\242\345\206\205\345\256\271:", 0, QApplication::UnicodeUTF8));
        enter_checkbox->setText(QApplication::translate("AbstractSearchForm", "\345\205\245\344\276\265", 0, QApplication::UnicodeUTF8));
        checkBox_5->setText(QApplication::translate("AbstractSearchForm", "\351\200\206\350\241\214", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AbstractSearchForm: public Ui_AbstractSearchForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABSTRACTSEARCHFORM_H
