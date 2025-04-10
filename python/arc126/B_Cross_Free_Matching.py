from functools import cache
n, m = [int(x) for x in input().split()]
seg = [None]*m
for i in range(m):
    seg[i] = [int(x) for x in input().split()]
seg.sort()
@cache
def dfs(i, j):
    if i == n: return 0
    res = dfs(i+1, j)
    if seg[i][1] > j:
        res = max(res, 1+dfs(i+1, seg[i][1]))
    return res
print(dfs(0, 0))