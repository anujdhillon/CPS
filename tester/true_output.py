sa, sb, sc, sd, k = list(map(int, input().split()))
a = list(map(int, input().split()))
b = list(map(int, input().split()))
c = list(map(int, input().split()))
d = list(map(int, input().split()))

a1, a2 = [], []

for x in a:
    for y in b:
        a1.append(x+y)

for x in c:
    for y in d:
        a2.append(x+y)

fin = []

for x in a1:
    for y in a2:
        fin.append(x*y)
fin.sort()
print(fin[k-1])
