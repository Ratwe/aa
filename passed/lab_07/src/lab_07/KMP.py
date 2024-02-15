from prefix import get_prefix_array


def kmp(text, pattern):
    n = len(text)
    m = len(pattern)
    pi = get_prefix_array(pattern)
    q = 0
    comparisons = 0

    for i in range(n):
        while q > 0 and pattern[q] != text[i]:
            q = pi[q - 1]
            comparisons += 1
        comparisons += 1
        if pattern[q] == text[i]:
            q += 1
        if q == m:
            return i - m + 1, comparisons
    return -1, comparisons
