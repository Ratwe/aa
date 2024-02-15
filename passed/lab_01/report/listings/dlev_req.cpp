int DistanceSolver::recursiveDamerauLevenshtein(int L1, int L2) {
    // Base case: If both strings are empty, return 0 (edit distance)
    if (L1 == 0 && L2 == 0) return 0;

    // If one of the strings is empty, return the length of the other string
    if (L1 == 0) return L2;
    if (L2 == 0) return L1;

    // Calculate the cost for the current character pair
    int cost = (S1[L1 - 1] == S2[L2 - 1]) ? 0 : 1;

    // Calculate the edit distances for insertion, deletion, and substitution
    int insertion = recursiveDamerauLevenshtein(L1, L2 - 1) + 1;
    int deletion = recursiveDamerauLevenshtein(L1 - 1, L2) + 1;
    int substitution = recursiveDamerauLevenshtein(L1 - 1, L2 - 1) + cost;

    // Find the minimum edit distance among the three operations
    int result = min(min(insertion, deletion), substitution);

    // Check for character transposition
    if (L1 > 1 && L2 > 1 && S1[L1 - 1] == S2[L2 - 2] && S1[L1 - 2] == S2[L2 - 1]) {
        int transposition = recursiveDamerauLevenshtein(L1 - 2, L2 - 2) + cost;
        result = min(result, transposition);
    }

    return result;
}
