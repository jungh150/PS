from sys import stdin

task = [0 for i in range(0, 31)]

for _ in range(28):
    task[int(stdin.readline())] = 1

for i in range(1, 31):
    if task[i] == 0:
        print(i)