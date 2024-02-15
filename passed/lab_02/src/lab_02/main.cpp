#include <iostream>
#include "algo.h"
#include "time.h"
#include "io_matrix.h"

using namespace std;

#define MSG "\n\t����\n\n"\
		"1. ������������ ��������\n"\
		"2. �������� ��������� \n"\
		"3. ���������������� �������� ���������\n"\
		"4. �������� ���������\n"\
		"5. ������ ������� \n"\
		"0. ����� \n\n"\
		"�����: "\

int input_cmd() {
	cout << MSG;

	int cmd = -1;
	cin >> cmd;

	if (cmd < 0 || cmd > 5) {
		cout << "������! ������������ ����� �������." << endl;
		return -1;
	}

	return cmd;
}

int test() {
	// ������� � ��������� ������� mA � mB ���������� ����������
	vector<vector<double>> mA = { {1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0} };
	vector<vector<double>> mB = { {9.0, 8.0, 7.0}, {6.0, 5.0, 4.0}, {3.0, 2.0, 1.0} };
	vector<vector<double>> mC;

	// ������� ��������� ������ MatrixSolver
	MatrixSolver solver(mA, mB);

	// ��������� ������������ ��������
	mC = solver.classic_algo();
	cout << "Classic Algorithm Result:" << endl;
	print_matrice(mC);

	// ��������� �������� ���������
	mC = solver.winograd_algo(0);
	cout << "Winograd Algorithm (Non-Optimized) Result:" << endl;
	print_matrice(mC);

	mC = solver.winograd_algo(1);
	cout << "Winograd Algorithm (Optimized) Result:" << endl;
	print_matrice(mC);

	// ��������� �������� ���������
	solver.n = solver.mA.size();
	solver.q = solver.mA[0].size();
	solver.increase_matrices_to_power_of_two();
	solver.strassen_algo(solver.mA, solver.mB);
	solver.crop();
	cout << "Strassen Algorithm Result:" << endl;
	print_matrice(mC);

	return 0;
}

int main() {
	//test();

	setlocale(LC_ALL, "rus");
	int cmd = -1;

	vector<vector<double>> mA, mB, mC;
	MatrixSolver solver(mA, mB);

	while (cmd != 0) {
		cmd = input_cmd();

		if (cmd != 5 && cmd) {
			input_matrices(solver.mA, solver.mB);
			print_matrices(solver.mA, solver.mB);
		}

		switch (cmd) {
			case 1:
				mC = solver.classic_algo();
				break;
			case 2:
				mC = solver.winograd_algo(0);
				break;
			case 3:
				mC = solver.winograd_algo(1);
				break;
			case 4:
				solver.n = solver.mA.size();
				solver.q = solver.mA[0].size();
				solver.increase_matrices_to_power_of_two();
				solver.strassen_algo(solver.mA, solver.mB);
				solver.crop();
				mC = solver.mC;
				break;
			case 5:
				compare_time();
				break;
		}

		if (cmd != 5 && cmd) {
			print_matrice(mC);
		}
	}
}