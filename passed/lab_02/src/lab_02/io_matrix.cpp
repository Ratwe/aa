#include "io_matrix.h"
#include <iostream>

void input_matrices(vector<vector<double>>& mA, vector<vector<double>>& mB) {

    int rowA, colA, colB;

    cout << "�������:" << endl;

    cout << "���-�� ����� ������ ������� �: ";
    cin >> rowA;
    cout << "���-�� �������� ������ ������� �: ";
    cin >> colA;
    cout << "���-�� �������� ������ ������� �: ";
    cin >> colB;

    // �������������� ������� ������ mA � mB
    mA.resize(rowA, vector<double>(colA));
    mB.resize(colA, vector<double>(colB));

    // ��������� ������� A
    cout << "������� �������� ������� A:" << endl;
    for (int i = 0; i < rowA; i++) {
        for (int j = 0; j < colA; j++) {
            cin >> mA[i][j];
        }
    }

    // ��������� ������� B
    cout << "������� �������� ������� B:" << endl;
    for (int i = 0; i < colA; i++) {
        for (int j = 0; j < colB; j++) {
            cin >> mB[i][j];
        }
    }
}

void print_matrices(const vector<vector<double>>&mA, const vector<vector<double>>&mB) {
    cout << "������� A:" << endl;
    for (const auto& row : mA) {
        for (double element : row) {
            cout << element << " ";
        }
        cout << endl;
    }

    cout << "������� B:" << endl;
    for (const auto& row : mB) {
        for (double element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
}

void print_matrice(const vector<vector<double>>& mC) {
    cout << "������� C:" << endl;
    for (const auto& row : mC) {
        for (double element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
}