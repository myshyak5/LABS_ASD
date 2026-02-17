class HashTable:
    def __init__(self, size):
        self.size = size
        self.table = [[] for _ in range(size)]

    def hash_function(self, key):
        total = 0
        for char in str(key):
            total += ord(char)
        return total % self.size

    def insert(self, key, value):
        index = self.hash_function(key)
        for i, (k, v) in enumerate(self.table[index]):
            if k == key:
                self.table[index][i] = (key, value)
                return
        self.table[index].append((key, value))

def read_file(filename):
    with open(filename, 'r', encoding='utf-8') as file:
        text = file.read()
    words = []
    for word in text.split():
        clean_word = ''.join(char for char in word if char.isalnum()).lower()
        if clean_word:
            words.append(clean_word)
    return words

def main():
    words = read_file("input.txt")  
    if not words:
        return
    size = 2 * len(set(words))
    hash_table = HashTable(size=size)
    word_count = {}
    for word in words:
        if word in word_count:
            word_count[word] += 1
        else:
            word_count[word] = 1
    for word, count in word_count.items():
        hash_table.insert(word, count)
    with open("result.txt", "w", encoding="utf-8") as file:    
        for i, bucket in enumerate(hash_table.table):
            if bucket:
                file.write(f"Ячейка {i}: {bucket}\n")
                
if __name__ == "__main__":
    main()