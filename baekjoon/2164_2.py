from sys import stdin

class Stack:
    def __init__(self):
        self.items = []

    def push(self, item):
        self.items.append(item)

    def pop(self):
        if not self.isEmpty():
            return self.items.pop()
        else:
            print("Stack underflow")
            exit()

    def peek(self):
        return self.items[-1]
    
    def isEmpty(self):
        return not self.items
    
    def size(self):
        return len(self.items)
    
    def clear(self):
        self.items = []
    
