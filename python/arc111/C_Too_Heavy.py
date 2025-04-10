n = int(input())
a = [int(x) for x in input()]
b = [int(x) for x in input()]
p = [int(x) for x in input()]
#Make sure it's possible
for i in range(n):
    if b[p[i]]: break