/********************************************************************************
** Form generated from reading UI file 'file_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILE_DIALOG_H
#define UI_FILE_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_file_dialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *link;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *cancel;
    QPushButton *save;

    void setupUi(QDialog *file_dialog)
    {
        if (file_dialog->objectName().isEmpty())
            file_dialog->setObjectName("file_dialog");
        file_dialog->resize(427, 239);
        layoutWidget = new QWidget(file_dialog);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(20, 50, 361, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        link = new QLineEdit(layoutWidget);
        link->setObjectName("link");

        horizontalLayout->addWidget(link);

        layoutWidget1 = new QWidget(file_dialog);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(190, 180, 195, 31));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        cancel = new QPushButton(layoutWidget1);
        cancel->setObjectName("cancel");

        horizontalLayout_2->addWidget(cancel);

        save = new QPushButton(layoutWidget1);
        save->setObjectName("save");

        horizontalLayout_2->addWidget(save);


        retranslateUi(file_dialog);

        QMetaObject::connectSlotsByName(file_dialog);
    } // setupUi

    void retranslateUi(QDialog *file_dialog)
    {
        file_dialog->setWindowTitle(QCoreApplication::translate("file_dialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("file_dialog", "\320\237\321\203\321\202\321\214 \320\272 \321\204\320\260\320\271\320\273\321\203", nullptr));
        cancel->setText(QCoreApplication::translate("file_dialog", "\320\276\321\202\320\274\320\265\320\275\320\260", nullptr));
        save->setText(QCoreApplication::translate("file_dialog", "\321\201\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class file_dialog: public Ui_file_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILE_DIALOG_H
