int DistanceSolver::iterativeDamerauLevenshtein() {
    int L1 = S1.length();
    int L2 = S2.length();

    // Create a 2D vector for dynamic programming
    vector<vector<int>> dp(L1 + 1, vector<int>(L2 + 1, 0));

    // Initialize the first row and column
    for (int i = 0; i <= L1; i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= L2; j++) {
        dp[0][j] = j;
    }

    // Calculate the minimum edit distance using dynamic programming
    for (int i = 1; i <= L1; i++) {
        for (int j = 1; j <= L2; j++) {
            int cost = (S1[i - 1] == S2[j - 1]) ? 0 : 1;
            dp[i][j] = min(min(dp[i - 1][j] + 1, dp[i][j - 1] + 1), dp[i - 1][j - 1] + cost);

            // Check for character transposition
            if (i > 1 && j > 1 && S1[i - 1] == S2[j - 2] && S1[i - 2] == S2[j - 1]) {
                dp[i][j] = min(dp[i][j], dp[i - 2][j - 2] + cost);
            }
        }
    }

    // Return the minimum edit distance
    return dp[L1][L2];
}
