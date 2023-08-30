from collections import deque
import sys

deq = deque()
n = int(sys.stdin.readline())
count = 0

for i in range(0, n) :
    commend = sys.stdin.readline().split()

    if commend[0] == "push_front" :
        deq.appendleft(commend[1])
    elif commend[0] == "push_back" :
        deq.append(commend[1])
    elif commend[0] == "pop_front" :
        if len(deq) == 0 :
            print(-1)
        else :
            print(deq.popleft())
    elif commend[0] == "pop_back" :
        if len(deq) == 0 :
            print(-1)
        else :
            print(deq.pop())
    elif commend[0] == "size" :
        print(len(deq))
    elif commend[0] == "empty" :
        if len(deq) == 0 :
            print(1)
        else :
            print(0)
    elif commend[0] == "front" :
        if len(deq) == 0 :
            print(-1)
        else :
            print(deq[0])
    elif commend[0] == "back" :
        if len(deq) == 0 :
            print(-1)
        else : 
            print(deq[-1])
    
    count += 1