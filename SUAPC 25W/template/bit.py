#부분집합 구하기

arr = [1, 2, 3]
n = len(arr)

for i in range(1 << n):
    subset = [arr[j] for j in range(n) if (i & (1 << j))]
    print(subset)
