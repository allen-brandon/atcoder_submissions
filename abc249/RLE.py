from time import process_time
start = process_time()
n, mod = [int(x) for x in input().split()]
dp = [[0]*(n+1) for _ in range(n+1)]
dp[1][2] = 26
for i in range(2, n+1):
    if i < 10:
        dp[i][2] += 26
    elif i < 100:
        dp[i][3] += 26
    elif i < 1000:
        dp[i][4] += 26
    else:
        dp[i][5] += 26
    if not i % 100:
        current_time = process_time()
        print("Epoch: ", i)
        print(current_time)
    for j in range(n+1):
        dp[i][j] = dp[i-1][j]
        #Add in k = 2
        if i >= 1 and j >= 2:
            dp[i][j] += (dp[i-1][j-2]-dp[i-min(10, i)][j-2])*25
        #Add in k = 3
        if i >= 10 and j >= 3:
            dp[i][j] += (dp[i-10][j-3]-dp[i-min(100, i)][j-3])*25
        #Add in k = 4
        if i >= 100 and j >= 4:
            dp[i][j] += (dp[i-100][j-4]-dp[i-min(1000, i)][j-4])*25
        #Add in k = 5
        if i >= 1000 and j >= 5:
            dp[i][j] += (dp[i-1000][j-5]-dp[i-min(10000, i)][j-5])*25
            dp[i][j] %= mod
        
print(sum(dp[n][:-1])%mod)
print(dp[-1])
#for row in dp: print(row)