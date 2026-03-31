def solution(genres, plays):
    answer = []
    
    n = len(genres)
    
    dict1 = {}
    dict2 = {}

    for i in range(n):
        if genres[i] in dict1:
            dict1[genres[i]] += plays[i]
            dict2[genres[i]].append([plays[i], i])
        else:
            dict1[genres[i]] = plays[i]
            dict2[genres[i]] = [[plays[i], i]]

    dict1 = sorted(dict1.items(), key=lambda x: -x[1])
    
    for x in dict1:
        g = x[0]
        dict2[g].sort(key=lambda x: (-x[0], x[1]))
        answer.append(dict2[g][0][1])
        if len(dict2[g]) >= 2:
            answer.append(dict2[g][1][1])
    
    return answer