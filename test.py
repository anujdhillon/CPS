s = input().split(',')
words = []
for part in s:
    parts = part.split(';')
    for word in parts:
        words.append(word)

l1 = []
l2 = []

for word in words:
    if(word.isnumeric() and (word[0] != '0' or (word[0] == '0' and len(word) == 1))):
        l1.append(word)
    else:
        l2.append(word)
if not len(l1):
    print('-')
else:
    print('"', end="")
    print(",".join(l1), end="")
    print('"')

if not len(l2):
    print('-')
else:
    print('"', end="")
    print(",".join(l2), end="")
    print('"')
