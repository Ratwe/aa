#pragma once

#include <chrono>

using namespace std;

using milliseconds = chrono::milliseconds;

milliseconds linear_time(int reqs, int s, int x);
milliseconds parallel_time(int reqs, int s, int x);