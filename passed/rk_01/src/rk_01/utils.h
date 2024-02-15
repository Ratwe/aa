#pragma once

#include <string>
#include <mutex>
using namespace std;
using milliseconds = chrono::milliseconds;

void write_in_file(string filename, string str, mutex& mtx);
void clear_file(string filename);
void write_to_csv(int reqs, milliseconds linear_nano, milliseconds parallel_nano, string filename);