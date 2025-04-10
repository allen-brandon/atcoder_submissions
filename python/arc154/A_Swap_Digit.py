mod = 998244353
n, a, b = int(input()), list(input()), list(input())
for i in range(n):
    a[i], b[i] = max(a[i], b[i]), min(a[i], b[i])
x, y = 0, 0
for i in range(n):
    x+=int(a[n-1-i])*pow(10, i, mod)
    y+=int(b[n-1-i])*pow(10, i, mod)
print((x%mod)*(y%mod)%mod)