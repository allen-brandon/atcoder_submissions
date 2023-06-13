from collections import deque
s = input()
n = len(s)
seen = set()
st = deque([set()])
for i in range(n):
    match s[i]:
        case '(':
            st.append(set())
        case ')':
            seen -= st[-1]
            st.pop()
        case _:
            if s[i] in seen:
                print("No")
                quit()
            seen.add(s[i])
            st[-1].add(s[i])
print("Yes")