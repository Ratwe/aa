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
    // Инициализируем генератор случайных чисел
    srand(time(0));

    // Создаем квадратную матрицу размером size x size
    vector<vector<double>> matrix(size, vector<double>(size));

    // Заполняем матрицу случайными значениями
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
    outputFile << "Размер матриц,Классический,Винограда,Винограда (опт.),Штрассена" << endl;

    int lengths[LEN_CNT] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    for (int i = 1; i <= LEN_CNT; i++) {
        
        double totalDurationClassic = 0;
        double totalDurationWinograd = 0;
        double totalDurationOptimizedWinograd = 0;
        double totalDurationStrassen = 0;

        for (int test = 0; test < TESTS; test++) {
            // Создаем и заполняем матрицы mA и mB
            vector<vector<double>> mA, mB;
            mA = generate_random_square_matrix(i);
            mB = generate_random_square_matrix(i);
            MatrixSolver solver(mA, mB);

            // Измеряем время выполнения classic_algo
            unsigned __int64 tb1 = __rdtsc();
            vector<vector<double>> resultClassic = solver.classic_algo();
            unsigned __int64 te1 = __rdtsc();
            double durationClassic = static_cast<double>(te1 - tb1);
            totalDurationClassic += durationClassic;

            // Измеряем время выполнения winograd_algo
            unsigned __int64 tb2 = __rdtsc();
            vector<vector<double>> resultWinograd = solver.winograd_algo(0); // Передайте нужные параметры
            unsigned __int64 te2 = __rdtsc();
            double durationWinograd = static_cast<double>(te2 - tb2);
            totalDurationWinograd += durationWinograd;

            // Измеряем время выполнения optimized winograd_algo
            unsigned __int64 tb3 = __rdtsc();
            vector<vector<double>> resultOptimizedWinograd = solver.winograd_algo(1); // Передайте нужные параметры
            unsigned __int64 te3 = __rdtsc();
            double durationOptimizedWinograd = static_cast<double>(te3 - tb3);
            totalDurationOptimizedWinograd += durationOptimizedWinograd;

            // Измеряем время выполнения strassen_algo
            unsigned __int64 tb4 = __rdtsc();
            vector<vector<double>> resultStrassen = solver.strassen_algo(mA, mB);
            unsigned __int64 te4 = __rdtsc();
            double durationStrassen = static_cast<double>(te4 - tb4);
            totalDurationStrassen += durationStrassen;
        }

        // Выводим результаты
        cout << "Размер матрицы: " << i << endl;
        cout << "Время выполнения классического алгоритма: " << totalDurationClassic / TESTS << " тактов" << endl;
        cout << "Время выполнения алгоритма Винограда: " << totalDurationWinograd / TESTS << " тактов" << endl;
        cout << "Время выполнения оптимизированного алгоритма Винограда: " << totalDurationOptimizedWinograd / TESTS << " тактов" << endl;
        cout << "Время выполнения алгоритма Штрассена: " << totalDurationStrassen / TESTS << " тактов" << endl;

        outputFile << i << ','
            << scientific << setprecision(3) << totalDurationClassic / TESTS << ','
            << scientific << setprecision(3) << totalDurationWinograd / TESTS << ','
            << scientific << setprecision(3) << totalDurationOptimizedWinograd / TESTS << ','
            << scientific << setprecision(3) << totalDurationStrassen / TESTS << endl;

    }

    outputFile.close();
}