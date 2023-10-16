int DistanceSolver::recursiveCacheDamerauLevenshtein(int L1, int L2) {
    if (cache[L1][L2] != INT_MAX) {
        return cache[L1][L2];
    }
    if (L1 == 0) {
        cache[L1][L2] = L2;
        return L2;
    }
    if (L2 == 0) {
        cache[L1][L2] = L1;
        return L1;
    }

    int cost = (S1[L1 - 1] == S2[L2 - 1]) ? 0 : 1;
    int insertion = recursiveCacheDamerauLevenshtein(L1, L2 - 1) + 1;
    int deletion = recursiveCacheDamerauLevenshtein(L1 - 1, L2) + 1;
    int substitution = recursiveCacheDamerauLevenshtein(L1 - 1, L2 - 1) + cost;
    int result = min(min(insertion, deletion), substitution);

    if (L1 > 1 && L2 > 1 && S1[L1 - 1] == S2[L2 - 2] && S1[L1 - 2] == S2[L2 - 1]) {
        int transposition = recursiveCacheDamerauLevenshtein(L1 - 2, L2 - 2) + cost;
        result = min(result, transposition);
    }

    cache[L1][L2] = result;
    return result;
}
