/********************************************************************************
** Form generated from reading ui file 'second.ui'
**
** Created: Mon Sep 5 14:47:55 2011
**      by: Qt User Interface Compiler version 4.5.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SECOND_H
#define UI_SECOND_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Second
{
public:
    QLabel *label;
    QPushButton *closePushButton;

    void setupUi(QWidget *Second)
    {
        if (Second->objectName().isEmpty())
            Second->setObjectName(QString::fromUtf8("Second"));
        Second->resize(300, 300);
        label = new QLabel(Second);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 80, 131, 16));
        closePushButton = new QPushButton(Second);
        closePushButton->setObjectName(QString::fromUtf8("closePushButton"));
        closePushButton->setGeometry(QRect(180, 240, 75, 23));

        retranslateUi(Second);

        QMetaObject::connectSlotsByName(Second);
    } // setupUi

    void retranslateUi(QWidget *Second)
    {
        Second->setWindowTitle(QApplication::translate("Second", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Second", "\350\277\231\346\230\257\347\254\254\344\272\214\344\270\252 UI !!", 0, QApplication::UnicodeUTF8));
        closePushButton->setText(QApplication::translate("Second", "\345\205\263\351\227\255", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(Second);
    } // retranslateUi

};

namespace Ui {
    class Second: public Ui_Second {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECOND_H
