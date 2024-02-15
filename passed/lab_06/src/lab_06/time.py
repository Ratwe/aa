import csv
from ant import ant_algorithm
from bruteforce import brute_force
from matrix import get_random_matrix
from plot import plot_data
from time import perf_counter, time  # Используем time вместо time

def print_file_content(filename):
    with open(filename, newline='') as csvfile:
        csv_reader = csv.reader(csvfile)
        for row in csv_reader:
            print(row)


def bruteforce_test(matrix, iterations):
    total_time = 0.0  # Изменяем на float
    for _ in range(iterations):
        start_time = perf_counter()  # Изменяем на perf_counter()
        brute_force(len(matrix), matrix)
        end_time = perf_counter()  # Изменяем на perf_counter()
        total_time += end_time - start_time
    return total_time  # Убираем Decimal

def ant_algorithm_test(matrix, iterations):
    total_time = 0.0  # Изменяем на float
    for _ in range(iterations):
        start_time = perf_counter()  # Изменяем на perf_counter()
        ant_algorithm(matrix, len(matrix), 0.5, 0.2, 0.5, 1, 1)
        end_time = perf_counter()  # Изменяем на perf_counter()
        total_time += end_time - start_time
    return total_time  # Убираем Decimal

def test():
    iterations = 100
    with open('results.csv', 'w', newline='') as csvfile:
        csv_writer = csv.writer(csvfile)
        csv_writer.writerow(['Matrix Size', 'Bruteforce Time', 'Ant Algorithm Time'])

        for size in range(2, 11):
            print(size)
            matrix = get_random_matrix(size, 1, 100)

            bruteforce_time = bruteforce_test(matrix, iterations)
            ant_algorithm_time = ant_algorithm_test(matrix, iterations)

            csv_writer.writerow([size, bruteforce_time, ant_algorithm_time])

test()
# plot_data("results.csv", "Время (нс)")
print_file_content("results.csv")

