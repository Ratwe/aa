#include <stdio.h>
#include <iostream>
#include <chrono>
#include "test.h"
#include "algorithms.h"

#include <intrin.h>

#pragma intrinsic(__rdtsc)


#define LEN_CNT 6
#define TESTS 1

using namespace std;

pair<string, string> getStrings() {
    string S1, S2;

    cout << "Введите первую строку S1: ";
    cin >> S1;

    cout << "Введите вторую строку S2: ";
    cin >> S2;

    return make_pair(S1, S2);
}

int normal_mode() {
    pair<string, string> S = getStrings();
    DistanceSolver solver(S.first, S.second);
    solver.init_cache();

    int result, resultD;
    double totalDurationDamerauLevenshtein = 0, totalDurationLevenshtein = 0, totalDurationRecursiveDamerauLevenshtein = 0, totalDurationRecursiveCacheDamerauLevenshtein = 0;

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
    if (resultD != solver.recursiveDamerauLevenshtein(S.first.length(), S.second.length()))
        return 1;
    unsigned __int64 te3 = __rdtsc();
    double durationRecursiveDamerauLevenshtein = te3 - tb3;
    totalDurationRecursiveDamerauLevenshtein += durationRecursiveDamerauLevenshtein;

    // Засекаем время для recursiveCacheDamerauLevenshtein
    unsigned __int64 tb4 = __rdtsc();
    if (resultD != solver.recursiveCacheDamerauLevenshtein(S.first.length(), S.second.length()))
        return 2;
    unsigned __int64 te4 = __rdtsc();
    double durationRecursiveCacheDamerauLevenshtein = te4 - tb4;
    totalDurationRecursiveCacheDamerauLevenshtein += durationRecursiveCacheDamerauLevenshtein;
    


    // Вывод общего времени выполнения и среднего времени для каждого алгоритма
    cout << "Расстояние Левенштейна: " << result << endl;
    cout << "Расстояние Дамерау-Левенштейна: " << resultD << endl;
    cout << "Левенштейн: " << fixed << std::scientific << totalDurationLevenshtein << " тактов" << endl;
    cout << "Дамерау-Левенштейн: " << fixed << std::scientific << totalDurationDamerauLevenshtein << " тактов" << endl;
    cout << "Рекурсивный Дамерау-Левенштейн: " << std::scientific << totalDurationRecursiveDamerauLevenshtein << " тактов" << endl;
    cout << "Рекурсивный Дамерау-Левенштейн с кэшем: " << fixed << std::scientific << totalDurationRecursiveCacheDamerauLevenshtein << " тактов" << endl;

    return 0;
}

int greetings() {
    std::cout << "Для тестирования введите 1\nДля стандартного режима введите 2: ";
    int mode;
    cin >> mode;

    if (mode == 1)
        return tests();
    else
        return normal_mode();
}
    