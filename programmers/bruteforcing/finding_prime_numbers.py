def solution(numbers):
    res = set()
    n = len(numbers)
    
    used = [False for _ in range(n)]
    
    def func(cnt, num):
        nonlocal res
            
        isprime = True
        for i in range(2, num):
            if i * i > num:
                break
            if num % i == 0:
                isprime = False
                break
        
        if num == 0 or num == 1:
            isprime = False

        if isprime:
            res.add(num)
            
        if cnt == n:
            return
        
        for i in range(n):
            if not used[i]:
                used[i] = True
                func(cnt + 1, 10 * num + int(numbers[i]))
                used[i] = False
    
    func(0, 0)

    return len(res)