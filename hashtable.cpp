#include <iostream>
#include <string>
#include <windows.h>
#include "hashtable.h"
#include <cmath>
#include "QDebug"

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
	
	int HASHTABLE::key_conversion(date date) {
		return pow(date.day,3) + pow(date.month,2) + date.year;
	}

	int HASHTABLE::first_hash_function(int key) {
		std::string number = std::to_string(key);
		int hash = 0;

		for (auto num = number.begin(); num != number.end(); num++) {
			hash += ((*num) - '0');
		}
		return (hash % size_of_table);
	}

	int HASHTABLE::second_hash_function(int key) {
		return (1 + key % (size_of_table - 1));
	}

	int HASHTABLE::calculation_hash(int key, int attempt) {
		return (first_hash_function(key) + attempt * second_hash_function(key)) % size_of_table;
	}

	int HASHTABLE::solve_add_collision(int key, int attempt) {
		if (attempt == size_of_table) { rehash(size_of_table, size_of_table * 2); attempt = 0; }
		int hash = calculation_hash(key, attempt);

		if (table[hash].status == 0) { return hash; }
		else if (table[hash].status == 1 && key == key_conversion(table[hash].human.date)) { return -1; }
		else {
			if (table[hash].status == 2 && solve_add_collision(key, attempt + 1) != -1) {
				return hash;
			}
			else {
				return solve_add_collision(key, attempt + 1);
			}
		}
	}

    search HASHTABLE::solve_search_collision(int key, int attempt, int counts) {
		int hash = calculation_hash(key, attempt);

        if (table[hash].status == 0) { search hum; hum.human = nullptr; hum.steps = -1; return hum; }
		else if (table[hash].status == 2 || (table[hash].status == 1 && key != key_conversion(table[hash].human.date)))
		{
            return solve_search_collision(key, attempt + 1, counts+1);
		}
        else { search hum; hum.human = &(table[hash].human); hum.steps = counts;return hum;}
	}

	void HASHTABLE::solve_delete_collision(int key, int attempt, date date, direction_code code, std::string fullname, std::string name_of_the_discipline) {
		int hash = calculation_hash(key, attempt);

		if (table[hash].status == 0) { std::cout << "no such element" << std::endl; }
		else if (table[hash].status == 2 || (table[hash].status == 1 && key != key_conversion(table[hash].human.date)))
		{
			solve_delete_collision(key, attempt + 1, date, code, fullname, name_of_the_discipline);
		}
		else {

			if (table[hash].human.date == date && table[hash].human.fullname == fullname && table[hash].human.code == code && table[hash].human.name_of_the_discipline == name_of_the_discipline) {
				table[hash].human.code.first_num = NULL;
				table[hash].human.code.second_num = NULL;
				table[hash].human.code.third_num = NULL;
				table[hash].human.fullname = "";
				table[hash].human.name_of_the_discipline = "";
				table[hash].human.date.day = NULL;
				table[hash].human.date.month = NULL;
				table[hash].human.date.year = NULL;
				table[hash].status = 2;

				count_of_cells -= 1;
				fill_factor = double(count_of_cells) / double(size_of_table);

				if (fill_factor <= 0.4) {
					rehash(size_of_table, size_of_table / 2 + 1);
				}
			}
		}
	}

	void HASHTABLE::rehash(int cur_table_size, int new_table_size) {
		CELL* cur_table = new CELL[new_table_size];
		std::swap(table, cur_table);
		count_of_cells = 0;
		size_of_table = new_table_size;
		fill_factor = double(count_of_cells) / double(size_of_table);

		for (int i = 0; i < cur_table_size; i++) {
			if (cur_table[i].status == 1) {
				add_element(cur_table[i].human.date, cur_table[i].human.code, cur_table[i].human.fullname, cur_table[i].human.name_of_the_discipline);
				cur_table[i].human.code.first_num = NULL;
				cur_table[i].human.code.second_num = NULL;
				cur_table[i].human.code.third_num = NULL;
				cur_table[i].human.fullname = "";
				cur_table[i].human.name_of_the_discipline = "";
				cur_table[i].human.date.day = NULL;
				cur_table[i].human.date.month = NULL;
				cur_table[i].human.date.year = NULL;
				cur_table[i].status = NULL;
			}
			else {
				cur_table[i].status = NULL;
			}
		}

		delete[] cur_table;
		cur_table = nullptr;

	}

	//void parse_to_human(human& new_cell, std::string info, int num_of_line) {
	//	std::string buffer = "";
	//	short marker = 0;

	//	for (auto sym = info.begin(); sym != info.end(); sym++) {
	//		if (*sym == ';') {
	//			switch (marker) {
	//			case 0:
	//				new_cell.fullname = buffer;
	//				break;
	//			case 1:
	//				new_cell.car_info.brand = buffer;
	//				break;

	//			case 2:
	//				new_cell.car_info.model = buffer;
	//				break;

	//			case 3:
	//				new_cell.application_number = stoi(buffer);
	//				break;
	//			}
	//			buffer = "";
	//			marker++;
	//		}
	//		else {
	//			buffer += *sym;
	//		}
	//	}
	//	new_cell.number_of_file_string = num_of_line;
	//}

	HASHTABLE::HASHTABLE(int start_size) {
		if (start_size > 0) {
			table = new CELL[start_size];
			size_of_table = start_size;
		}
		else {
			table = new CELL[4];
			size_of_table = 4;
		}
	}

    std::vector<CELL> HASHTABLE::table_info(){
        std::vector<CELL> humans;
        if (table != nullptr){
            for(int i = 0;i<size_of_table;i++){
                humans.push_back(table[i]);
            }
        }
        return humans;
    }

	void HASHTABLE::add_element(date date, direction_code code, std::string fullname, std::string name_of_the_discipline) {
		int key = key_conversion(date);
		int hash = calculation_hash(key, 0);

		if (table[hash].status == 0) {
			table[hash].human.fullname = fullname;
			table[hash].human.code = code;
			table[hash].human.date = date;
			table[hash].human.name_of_the_discipline = name_of_the_discipline;
			table[hash].status = 1;

			count_of_cells += 1;
			fill_factor = double(count_of_cells) / double(size_of_table);

			if (fill_factor >= 0.7) {
				rehash(size_of_table, size_of_table * 2);
			}
		}
		else if (table[hash].status == 1 && (key_conversion(table[hash].human.date) != key_conversion(date))) {
			int new_hash = solve_add_collision(key, 1);
			if (new_hash != -1) {
				table[new_hash].human.fullname = fullname;
				table[new_hash].human.code = code;
				table[new_hash].human.date = date;
				table[new_hash].human.name_of_the_discipline = name_of_the_discipline;
				table[new_hash].status = 1;
				
				count_of_cells += 1;
				fill_factor = double(count_of_cells) / double(size_of_table);

				if (fill_factor >= 0.8) {
					rehash(size_of_table, size_of_table * 2);
				}
			}
		}

	}

    search HASHTABLE::search_element(date date) {
		int key = key_conversion(date);
		int hash = calculation_hash(key, 0);
        int count = 1;

        if (table[hash].status == 0) { search hum; hum.human = nullptr; hum.steps = -1; return hum; }
		else if (table[hash].status == 2 || (table[hash].status == 1 && key != key_conversion(table[hash].human.date)))
		{
            solve_search_collision(key, 1, count);
		}
        else {search hum; hum.human = &(table[hash].human);hum.steps = count; return hum;}

	}

	void HASHTABLE::delete_element(date date, direction_code code, std::string fullname, std::string name_of_the_discipline) {
		int key = key_conversion(date);
		int hash = calculation_hash(key, 0);

		if (table[hash].status == 0) { std::cout << "no such element"; }
		else if (table[hash].status == 2 || (table[hash].status == 1 && key != key_conversion(table[hash].human.date)))
		{
			solve_delete_collision(key, 1, date, code, fullname, name_of_the_discipline);
		}
		else {
			if (table[hash].human.date == date && table[hash].human.fullname == fullname && table[hash].human.code == code && table[hash].human.name_of_the_discipline == name_of_the_discipline) {
				table[hash].human.code.first_num = NULL;
				table[hash].human.code.second_num = NULL;
				table[hash].human.code.third_num = NULL;
				table[hash].human.fullname = "";
				table[hash].human.name_of_the_discipline = "";
				table[hash].human.date.day = NULL;
				table[hash].human.date.month = NULL;
				table[hash].human.date.year = NULL;
				table[hash].status = 2;

				count_of_cells -= 1;
				fill_factor = double(count_of_cells) / double(size_of_table);

                if (fill_factor <= 0.3) {
					rehash(size_of_table, size_of_table / 2 + 1);
				}
			}
		}

	}

	/*void print() {
		std::cout << std::setiosflags(std::ios::left);
		std::cout << std::setw(7) << "статус";
		std::cout << std::setw(7) << "индекс";
		std::cout << std::setw(20) << "заявка";
		std::cout << std::setw(45) << "ФИО";
		std::cout << std::setw(40) << "МАШИНА";
		std::cout << std::setw(7) << "ПЕРВИЧНЫЙ ХЭШ" << std::endl;
		for (int I = 0; I < size_of_table; I++)
		{
			std::cout << std::setw(7) << table[I].status;
			std::cout << std::setw(7) << I;
			std::cout << std::setw(20) << table[I].human.application_number;
			std::cout << std::setw(45) << table[I].human.fullname;
			std::cout << std::setw(40) << table[I].human.car_info.brand + " " + table[I].human.car_info.model;
			std::cout << std::setw(7) << calculation_hash(key_conversion(table[I].human.fullname, table[I].human.application_number), 0) << std::endl;
		}
		std::cout << std::endl;
	}*/

	//void fill_table(std::string file_name) {
	//	std::ifstream file(file_name);
	//	std::string line = "";
	//	int num = 1;

	//	if (file.is_open()) {
	//		human human;

	//		while (!file.eof()) {
	//			std::getline(file, line);
	//			parse_to_human(human, line, num);
	//			add_element(human.fullname, human.car_info.brand, human.car_info.model, human.application_number, human.number_of_file_string);
	//			num++;
	//			if (human.fullname == "Кузнецова Елена Сергеевна" || human.fullname == "Михайлова Валерия Владимировна") {
	//				print();
	//			}
	//		}
	//		file.close();
	//	}
	//}

	/*void print(std::string way) {
		std::ofstream file(way);

		file << std::setiosflags(std::ios::left);
		file << std::setw(7) << "статус";
		file << std::setw(7) << "индекс";
		file << std::setw(20) << "заявка";
		file << std::setw(45) << "ФИО";
		file << std::setw(40) << "МАШИНА";
		file << std::setw(7) << "ПЕРВИЧНЫЙ ХЭШ" << std::endl;
		for (int I = 0; I < size_of_table; I++)
		{
			file << std::setw(7) << table[I].status;
			file << std::setw(7) << I;
			file << std::setw(20) << table[I].human.application_number;
			file << std::setw(45) << table[I].human.fullname;
			file << std::setw(40) << table[I].human.car_info.brand + " " + table[I].human.car_info.model;
			file << std::setw(7) << calculation_hash(key_conversion(table[I].human.fullname, table[I].human.application_number), 0) << std::endl;
		}
		file << std::endl;
	}*/

	int HASHTABLE::cells() {
		return count_of_cells;
	}

    int HASHTABLE::size(){
        return size_of_table;
    }

    void HASHTABLE::all_humans(std::vector<human>& humans){
        for(int i=0;i<size_of_table;i++){
            if(table[i].status == 1){
                humans.push_back(table[i].human);
            }
        }
    }

	HASHTABLE::~HASHTABLE() {
		delete[] table;
		table = nullptr;
	}
