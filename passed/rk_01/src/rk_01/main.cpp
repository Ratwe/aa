#include <iostream>
#include "conveyor.h"
#include "time.h"
#include "utils.h"

using namespace std;
using milliseconds = chrono::milliseconds;

// ����������� �������� ��� ������� ����
const int LINEAR_PROCESSING = 1;
const int PARALLEL_PROCESSING = 2;
const int TIME_MEASUREMENTS = 3;
const int EXIT_PROGRAM = 0;

// ������� ������ ����
void printMenu() {
    cout << "\n\n\n�������� ����������� ������:\n";
    cout << "1 - ��������� ���������������� ���������\n";
    cout << "2 - ��������� ������������ ���������\n";
    cout << "3 - ������ ������� ����������\n";
    cout << "0 - �����\n\n";
    cout << "��� �����: ";
}

int ask_params(int& reqs, int& s, int& x) {
    cout << "������� ���-�� ������, ����� ������� ���������, ���-�� ��������� ������: ";
    cin >> reqs >> s >> x;
    if (s > 10 || s < 6) {
        cout << "����� ��������� ������ ���� � ���������� [6; 10]" << endl;
        return 1;
    }
    return 0;
}

int ask_time_params(int& reqs1, int& reqs2, int& step, int& s, int& x) {
    cout << "������� ���. � ����. ���-�� ������, ���, ����� ������� ���������, ���-�� ��������� ������: ";
    cin >> reqs1 >> reqs2 >> step >> s >> x;
    if (s > 10 || s < 6) {
        cout << "����� ��������� ������ ���� � ���������� [6; 10]" << endl;
        return 1;
    }
    return 0;
}



int main() {
    setlocale(LC_ALL, "rus");

    int choice = NULL;
    int reqs = NULL;
    int s = NULL;
    int x = NULL;
    int reqs1 = NULL;
    int reqs2 = NULL;
    int step = NULL;
    mutex mtx;

    do {
        printMenu();
        cin >> choice;

        // ������� ������ ����� � ������ ������������� �����
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n�������� ����, ��������� �������.\n\n";
            continue;
        }

        switch (choice) {
            case LINEAR_PROCESSING:
                if (ask_params(reqs, s, x)) {
                    cout << "\n�������� ����, ��������� �������.\n\n";
                    continue;
                }
                clear_file("log.txt");
                linear(reqs, s, x);
                break;
            case PARALLEL_PROCESSING:
                if (ask_params(reqs, s, x)) {
                    cout << "\n�������� ����, ��������� �������.\n\n";
                    continue;
                }
                clear_file("log.txt");
                parallel(reqs, s, x);
                break;
            case TIME_MEASUREMENTS:
                if (ask_time_params(reqs1, reqs2, step, s, x)) {
                    cout << "\n�������� ����, ��������� �������.\n\n";
                    continue;
                }
                clear_file("time.csv");
                write_in_file("time.csv", "������ (��), ���� �����, ��� ������", mtx);
                for (int i = reqs1; i <= reqs2; i += step) {
                    clear_file("log.txt");
                    milliseconds linear_nano = linear_time(i, s, x);
                    clear_file("log.txt");
                    milliseconds parallel_nano = parallel_time(i, s, x);
                    write_to_csv(i, linear_nano, parallel_nano, "time.csv");
                }
                break;
            case EXIT_PROGRAM:
                break;
            default:
                cout << "\n�������� ����, ��������� �������.\n\n";
                break;
        }
    } while (choice != EXIT_PROGRAM);

    return 0;
}
