import os
import pandas as pd
import matplotlib.pyplot as plt

def plot_data(file_path, y_label):
    # Загрузка данных из CSV файла
    data = pd.read_csv(file_path, encoding='windows-1251')

    # Получение названий столбцов
    columns = data.columns

    # Извлечение данных для оси Y и остальных столбцов для оси X
    Y_column = columns[0]
    X_columns = columns[1:]

    # Создание графика
    plt.figure(figsize=(10, 6))  # размер графика

    # Построение графика для каждого столбца X
    for column in X_columns:
        plt.plot(data[Y_column], data[column], marker='o', label=column)

    # Настройка заголовка и меток осей
    plt.xlabel(Y_column)
    plt.ylabel(y_label)
    # plt.yscale('log')  # установка экспоненциальной шкалы для Y
    plt.legend()  # добавление легенды
    plt.grid(True)

    # Сохранение файла с расширением .pdf
    # plt.savefig(os.path.splitext(file_path)[0] + '_logscale.pdf', bbox_inches='tight')
    plt.savefig(os.path.splitext(file_path)[0] + '.pdf', bbox_inches='tight')

    plt.show()

# Вызов функции plot_data с указанным файлом и меткой для Y-оси
plot_data("time.csv", "Время (мс)")
