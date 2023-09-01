import sys

data = sys.stdin.readline().strip()
alpha = [0] * 26

for i in range(0, len(data)) :
    if ord(data[i]) < 91 :
        alpha[ord(data[i])-65] += 1
    else :
        alpha[ord(data[i])-97] += 1

maxIndex = 0
max = alpha[0]
count = 0

for i in range(0, 26) :
    if alpha[i] > max :
        max = alpha[i]
        maxIndex = i

for i in range(0, 26) :
    if max == alpha[i] :
        count += 1

if count == 1 :
    print(chr(maxIndex+65))
else :
    print("?")