def solution(n, m, x, y, queries):
    # 도착점의 범위를 저장할 변수들
    min_row = x
    max_row = x
    min_col = y
    max_col = y
    
    # 쿼리를 거꾸로 실행
    for cmd, dx in reversed(queries):
        # 열 번호가 감소하는 방향 (원래는 증가)
        if cmd == 0:
            if max_col + dx < m:
                max_col += dx
            else:
                max_col = m - 1
            if min_col != 0:
                min_col += dx
                
        # 열 번호가 증가하는 방향 (원래는 감소)
        elif cmd == 1:
            if min_col - dx >= 0:
                min_col -= dx
            else:
                min_col = 0
            if max_col != m-1:
                max_col -= dx
                
        # 행 번호가 감소하는 방향 (원래는 증가)
        elif cmd == 2:
            if max_row + dx < n:
                max_row += dx
            else:
                max_row = n - 1
            if min_row != 0:
                min_row += dx
                
        # 행 번호가 증가하는 방향 (원래는 감소)
        else:
            if min_row - dx >= 0:
                min_row -= dx
            else:
                min_row = 0
            if max_row != n-1:
                max_row -= dx
        
        # 불가능한 경우 체크
        if min_row > max_row or min_col > max_col:
            return 0
            
    # 가능한 시작점의 개수 계산
    return (max_row - min_row + 1) * (max_col - min_col + 1)