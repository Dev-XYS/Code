d = { 0:0, 1:1 }

def solve(x) :
    if x in d :
        return d[x]
    if x & 1 == 1 :
        d[x] = solve(x >> 1) + solve((x >> 1) + 1)
    else :
        d[x] = solve(x >> 1)
    return d[x]

T = int(raw_input())
for i in range(T) :
    print(solve(int(raw_input())))
