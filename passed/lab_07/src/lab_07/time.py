import csv
import random
import string

from KMP import kmp
from plot import plot_data
from standart import standart
from time import perf_counter


def print_file_content(filename):
    with open(filename, newline='') as csvfile:
        csv_reader = csv.reader(csvfile)
        for row in csv_reader:
            print(row)


def standart_test(text, pattern, iterations):
    total_time = 0.0
    for _ in range(iterations):
        start_time = perf_counter()
        standart(text, pattern)
        end_time = perf_counter()
        total_time += end_time - start_time
    return total_time


def kmp_test(text, pattern, iterations):
    total_time = 0.0
    for _ in range(iterations):
        start_time = perf_counter()
        kmp(text, pattern)
        end_time = perf_counter()
        total_time += end_time - start_time
    return total_time


def generate_text_and_pattern(text_length, pattern_length, pattern_at_end=True, occur=True, randoming=False):
    text = ''.join(random.choices(string.ascii_lowercase, k=text_length))
    start_index = None

    if randoming is True:
        start_index = random.randint(0, text_length - pattern_length)
        pattern = text[start_index:start_index + pattern_length]

    if not occur:
        pattern = ''.join(random.choices(string.ascii_lowercase, k=pattern_length))
    else:
        if pattern_at_end:
            start_index = max(text_length - pattern_length, 0)
        elif not pattern_at_end:
            start_index = 0

        pattern = text[start_index:start_index + pattern_length]

    return text, pattern


def test():
    iterations = 100
    with open('results.csv', 'w', newline='') as csvfile:
        csv_writer = csv.writer(csvfile)
        csv_writer.writerow(['Размер текста', 'Размер паттерна', 'Стандартный', 'КМП',])

        for pw in range(8, 16):
            size = 2 ** pw
            pattern_size = 100
            print(size, pattern_size)

            text, pattern = generate_text_and_pattern(size, pattern_size, randoming=True)
            standart_time = standart_test(text, pattern, iterations) / iterations
            kmp_time = kmp_test(text, pattern, iterations) / iterations

            csv_writer.writerow([size, pattern_size, standart_time, kmp_time])


test()
print_file_content("results.csv")
plot_data("results.csv", "Время (секунд)")