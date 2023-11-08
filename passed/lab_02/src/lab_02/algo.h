#ifndef ALGO_H
#define ALGO_H

#include <string>
#include <vector>

using namespace std;

class MatrixSolver {
public:
    MatrixSolver(vector<vector<double>>& mA, vector<vector<double>>& mB);
    void increase_matrices_to_power_of_two();
    void set_matrices(vector<vector<double>>& mA, vector<vector<double>>& mB);

    void crop() {
        mC.resize(n);
        for (int i = 0; i < n; i++) 
            mC[i].resize(q);
    }

    vector<vector<double>> classic_algo();
    vector<vector<double>> winograd_algo(int optimized);
    vector<vector<double>> strassen_algo(const vector<vector<double>>& A, const vector<vector<double>>& B);

//private:
    int n, q;
    vector<vector<double>> mA, mB, mC;
};

#endif