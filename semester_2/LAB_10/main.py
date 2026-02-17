def egg_drop(eggs, floors):
    dp = [[0] * (floors + 1) for _ in range(eggs + 1)]
    for f in range(1, floors + 1):
        dp[1][f] = f
    for e in range(1, eggs + 1):
        dp[e][1] = 1
        dp[e][0] = 0
    for e in range(2, eggs + 1):
        for f in range(2, floors + 1):
            dp[e][f] = float('inf')
            for x in range(1, f + 1):
                res = 1 + max(dp[e-1][x-1], dp[e][f-x])
                if res < dp[e][f]:
                    dp[e][f] = res
    return dp[eggs][floors]

if __name__ == "__main__":
    print(egg_drop(2, 100))