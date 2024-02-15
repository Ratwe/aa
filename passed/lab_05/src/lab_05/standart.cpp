#include <stdio.h>
#include <string>
#include <iostream>

#include "standart.h"
#include <mutex>
#include "utils.h"

using namespace std;

void standart(string str, string sub, mutex &mtx) {
    size_t n = str.length();
    size_t s = sub.length();

    for (int i = 0; i <= n - s; i++) {
        int j;
        for (j = 0; j < s; j++) {
            if (str[i + j] != sub[j])
                break;
        }
        if (j == s) {
            // cout << "Substring found at position " << i << endl;
            write_in_file("log.txt", "Стандартный: " + sub + " найдена в позиции " + to_string(i), mtx);
        }
    }
}