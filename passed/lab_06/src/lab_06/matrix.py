from random import randint


def input_matrix(size):
    """
        Ввод матрицы.
    """

    matrix = []

    print("\nВведите матрицу стоимостей:")
    for i in range(size):
        matrix.append([])

        for j in range(size):
            matrix[i].append(int(input()))

    return matrix


def print_matrix(matrix):
    """
        Печать матрицы.
    """

    for i in range(len(matrix[0])):
        for j in range(len(matrix[0])):
            print(matrix[i][j], end=" ")

        print("")


def get_random_matrix(size, low, top):
    """
        Случайная матрица.
    """

    matrix = [[0 for i in range(size)] for j in range(size)]

    for i in range(size):
        for j in range(i + 1, size):
            value = randint(low, top)
            # шанс 20%, что ячейка = гора, через которую нельзя пройти
            # if randint(0, 5) == 0:
            #     matrix[i][j] = float('inf')
            #     matrix[j][i] = float('inf')
            #     continue
            matrix[i][j] = value
            value = randint(low, top)
            matrix[j][i] = value

    return matrix


def get_file_matrix(file, size):
    """
        Получить матрицу из файла.
    """

    f = open(file, "r")

    matrix = [[0 for i in range(size)] for j in range(size)]

    i = 0

    for row in f.readlines():
        j = 0
        for num in row.split():
            matrix[i][j] = int(num)
            j += 1
        i += 1

    f.close()

    return matrix


def write_random_matrix_to_file(filename, size, low, top):
    """
    Генерирует случайную матрицу и записывает ее в файл.
    """
    matrix = get_random_matrix(size, low, top)

    with open(filename, 'w') as file:
        for row in matrix:
            file.write(' '.join(str(elem) for elem in row) + '\n')


write_random_matrix_to_file("data/m2.txt", 10, 1, 9)
