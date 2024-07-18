#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <sys/stat.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    struct stat sb;
    QString size = ui->hashtable_size->text();
    QString link = ui->link->text();
    bool flag;
    int int_size = size.split(" ")[0].toInt(&flag);
    if ((flag && int_size > 0) && (link == "" || (stat(link.toStdString().c_str(), &sb) == 0 && link.toStdString().substr(link.size()-3) == "txt"))){
        hide();
        window = new secondwindow(this, int_size, link.toStdString());
        window->show();
    }
    else{
        QMessageBox::warning(this, "Ошибка", "Значение размера задано не верно или неверно указан файл или его формат");
    }
}

