def solution(numbers, target):
    n = len(numbers)
    list1 = [0 for _ in range(30001)]

    list1[numbers[0] + 1000] = 1
    list1[-numbers[0] + 1000] = 1

    for i in range(1, n):
        list2 = [0 for _ in range(30001)]
        for j in range(30001):
            if j + numbers[i] >= 0 and j + numbers[i] < 30001:
                list2[j + numbers[i]] += list1[j]
            if j - numbers[i] >= 0 and j - numbers[i] < 30001:
                list2[j - numbers[i]] += list1[j]
        list1, list2 = list2, list1
        
    answer = list1[target + 1000]
    
    return answer