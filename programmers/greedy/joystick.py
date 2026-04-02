def solution(name):
    n = len(name)
    
    ans1 = 0
    for c in name:
        ans1 += min(ord(c) - ord('A'), ord('Z') - ord(c) + 1)
    
    ans2 = n
    for i in range(n):
        acnt = 0
        for j in range(i, n):
            if name[j] == 'A':
                acnt += 1
            else:
                break
        
        x = i
        y = n - i - acnt
        
        if x == 0:
            ans2 = min(ans2, y)
        else:
            ans2 = min(ans2, (x - 1) * 2 + y)
            ans2 = min(ans2, 2 * y + x - 1)

    return ans1 + ans2