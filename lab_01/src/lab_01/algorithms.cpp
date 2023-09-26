#include "algorithms.h"

DistanceSolver::DistanceSolver(const string& first, const string& second) : S1(first), S2(second) {
    
}

int DistanceSolver::iterativeLevenshtein() {
    int L1 = S1.length();
    int L2 = S2.length();

    // Создаем и инициализируем матрицу размером (L1+1) x (L2+1)
    vector<vector<int>> dp(L1 + 1, vector<int>(L2 + 1, 0));

    // Инициализируем первую строку и первый столбец матрицы
    for (int i = 0; i <= L1; i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= L2; j++) {
        dp[0][j] = j;
    }

    // Заполняем матрицу
    for (int i = 1; i <= L1; i++) {
        for (int j = 1; j <= L2; j++) {
            int cost = (S1[i - 1] == S2[j - 1]) ? 0 : 1;
            dp[i][j] = min(min(dp[i - 1][j] + 1, dp[i][j - 1] + 1), dp[i - 1][j - 1] + cost);
        }
    }

    // Расстояние Левенштейна находится в правом нижнем углу матрицы
    return dp[L1][L2];
}

int DistanceSolver::iterativeDamerauLevenshtein() {
    int L1 = S1.length();
    int L2 = S2.length();

    vector<vector<int>> dp(L1 + 1, vector<int>(L2 + 1, 0));

    for (int i = 0; i <= L1; i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= L2; j++) {
        dp[0][j] = j;
    }

    for (int i = 1; i <= L1; i++) {
        for (int j = 1; j <= L2; j++) {
            int cost = (S1[i - 1] == S2[j - 1]) ? 0 : 1;
            dp[i][j] = min(min(dp[i - 1][j] + 1, dp[i][j - 1] + 1), dp[i - 1][j - 1] + cost);

            // Проверка на транспозицию символов
            if (i > 1 && j > 1 && S1[i - 1] == S2[j - 2] && S1[i - 2] == S2[j - 1]) {
                dp[i][j] = min(dp[i][j], dp[i - 2][j - 2] + cost);
            }
        }
    }

    return dp[L1][L2];
}
int DistanceSolver::recursiveDamerauLevenshtein(int L1, int L2) {
    // Базовый случай: Если одна из строк пуста, возвращаем длину другой строки
    if (L1 == 0 && L2 == 0) return 0;

    if (L1 == 0) return L2;
    if (L2 == 0) return L1;

    int cost = (S1[L1 - 1] == S2[L2 - 1]) ? 0 : 1;

    int insertion = recursiveDamerauLevenshtein(L1, L2 - 1) + 1;
    int deletion = recursiveDamerauLevenshtein(L1 - 1, L2) + 1;
    int substitution = recursiveDamerauLevenshtein(L1 - 1, L2 - 1) + cost;

    int result = min(min(insertion, deletion), substitution);

    // Проверка на транспозицию символов
    if (L1 > 1 && L2 > 1 && S1[L1 - 1] == S2[L2 - 2] && S1[L1 - 2] == S2[L2 - 1]) {
        int transposition = recursiveDamerauLevenshtein(L1 - 2, L2 - 2) + cost;
        result = min(result, transposition);
    }

    return result;
}


void DistanceSolver::init_cache() {
    cache = vector<vector<int>>(S1.length() + 1, vector<int>(S2.length() + 1, INT_MAX));
}

int DistanceSolver::recursiveCacheDamerauLevenshtein(int L1, int L2) {
    // Проверка на наличие значения в кеше
    if (cache[L1][L2] != INT_MAX) {
        return cache[L1][L2];
    }

    // Базовый случай: Если одна из строк пуста, возвращаем длину другой строки
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

    // Проверка на транспозицию символов
    if (L1 > 1 && L2 > 1 && S1[L1 - 1] == S2[L2 - 2] && S1[L1 - 2] == S2[L2 - 1]) {
        int transposition = recursiveCacheDamerauLevenshtein(L1 - 2, L2 - 2) + cost;
        result = min(result, transposition);
    }

    // Сохранение значения в кеше
    cache[L1][L2] = result;

    return result;
}