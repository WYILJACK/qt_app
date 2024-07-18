#include "file_dialog.h"
#include "ui_file_dialog.h"
#include <QMessageBox>
#include <sys/stat.h>
#include <fstream>

file_dialog::file_dialog(TREE*& tree, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::file_dialog)
{
    ui->setupUi(this);
    this->tree = tree;
}

file_dialog::~file_dialog()
{
    delete ui;
}


void file_dialog::on_save_clicked()
{
    struct stat sb;
    QString link = ui->link->text();
    bool flag;
    if (((stat(link.toStdString().c_str(), &sb) == 0 && link.toStdString().substr(link.size()-3) == "txt"))){
        save_data(link.toStdString());
    }
    else{
        QMessageBox::warning(this, "Ошибка", "Неверно указанный файл");
    }
}

void file_dialog::save_data(std::string link){
    std::ofstream file(link);
    if (file.is_open()){
        std::vector<human> all_info;
        tree->all_info(all_info);

        for(auto hum = all_info.begin();hum!=all_info.end();hum++){
            if((*hum).code.first_num % 10 == 0){file << "0"+std::to_string((*hum).code.first_num);}
            else{file<<(*hum).code.first_num;}

            if((*hum).code.second_num % 10 == 0){file << ".0"+std::to_string((*hum).code.second_num)<<".";}
            else{file<<"." + std::to_string((*hum).code.second_num) + ".";}

            if((*hum).code.third_num % 10 == 0){file << "0"+std::to_string((*hum).code.third_num);}
            else{file<<(*hum).code.third_num;}

            file <<";";

            file << (*hum).name_of_the_discipline<<";";
            file << (*hum).fullname<<";";

            if ((*hum).date.day % 10 == 0){file << "0"+std::to_string((*hum).date.day);}
            else{file <<(*hum).date.day;}

            if ((*hum).date.month % 10 == 0){file << "0"+std::to_string((*hum).date.month);}
            else{file <<(*hum).date.month;}

            file<<(*hum).date.year;
            file<< ";";
            file << std::endl;
        }
    }

    this->close();
}

void file_dialog::on_cancel_clicked()
{
        this->close();
}

