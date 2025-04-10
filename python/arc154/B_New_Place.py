from collections import Counter
n, s, t = int(input()), input(), input()
if Counter(s) != Counter(t):
    print(-1)
    quit()
j = n-1
for i in range(n-1, -1, -1):
    if t[i] == s[j]:
        j-=1
print(j+1)