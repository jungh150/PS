def solution(progresses, speeds):
    answer = []

    n = len(progresses)
    idx = 0
    
    progresses = [100 - x for x in progresses]
    
    while n - idx >= 1:
        time = (progresses[idx] + speeds[idx] - 1) // speeds[idx]

        for i in range(idx, n):
            progresses[i] -= time * speeds[i]
        
        cnt = 0
        while n - idx >= 1 and progresses[idx] <= 0:
            cnt += 1
            idx += 1
        
        answer.append(cnt)
        
    return answer