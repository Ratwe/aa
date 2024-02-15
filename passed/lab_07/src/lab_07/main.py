import random
import string

from KMP import kmp


def generate_random_string(length):
    return ''.join(random.choices(string.ascii_lowercase, k=length))


def find_substring_menu():
    print("Выберите действие:")
    print("1. Ввести строку и подстроку вручную")
    print("2. Сгенерировать случайные строку и подстроку")
    print("0. Выход")
    choice = input("Ваш выбор (1 или 2): ")

    if choice == '1':
        text = input("Введите строку: ")
        pattern = input("Введите подстроку для поиска: ")
    elif choice == '2':
        text_length = int(input("Введите длину строки: "))
        pattern_length = int(input("Введите длину подстроки: "))
        text = generate_random_string(text_length)
        pattern = generate_random_string(pattern_length)
        print("Сгенерированная строка:", text)
        print("Сгенерированная подстрока для поиска:", pattern)
    else:
        print("Выход.")
        return 0

    algorithm_choice = input("Выберите алгоритм для поиска (1 - стандартный, 2 - КМП): ")

    if algorithm_choice == '1':
        index = text.find(pattern)
        if index != -1:
            print("Подстрока найдена в позиции", index)
        else:
            print("Подстрока не найдена в строке.")
    elif algorithm_choice == '2':
        index = kmp(text, pattern)
        if index != -1:
            print("Подстрока найдена в позиции", index)
        else:
            print("Подстрока не найдена в строке.")
    else:
        print("Неправильный выбор алгоритма.")

    return 1


# Example usage
res = 1
while res:
    res = find_substring_menu()
