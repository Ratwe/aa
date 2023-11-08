#include "io_matrix.h"
#include <iostream>

void input_matrices(vector<vector<double>>& mA, vector<vector<double>>& mB) {

    int rowA, colA, colB;

    cout << "Введите:" << endl;

    cout << "Кол-во строк первой матрицы А: ";
    cin >> rowA;
    cout << "Кол-во столбцов первой матрицы А: ";
    cin >> colA;
    cout << "Кол-во столбцов второй матрицы Б: ";
    cin >> colB;

    // Инициализируем размеры матриц mA и mB
    mA.resize(rowA, vector<double>(colA));
    mB.resize(colA, vector<double>(colB));

    // Заполняем матрицу A
    cout << "Введите элементы матрицы A:" << endl;
    for (int i = 0; i < rowA; i++) {
        for (int j = 0; j < colA; j++) {
            cin >> mA[i][j];
        }
    }

    // Заполняем матрицу B
    cout << "Введите элементы матрицы B:" << endl;
    for (int i = 0; i < colA; i++) {
        for (int j = 0; j < colB; j++) {
            cin >> mB[i][j];
        }
    }
}

void print_matrices(const vector<vector<double>>&mA, const vector<vector<double>>&mB) {
    cout << "Матрица A:" << endl;
    for (const auto& row : mA) {
        for (double element : row) {
            cout << element << " ";
        }
        cout << endl;
    }

    cout << "Матрица B:" << endl;
    for (const auto& row : mB) {
        for (double element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
}

void print_matrice(const vector<vector<double>>& mC) {
    cout << "Матрица C:" << endl;
    for (const auto& row : mC) {
        for (double element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
}