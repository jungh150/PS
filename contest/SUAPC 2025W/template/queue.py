import heapq

pq = []  # 최소 힙
heapq.heappush(pq, 3)
heapq.heappush(pq, 1)
heapq.heappush(pq, 2)

print(heapq.heappop(pq))  # 1
print(heapq.heappop(pq))  # 2
print(heapq.heappop(pq))  # 3



##################




from queue import PriorityQueue

pq = PriorityQueue()
pq.put(3)  # 숫자가 낮을수록 우선순위가 높음
pq.put(1)
pq.put(4)
pq.put(2)

print(pq.get())  # 1
print(pq.get())  # 2
print(pq.get())  # 3
print(pq.get())  # 4




##################





from collections import deque

class PriorityQueueDeque:
    def __init__(self):
        self.queue = deque()

    def push(self, value):
        """ 우선순위가 낮은 값을 먼저 넣기 (정렬 유지) """
        if not self.queue:
            self.queue.append(value)
        else:
            for i, v in enumerate(self.queue):
                if v > value:  # 작은 값이 먼저 오도록 삽입
                    self.queue.insert(i, value)
                    return
            self.queue.append(value)  # 끝까지 크면 뒤에 추가

    def pop(self):
        """ 최소값을 반환하고 제거 """
        if self.queue:
            return self.queue.popleft()  # 정렬된 상태에서 첫 번째 원소 제거
        return None

    def peek(self):
        """ 최소값 조회 """
        return self.queue[0] if self.queue else None

    def is_empty(self):
        return not self.queue
