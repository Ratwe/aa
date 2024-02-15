import itertools


def calculate_cost(matrix, route):
    return sum(matrix[start_city][end_city] for start_city, end_city in zip(route, route[1:]))


def get_all_routes(n):
    cities = list(range(n))
    permutations = list(itertools.permutations(cities))
    valid_paths = [p + (p[0],) for p in permutations]
    return valid_paths


def brute_force(n, matrix):
    routes = get_all_routes(n)
    min_cost = float('inf')
    min_route = None
    for route in routes:
        current_cost = calculate_cost(matrix, route)
        if current_cost < min_cost:
            min_cost = current_cost
            min_route = route
    return min_route, min_cost


test_matrix = [[0, 10, 15, 20, 25], [10, 0, 35, 5, 10], [15, 35, 0, 30, 5], [20, 5, 30, 0, 15], [25, 10, 5, 15, 0]]

n = 5

min_route, min_cost = brute_force(n, test_matrix)