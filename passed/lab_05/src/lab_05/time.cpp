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
    mutex mtx;
    auto t1 = chrono::steady_clock::now();

    for (int i = 0; i < reqs; i++) {
        
        string sub = generate_substring(s);
        string str = generate_string(sub, x);

        standart(str, sub, mtx);
        KMP(str, sub, mtx);
       
    }

    auto t2 = chrono::steady_clock::now();
    milliseconds time = milliseconds(chrono::duration_cast<milliseconds>(t2 - t1).count());

    return time;
}

milliseconds parallel_time(int reqs, int s, int x) {
    vector<thread> threads;
    queue<pair<string, string>> q;
    mutex mtx;
    auto t1 = chrono::steady_clock::now();

    for (int i = 0; i < reqs; i++) {
        threads.emplace_back([&q, s, x, &mtx]() {
            string sub = generate_substring(s);
            string str = generate_string(sub, x);
            lock_guard<mutex> lock(mtx);
            q.push(make_pair(str, sub)); // Добавляем пару строк в очередь
            });
    }

    // Ждем завершения всех потоков
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
    // Дожидаемся завершения всех потоков
    for (auto& thread : threads) {
        thread.join();
    }

    auto t2 = chrono::steady_clock::now();
    milliseconds time = milliseconds(chrono::duration_cast<milliseconds>(t2 - t1).count());

    return time;
}