from functools import cmp_to_key

def comp(a, b):
    if a + b <= b + a:
        return 1
    else:
        return -1

def solution(numbers):
    a = [str(x) for x in numbers]
    a.sort(key=cmp_to_key(comp))

    answer = ''
    for c in a:
        answer += c
    
    if answer[0] == '0':
        answer = '0'

    return answer