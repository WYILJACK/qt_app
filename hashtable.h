#pragma once
#include <string>
#include<vector>


struct direction_code {
    int first_num = 0;
	int second_num = 0;
	int third_num = 0;

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
struct search
{
    human* human;
    int steps;

};
struct CELL {
	human human;
	int status = 0;
};

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
    search solve_search_collision(int key, int attempt,int counts);
	void solve_delete_collision(int key, int attempt, date date, direction_code code, std::string fullname, std::string name_of_the_discipline);
	void rehash(int cur_table_size, int new_table_size);

public:
	HASHTABLE(int start_size);
    std::vector<CELL> table_info();
	void add_element(date date, direction_code code, std::string fullname, std::string name_of_the_discipline);
    search search_element(date date);
	void delete_element(date date, direction_code code, std::string fullname, std::string name_of_the_discipline);
	int cells();
    int size();
    void all_humans(std::vector<human>& humans);
	~HASHTABLE();
};

//dfe
