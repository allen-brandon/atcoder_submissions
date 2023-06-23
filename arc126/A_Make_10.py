import time
t = int(input())

def solve(a, b, c):
    b = b//2
    res = 0
    x = min(b, c)
    res+=x
    b-=x
    c-=x
    print(a,b,c, res)
    if b:
        y = min(b, a//2)
        res+=y
        a-=y*2
        b-=y
    else:
        y = min(c//2, a)
        res+=y
        a-=y
        c-=y*2
    print(a,b,c, res)
    z = a//5
    a-=z*5
    print(a, b, c, res)
    return res+(a//5)

for _ in range(t):
    a, b, c = [int(x) for x in input().split()]
    time.sleep(1)
    print(solve(a, b, c))