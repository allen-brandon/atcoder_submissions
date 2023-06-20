from collections import defaultdict
from collections import deque
n = int(input())
ans = 0

adj = defaultdict(list)
for i in range(n):
    a, b = [int(x) for x in input().split()]
    adj[a].append(b)
    adj[b].append(a)
seen = {}
for node in adj:
    if node in seen: continue
    seen[node] = -1
    st = deque([node])
    cycle, count = 0, 1
    while st:
        node = st.pop()
        for nei in adj[node]:
            if nei in seen:
                if seen[node] != nei: cycle = 1
                continue
            count+=1
            st.append(nei)
            seen[nei] = node
    ans+=count-1+cycle
print(ans)