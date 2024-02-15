#include "io_array.h"
#include <iostream>
#include <vector>

std::vector<int> fill_array() {
    int size;

    std::cout << "Введите размер массива: ";
    std::cin >> size;

    std::vector<int> array;

    for (int i = 0; i < size; ++i) {
        int value;
        std::cin >> value;  
        array.push_back(value);
    }

    return array;
}

void print_array(const std::vector<int>& array) {
    std::cout << "Массив: ";
    for (const int& value : array) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}