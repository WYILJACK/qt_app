#include "debugger.h"
#include "ui_debugger.h"

debugger::debugger(TREE*& root, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::debugger)
{
    ui->setupUi(this);
    this->tree = root;
    table_design(tree->root);
    tree_design();
}

debugger::~debugger()
{
    delete ui;
}

void debugger::table_design(Vertex* root){
    ui->tableWidget->removeColumn(0);
    ui->tableWidget->removeColumn(0);
    ui->tableWidget->removeColumn(0);
    ui->tableWidget->removeColumn(0);
    int rows = ui->tableWidget->rowCount();
    for(int i = 0;i<rows;i++){
        ui->tableWidget->removeRow(0);
    }
    ui->tableWidget->setColumnCount(4);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Статус ячейки" << "Название дисциплины" << "ФИО преподавателя"<< "Дата");


    output_hash_data(root);
}

void debugger::output_hash_data(Vertex* root){
    if(root != &this->tree->NIL){
        this->output_hash_data(root->left_son);
        this->output_hash_data(root->right_son);

        std::vector<CELL> humans = root->table->table_info();

        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setVerticalHeaderItem(ui->tableWidget->rowCount()-1, new QTableWidgetItem((std::to_string(root->code->first_num) + "." + std::to_string(root->code->second_num) + "." + std::to_string(root->code->third_num)).data()));

        for (int i = 0; i < humans.size();i++){
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setVerticalHeaderItem(ui->tableWidget->rowCount()-1,new QTableWidgetItem(i));

            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(QString::number(humans[i].status)));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(humans[i].human.name_of_the_discipline.data()));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, new QTableWidgetItem(humans[i].human.fullname.data()));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3, new QTableWidgetItem((std::to_string((humans[i]).human.date.day)+"."+std::to_string(humans[i].human.date.month)+"."+std::to_string(humans[i].human.date.year)).c_str()));
        }
    }
}

void debugger::output_tree(Vertex* root, int col){
    QTreeWidgetItem *item = new QTreeWidgetItem();
    if (root == &tree->NIL) {
        return;
    }
    if (root->parent->right_son == root) {
        for (int i = 0; i < col; i++) {
            item->setText(i,"");

        }
        item->setText(col,("R| " + std::to_string(root->code->first_num) + "." + std::to_string(root->code->second_num) + "." + std::to_string(root->code->third_num)).data());
    }
    else if (root->parent->left_son == root){
        for (int i = 0; i < col; i++) {
            item->setText(i,"");

        }
        item->setText(col,("L| " + std::to_string(root->code->first_num) + "." + std::to_string(root->code->second_num) + "." + std::to_string(root->code->third_num)).data());
    }
    else{item->setText(col,(std::to_string(root->code->first_num) + "." + std::to_string(root->code->second_num) + "." + std::to_string(root->code->third_num)).data());}
    if (root->color) {
        item->setBackground(col,Qt::red);
    }
    else {
        item->setBackground(col,Qt::black);
    }

    item->setForeground(col, Qt::white);
    ui->treeWidget->addTopLevelItem(item);
    output_tree(root->right_son, col + 1);
    output_tree(root->left_son,col +1 );
}

int debugger::max_col_tree(Vertex* root, int col){
    if (root == &tree->NIL && col == 0) {
        return 0;
    }
    if (root == &tree->NIL) {
        return col;
    }
    return std::max(max_col_tree(root->right_son, col + 1),max_col_tree(root->left_son,col +1 ));
}

void debugger::tree_design(){
    ui->treeWidget->clear();
    ui->treeWidget->setColumnCount(max_col_tree(tree->root,0)+1);
    output_tree(tree->root,0);
}

void debugger::on_pushButton_clicked()
{
    table_design(tree->root);
    tree_design();
}


void debugger::on_cancel_clicked()
{
        this->close();
}

