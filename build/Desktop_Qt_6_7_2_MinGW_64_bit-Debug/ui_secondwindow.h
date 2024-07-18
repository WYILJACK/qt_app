/********************************************************************************
** Form generated from reading UI file 'secondwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SECONDWINDOW_H
#define UI_SECONDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_secondwindow
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout_2;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *code;
    QLineEdit *discipline;
    QLineEdit *fullname;
    QLineEdit *date;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *add_button;
    QPushButton *delete_button;
    QPushButton *search_button;
    QPushButton *debugging_button;
    QPushButton *pushButton;

    void setupUi(QDialog *secondwindow)
    {
        if (secondwindow->objectName().isEmpty())
            secondwindow->setObjectName("secondwindow");
        secondwindow->resize(1043, 662);
        verticalLayout_2 = new QVBoxLayout(secondwindow);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        scrollArea = new QScrollArea(secondwindow);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1017, 522));
        horizontalLayout_2 = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        tableWidget = new QTableWidget(scrollAreaWidgetContents);
        tableWidget->setObjectName("tableWidget");

        horizontalLayout_2->addWidget(tableWidget);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_2 = new QLabel(secondwindow);
        label_2->setObjectName("label_2");

        horizontalLayout_4->addWidget(label_2);

        label_4 = new QLabel(secondwindow);
        label_4->setObjectName("label_4");

        horizontalLayout_4->addWidget(label_4);

        label_3 = new QLabel(secondwindow);
        label_3->setObjectName("label_3");

        horizontalLayout_4->addWidget(label_3);

        label = new QLabel(secondwindow);
        label->setObjectName("label");

        horizontalLayout_4->addWidget(label);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        code = new QLineEdit(secondwindow);
        code->setObjectName("code");

        horizontalLayout_3->addWidget(code);

        discipline = new QLineEdit(secondwindow);
        discipline->setObjectName("discipline");

        horizontalLayout_3->addWidget(discipline);

        fullname = new QLineEdit(secondwindow);
        fullname->setObjectName("fullname");

        horizontalLayout_3->addWidget(fullname);

        date = new QLineEdit(secondwindow);
        date->setObjectName("date");

        horizontalLayout_3->addWidget(date);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(16, 5, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        add_button = new QPushButton(secondwindow);
        add_button->setObjectName("add_button");

        horizontalLayout->addWidget(add_button);

        delete_button = new QPushButton(secondwindow);
        delete_button->setObjectName("delete_button");

        horizontalLayout->addWidget(delete_button);

        search_button = new QPushButton(secondwindow);
        search_button->setObjectName("search_button");

        horizontalLayout->addWidget(search_button);

        debugging_button = new QPushButton(secondwindow);
        debugging_button->setObjectName("debugging_button");

        horizontalLayout->addWidget(debugging_button);

        pushButton = new QPushButton(secondwindow);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(secondwindow);

        QMetaObject::connectSlotsByName(secondwindow);
    } // setupUi

    void retranslateUi(QDialog *secondwindow)
    {
        secondwindow->setWindowTitle(QCoreApplication::translate("secondwindow", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("secondwindow", "\320\272\320\276\320\264 \320\275\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\217", nullptr));
        label_4->setText(QCoreApplication::translate("secondwindow", "\320\264\320\270\321\201\321\206\320\270\320\277\320\273\320\270\320\275\320\260", nullptr));
        label_3->setText(QCoreApplication::translate("secondwindow", "\320\244\320\230\320\236 \320\277\321\200\320\265\320\277\320\276\320\264\320\260\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        label->setText(QCoreApplication::translate("secondwindow", "\320\264\320\260\321\202\320\260", nullptr));
        add_button->setText(QCoreApplication::translate("secondwindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        delete_button->setText(QCoreApplication::translate("secondwindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        search_button->setText(QCoreApplication::translate("secondwindow", "\320\235\320\260\320\271\321\202\320\270", nullptr));
        debugging_button->setText(QCoreApplication::translate("secondwindow", "\320\276\320\272\320\275\320\276 \320\276\321\202\320\273\320\260\320\264\320\272\320\270", nullptr));
        pushButton->setText(QCoreApplication::translate("secondwindow", "\320\222\321\213\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\262 \321\204\320\260\320\271\320\273", nullptr));
    } // retranslateUi

};

namespace Ui {
    class secondwindow: public Ui_secondwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECONDWINDOW_H
