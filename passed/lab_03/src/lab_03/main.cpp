#include <iostream>
#include "algo.h"
#include "time.h"
#include "io_array.h"

using namespace std;

#define MSG "\n\tМеню\n\n"\
		"1. Сортировная выбором\n"\
		"2. Сортировка перемешиванием \n"\
		"3. Замеры времени \n"\
		"0. Выход \n\n"\
		"Выбор: "\

int input_cmd() {
	cout << MSG;

	int cmd = -1;
	cin >> cmd;

	if (cmd < 0 || cmd > 3) {
		cout << "Ошибка! Неправильный номер команды." << endl;
		return -1;
	}

	return cmd;
}

int main() {
	//test();

	setlocale(LC_ALL, "rus");
	int cmd = -1;
	std::vector<int> array;

	while (cmd != 0) {
		cmd = input_cmd();

		if (cmd != 3 && cmd)
			array = fill_array();

		switch (cmd) {
			case 1:
				selection_sort(array);
				break;
			case 2:
				shaker_sort(array);
				break;
			case 3:
				compare_time();
				break;
		}

		if (cmd != 3 && cmd) {
			print_array(array);
		}
	}
}