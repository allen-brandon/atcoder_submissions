import heapq
n, k = [int(x) for x in input().split()]
queries = [[int(x) for x in input().split()] for i in range(n)]
h, st, y, msf = [], [], 0, 0
for i in range(n-1, -1, -1):
    t, y = queries[i]
    if t == 1:
        heapq.heappush(h, -y)
    else:
        st.append((y, k-len(st)))
        if len(st) == k: break
print(msf)