#include <string>
#include <fstream>
#include <iostream>
#include <mutex>
using namespace std;
using milliseconds = chrono::milliseconds;


void write_in_file(string filename, string str, mutex& mtx) {

    ofstream outfile(filename, ios::app);
    if (outfile.is_open()) {
        lock_guard<mutex> lock(mtx);
        outfile << str << endl;
        outfile.close();
    }
}

void clear_file(string filename) {
    ofstream outfile(filename, ofstream::trunc);
    if (outfile.is_open())
        outfile.close();
    else 
        cerr << "Невозможно открыть файл для очистки!" << endl;
}

void write_to_csv(int reqs, milliseconds linear_nano, milliseconds parallel_nano, string filename) {
    ofstream outfile(filename, ios::app);
    if (outfile.is_open()) {
        outfile << reqs << "," << linear_nano.count() << "," << parallel_nano.count() << endl;
        outfile.close();
    }
    else {
        cerr << "Невозможно открыть файл для записи!" << endl;
    }
}