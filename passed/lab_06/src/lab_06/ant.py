import itertools
from math import inf
from random import random

from matrix import get_random_matrix, print_matrix, get_file_matrix, input_matrix

from bruteforce import brute_force

FULL = 1
ANT = 2
BOTH = 3
MIN_PHEROMONE = 0.001
START_PHEROMON = 1


def get_cost(matrix, route):
    """
        Найти стоимость маршрута.
    """

    cur_cost = 0

    for num in range(len(route) - 1):
        start_city = route[num]
        end_city = route[num + 1]

        cur_cost += matrix[start_city][end_city]

    return cur_cost


def get_all_routes(cities):
    """
        Получить все
        возможные маршруты.
    """

    routes = []

    for route in itertools.permutations(cities, len(cities)):
        route = list(route)
        route.append(route[0])
        routes.append(route)

    return routes


def get_q(matrix, size):
    """
        Получить длину оптимального пути.
    """

    q = 0
    count = 0

    for i in range(size):
        for j in range(i + 1, size):
            q += matrix[i][j] * 2
            count += 2

    return q / count


def get_proximity(matrix, size):
    """
        Получить матрицу видимостей городов.

        Видимость города j из города i
        обратно пропорциональна расстоянию
        между этими городами.
    """

    proximity = [[0 for i in range(size)] for j in range(size)]

    for i in range(size):
        for j in range(i):
            proximity[i][j] = 1 / matrix[i][j]
            proximity[j][i] = proximity[i][j]

    return proximity


def get_visited_cities(cities, count_ants):
    """
        Получить посещенные города.

        Не те, которые надо посетить,
        чтобы все муравьи пошли по
        разным путям.
    """

    visited = [[] for _ in range(count_ants)]

    for ant in range(count_ants):
        visited[ant].append(cities[ant])

    return visited


def get_probability(pheromones, proximity, visited, a, b, ant, city_count):
    """
        Определить вероятность
        перехода k-ого муравья
        из города i в город j.
    """

    # Вероятности того, что муравей перейдет в город city
    probabilities = [0] * city_count

    # Муравей находится в последнем посещенном городе
    now_city = visited[ant][-1]

    for city in range(city_count):
        if city not in visited[ant]:

            # Желание муравья перейти в город city
            p = (pheromones[now_city][city] ** a) * \
                (proximity[now_city][city] ** b)

            probabilities[city] = p
        else:
            probabilities[city] = 0

    # Cумма желаний муравья перейти из текущего города
    # ко всем другим еще не посещенным городам
    sum_p = sum(probabilities)

    for city in range(city_count):
        probabilities[city] /= sum_p

    return probabilities


def choose_city(probabilities):
    """
        Выбор города
        случайным образом.
    """

    num = random()
    value = 0

    for i in range(len(probabilities)):
        value += probabilities[i]

        if value > num:
            return i


def check_route(i, j, route):
    """
        Проверка принадлежности
        дороги (i, j) маршруту.
    """

    if i in route:
        index_i = route.index(i)

        if j == route[index_i + 1]:
            return True

    return False


def update_pheromone(visited, matrix, pheromones, city_count, p, q, elite_ants_count, min_cost):
    """
        Обновление следов феромона.
    """

    for i in range(city_count):
        for j in range(city_count):
            add = 0

            for ant in range(city_count):
                if check_route(i, j, visited[ant]):
                    cost = get_cost(matrix, visited[ant])
                    add += q / cost

            pheromones[i][j] *= (1 - p)
            pheromones[i][j] += add + elite_ants_count * q / min_cost

            if pheromones[i][j] < MIN_PHEROMONE:
                pheromones[i][j] = MIN_PHEROMONE

    return pheromones




def ant_algorithm(matrix, size, a, b, p, iterations, elite_ants_count):
    """
        Муравьиный алгоритм.
    """

    cities = [i for i in range(size)]
    min_cost = inf
    min_route = None

    # Длина среднего пути (Ant Colony Optimization)
    # Q — регулируемый параметр, значение которого выбирают одного порядка с длиной оптимального маршрута
    q = get_q(matrix, size)

    # Матрица видимости всех городов
    proximity = get_proximity(matrix, size)
    # Матрица феромонов
    pheromones = [[START_PHEROMON for i in range(size)] for j in range(size)]
    count_ants = size

    for _ in range(iterations):
        # Номера всех городов
        # Начальные города, из которых муравьи начнут путь
        visited = get_visited_cities(cities, count_ants)

        for ant in range(count_ants):
            while len(visited[ant]) != count_ants:
                # Вероятностно-пропорциональное правило
                pk = get_probability(pheromones, proximity,
                                     visited, a, b, ant, size)

                # Выбор следующего города
                next_city = choose_city(pk)
                visited[ant].append(next_city)
            # Замкнуть маршрут
            visited[ant].append(visited[ant][0])

            # Получить стоимость полученного маршрута
            cur_cost = get_cost(matrix, visited[ant])

            if cur_cost < min_cost:
                min_cost = cur_cost
                min_route = visited[ant]

        # Обновить значения феромона на всех путях
        pheromones = update_pheromone(visited, matrix, pheromones, size, p, q, elite_ants_count, min_cost)

    return min_route, min_cost


def print_route(route, cost):
    """
        Печать маршрута и его стоимости.
    """

    for num in range(len(route)):
        if num != len(route) - 1:
            print(route[num] + 1, "->", end=" ")

    print(route[0] + 1)

    print("Его стоимость : ", cost)



