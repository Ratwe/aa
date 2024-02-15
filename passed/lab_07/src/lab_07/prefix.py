def get_prefix_array(x):
    m = len(x)
    pi = [0] * m
    k = 0

    for q in range(1, m):
        while k > 0 and x[k] != x[q]:
            k = pi[k - 1]
        if x[k] == x[q]:
            k += 1
        pi[q] = k

    return pi
