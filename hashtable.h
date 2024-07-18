#pragma once
#include <string>
struct direction_code {
    int first_num = NULL;
    int second_num = NULL;
    int third_num = NULL;

    direction_code& operator=(const direction_code& right) {
        if (this != &right) {
            first_num = right.first_num;
            second_num = right.second_num;
            third_num = right.third_num;
        }
        return *this;
    }
};
struct date {
    int day = NULL;
    int month = NULL;
    int year = NULL;

    date& operator=(const date& right) {
        if (this != &right) {
            day = right.day;
            month = right.month;
            year = right.year;
        }
        return *this;
    }
};
struct human {
    std::string fullname = "";
    std::string name_of_the_discipline = "";
    date date;
    direction_code code;
};
struct CELL {
    human human;
    int status = 0;
};

bool operator==(const date& a1, const date& a2)
{
    if ((a1.day == a2.day) && (a1.month == a2.month) && (a1.year == a2.year)) { return true; }
    else { return false; }
}
bool operator==(const direction_code& a1, const direction_code& a2)
{
    if ((a1.first_num == a2.first_num) && (a1.second_num == a2.second_num) && (a1.third_num == a2.third_num)) { return true; }
    else { return false; }
}


class HASHTABLE {
private:
    CELL* table = nullptr;
    int size_of_table = 0;
    int count_of_cells = 0;
    double fill_factor = 0;

    int key_conversion(date date);
    int first_hash_function(int key);
    int second_hash_function(int key);
    int calculation_hash(int key, int attempt);
    int solve_add_collision(int key, int attempt);
    void solve_search_collision(int key, int attempt);
    void solve_delete_collision(int key, int attempt, date date, direction_code code, std::string fullname, std::string name_of_the_discipline);
    void rehash(int cur_table_size, int new_table_size);

public:
    HASHTABLE(int start_size);
    void add_element(date date, direction_code code, std::string fullname, std::string name_of_the_discipline);
    void search_element(date date);
    void delete_element(date date, direction_code code, std::string fullname, std::string name_of_the_discipline);
    int cells();
    ~HASHTABLE();
};

//dfe
