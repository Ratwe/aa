#include <string>
#include "algorithms.h"
#include <chrono>

#include <intrin.h>

#pragma intrinsic(__rdtsc)

#define LEN_CNT 10
#define TESTS 1000

// Генерирует случайную строку заданной длины
string generateRandomString(int length) {
    static const string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) {
        result.push_back(charset[rand() % charset.length()]);
    }
    return result;
}

int tests() {
    int lengths[LEN_CNT] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    for (int i = 0; i < LEN_CNT; i++) {
        double totalDurationDamerauLevenshtein = 0;
        double totalDurationLevenshtein = 0;
        double totalDurationRecursiveDamerauLevenshtein = 0;
        double totalDurationRecursiveCacheDamerauLevenshtein = 0;

        for (int test = 0; test < TESTS; test++) {
            // Генерируем две случайные строки заданной длины
            string randomString1 = generateRandomString(lengths[i]);
            string randomString2 = generateRandomString(lengths[i]);

            // Инициализируем DistanceSolver с этими строками
            DistanceSolver solver(randomString1, randomString2);
            solver.init_cache();

            int result, resultD;

            // Засекаем время для Damerau-Levenshtein
            unsigned __int64 tb1 = __rdtsc();
            resultD = solver.iterativeDamerauLevenshtein();
            unsigned __int64 te1 = __rdtsc();
            double durationDamerauLevenshtein = te1 - tb1;
            totalDurationDamerauLevenshtein += durationDamerauLevenshtein;

            // Засекаем время для Levenshtein
            unsigned __int64 tb2 = __rdtsc();
            result = solver.iterativeLevenshtein();
            unsigned __int64 te2 = __rdtsc();
            double durationLevenshtein = te2 - tb2;
            totalDurationLevenshtein += durationLevenshtein;

            // Засекаем время для recursiveDamerauLevenshtein
            unsigned __int64 tb3 = __rdtsc();
            if (resultD != solver.recursiveDamerauLevenshtein(randomString1.length(), randomString2.length()))
                return 1;
            unsigned __int64 te3 = __rdtsc();
            double durationRecursiveDamerauLevenshtein = te3 - tb3;
            totalDurationRecursiveDamerauLevenshtein += durationRecursiveDamerauLevenshtein;

            // Засекаем время для recursiveCacheDamerauLevenshtein
            unsigned __int64 tb4 = __rdtsc();
            if (resultD != solver.recursiveCacheDamerauLevenshtein(randomString1.length(), randomString2.length()))
                return 2;
            unsigned __int64 te4 = __rdtsc();
            double durationRecursiveCacheDamerauLevenshtein = te4 - tb4;
            totalDurationRecursiveCacheDamerauLevenshtein += durationRecursiveCacheDamerauLevenshtein;
        }

        // Вывод среднего времени выполнения для каждой длины строки
        cout << "Длина: " << lengths[i] << endl;
        cout << "Среднее время Дамерау-Левенштейна: " << fixed << std::scientific << totalDurationDamerauLevenshtein / TESTS << " ticks" << endl;
        cout << "Среднее время Левенштейна: " << fixed << std::scientific << totalDurationLevenshtein / TESTS << " ticks" << endl;
        cout << "Среднее время рекурсивного Дамерау-Левенштейна: " << fixed << std::scientific << totalDurationRecursiveDamerauLevenshtein / TESTS << " ticks" << endl;
        cout << "Среднее время рекурсивного Дамерау-Левенштейна с кэшем: " << fixed << std::scientific << totalDurationRecursiveCacheDamerauLevenshtein / TESTS << " ticks" << endl;
    }
}