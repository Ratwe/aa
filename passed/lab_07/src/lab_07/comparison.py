import csv
import random
import string

from KMP import kmp
from standart import standart


def print_file_content(filename):
    with open(filename, newline='') as csvfile:
        csv_reader = csv.reader(csvfile)
        for row in csv_reader:
            print(row)


def standart_test(text, pattern, iterations):
    total_comparisons = 0
    for _ in range(iterations):
        _, comparisons = standart(text, pattern)
        total_comparisons += comparisons
    return total_comparisons


def kmp_test(text, pattern, iterations):
    total_comparisons = 0
    for _ in range(iterations):
        _, comparisons = kmp(text, pattern)
        total_comparisons += comparisons
    return total_comparisons


def generate_text_and_pattern(text_length, pattern_length, pattern_at_end=True, occur=True):
    text = ''.join(random.choices(string.ascii_lowercase, k=text_length))
    start_index = None

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
    with open('results_comparison.csv', 'w', newline='', encoding='utf-8') as csvfile:
        csv_writer = csv.writer(csvfile)
        csv_writer.writerow(['Размер текста', 'Размер паттерна', 'Стандартный без вхождения', 'КМП без вхождения',
                             'Стандартный вхождение в начале', 'КМП вхождение в начале', 'Стандартный вхождение в конце', 'КМП вхождение в конце'])

        for pw in range(8, 16):
            size = 2 ** pw
            pattern_size = int(size / 32)
            print(size, pattern_size)

            text, pattern = generate_text_and_pattern(size, pattern_size, occur=False)
            standart_comparisons_no_occur = standart_test(text, pattern, iterations) / iterations
            kmp_comparisons_no_occur = kmp_test(text, pattern, iterations) / iterations
            text, pattern = generate_text_and_pattern(size, pattern_size, occur=True, pattern_at_end=False)
            standart_comparisons_begin_occur = standart_test(text, pattern, iterations) / iterations
            kmp_comparisons_begin_occur = kmp_test(text, pattern, iterations) / iterations
            text, pattern = generate_text_and_pattern(size, pattern_size, occur=True, pattern_at_end=True)
            standart_comparisons_end_occur = standart_test(text, pattern, iterations) / iterations
            kmp_comparisons_end_occur = kmp_test(text, pattern, iterations) / iterations

            csv_writer.writerow(
                [size, pattern_size, int(standart_comparisons_no_occur), int(kmp_comparisons_no_occur), int(standart_comparisons_begin_occur),
                 int(kmp_comparisons_begin_occur), int(standart_comparisons_end_occur), int(kmp_comparisons_end_occur)])


test()
print_file_content("results_comparison.csv")
