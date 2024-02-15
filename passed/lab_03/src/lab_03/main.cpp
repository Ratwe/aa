#include <iostream>
#include "algo.h"
#include "time.h"
#include "io_array.h"

using namespace std;

#define MSG "\n\t����\n\n"\
		"1. ����������� �������\n"\
		"2. ���������� �������������� \n"\
		"3. ������ ������� \n"\
		"0. ����� \n\n"\
		"�����: "\

int input_cmd() {
	cout << MSG;

	int cmd = -1;
	cin >> cmd;

	if (cmd < 0 || cmd > 3) {
		cout << "������! ������������ ����� �������." << endl;
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