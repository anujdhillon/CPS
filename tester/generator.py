from random import randint, random
sa = randint(1, 50)
sb = randint(1, 50)
sc = randint(1, 50)
sd = randint(1, 50)
k = randint(1, sa*sb*sc*sd)
print(sa, sb, sc, sd, k)
for i in range(sa):
    print(randint(0, 0), end=" ")
print()
for i in range(sb):
    print(randint(0, 0), end=" ")
print()
for i in range(sc):
    print(randint(0, 0), end=" ")
print()
for i in range(sd):
    print(randint(0, 1), end=" ")
