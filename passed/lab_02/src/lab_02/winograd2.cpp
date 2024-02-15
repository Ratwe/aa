    else {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m / 2; j++)
                row[i] += mA[i][2 * j] * mA[i][2 * j + 1];

        for (int i = 0; i < q; i++)
            for (int j = 0; j < m / 2; j++)
                column[i] += mB[2 * j][i] * mB[2 * j + 1][i];

        for (int i = 0; i < n; i++)
            for (int j = 0; j < q; j++) {
                mC[i][j] = -row[i] - column[j];
                for (int k = 0; k < m / 2; k++)
                    mC[i][j] += (mA[i][2 * k] + mB[2 * k + 1][j]) * (mA[i][2 * k + 1] + mB[2 * k][j]);
            }
    }

    if (m % 2 == 1)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < q; j++)
                mC[i][j] += mA[i][m - 1] * mB[m - 1][j];
    return mC;
}