def prefix_function(pattern):
    m = len(pattern)
    pi = [0] * m
    j = 0
    for i in range(1, m):
        while j > 0 and pattern[i] != pattern[j]:
            j = pi[j - 1]
        if pattern[i] == pattern[j]:
            j += 1
        pi[i] = j
    return pi

def kmp_search(text, pattern):
    if not pattern:
        return []
    n = len(text)
    m = len(pattern)
    if m > n:
        return []
    pi = prefix_function(pattern)
    result = []
    j = 0
    for i in range(n):
        while j > 0 and text[i] != pattern[j]:
            j = pi[j - 1]
        if text[i] == pattern[j]:
            j += 1
        if j == m:
            result.append(i - m + 1)
            j = pi[j - 1]
    return result

def main():
    text = "ABABDABACDABABCABAB"
    pattern = "AB"
    positions = kmp_search(text, pattern)
    print("Текст:", text)
    print("Образец:", pattern)
    print("Позиции вхождений:", positions)


if __name__ == "__main__":
    main()