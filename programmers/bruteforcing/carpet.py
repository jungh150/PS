def solution(brown, yellow):
    answer = []

    tmp = brown // 2 + 2
    for i in range(3, tmp - 2):
        j = tmp - i
        if (i - 2) * (j - 2) == yellow:
            answer.append(max(i, j));
            answer.append(min(i, j));
            break

    return answer