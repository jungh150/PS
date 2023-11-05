from sys import stdin
import sys

sys.setrecursionlimit(10**8)

n, k = map(int, stdin.readline().split())
data = list(map(int, stdin.readline().split()))

def swap(i, j):
    global data
    temp = data[i]
    data[i] = data[j]
    data[j] = temp

def quickSort(s, e):
    global data

    if s >= e:
        return

    m = (s + e) // 2
    swap(s, m)
    pivot = data[s]
    i = s + 1
    j = e

    while i <= j:
        while i <= e and data[i] < pivot:
            i += 1
        while j >= s and data[j] > pivot:
            j -= 1
        if i < j:
            swap(i, j)
            i += 1
            j -= 1
    
    data[s] = data[j]
    data[j] = pivot

    quickSort(s, j-1)
    quickSort(j+1, e)

quickSort(0, n-1)
print(data[k-1])