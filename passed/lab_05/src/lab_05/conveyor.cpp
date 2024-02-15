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

		standart(str, sub, mtx);
		KMP(str, sub, mtx);
	}

	return;
}

void parallel(int reqs, int s, int x) {
	vector<thread> threads;
    queue<pair<string, string>> q;
    mutex mtx;

    for (int i = 0; i < reqs; i++) {
        threads.emplace_back([&q, s, x, &mtx]() {
            string sub = generate_substring(s);
            string str = generate_string(sub, x);
            lock_guard<mutex> lock(mtx);
            q.push(make_pair(str, sub));
            });
    }

    for (auto& thread : threads) {
        thread.join();
    }
    threads.clear();

    for (int i = 0; i < reqs; ++i) {
        auto result = q.front();
        q.pop();
        string str = result.first;
        string sub = result.second;

        threads.emplace_back([&mtx, str, sub]() {
            standart(str, sub, ref(mtx));
            });

        threads.emplace_back([&mtx, str, sub]() {
            KMP(str, sub, ref(mtx));
            });
    }

    int i = 1;
    for (auto& thread : threads) {
        thread.join();
    }
}