#include "io_array.h"
#include "time.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <intrin.h>

#define STEP 10

std::vector<int> generate_random_array(int size) {
    srand(static_cast<unsigned int>(time(0)));

    std::vector<int> array;

    for (int i = 0; i < size; ++i) {
        array.push_back(rand() % 100);
    }

    return array;
}

void compare_time() {
    ofstream outputFile;
    outputFile.open("time.csv");
    outputFile << "Размер массива,Сортировка выбором,Сортировка перемешиванием" << endl;

    const int MAX_SIZE = 10 * STEP;  // Set a maximum size based on STEP
    const int TESTS = 1000;

    for (int i = STEP; i <= MAX_SIZE; i += STEP) {
        double totalDurationSelection = 0;
        double totalDurationShaker = 0;

        for (int test = 0; test < TESTS; test++) {
            // Create and fill the array
            std::vector<int> myArray = generate_random_array(i);

            // Measure the time for selection sort
            unsigned __int64 tb1 = __rdtsc();
            selection_sort(myArray);
            unsigned __int64 te1 = __rdtsc();
            double durationSelection = static_cast<double>(te1 - tb1);
            totalDurationSelection += durationSelection;

            // Measure the time for shaker sort
            unsigned __int64 tb2 = __rdtsc();
            shaker_sort(myArray);
            unsigned __int64 te2 = __rdtsc();
            double durationShaker = static_cast<double>(te2 - tb2);
            totalDurationShaker += durationShaker;
        }

        // Output the results
        cout << "Размер массива: " << i << endl;
        cout << "Время выполнения сортировки выбором: " << totalDurationSelection / TESTS << " тактов" << endl;
        cout << "Время выполнения сортировки перемешиванием: " << totalDurationShaker / TESTS << " тактов" << endl;

        outputFile << i << ','
            << scientific << setprecision(3) << totalDurationSelection / TESTS << ','
            << scientific << setprecision(3) << totalDurationShaker / TESTS << endl;
    }

    outputFile.close();
}
