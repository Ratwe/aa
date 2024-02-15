from ant import ant_algorithm, print_route, ANT, FULL, BOTH
from bruteforce import brute_force
from matrix import input_matrix, get_file_matrix, print_matrix, get_random_matrix


def menu(alg_type):
    """
        Решение задачи
        коммивояжера.
    """

    try:
        count = int(input("\nВведите число городов: "))
    except:
        print("\nНеверно введено число городов.\n")
        return

    input_type = int(input(
        """
        Выберите способ ввода матрицы стоимостей:
            1. Ручной ввод
            2. Случайная матрица
            3. Загрузить из файла
        Выбор: """))

    matrix = None
    if input_type == 1:
        matrix = input_matrix(count)
    elif input_type == 2:
        low = int(input("\nВведите нижнюю границу стоимостей: "))
        top = int(input("Введите верхнюю границу стоимостей: "))

        matrix = get_random_matrix(count, low, top)
    elif input_type == 3:
        file = input("Введите название файла: ")
        matrix = get_file_matrix(file, count)

    print("\nИсходная матрица стоимостей:")
    print_matrix(matrix)

    if alg_type == FULL or alg_type == BOTH:
        route1, cost1 = brute_force(count, matrix)

        print("\n\n=== Полный перебор === ")
        print("Самый короткий маршрут: ")
        print_route(route1, cost1)
    if alg_type == ANT or alg_type == BOTH:
        a = float(input("\nВведите параметр α: "))
        # a - сила желания пойти в ближайший город
        # b - сила желания пойти туда, где больше феромона
        b = 1 - a
        p = float(input("Введите коэффициент испарения: "))
        iterations = int(input("Введите кол-во итераций: "))
        elite_ants_count = int(input("Введите кол-во элитных муравьёв: "))

        route2, cost2 = ant_algorithm(matrix, count, a, b, p, iterations, elite_ants_count)

        print("\n\n=== Муравьиный алгоритм === ")
        print("Самый короткий маршрут: ")
        print_route(route2, cost2)


def parameterization():
    """
        Параметризация.
    """

    alpha = [k / 10 for k in range(1, 10)]
    evaporation = [k / 10 for k in range(1, 10)]
    days = [10, 25, 50, 100, 200, 300, 400, 500]
    count = 10

    matrix1 = get_file_matrix("data/m1.txt", count)
    matrix2 = get_file_matrix("data/m2.txt", count)
    matrix3 = get_file_matrix("data/m3.txt", count)

    _, ideal1 = brute_force(count, matrix1)
    _, ideal2 = brute_force(count, matrix2)
    _, ideal3 = brute_force(count, matrix3)

    result1 = open("data/m1_result.txt", "w")
    result2 = open("data/m2_result.txt", "w")
    result3 = open("data/m3_result.txt", "w")

    sep = " & "
    ender = " \\\\"

    stage = 0
    count_all = len(alpha) * len(evaporation)

    for a in alpha:
        b = 1 - a
        for p in evaporation:
            stage += 1
            for day in days:
                _, first = ant_algorithm(matrix1, count, a, b, p, day, elite_ants_count=0)
                _, second = ant_algorithm(matrix2, count, a, b, p, day, elite_ants_count=0)
                _, third = ant_algorithm(matrix3, count, a, b, p, day, elite_ants_count=0)

                str1 = "%4.1f%s%4.1f%s%4d%s%5d%s%5d%s\n" \
                       % (a, sep, p, sep, day, sep, ideal1, sep, first - ideal1, ender)

                str2 = "%4.1f%s%4.1f%s%4d%s%5d%s%5d%s\n" \
                       % (a, sep, p, sep, day, sep, ideal2, sep, second - ideal2, ender)

                str3 = "%4.1f%s%4.1f%s%4d%s%5d%s%5d%s\n" \
                       % (a, sep, p, sep, day, sep, ideal3, sep, third - ideal3, ender)

                result1.write(str1)
                result2.write(str2)
                result3.write(str3)

            print("Progress: %3d%s" % ((stage / count_all) * 100, "%"))

    result1.close()
    result2.close()
    result3.close()


# Define function to read data from file
def read_file(filename):
    data = []
    with open(filename, 'r') as file:
        for line in file:
            # Split each line by '&' and remove leading/trailing whitespace
            line_data = [item.strip() for item in line.strip().split('&')]
            # Append the line data to the list
            data.append(line_data)
    return data


# Define function to compare three files
def compare_files(file1, file2, file3):
    data1 = read_file(file1)
    data2 = read_file(file2)
    data3 = read_file(file3)

    row4_avg = []  # Список для хранения среднего значения row4 на каждой итерации

    for i in range(len(data1)):
        row1 = [float(value.strip(' \\\\')) for value in data1[i]]
        row2 = [float(value.strip(' \\\\')) for value in data2[i]]
        row3 = [float(value.strip(' \\\\')) for value in data3[i]]

        # Подсчет среднего значения row4 на текущей итерации
        row4_avg.append((row1[4] + row2[4] + row3[4]) / 3)

        if row1[4] == 0 or row2[4] == 0 or row3[4] == 0:
            print(f"File 1: {row1}")
            print(f"File 2: {row2}")
            print(f"File 3: {row3}")
            print("---------------------------------------------")

    # Находим Y строк с наименьшим средним значением row4
    sorted_indices = sorted(range(len(row4_avg)), key=lambda k: row4_avg[k])
    for i in range(10):
        idx = sorted_indices[i]
        print(f"Row {idx + 1}: {data1[idx]}, {data2[idx]}, {data3[idx]}")


# parameterization()
# compare_files("data/m1_result.txt", "data/m2_result.txt", "data/m3_result.txt")

