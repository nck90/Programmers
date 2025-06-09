def solution(heights):
    n = len(heights)
    heights.sort() # 높이 배열을 오름차순으로 정렬

    minus_v = [] # 계산된 높이 차이들을 저장할 리스트

    if n % 2 == 1: # 홀수 개의 높이인 경우
        # 짝수 개일 때와 유사하게, 작은 절반과 큰 절반을 짝지어 차이 계산
        # n // 2 는 (n-1) / 2 와 동일
        for i in range(n // 2): 
            minus_v.append(heights[i + n // 2] - heights[i])
        
        # 홀수일 때 남는 가장 큰 값(J)과 중간 그룹의 첫 번째 값(heights[n // 2])의 차이 추가
        minus_v.append(heights[n - 1] - heights[n // 2])
        
        minus_v.sort() # 계산된 차이들을 정렬
        return minus_v[1] # 두 번째로 작은 값 반환
    else: # 짝수 개의 높이인 경우
        # 작은 절반(heights[0] ~ heights[n/2 - 1])과 큰 절반(heights[n/2] ~ heights[n-1])을 짝지음
        for i in range(n // 2):
            minus_v.append(heights[i + n // 2] - heights[i])
        
        minus_v.sort() # 계산된 차이들을 정렬
        return minus_v[0] # 가장 작은 값 반환