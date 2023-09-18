from sys import stdin

class Stack :
    def __init__(self) :
        self.items = []
    
    def push(self, item) :
        self.items.append(item)

    def pop(self) :
        if not self.isEmpty() :
            return self.items.pop()
        else :
            return -1
    
    def peek(self) :
        if not self.isEmpty() :
            return self.items[-1]
        else :
            return -1

    def isEmpty(self) :
        return not self.items

    def size(self) :
        return len(self.items)
    
    def clear(self) :
        self.items = []

while True:
    stk = Stack()
    isVPS = True
    str = stdin.readline()

    if str == ".\n":
        break

    for i in range(0, len(str)):
        if str[i] == "[":
            stk.push(1)
        elif str[i] == "]":
            if stk.peek() == 1:
                stk.pop()
            else:
                isVPS = False
        elif str[i] == "(":
            stk.push(2)
        elif str[i] == ")":
            if stk.peek() == 2:
                stk.pop()
            else:
                isVPS = False
    
    if stk.size() != 0:
        isVPS = False
    
    if isVPS:
        print("yes")
    else:
        print("no")