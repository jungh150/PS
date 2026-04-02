def solution(n, times):
    l = 0
    r = 10 ** 15
    while (l < r):
        m = (l + r) // 2
        sumt = 0
        for x in times:
            sumt += m // x

        if sumt >= n:
            r = m
        else:
            l = m + 1
    
    answer = l
    return answer