from functools import cache
import math
h, w = [int(x) for x in input().split()]
arr = [None]*h
for i in range(h):
    arr[i] = [int(x) for x in input().split()]
d = [(-1,0),(0,1),(1,0),(0,-1)]
inf = math.inf
@cache
def dfs(i, jSwap, kSwap):
    if i == 0:
        return min(dfs(1, 0, 0), dfs(1, 1, 0)+1)
    #Check only against previous row
    #res[0]: don't swap
    #res[1]: swap
    res = [0, 0]
    for swap in range(2):
        #Make sure previous row is valid with this swap choice
        for j in range(w):
            bit = jSwap^arr[i-1][j]
            isolated = 1
            for di, dj in d:
                if 0 <= i-1+di < h and 0 <= j+dj < w:
                    other =  swap^arr[i][j] if di == 1 else kSwap^arr[i-2][j] if di == -1 else jSwap^arr[i-1][j+dj]
                    if bit ^ other: continue
                    isolated = 0
                    break
            #An isolated square was found. Return impossible.
            if isolated:
                res[swap] = inf
                break
    #Return 0 if possible or inf if impossible
    if i == h: return min(res)
    #This swap choice is valid. Return the min from here on out.
    for swap in range(2):
        if res[swap] != inf: res[swap] = dfs(i+1, swap, jSwap)
    res[1]+=1
    return min(res)
print(dfs(0, 0, 0) if dfs(0, 0, 0) != inf else -1)