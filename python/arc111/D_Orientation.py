from collections import defaultdict
n, m = [int(x) for x in input().split()]
edges = []
adj = defaultdict(dict)
seen = {}
for i in range(m):
    edges.append([int(x) for x in input().split()])
c = [0] + [int(x) for x in input().split()]
for i, (a, b) in enumerate(edges):
    if c[a] == c[b]:
        adj[a][b] = i
        adj[b][a] = i

def dfs(node, depth):
    if depth == 998: return
    for nei in adj[node]:
        if adj[node][nei] in seen: continue
        seen[adj[node][nei]] = node
        dfs(nei, depth+1)

for i, (a, b) in enumerate(edges):
    if i in seen:
        if seen[i] == a:
            print("->")
        else:
            print("<-")
        continue
    if c[a] > c[b]:
        print("->")
    elif c[a] < c[b]:
        print("<-")
    else:
        print("->")
        seen[adj[a][b]] = a
        dfs(b, 1)