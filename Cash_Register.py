s = input()

i, res = 0, 0
while i < len(s):
    if s[i] == '0' and i < len(s) and s[i+1] == '0':
        i+=1
    res+=1
    i+=1
print(res)