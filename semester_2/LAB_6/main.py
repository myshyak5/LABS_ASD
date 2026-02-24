def rabin_karp_search(text, pattern):
    n = len(text)
    m = len(pattern)
    positions = []
    if m > n or m == 0:
        return positions
    base = 256
    prime = int(1e9) + 7
    pattern_hash = 0
    text_hash = 0
    for i in range(m):
        pattern_hash = (pattern_hash * base + ord(pattern[i])) % prime
        text_hash = (text_hash * base + ord(text[i])) % prime
    h = 1
    for i in range(m - 1):
        h = (h * base) % prime
    for i in range(n - m + 1):
        if pattern_hash == text_hash:
            match = True
            for j in range(m):
                if text[i + j] != pattern[j]:
                    match = False
                    break
            if match:
                positions.append(i)
        if i < n - m:
            text_hash = (base * (text_hash - ord(text[i]) * h) + ord(text[i + m])) % prime
            if text_hash < 0:
                text_hash += prime
    return positions

if __name__ == "__main__":
    text = "ABABDABACDABABCABAB"
    pattern = "AB"
    positions = rabin_karp_search(text, pattern)
    
    print("Текст:", text)
    print("Образец:", pattern)
    print("Позиции вхождений:", positions)