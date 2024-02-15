#include <iostream>
#include "conveyor.h"
#include "time.h"
#include "utils.h"

using namespace std;
using milliseconds = chrono::milliseconds;

// Определение констант для выборов меню
const int LINEAR_PROCESSING = 1;
const int PARALLEL_PROCESSING = 2;
const int TIME_MEASUREMENTS = 3;
const int EXIT_PROGRAM = 0;

// Функция вывода меню
void printMenu() {
    cout << "\n\n\nВыберите необходимую задачу:\n";
    cout << "1 - запустить последовательную обработку\n";
    cout << "2 - запустить параллельную обработку\n";
    cout << "3 - замеры времени реализации\n";
    cout << "0 - выход\n\n";
    cout << "Ваш выбор: ";
}

int ask_params(int& reqs, int& s, int& x) {
    cout << "Введите кол-во заявок, длину искомой подстроки, кол-во сегментов строки: ";
    cin >> reqs >> s >> x;
    if (s > 10 || s < 6) {
        cout << "Длина подстроки должна быть в промежутке [6; 10]" << endl;
        return 1;
    }
    return 0;
}

int ask_time_params(int& reqs1, int& reqs2, int& step, int& s, int& x) {
    cout << "Введите мин. и макс. кол-во заявок, шаг, длину искомой подстроки, кол-во сегментов строки: ";
    cin >> reqs1 >> reqs2 >> step >> s >> x;
    if (s > 10 || s < 6) {
        cout << "Длина подстроки должна быть в промежутке [6; 10]" << endl;
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

        // Очистка буфера ввода в случае некорректного ввода
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nНеверный ввод, повторите попытку.\n\n";
            continue;
        }

        switch (choice) {
            case LINEAR_PROCESSING:
                if (ask_params(reqs, s, x)) {
                    cout << "\nНеверный ввод, повторите попытку.\n\n";
                    continue;
                }
                clear_file("log.txt");
                linear(reqs, s, x);
                break;
            case PARALLEL_PROCESSING:
                if (ask_params(reqs, s, x)) {
                    cout << "\nНеверный ввод, повторите попытку.\n\n";
                    continue;
                }
                clear_file("log.txt");
                parallel(reqs, s, x);
                break;
            case TIME_MEASUREMENTS:
                if (ask_time_params(reqs1, reqs2, step, s, x)) {
                    cout << "\nНеверный ввод, повторите попытку.\n\n";
                    continue;
                }
                clear_file("time.csv");
                write_in_file("time.csv", "Заявки (шт), Один поток, Два потока", mtx);
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
                cout << "\nНеверный ввод, повторите попытку.\n\n";
                break;
        }
    } while (choice != EXIT_PROGRAM);

    return 0;
}
