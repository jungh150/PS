from sys import stdin

n = int(stdin.readline())
data = []
tmp = [0] * n
for i in range(n):
    data.append(int(stdin.readline()))

def mergeSort(s, e):
    if e - s < 1:
        return

    m = (s + e) // 2
    mergeSort(s, m)
    mergeSort(m+1, e)

    for i in range(s, e+1):
        tmp[i] = data[i]

    k = s
    index1 = s
    index2 = m+1

    while index1 <= m and index2 <= e:
        if tmp[index1] > tmp[index2]:
            data[k] = tmp[index2]
            index2 += 1
            k += 1
        else:
            data[k] = tmp[index1]
            index1 += 1
            k += 1
    
    while index1 <= m:
        data[k] = tmp[index1]
        index1 += 1
        k += 1
    while index2 <= e:
        data[k] = tmp[index2]
        index2 += 1
        k += 1

mergeSort(0, n-1)

for i in data:
    print(i)