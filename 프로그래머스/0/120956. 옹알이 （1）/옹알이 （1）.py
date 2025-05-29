def solution(babbling):
    answer = 0
    can = ["aya", "ye", "woo", "ma"]
    for b in babbling:
        for c in can:
            b = b.replace(c, ' ')
        if len(b.strip()) == 0:
            answer += 1
    return answer