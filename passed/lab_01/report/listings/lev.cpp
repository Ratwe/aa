int DistanceSolver::iterativeLevenshtein() {
    int L1 = S1.length();
    int L2 = S2.length();

    // Create and initialize a matrix of size (L1+1) x (L2+1)
    vector<vector<int>> dp(L1 + 1, vector<int>(L2 + 1, 0));

    // Initialize the first row and the first column of the matrix
    for (int i = 0; i <= L1; i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= L2; j++) {
        dp[0][j] = j;
    }

    // Fill in the matrix
    for (int i = 1; i <= L1; i++) {
        for (int j = 1; j <= L2; j++) {
            int cost = (S1[i - 1] == S2[j - 1]) ? 0 : 1;
            dp[i][j] = min(min(dp[i - 1][j] + 1, dp[i][j - 1] + 1), dp[i - 1][j - 1] + cost);
        }
    }

    // The Levenshtein distance is found in the bottom-right corner of the matrix
    return dp[L1][L2];
}
