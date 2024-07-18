#pragma once
#include <windows.h>
#include <conio.h>
#include "hashtable.h"

struct Vertex {
    bool color = true;
    direction_code* code;
    HASHTABLE* table;
    Vertex* parent = nullptr;
    Vertex* left_son = nullptr;
    Vertex* right_son = nullptr;
};

class TREE {
private:
    int size_of_table = 2;
    Vertex NIL = { false,nullptr,nullptr,nullptr,nullptr };
    Vertex* root = &NIL;

    //bool check(std::string key);
    int compare(direction_code value_in_tree, direction_code new_value);
    void left_rotate(Vertex* par_vertex);
    void right_rotate(Vertex* par_vertex);
    Vertex* tree_max(Vertex* ver);
    void insert_fixup(Vertex* added_node);
    void delete_ver(direction_code key);
    void delete_fixup(Vertex* instal_ver);

public:
    void clear_memory_tree(Vertex*& root);
    void find_element_in_tree(Vertex* root, direction_code code, date date);
    void delete_human(human human);
    void insert(human key);

};
