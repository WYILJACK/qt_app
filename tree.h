#pragma once
#include <windows.h>
#include <conio.h>
#include <string>
#include "hashtable.h"
#include <vector>

struct Vertex {
    bool color = true;
    direction_code* code;
    HASHTABLE* table = nullptr;
    Vertex* parent = nullptr;
    Vertex* left_son = nullptr;
    Vertex* right_son = nullptr;
};

class TREE {
private:
    int size = 2;
    std::string link = "";

    int compare(direction_code value_in_tree, direction_code new_value);
    void left_rotate(Vertex* par_vertex);
    void right_rotate(Vertex* par_vertex);
    Vertex* tree_max(Vertex* ver);
    void insert_fixup(Vertex* added_node);
    void delete_ver(direction_code key);
    void delete_fixup(Vertex* instal_ver);
    void fill_tree(std::string link);

public:
    Vertex NIL = {false,nullptr,nullptr,nullptr,nullptr,nullptr };
    Vertex* root = &NIL;

    TREE(int start_table_size, std::string link);
    bool check_num(std::string num);
    bool check_name(std::string name);
    bool parse(std::string info, human& human);
    bool check_root();
    void clear_memory_tree(Vertex*& root);
    search find_element_in_tree(direction_code code, date date);
    void delete_human(human human);
    void insert(human key);
    void all_people(Vertex* root,std::vector<human>& humans);
    void all_info(std::vector<human>& humans);
};
