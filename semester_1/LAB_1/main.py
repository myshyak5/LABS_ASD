dict_br = {
    "(": ")",
    "[": "]",
    "{": "}"
}

stack = []
inp = input("Введите строку: ")

for char in inp:
    if char in dict_br:
        stack.append(char)
    elif char in dict_br.values():
        if not stack:
            print("Строка не существует")
            exit()
        last_open = stack[-1]
        if dict_br[last_open] == char:
            stack.pop()
        else:
            print("Строка не существует")
            exit()

if len(stack) == 0:
    print("Строка существует")
else:
    print("Строка не существует")