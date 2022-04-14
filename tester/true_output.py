import math

l, r = list(map(int, input().split()))
ans = 1
for i in range(l, r+1):
    for j in range(i+1, r+1):
        if(math.gcd(i, j) == 1):
            ans = max(ans, j-i)
print(ans)
