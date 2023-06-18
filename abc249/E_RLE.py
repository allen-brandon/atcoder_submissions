n, mod = [int(x) for x in input().split()]
if n == 1:
    print(0)
    quit()
dp = [[0]*(n+1) for _ in range(n+1)]

powers = [10**x for x in range(5)]

#Insert initial segments
for k in range(4):
    for i in range(powers[k], min(n+1, powers[k+1])):
        dp[i][k+2] += 26

#Insert subsequent segments
for i in range(2, n+1):
    for j in range(n+1):
        dp[i][j] += dp[i-1][j]
        for k in range(4):
            if i >= powers[k] and j >= k+2:
                dp[i][j] += (dp[i-powers[k]][j-k-2]-dp[i-min(powers[k+1], i)][j-k-2])*25
        dp[i][j] %= mod
print((sum(dp[n][:-1])-sum(dp[n-1][:-1]))%mod)