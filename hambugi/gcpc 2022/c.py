import sys
input = sys.stdin.readline
n,q = map(int,input().split())

blocked = set()

def check(start,end,n,blocked):
    num = 0
    for i in range(start,end+1):
        if i in blocked:
            num += 1
            break
    for i in range(end,start+n+1):
        if i%n == 0 and n in blocked:
            num += 1 
            break
        if i%n in blocked:
            num += 1
            break
    if num == 2:
        return "impossibe"
    return "possible"



for i in range(q):
    lst = list(input().split())
    if lst[0] == '-':
        blocked.add(int(lst[1]))
    elif lst[0] == '+':
        blocked.remove(int(lst[1]))
    else:
        if not blocked:
            print("possible")
        elif len(blocked) == 1:
            if int(lst[1]) in blocked :
                print("impossible")
            else:
                print("possible")
        else:
            nums = (int(lst[1]),int(lst[2]))
            start = min(nums)
            end = max(nums)
            print(check(start,end,n,blocked))
                