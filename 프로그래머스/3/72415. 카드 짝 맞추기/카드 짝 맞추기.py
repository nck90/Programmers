from collections import deque
from itertools import permutations
from copy import deepcopy

def ctrl_move(r, c, dr, dc, board):
    cr, cc = r, c
    while True:
        nr, nc = cr + dr, cc + dc
        if not (0 <= nr < 4 and 0 <= nc < 4):
            return cr, cc
        if board[nr][nc] != 0:
            return nr, nc
        cr, cc = nr, nc
        
def bfs(start, end, board):
    if start == end:
        return 0
    q = deque([(start[0], start[1], 0)])
    visited = [[False]*4 for _ in range(4)]
    visited[start[0]][start[1]] = True
    moves = [(0,1),(0,-1),(1,0),(-1,0)]

    while q:
        r, c, cnt = q.popleft()
        for dr, dc in moves:
            nr, nc = r + dr, c + dc
            if 0 <= nr < 4 and 0 <= nc < 4 and not visited[nr][nc]:
                if (nr, nc) == end:
                    return cnt + 1
                visited[nr][nc] = True
                q.append((nr, nc, cnt + 1))

            cr, cc = ctrl_move(r, c, dr, dc, board)
            if not visited[cr][cc]:
                if (cr, cc) == end:
                    return cnt + 1
                visited[cr][cc] = True
                q.append((cr, cc, cnt + 1))
    return float('inf')

def solution(input_board, sr, sc):
    board = input_board
    location = [[] for _ in range(7)]
    nums = []
    for i in range(4):
        for j in range(4):
            if board[i][j]:
                nums.append(board[i][j])
                location[board[i][j]].append((i, j))
    nums = list(set(nums))

    answer = float('inf')
    for order in permutations(nums):
        bd = deepcopy(board)
        r, c = sr, sc
        cnt = 0
        for num in order:
            p1, p2 = location[num]
            d1 = bfs((r,c), p1, bd) + bfs(p1, p2, bd)
            d2 = bfs((r,c), p2, bd) + bfs(p2, p1, bd)
            if d1 <= d2:
                cnt += d1
                r, c = p2
            else:
                cnt += d2
                r, c = p1
            bd[p1[0]][p1[1]] = 0
            bd[p2[0]][p2[1]] = 0
            cnt += 2
        answer = min(answer, cnt)
    return answer
