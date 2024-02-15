#include <iostream>
#include <mutex>
#include <future>

#include "generate.h"
#include "KMP.h"
#include "standart.h"
#include "time.h"
#include <vector>
#include <queue>

using namespace std;

milliseconds linear_time(int reqs, int s, int x) {
    cout << "entered linear()" << endl;

    mutex mtx;
    auto t1 = chrono::steady_clock::now();

    for (int i = 0; i < reqs; i++) {
        string sub = generate_substring(s);
        string str = generate_string(sub, x);
        standart(str, sub, mtx, 0);
    }

    auto t2 = chrono::steady_clock::now();
    milliseconds time = milliseconds(chrono::duration_cast<milliseconds>(t2 - t1).count());

    return time;
}

milliseconds parallel_time(int reqs, int s, int x) {
    cout << "entered parallel()" << endl;

    vector<thread> threads;
    queue<pair<string, string>> q;
    mutex mtx;
    auto t1 = chrono::steady_clock::now();

    for (int i = 0; i < reqs; i++) {
        string sub = generate_substring(s);
        string str = generate_string(sub, x);
        size_t n = str.length();
        string first_half = str.substr(0, n / 2 + s - 1);
        string second_half = str.substr(n / 2, n / 2);

        // cout << "sub = " << sub << endl;
        // cout << "str = " << str << endl;

        threads.emplace_back([&mtx, first_half, second_half, sub, n]() {
            standart(first_half, sub, ref(mtx), 0);
            standart(second_half, sub, ref(mtx), n / 2);
            });
    }

    // Join all threads after they have been created
    for (auto& thread : threads) {
        thread.join();
    }

    threads.clear();


    auto t2 = chrono::steady_clock::now();
    milliseconds time = milliseconds(chrono::duration_cast<milliseconds>(t2 - t1).count());

    return time;
}