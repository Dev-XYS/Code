def A(x) :
    res = 1
    i =	1
    while i <= x :
        res *= i
        i += 1
    return res

def C(x, y) :
    res = 1
    i =	x
    while i > x	- y :
        res *= i
        i -= 1
    i = 1
    while i <= y :
        res /= i
        i += 1
    return res

d = raw_input().split()
n = (int)(d[0])
m = (int)(d[1])
print A(m) * (A(n + 2) * C(n + 3, m) - A(n + 1) * 2 * C(n + 2, m))
