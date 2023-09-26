#include <string>
#include "algorithms.h"
#include <chrono>

#include <intrin.h>

#pragma intrinsic(__rdtsc)

#define LEN_CNT 10
#define TESTS 1000

// ���������� ��������� ������ �������� �����
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
            // ���������� ��� ��������� ������ �������� �����
            string randomString1 = generateRandomString(lengths[i]);
            string randomString2 = generateRandomString(lengths[i]);

            // �������������� DistanceSolver � ����� ��������
            DistanceSolver solver(randomString1, randomString2);
            solver.init_cache();

            int result, resultD;

            // �������� ����� ��� Damerau-Levenshtein
            unsigned __int64 tb1 = __rdtsc();
            resultD = solver.iterativeDamerauLevenshtein();
            unsigned __int64 te1 = __rdtsc();
            double durationDamerauLevenshtein = te1 - tb1;
            totalDurationDamerauLevenshtein += durationDamerauLevenshtein;

            // �������� ����� ��� Levenshtein
            unsigned __int64 tb2 = __rdtsc();
            result = solver.iterativeLevenshtein();
            unsigned __int64 te2 = __rdtsc();
            double durationLevenshtein = te2 - tb2;
            totalDurationLevenshtein += durationLevenshtein;

            // �������� ����� ��� recursiveDamerauLevenshtein
            unsigned __int64 tb3 = __rdtsc();
            if (resultD != solver.recursiveDamerauLevenshtein(randomString1.length(), randomString2.length()))
                return 1;
            unsigned __int64 te3 = __rdtsc();
            double durationRecursiveDamerauLevenshtein = te3 - tb3;
            totalDurationRecursiveDamerauLevenshtein += durationRecursiveDamerauLevenshtein;

            // �������� ����� ��� recursiveCacheDamerauLevenshtein
            unsigned __int64 tb4 = __rdtsc();
            if (resultD != solver.recursiveCacheDamerauLevenshtein(randomString1.length(), randomString2.length()))
                return 2;
            unsigned __int64 te4 = __rdtsc();
            double durationRecursiveCacheDamerauLevenshtein = te4 - tb4;
            totalDurationRecursiveCacheDamerauLevenshtein += durationRecursiveCacheDamerauLevenshtein;
        }

        // ����� �������� ������� ���������� ��� ������ ����� ������
        cout << "�����: " << lengths[i] << endl;
        cout << "������� ����� �������-�����������: " << fixed << std::scientific << totalDurationDamerauLevenshtein / TESTS << " ticks" << endl;
        cout << "������� ����� �����������: " << fixed << std::scientific << totalDurationLevenshtein / TESTS << " ticks" << endl;
        cout << "������� ����� ������������ �������-�����������: " << fixed << std::scientific << totalDurationRecursiveDamerauLevenshtein / TESTS << " ticks" << endl;
        cout << "������� ����� ������������ �������-����������� � �����: " << fixed << std::scientific << totalDurationRecursiveCacheDamerauLevenshtein / TESTS << " ticks" << endl;
    }
}