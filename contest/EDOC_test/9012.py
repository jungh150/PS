import sys

t = int(sys.stdin.readline())

for i in range(0, t) :
    data = sys.stdin.readline().strip()
    stk = []
    isVPS = True

    for j in range(0, len(data)) :
        if data[j] == '(' :
            stk.append(1)
        elif data[j] == ')' :
            if len(stk) == 0 :
                isVPS = False
                break
            else :
                del stk[-1]
    
    if len(stk) != 0 :
        isVPS = False

    if isVPS :
        print("YES")
    else :
        print("NO")