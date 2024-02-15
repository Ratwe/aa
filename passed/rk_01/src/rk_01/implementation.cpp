#include <iostream>
#include <mutex>
#include <future>

#include "conveyor.h"
#include "generate.h"
#include "KMP.h"
#include "standart.h"
#include <vector>
#include <queue>

using namespace std;

void linear(int reqs, int s, int x) {
    mutex mtx;

	for (int i = 0; i < reqs; i++) {
		string sub = generate_substring(s);
		string str = generate_string(sub, x);

		standart(str, sub, mtx, 0);
	}
}

void parallel(int reqs, int s, int x) {
	vector<thread> threads;
    queue<pair<string, string>> q;
    mutex mtx;

    for (int i = 0; i < reqs; ++i) {
        string sub = generate_substring(s);
        string str = generate_string(sub, x);
        size_t n = str.length();
        string first_half = str.substr(0, n / 2 + s);
        string second_half = str.substr(n / 2, s);

        threads.emplace_back([&mtx, first_half, second_half, sub, n]() {
            standart(first_half, sub, ref(mtx), 0);
            standart(second_half, sub, ref(mtx), n / 2);
            });
    }                     
    for (auto& thread : threads)
        thread.join();

    threads.clear();
}