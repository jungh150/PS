from sys import stdin

n = int(stdin.readline())
data = list(map(int, stdin.readline().split()))
tmp = [0] * n
result = 0

def mergeSort(s, e):
    global result

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
            result += m - index1 + 1
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

print(result)