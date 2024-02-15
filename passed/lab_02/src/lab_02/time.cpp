#include "algo.h"
#include "time.h"
#include <time.h>
#include <intrin.h> 
#include <iostream>
#include <fstream>
#include <iomanip>

#define LEN_CNT 10
#define TESTS 1000

vector<vector<double>> generate_random_square_matrix(int size) {
    // �������������� ��������� ��������� �����
    srand(time(0));

    // ������� ���������� ������� �������� size x size
    vector<vector<double>> matrix(size, vector<double>(size));

    // ��������� ������� ���������� ����������
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = static_cast<double>(rand()) / RAND_MAX * 10.0;
        }
    }

    return matrix;
}

void compare_time()
{
    ofstream outputFile;
    outputFile.open("time.csv");
    outputFile << "������ ������,������������,���������,��������� (���.),���������" << endl;

    int lengths[LEN_CNT] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    for (int i = 1; i <= LEN_CNT; i++) {
        
        double totalDurationClassic = 0;
        double totalDurationWinograd = 0;
        double totalDurationOptimizedWinograd = 0;
        double totalDurationStrassen = 0;

        for (int test = 0; test < TESTS; test++) {
            // ������� � ��������� ������� mA � mB
            vector<vector<double>> mA, mB;
            mA = generate_random_square_matrix(i);
            mB = generate_random_square_matrix(i);
            MatrixSolver solver(mA, mB);

            // �������� ����� ���������� classic_algo
            unsigned __int64 tb1 = __rdtsc();
            vector<vector<double>> resultClassic = solver.classic_algo();
            unsigned __int64 te1 = __rdtsc();
            double durationClassic = static_cast<double>(te1 - tb1);
            totalDurationClassic += durationClassic;

            // �������� ����� ���������� winograd_algo
            unsigned __int64 tb2 = __rdtsc();
            vector<vector<double>> resultWinograd = solver.winograd_algo(0); // ��������� ������ ���������
            unsigned __int64 te2 = __rdtsc();
            double durationWinograd = static_cast<double>(te2 - tb2);
            totalDurationWinograd += durationWinograd;

            // �������� ����� ���������� optimized winograd_algo
            unsigned __int64 tb3 = __rdtsc();
            vector<vector<double>> resultOptimizedWinograd = solver.winograd_algo(1); // ��������� ������ ���������
            unsigned __int64 te3 = __rdtsc();
            double durationOptimizedWinograd = static_cast<double>(te3 - tb3);
            totalDurationOptimizedWinograd += durationOptimizedWinograd;

            // �������� ����� ���������� strassen_algo
            unsigned __int64 tb4 = __rdtsc();
            vector<vector<double>> resultStrassen = solver.strassen_algo(mA, mB);
            unsigned __int64 te4 = __rdtsc();
            double durationStrassen = static_cast<double>(te4 - tb4);
            totalDurationStrassen += durationStrassen;
        }

        // ������� ����������
        cout << "������ �������: " << i << endl;
        cout << "����� ���������� ������������� ���������: " << totalDurationClassic / TESTS << " ������" << endl;
        cout << "����� ���������� ��������� ���������: " << totalDurationWinograd / TESTS << " ������" << endl;
        cout << "����� ���������� ����������������� ��������� ���������: " << totalDurationOptimizedWinograd / TESTS << " ������" << endl;
        cout << "����� ���������� ��������� ���������: " << totalDurationStrassen / TESTS << " ������" << endl;

        outputFile << i << ','
            << scientific << setprecision(3) << totalDurationClassic / TESTS << ','
            << scientific << setprecision(3) << totalDurationWinograd / TESTS << ','
            << scientific << setprecision(3) << totalDurationOptimizedWinograd / TESTS << ','
            << scientific << setprecision(3) << totalDurationStrassen / TESTS << endl;

    }

    outputFile.close();
}