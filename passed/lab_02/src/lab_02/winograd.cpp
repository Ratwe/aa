vector<vector<double>> MatrixSolver::winograd_algo(int optimized) {
    int n = mA.size();
    int m = mA[0].size();
    int q = mB[0].size();

    mC.resize(n, vector<double>(q));
    vector<double> row(n, 0);
    vector<double> column(q, 0);

    if (optimized == 1) {
        int half_m = m >> 1;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < half_m; j++)
                row[i] += mA[i][j << 1] * mA[i][(j << 1) + 1];

        for (int i = 0; i < q; i++)
            for (int j = 0; j < half_m; j++)
                column[i] += mB[j << 1][i] * mB[(j << 1) + 1][i];

        for (int i = 0; i < n; i++)
            for (int j = 0; j < q; j++) {
                mC[i][j] = -row[i] - column[j];
                for (int k = 0; k < half_m; k++)
                    mC[i][j] += (mA[i][k << 1] + mB[(k << 1) + 1][j]) * (mA[i][(k << 1) + 1] + mB[k << 1][j]);
            }
    }
