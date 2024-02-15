#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include "KMP.h"
#include "prefix.h"
#include "utils.h"

using namespace std;

void KMP(string str, string sub, mutex& mtx) {
    vector<int> prefix = get_prefix(sub);

    size_t n = str.length();
    size_t s = sub.length();
    int j = 0;

    for (int i = 0; i < n; i++) {
        while (j > 0 && str[i] != sub[j]) {
            j = prefix[j - 1];
        }
        if (str[i] == sub[j]) {
            j++;
        }
        if (j == s) {
            // cout << "Substring found at position " << i - s + 1 << endl;

            write_in_file("log.txt", "КМП: " + sub + " найдена в позиции " + to_string(i - s + 1), mtx);

            j = prefix[j - 1];
        }
    }
}