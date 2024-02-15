vector<vector<double>> MatrixSolver::classic_algo() {
    int rowsA = mA.size();
    int colsA = mA[0].size();
    int colsB = mB[0].size();

    vector<vector<double>> res(rowsA, vector<double>(colsB, 0.0));

    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            for (int k = 0; k < colsA; k++) {
                res[i][j] += mA[i][k] * mB[k][j];
            }
        }
    }

    mC = res;
    return res;
}