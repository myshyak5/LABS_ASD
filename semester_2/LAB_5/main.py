def badCharHeuristic(string, size):
    badChar = [-1] * 256
    for i in range(size):
        badChar[ord(string[i])] = i
    return badChar

def bm_substring_search(text, pattern):
    m = len(pattern)
    n = len(text)
    badChar = badCharHeuristic(pattern, m)
    s = 0
    positions = [] 
    
    while s <= n - m:
        j = m - 1
        while j >= 0 and pattern[j] == text[s + j]:
            j -= 1
        if j < 0:
            positions.append(s)
            if s + m < n:
                s += m - badChar[ord(text[s + m])]
            else:
                s += 1
        else:
            s += max(1, j - badChar[ord(text[s + j])])
    return positions


if __name__ == "__main__":
    text = "ABABDABACDABABCABAB"
    pattern = "AB"
    positions = bm_substring_search(text, pattern)
    
    print("\nТекст:", text)
    print("Образец:", pattern)
    print("Позиции вхождений:", positions)