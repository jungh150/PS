class Queue :
    def __init__(self) :
        self.items = []
    
    def push(self, item) :
        self.items.append(item)

    def pop(self) :
        if not self.isEmpty() :
            object = self.items[0]
            self.items = self.items[1:]
            return object
        else :
            print("Que underflow")
            exit()
    
    def front(self) :
        if not self.isEmpty() :
            return self.items[0]
        else :
            print("Que underflow")
            exit()
    
    def back(self) :
        if not self.isEmpty() :
            return self.items[-1]
        else :
            print("Que underflow")
            exit()

    def isEmpty(self) :
        return not self.items

    def size(self) :
        return len(self.items)
    
    def clear(self) :
        self.items = []