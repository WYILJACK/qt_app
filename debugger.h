#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <QDialog>
#include "C:\Users\User\source\repos\KURSACH\tree.h"

namespace Ui {
class debugger;
}

class debugger : public QDialog
{
    Q_OBJECT

public:
    explicit debugger(TREE*& root, QWidget *parent = nullptr);
    ~debugger();
    void output_hash_data(Vertex* root);
    void output_tree(Vertex* root, int col);
    void table_design(Vertex* root);
    void tree_design();
    int max_col_tree(Vertex* root, int col);

private slots:
    void on_pushButton_clicked();

    void on_cancel_clicked();

private:
    Ui::debugger *ui;
    TREE* tree = new TREE(0,"");
};

#endif // DEBUGGER_H
