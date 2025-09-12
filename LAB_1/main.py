dict_br = {
    "(": ")",
    "[": "]",
    "{": "}"
}
stack = []
inp = str(input())
for i in inp:
    for k, v in dict_br.items():
        if i == k:
            stack.append(i)
        elif i == v:
            if k in stack:
                stack.remove(k)
            else:
                stack.append(i)
                break
if len(stack) == 0: print("Yes")
else: print("No")