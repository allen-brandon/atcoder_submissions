t = int(input())

def solve(n, a, b):
    for i in range(n):
        if a[i] != b[0]: continue
        dif, k = 0, i
        for j in range(n):
            #Stopped working on this line:
            if b[j] != a[i+j]: break
        else:
            if dif: return "Yes"
    return "No"
        









for _ in range(t):
    n, a, b = int(input()), [int(x) for x in input().split()], [int(x) for x in input().split()]
    print(solve(n, a, b))