#include "algo.h"
#include <iostream>
#include <windows.h>

MatrixSolver::MatrixSolver(vector<vector<double>>& mA, vector<vector<double>>& mB) : mA(mA), mB(mB) {
}

void MatrixSolver::set_matrices(vector<vector<double>>& A, vector<vector<double>>& B) {
    mA = A;
    mB = B;
}

void MatrixSolver::increase_matrices_to_power_of_two() {
    int n = mA.size();
    int m = mA[0].size(); // Предполагаем, что матрицы mA и mB имеют одинаковый размер

    // Находим ближайшие степени двойки для строк и столбцов
    int new_size = 1;
    while (new_size < max(n, m)) {
        new_size *= 2;
    }

    // Если размер не является степенью двойки, увеличиваем его до степени двойки
    if (n < new_size || m < new_size) {
        // Увеличиваем количество строк до new_size
        while (n < new_size) {
            vector<double> row(m, 0.0);
            mA.push_back(row);
            mB.push_back(row);
            n++;
        }

        // Увеличиваем количество столбцов до new_size
        for (int i = 0; i < new_size; i++) {
            while (m < new_size) {
                mA[i].push_back(0.0);
                mB[i].push_back(0.0);
                m++;
            }
        }
    }
}


vector<vector<double>> MatrixSolver::winograd_algo(int optimized) {
    int n = mA.size();
    int m = mA[0].size();
    int q = mB[0].size();

    mC.resize(n, vector<double>(q));
    vector<double> row(n, 0);
    vector<double> column(q, 0);

    if (optimized == 1) {
        int half_m = m >> 1;
        // Предварительные вычисления
        for (int i = 0; i < n; i++)
            for (int j = 0; j < half_m; j++)
                row[i] += mA[i][j << 1] * mA[i][(j << 1) + 1];

        for (int i = 0; i < q; i++)
            for (int j = 0; j < half_m; j++)
                column[i] += mB[j << 1][i] * mB[(j << 1) + 1][i];

        // Умножение матриц
        for (int i = 0; i < n; i++)
            for (int j = 0; j < q; j++) {
                mC[i][j] = -row[i] - column[j];
                for (int k = 0; k < half_m; k++)
                    mC[i][j] += (mA[i][k << 1] + mB[(k << 1) + 1][j]) * (mA[i][(k << 1) + 1] + mB[k << 1][j]);
            }
    }
    else {
        for (int i = 0; i < n; i++) 
            for (int j = 0; j < m / 2; j++) 
                row[i] += mA[i][2 * j] * mA[i][2 * j + 1];

        for (int i = 0; i < q; i++) 
            for (int j = 0; j < m / 2; j++) 
                column[i] += mB[2 * j][i] * mB[2 * j + 1][i];
            
        // Умножение матриц
        for (int i = 0; i < n; i++) 
            for (int j = 0; j < q; j++) {
                mC[i][j] = -row[i] - column[j];
                for (int k = 0; k < m / 2; k++) 
                    mC[i][j] += (mA[i][2 * k] + mB[2 * k + 1][j]) * (mA[i][2 * k + 1] + mB[2 * k][j]);
            }
    }

    if (m % 2 == 1)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < q; j++)
                mC[i][j] += mA[i][m - 1] * mB[m - 1][j];

    return mC;
}

vector<vector<double>> MatrixSolver::classic_algo() {
    int rowsA = mA.size();
    int colsA = mA[0].size();
    int colsB = mB[0].size();

    // Создаем матрицу для результата умножения
    vector<vector<double>> res(rowsA, vector<double>(colsB, 0.0));

    // Выполняем классическое умножение матриц
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            for (int k = 0; k < colsA; k++) {
                res[i][j] += mA[i][k] * mB[k][j];
            }
        }
    }

    mC = res;
    return res;
}

// Функция для сложения двух матриц
vector<vector<double>> matrix_addition(const vector<vector<double>>& A, const vector<vector<double>>& B) {
    int n = A.size();
    vector<vector<double>> C(n, vector<double>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

// Функция для вычитания одной матрицы из другой
vector<vector<double>> matrix_subtraction(const vector<vector<double>>& A, const vector<vector<double>>& B) {
    int n = A.size();
    vector<vector<double>> C(n, vector<double>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

// Функция для умножения двух матриц с использованием алгоритма Штрассена
vector<vector<double>> MatrixSolver::strassen_algo(const vector<vector<double>>& A, const vector<vector<double>>& B) {
    int n = A.size();

    // Базовый случай: если матрица имеет размер 1x1, выполните обычное умножение
    if (n == 1) {
        vector<vector<double>> C(1, vector<double>(1, 0));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    // Разбиваем матрицы A и B на 4 подматрицы
    int half_size = n / 2;
    vector<vector<double>> A11(half_size, vector<double>(half_size));
    vector<vector<double>> A12(half_size, vector<double>(half_size));
    vector<vector<double>> A21(half_size, vector<double>(half_size));
    vector<vector<double>> A22(half_size, vector<double>(half_size));
    vector<vector<double>> B11(half_size, vector<double>(half_size));
    vector<vector<double>> B12(half_size, vector<double>(half_size));
    vector<vector<double>> B21(half_size, vector<double>(half_size));
    vector<vector<double>> B22(half_size, vector<double>(half_size));

    for (int i = 0; i < half_size; i++) {
        for (int j = 0; j < half_size; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half_size];
            A21[i][j] = A[i + half_size][j];
            A22[i][j] = A[i + half_size][j + half_size];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half_size];
            B21[i][j] = B[i + half_size][j];
            B22[i][j] = B[i + half_size][j + half_size];
        }
    }

    // Рекурсивно вычисляем 7 произведений матриц
    vector<vector<double>> P1 = strassen_algo(A11, matrix_subtraction(B12, B22));
    vector<vector<double>> P2 = strassen_algo(matrix_addition(A11, A12), B22);
    vector<vector<double>> P3 = strassen_algo(matrix_addition(A21, A22), B11);
    vector<vector<double>> P4 = strassen_algo(A22, matrix_subtraction(B21, B11));
    vector<vector<double>> P5 = strassen_algo(matrix_addition(A11, A22), matrix_addition(B11, B22));
    vector<vector<double>> P6 = strassen_algo(matrix_subtraction(A12, A22), matrix_addition(B21, B22));
    vector<vector<double>> P7 = strassen_algo(matrix_subtraction(A11, A21), matrix_addition(B11, B12));

    // Вычисляем подматрицы C11, C12, C21, C22
    vector<vector<double>> C11 = matrix_addition(matrix_subtraction(matrix_addition(P5, P4), P2), P6);
    vector<vector<double>> C12 = matrix_addition(P1, P2);
    vector<vector<double>> C21 = matrix_addition(P3, P4);
    vector<vector<double>> C22 = matrix_subtraction(matrix_subtraction(matrix_addition(P5, P1), P3), P7);

    // Собираем результирующую матрицу C
    vector<vector<double>> C(n, vector<double>(n, 0));
    for (int i = 0; i < half_size; i++) {
        for (int j = 0; j < half_size; j++) {
            C[i][j] = C11[i][j];
            C[i][j + half_size] = C12[i][j];
            C[i + half_size][j] = C21[i][j];
            C[i + half_size][j + half_size] = C22[i][j];
        }
    }

    mC = C;
    return C;
}