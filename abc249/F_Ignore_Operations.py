import heapq
n, k = [int(x) for x in input().split()]
queries = [[int(x) for x in input().split()] for i in range(n)]
h, x, msf = [], 0, 0
for i in range(n-1, -1, -1):
    t, y = queries[i]
    if t == 1:
        heapq.heappush(h, y)
        x+=y
    else:
        k-=1
        while len(h) > k:
            x -= heapq.heappop(h)
        msf = max(msf, x+y)
        
        
print(msf)