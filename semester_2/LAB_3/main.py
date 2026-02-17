def build_finite_automaton(pattern) -> list:
    m = len(pattern)
    ALPHABET_SIZE = 256
    transition = [[0] * ALPHABET_SIZE for _ in range(m + 1)]
    for state in range(m + 1):
        for ch in range(ALPHABET_SIZE):
            char = chr(ch)
            if state < m and char == pattern[state]:
                transition[state][ch] = state + 1
            else:
                for k in range(min(m, state + 1), 0, -1):
                    if pattern[k-1] == char and all(pattern[i] == pattern[state-k+1+i] for i in range(k-1)):
                        transition[state][ch] = k
                        break
    
    return transition

def finite_automaton_search(text, pattern) -> list:
    m = len(pattern)
    transition = build_finite_automaton(pattern)
    state = 0
    occurrences = []
    for i, char in enumerate(text):
        state = transition[state][ord(char) % 256]
        if state == m:
            occurrences.append(i - m + 1)
    return occurrences

def main():
    text = "ABABDABACDABABCABAB"
    pattern = "AB"
    positions = finite_automaton_search(text, pattern)
    print("Текст:", text)
    print("Образец:", pattern)
    print("Позиции вхождений:", positions)


if __name__ == "__main__":
    main()