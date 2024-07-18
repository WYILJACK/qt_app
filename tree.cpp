#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <string>
#include "hashtable.h"
#include "tree.h"

    int TREE::compare(direction_code value_in_tree, direction_code new_value) {
        if (value_in_tree.first_num < new_value.first_num) {
            return -1;
        }
        else if (value_in_tree.first_num > new_value.first_num) {
            return 1;
        }
        else {
            if (value_in_tree.second_num < new_value.second_num) {
                return -1;
            }
            else if (value_in_tree.second_num > new_value.second_num) {
                return 1;
            }
            else {
                if (value_in_tree.third_num < new_value.third_num) {
                    return -1;
                }
                else if (value_in_tree.third_num > new_value.third_num) {
                    return 1;
                }
                return 0;
            }
        }
    }

    void TREE::left_rotate(Vertex* par_vertex) {
        Vertex* cur_vertex = par_vertex->right_son;
        par_vertex->right_son = cur_vertex->left_son;

        if (cur_vertex->left_son != &NIL) {
            cur_vertex->left_son->parent = par_vertex;
        }
        cur_vertex->parent = par_vertex->parent;
        if (par_vertex->parent == &NIL) {
            root = cur_vertex;
        }
        else if (par_vertex == par_vertex->parent->left_son) {
            par_vertex->parent->left_son = cur_vertex;
        }
        else {
            par_vertex->parent->right_son = cur_vertex;
        }
        cur_vertex->left_son = par_vertex;
        par_vertex->parent = cur_vertex;
    }

    void TREE::right_rotate(Vertex* par_vertex) {
        Vertex* cur_vertex = par_vertex->left_son;
        par_vertex->left_son = cur_vertex->right_son;

        if (cur_vertex->right_son != &NIL) {
            cur_vertex->right_son->parent = par_vertex;
        }
        cur_vertex->parent = par_vertex->parent;
        if (par_vertex->parent == &NIL) {
            root = cur_vertex;
        }
        else if (par_vertex == par_vertex->parent->left_son) {
            par_vertex->parent->left_son = cur_vertex;
        }
        else {
            par_vertex->parent->right_son = cur_vertex;
        }
        cur_vertex->right_son = par_vertex;
        par_vertex->parent = cur_vertex;
    }

    Vertex* TREE::tree_max(Vertex* ver) {
        while (ver->right_son != &NIL) {
            ver = ver->right_son;
        }
        return ver;
    }

    void TREE::insert_fixup(Vertex* added_node) {
        Vertex* uncle_node;
        while (added_node->parent->color == true) {
            if (added_node->parent == added_node->parent->parent->left_son) {
                uncle_node = added_node->parent->parent->right_son;
                if (uncle_node->color) {
                    added_node->parent->color = false;
                    uncle_node->color = false;
                    added_node->parent->parent->color = true;
                    added_node = added_node->parent->parent;
                }
                else {
                    if (added_node == added_node->parent->right_son) {
                        added_node = added_node->parent;
                        left_rotate(added_node);
                    }
                    added_node->parent->color = false;
                    added_node->parent->parent->color = true;
                    right_rotate(added_node->parent->parent);
                }
            }
            else {
                uncle_node = added_node->parent->parent->left_son;
                if (uncle_node->color) {
                    added_node->parent->color = false;
                    uncle_node->color = false;
                    added_node->parent->parent->color = true;
                    added_node = added_node->parent->parent;
                }
                else {
                    if (added_node == added_node->parent->left_son) {
                        added_node = added_node->parent;
                        right_rotate(added_node);
                    }
                    added_node->parent->color = false;
                    added_node->parent->parent->color = true;
                    left_rotate(added_node->parent->parent);
                }
            }
        }
        root->color = false;
    }

    void TREE::delete_ver(direction_code key) {
        Vertex* cur_ver = root;
        int res = compare(*(cur_ver->code), key);

        while (cur_ver != &NIL && res != 0) {
            res = compare(*(cur_ver->code), key);
            if (res == 1) {
                cur_ver = cur_ver->left_son;
            }
            else if (res == -1) {
                cur_ver = cur_ver->right_son;
            }
        }

        if (cur_ver != &NIL) {
            Vertex* del_ver = cur_ver;
            bool del_ver_color = true;

            if (del_ver->right_son == &NIL && del_ver->left_son != &NIL) {
                del_ver_color = del_ver->color;
                if (del_ver->parent != &NIL) {
                    if (del_ver->parent->right_son == del_ver) {
                        del_ver->parent->right_son = del_ver->left_son;
                    }
                    else {
                        del_ver->parent->left_son = del_ver->left_son;
                    }
                }
                del_ver->left_son->parent = del_ver->parent;
            }
            else if (del_ver->left_son == &NIL && del_ver->right_son != &NIL) {
                del_ver_color = del_ver->color;
                if (del_ver->parent != &NIL) {
                    if (del_ver->parent->right_son == del_ver) {
                        del_ver->parent->right_son = del_ver->right_son;
                    }
                    else {
                        del_ver->parent->left_son = del_ver->right_son;
                    }
                }
                del_ver->right_son->parent = del_ver->parent;
            }
            else if (del_ver->left_son == &NIL && del_ver->right_son == &NIL) {
                del_ver_color = del_ver->color;
                if (del_ver->parent->left_son == del_ver) {
                    del_ver->parent->left_son = &NIL;
                }
                else {
                    del_ver->parent->right_son = &NIL;
                }
            }
            else {
                del_ver = tree_max(del_ver->left_son);

                std::swap(cur_ver->table, del_ver->table);
                direction_code* trans_code = del_ver->code;

                delete_ver(*(del_ver->code));
                cur_ver->code = trans_code;

                return;
            }
            if (!del_ver_color) {
                delete_fixup(del_ver);
            }
            cur_ver = del_ver;

            if (del_ver->parent != &NIL) {
                while (cur_ver->parent != &NIL) {
                    cur_ver = cur_ver->parent;
                }
                root = cur_ver;
            }
            else if (del_ver->parent == &NIL && del_ver->right_son == &NIL && del_ver->left_son == &NIL) {
                root = &NIL;
            }
            else {
                if (del_ver->left_son != &NIL) {
                    cur_ver = del_ver->left_son;
                }
                else {
                    cur_ver = del_ver->right_son;
                }
                while (cur_ver->parent != &NIL) {
                    cur_ver = cur_ver->parent;
                }
                root = cur_ver;
            }

            del_ver->code = nullptr;
            del_ver->table->~HASHTABLE();
            del_ver->parent = nullptr;
            delete del_ver;
        }
    }

    void TREE::delete_fixup(Vertex* instal_ver) {
        Vertex* cur_ver = instal_ver;

        if (instal_ver->left_son->color) {
            instal_ver->left_son->color = false;
            return;
        }
        else if (instal_ver->right_son->color) {
            instal_ver->right_son->color = false;
            return;
        }
        while (cur_ver != root && !cur_ver->color) {
            if (cur_ver->parent->right_son->color) {
                cur_ver->parent->color = true;
                cur_ver->parent->right_son->color = false;
                left_rotate(cur_ver->parent);
            }
            else if (cur_ver->parent->left_son->color) {
                cur_ver->parent->color = true;
                cur_ver->parent->left_son->color = false;
                right_rotate(cur_ver->parent);
            }
            else if ((cur_ver->parent->left_son != &NIL && !cur_ver->parent->left_son->left_son->color && !cur_ver->parent->left_son->right_son->color) || (cur_ver->parent->right_son == &NIL && cur_ver->parent->left_son == &NIL)) {
                if (cur_ver->parent->left_son != &NIL) {
                    cur_ver->parent->left_son->color = true;
                    if (cur_ver->parent->color) {
                        cur_ver->parent->color = false;
                        cur_ver = root;
                    }
                    else {
                        cur_ver = cur_ver->parent;
                    }
                }
                else {
                    cur_ver->parent->color = false;
                }
            }
            else if ((cur_ver->parent->right_son != &NIL && !cur_ver->parent->right_son->left_son->color && !cur_ver->parent->right_son->right_son->color) || (cur_ver->parent->right_son == &NIL && cur_ver->parent->left_son == &NIL)) {
                if (cur_ver->parent->right_son != &NIL) {
                    cur_ver->parent->right_son->color = true;
                    if (cur_ver->parent->color) {
                        cur_ver->parent->color = false;
                        cur_ver = root;
                    }
                    else {
                        cur_ver = cur_ver->parent;
                    }
                }
                else {
                    cur_ver->parent->color = false;
                }
            }
            else {
                if (cur_ver->parent->left_son == &NIL && !cur_ver->parent->right_son->right_son->color) {

                    cur_ver->parent->right_son->color = !cur_ver->parent->right_son->color;
                    cur_ver->parent->right_son->left_son->color = !cur_ver->parent->right_son->left_son->color;
                    right_rotate(cur_ver->parent->right_son);

                }
                else if (cur_ver->parent->right_son == &NIL && !cur_ver->parent->left_son->left_son->color) {

                    cur_ver->parent->left_son->color = !cur_ver->parent->left_son->color;
                    cur_ver->parent->left_son->right_son->color = !cur_ver->parent->left_son->right_son->color;
                    left_rotate(cur_ver->parent->left_son);
                }

                if (cur_ver->parent->left_son == &NIL || cur_ver->parent->left_son == cur_ver) {
                    cur_ver->parent->right_son->color = cur_ver->parent->color;
                    cur_ver->parent->right_son->right_son->color = !cur_ver->parent->right_son->right_son->color;
                    cur_ver->parent->color = cur_ver->parent->right_son->right_son->color;
                    left_rotate(cur_ver->parent);
                }
                else if (cur_ver->parent->right_son == &NIL || cur_ver->parent->right_son == cur_ver) {
                    cur_ver->parent->left_son->color = cur_ver->parent->color;
                    cur_ver->parent->left_son->left_son->color = !cur_ver->parent->left_son->left_son->color;
                    cur_ver->parent->color = cur_ver->parent->left_son->left_son->color;
                    right_rotate(cur_ver->parent);
                }
                cur_ver = root;
            }
        }

    }

    void TREE::fill_tree(std::string link) {
        std::ifstream file_in(link);
        std::string info = "";
        human human;

        if (file_in.is_open()) {
            while (!file_in.eof()) {
                getline(file_in, info);
                if (parse(info, human)) {
                    insert(human);
                }
                else {
                    //������ ���������� � �����-�� ������;
                }
            }
        }
        file_in.close();
    }

    bool TREE::check_num(std::string num){
        int count = 0;

            for (auto sym = num.begin(); sym != num.end(); sym++) {
                if (count != 2 && count != 5) {
                    if (int(*sym) < 48 || int(*sym) > 57) {
                        return false;
                    }
                }
                else {
                    if (*sym != '.') { return false; }
                }
                count++;
            }

        return true;
    }

    bool TREE::check_name(std::string name) {
        if (name != "") {
            for (auto sym = name.begin(); sym != name.end(); sym++) {
                int a = int(*sym);
                if ((a < 0 )|| *sym == ' ') {
                }else{return false;}
            }
        }
        else { return false; }

        return true;
    }

    bool TREE::parse(std::string info, human& human) {
        std::string buffer = "";
        short marker = 0;

        for (auto sym = info.begin(); sym != info.end(); sym++) {
            if (*sym == ';') {
                switch (marker) {
                case 0:
                    if (check_num(buffer) && buffer.length() == 8) {
                        human.code.first_num = std::stoi(buffer.substr(0,2));
                        human.code.second_num = std::stoi(buffer.substr(3, 2));
                        human.code.third_num = std::stoi(buffer.substr(6, 2));
                    }
                    else { return false; }
                    break;

                case 1:
                    if (check_name(buffer)) {
                        human.name_of_the_discipline = buffer;
                    }
                    else {
                        return false;
                    }

                    break;

                case 2:
                    if (check_name(buffer)) {
                        human.fullname = buffer;
                    }
                    else {
                        return false;
                    }
                    break;

                case 3:
                    if (check_num(buffer) && buffer.length() == 10) {
                        human.date.day = std::stoi(buffer.substr(0,2));
                        human.date.month = std::stoi(buffer.substr(3, 2));
                        human.date.year = std::stoi(buffer.substr(6, 4));
                    }
                    else {
                        return false;
                    }
                    break;
                }
                buffer = "";
                marker++;
            }
            else {
                buffer += *sym;
            }
        }
    }

    TREE::TREE(int start_table_size, std::string link) {
        size = start_table_size;
        this->link = link;
        if (link != "") {
            fill_tree(link);
        }
    }

    bool TREE::check_root(){
        if (root == &NIL){
            return false;
        }else{return true;}
    }

    void TREE::clear_memory_tree(Vertex*& root) {
        if (root != &NIL) {
            clear_memory_tree(root->left_son);
            clear_memory_tree(root->right_son);
            delete root;
            root = &NIL;
        }
    }

    search TREE::find_element_in_tree(direction_code code, date date) {
        Vertex* cur_ver = root;
        search hum;
        int steps = 1;
        while (cur_ver != &NIL) {
            int res = compare(*(cur_ver->code), code);
            if (res == 1) {
                cur_ver = cur_ver->left_son;
            }
            else if (res == -1) {
                cur_ver = cur_ver->right_son;
            }
            else {
                hum = cur_ver->table->search_element(date);
                if (hum.steps != -1){
                hum.steps +=steps;
                }
                return hum;
            }
            steps++;
        }
        hum.steps = -1;
        hum.human = nullptr;
        return hum;
    }


    void TREE::delete_human(human human) {
        Vertex* cur_ver = root;
        int res = compare(*(cur_ver->code), human.code);

        while (cur_ver != &NIL && res != 0) {
            res = compare(*(cur_ver->code), human.code);
            if (res == 1) {
                cur_ver = cur_ver->left_son;
            }
            else if (res == -1) {
                cur_ver = cur_ver->right_son;
            }
        }
        if (cur_ver == &NIL) {
            std::cout << "������ �������� �� ���� � ������" << std::endl;
        }
        else {
            cur_ver->table->delete_element(human.date, human.code, human.fullname, human.name_of_the_discipline);
            if (cur_ver->table->cells() == 0) {
                delete_ver(human.code);
            }
        }

    }


    void TREE::insert(human key) {
        Vertex* pre_ver = &NIL;
        Vertex* cur_ver = root;
        while (cur_ver != &NIL) {
            pre_ver = cur_ver;
            int res = compare(*(cur_ver->code), key.code);
            if (res == 1) {
                cur_ver = cur_ver->left_son;
            }
            else if (res == -1) {
                cur_ver = cur_ver->right_son;
            }
            else {
                if (cur_ver->table == nullptr) {
                    cur_ver->table = new HASHTABLE(size);
                }
                cur_ver->table->add_element(key.date, key.code, key.fullname, key.name_of_the_discipline);
                return;
            }
        }
        if (pre_ver == &NIL) {
            root = new Vertex;
            root->color = false;
            root->code = new direction_code;
            *(root->code) = key.code;
            root->parent = &NIL;
            root->left_son = &NIL;
            root->right_son = &NIL;
            root->table = new HASHTABLE(size);
            root->table->add_element(key.date, key.code, key.fullname, key.name_of_the_discipline);
        }
        else {
            int res = compare(*(pre_ver->code), key.code);
            if (res == 1) {
                pre_ver->left_son = new Vertex;
                pre_ver->left_son->table = new HASHTABLE(size);
                pre_ver->left_son->code = new direction_code;
                *(pre_ver->left_son->code) = key.code;
                pre_ver->left_son->color = true;
                pre_ver->left_son->parent = pre_ver;
                pre_ver->left_son->left_son = &NIL;
                pre_ver->left_son->right_son = &NIL;
                pre_ver->left_son->table->add_element(key.date, key.code, key.fullname, key.name_of_the_discipline);
                insert_fixup(pre_ver->left_son);
            }
            else if (res == -1) {
                pre_ver->right_son = new Vertex;
                pre_ver->right_son->table = new HASHTABLE(size);
                pre_ver->right_son->code = new direction_code;
                *(pre_ver->right_son->code) = key.code;
                pre_ver->right_son->color = true;
                pre_ver->right_son->parent = pre_ver;
                pre_ver->right_son->left_son = &NIL;
                pre_ver->right_son->right_son = &NIL;
                pre_ver->right_son->table->add_element(key.date, key.code, key.fullname, key.name_of_the_discipline);
                insert_fixup(pre_ver->right_son);
            }
        }
    }

    void TREE::all_people(Vertex* root,std::vector<human>& humans){
        if (root != &NIL) {
            if (root->table != nullptr && root->table->cells() != 0) {
                root->table->all_humans(humans);
            }
            all_people(root->left_son,humans);
            all_people(root->right_son,humans);
        }

    }

    void TREE::all_info(std::vector<human>& humans){
        all_people(root,humans);
    }

