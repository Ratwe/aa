#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class DistanceSolver {
public:
    DistanceSolver(const string& first, const string& second);

    int iterativeLevenshtein();
    int iterativeDamerauLevenshtein();
    int recursiveDamerauLevenshtein(int L1, int L2);
    int recursiveCacheDamerauLevenshtein(int L1, int L2);

    void init_cache();

private:
    string S1;
    string S2;

    vector<vector<int>> matrix;
    vector<vector<int>> cache;
};

#endif // ALGORITHM_H
