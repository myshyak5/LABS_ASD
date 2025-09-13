x = int(input())

def maxDeg(b):
    n = 0
    while b**n <= x:
        n += 1
    return n

max_k, max_l, max_m = maxDeg(3), maxDeg(5), maxDeg(7)
final_res = set()

for k in range(max_k+1):
    for l in range(max_l+1):
        multKL = 3**k * 5**l
        if multKL > x:
            break
        for m in range(max_m+1):
            res = multKL * 7**m
            if res > x:
                break
            final_res.add(res)
final_res = sorted(final_res)
print(*final_res)