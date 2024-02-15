#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <locale.h>
#include <iomanip>

using namespace std;

void findSubstring(const string& fileContent, const string& substring, const string& outputFilePath,
    size_t shift, mutex& mtx, vector<condition_variable>& cVars, size_t index) {
    auto startTime = chrono::high_resolution_clock::now();

    size_t substringLength = substring.length();
    vector<size_t> positions;

    for (size_t i = 0; i < fileContent.length(); ++i) {
        if (fileContent.substr(i, substringLength) == substring) {
            positions.push_back(i + shift);
        }
    }

    lock_guard<mutex> lock(mtx);

    ofstream outputFile(outputFilePath, ios::app);
    for (size_t pos : positions) {
        outputFile << pos << "\n";
    }

    cVars[index].notify_one();

    auto endTime = chrono::high_resolution_clock::now();
    auto elapsedTime = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();

    cout << "Поток " << index << " завершил выполнение за " << elapsedTime / 1000.0 << " секунд\n";

    std::time_t currentTime = std::time(nullptr);
    std::tm* localTime = std::localtime(&currentTime);
    // std::cout << "Текущее время: ";
    // std::cout << localTime->tm_hour << ":" << localTime->tm_min << ":" << localTime->tm_sec << std::endl;
}

void mainThread(const string& filePath, size_t k) {
    ifstream file(filePath, ios::binary);
    if (!file.is_open()) {
        cerr << "Ошибка при открытии файла" << endl;
        return;
    }

    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    mutex mtx;
    vector<condition_variable> cVars(k);
    vector<thread> threads;

    size_t m = content.length();
    size_t t = m / k;

    string substring;
    cout << "Введите искомую подстроку: ";
    cin >> substring;

    for (size_t i = 0; i < k; ++i) {
        string threadFileContent = content.substr(i * t, i * t + substring.length() - 1);
        string threadFilePath = "out_thread_" + to_string(i) + ".txt";

        ofstream threadFile(threadFilePath, ios::trunc);
        threadFile << threadFileContent;
        threadFile.close();

        threads.emplace_back(findSubstring, threadFileContent, substring, "out.txt", i * t, ref(mtx),
            ref(cVars), i);
    }

    for (thread& th : threads) {
        th.join();
    }

    cout << "Все потоки завершили выполнение." << endl;
}

void readOutputFile(const string& outputFilePath) {
    ifstream outputFile(outputFilePath);
    if (!outputFile.is_open()) {
        cerr << "Ошибка при открытии выходного файла для чтения" << endl;
        return;
    }

    cout << "Содержимое выходного файла:" << endl;
    string line;
    while (getline(outputFile, line)) {
        cout << line << endl;
    }

    outputFile.close();
}

int main() {
    setlocale(LC_ALL, "ru");

    // Очищаем выходной файл перед первой записью
    ofstream outputFile("out.txt", ios::trunc);
    outputFile.close();

    string filePath = "10MB.txt";  // Файл с рандомными символами
    size_t k = 10;  // Указать количество потоков k

    mainThread(filePath, k);

    // Читаем и выводим содержимое выходного файла
    readOutputFile("out.txt");

    return 0;
}
