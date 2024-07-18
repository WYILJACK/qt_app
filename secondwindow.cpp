#include "secondwindow.h"
#include "ui_secondwindow.h"
#include <QMessageBox>

secondwindow::secondwindow(QWidget *parent, int size, std::string link)
    : QDialog(parent)
    , ui(new Ui::secondwindow)
{
    ui->setupUi(this);
    tree = new TREE(size, link);
    output_data();

}

secondwindow::~secondwindow()
{
    delete ui;
}

void secondwindow::output_data(){
    ui->tableWidget->removeColumn(0);
    ui->tableWidget->removeColumn(0);
    ui->tableWidget->removeColumn(0);
    ui->tableWidget->removeColumn(0);
    int rows = ui->tableWidget->rowCount();
    for(int i = 0;i<rows;i++){
        ui->tableWidget->removeRow(0);
    }

    ui->tableWidget->setColumnCount(4);
    // ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Код напраления" << "Название дисциплины" << "ФИО преподавателя"<< "Дата");

    if (tree->check_root()){
        std::vector<human> all_info;
        tree->all_info(all_info);
        for(auto hum = all_info.begin();hum!=all_info.end();hum++){
            ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem((std::to_string((*hum).code.first_num)+"."+std::to_string((*hum).code.second_num)+"."+std::to_string((*hum).code.third_num)).data()));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem((*hum).name_of_the_discipline.data()));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, new QTableWidgetItem((*hum).fullname.data()));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3, new QTableWidgetItem((std::to_string((*hum).date.day)+"."+std::to_string((*hum).date.month)+"."+std::to_string((*hum).date.year)).c_str()));
        }
    }
}

void secondwindow::on_add_button_clicked()
{
    QString code = ui->code->text();
    QString discipline = ui->discipline->text();
    QString fullname = ui->fullname->text();
    QString date = ui->date->text();

    if((tree->check_num(code.toStdString()) && code.toStdString().length() == 8 ) && tree->check_name(discipline.toStdString()) && tree->check_name(fullname.toStdString()) &&( tree->check_num(date.toStdString()) && date.toStdString().length() == 10 )){
        human human;
        tree->parse(code.toStdString()+';'+discipline.toStdString()+';'+fullname.toStdString()+';'+date.toStdString()+';',human);
        tree->insert(human);
    }
    else{QMessageBox::warning(this, "Ошибка", "Некорректные значения");}

    output_data();
}


void secondwindow::on_delete_button_clicked()
{
    QString code = ui->code->text();
    QString discipline = ui->discipline->text();
    QString fullname = ui->fullname->text();
    QString date = ui->date->text();

    if((tree->check_num(code.toStdString()) && code.toStdString().length() == 8 ) && tree->check_name(discipline.toStdString()) && tree->check_name(fullname.toStdString()) &&( tree->check_num(date.toStdString()) && date.toStdString().length() == 10 )){
        human human;
        tree->parse(code.toStdString()+';'+discipline.toStdString()+';'+fullname.toStdString()+';'+date.toStdString()+';',human);
        tree->delete_human(human);
    }
    else{QMessageBox::warning(this, "Ошибка", "Некорректные значения");}

    output_data();
}


void secondwindow::on_search_button_clicked()
{
    QString code = ui->code->text();
    QString date = ui->date->text();

    if((tree->check_num(code.toStdString()) && code.toStdString().length() == 8 ) && ( tree->check_num(date.toStdString()) && date.toStdString().length() == 10 )){
        human human;
        search inf;
        tree->parse(code.toStdString()+';'+"олег"+';'+"олег"+';'+date.toStdString()+';',human);
        inf = tree->find_element_in_tree(human.code,human.date);
        if(inf.steps == -1){QMessageBox::information(this,"Поиск неудачен","Не найден(");}
        else{QMessageBox::information(this,"Поиск удачен",( code.toStdString() + '\n' + inf.human->name_of_the_discipline + '\n' + inf.human->fullname +'\n'+date.toStdString()+'\n'+"Количество шагов " + std::to_string(inf.steps)).data());}
    }
    else{QMessageBox::warning(this, "Ошибка", "Некорректные значения");}


    output_data();
}


void secondwindow::on_debugging_button_clicked()
{
    debug = new debugger(tree,this);
    debug->show();
}


void secondwindow::on_pushButton_clicked()
{
    dialog = new file_dialog(tree,this);
    dialog->show();
}

