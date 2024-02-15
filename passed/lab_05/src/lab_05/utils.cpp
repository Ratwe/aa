#include <string>
#include <fstream>
#include <iostream>
#include <mutex>
#include <locale>
#include <codecvt>

using namespace std;
using milliseconds = chrono::milliseconds;

void write_in_file(string filename, string str, mutex& mtx) {
    lock_guard<mutex> lock(mtx);

    ofstream outfile(filename, ios::app | ios::binary);
    if (outfile.is_open()) {
        outfile.imbue(locale(locale(), new codecvt_utf8<wchar_t>)); // Устанавливаем кодировку UTF-8
        outfile << str << endl;
        outfile.close();
    }
    else {
        cerr << "Невозможно открыть файл для записи!" << endl;
    }
}

void clear_file(string filename) {
    wofstream outfile(filename, ofstream::trunc | ios::binary); // Заменяем ofstream на wofstream
    if (outfile.is_open())
        outfile.close();
    else
        cerr << "Невозможно открыть файл для очистки!" << endl;
}

void write_to_csv(int reqs, milliseconds linear_nano, milliseconds parallel_nano, string filename) {
    wofstream outfile(filename, ios::app | ios::binary); // Заменяем ofstream на wofstream
    if (outfile.is_open()) {
        outfile.imbue(locale(locale(), new codecvt_utf8<wchar_t>)); // Устанавливаем кодировку UTF-8
        outfile << reqs << "," << linear_nano.count() << "," << parallel_nano.count() << endl;
        outfile.close();
    }
    else {
        cerr << "Невозможно открыть файл для записи!" << endl;
    }
}
