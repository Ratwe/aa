#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> get_prefix(string sub) {
    int n = sub.length();
    vector<int> prefix(n, 0);
    int j = 0;

    for (int i = 1; i < n; i++) {
        while (j > 0 && sub[i] != sub[j]) {
            j = prefix[j - 1];
        }
        if (sub[i] == sub[j]) {
            j++;
        }
        prefix[i] = j;
    }
    return prefix;
}
