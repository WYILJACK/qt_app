#ifndef FILE_DIALOG_H
#define FILE_DIALOG_H

#include <QDialog>
#include "C:\Users\User\source\repos\KURSACH\tree.h"

namespace Ui {
class file_dialog;
}

class file_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit file_dialog(TREE*& tree, QWidget *parent = nullptr);
    ~file_dialog();
    void save_data(std::string link);

private slots:

    void on_save_clicked();

    void on_cancel_clicked();

private:
    Ui::file_dialog *ui;
    TREE* tree;
};

#endif // FILE_DIALOG_H
