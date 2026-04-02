def solution(n, number):
    answer = -1
    
    dp = [set() for _ in range(9)]

    tmp = n
    for i in range(1, 9):
        dp[i].add(tmp)
        tmp = tmp * 10 + n
    
    for i in range(1, 9):
        for j in range(1, 9):
            if (i + j > 8):
                continue
            for x in dp[i]:
                for y in dp[j]:
                    dp[i + j].add(x + y)
                    dp[i + j].add(x - y)
                    dp[i + j].add(y - x)
                    dp[i + j].add(x * y)
                    if y != 0:
                        dp[i + j].add(x // y)
                    if x != 0:
                        dp[i + j].add(y // x)
    
    for i in range(1, 9):
        if number in dp[i]:
            answer = i;
            break
    
    return answer