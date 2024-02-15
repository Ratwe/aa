def standart(text, pattern):
    n = len(text)
    m = len(pattern)
    comparisons = 0

    for i in range(n - m + 1):
        j = 0
        while j < m and text[i + j] == pattern[j]:
            j += 1
            comparisons += 1
        if j == m:
            return i, comparisons

    return -1, comparisons
