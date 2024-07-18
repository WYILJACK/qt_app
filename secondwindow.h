#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QDialog>
#include "C:\Users\User\source\repos\KURSACH\tree.h"
#include "debugger.h";
#include "file_dialog.h"

namespace Ui {
class secondwindow;
}

class secondwindow : public QDialog
{
    Q_OBJECT

public:
    explicit secondwindow(QWidget *parent = nullptr, int size = 2, std::string link = "");
    ~secondwindow();
    void output_data();

private slots:

    void on_add_button_clicked();

    void on_delete_button_clicked();

    void on_pushButton_clicked();

    void on_search_button_clicked();

    void on_debugging_button_clicked();

private:
    Ui::secondwindow *ui;
    TREE* tree;
    debugger *debug;
    file_dialog* dialog;

};

#endif // SECONDWINDOW_H
