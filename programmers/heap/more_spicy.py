import heapq

def solution(scoville, k):
    answer = 0
    heapq.heapify(scoville)

    while 1:
        tmp1 = heapq.heappop(scoville)

        if tmp1 >= k:
            heapq.heappush(scoville, tmp1)
            break
        
        if not scoville:
            answer = -1
            break

        tmp2 = heapq.heappop(scoville)
        
        heapq.heappush(scoville, tmp1 + 2 * tmp2)
        answer += 1
    
    return answer