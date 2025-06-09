import heapq

def solution(n, roads):
    adj = [[] for _ in range(n + 1)]
    for i, road in enumerate(roads):
        u, v, l, t = road
        road_idx = i + 1
        adj[u].append((v, l + t, road_idx, l))
        adj[v].append((u, l + t, road_idx, l))

    dist_from_start = [float('inf')] * (n + 1)
    count_sp_from_start = [0] * (n + 1)
    
    dist_from_start[1] = 0
    count_sp_from_start[1] = 1
    
    pq = [(0, 1)] 

    while pq:
        d, u = heapq.heappop(pq)

        if d > dist_from_start[u]:
            continue

        for v, current_cost, _, _ in adj[u]:
            if dist_from_start[u] + current_cost < dist_from_start[v]:

                dist_from_start[v] = dist_from_start[u] + current_cost
                count_sp_from_start[v] = count_sp_from_start[u]
                heapq.heappush(pq, (dist_from_start[v], v))
            elif dist_from_start[u] + current_cost == dist_from_start[v]:

                count_sp_from_start[v] += count_sp_from_start[u]

    D_initial = dist_from_start[n]

    total_shortest_paths = count_sp_from_start[n]

    dist_to_end = [float('inf')] * (n + 1)
    count_sp_to_end = [0] * (n + 1)   
    
    dist_to_end[n] = 0
    count_sp_to_end[n] = 1
    
    pq = [(0, n)] 

    while pq:
        d, u = heapq.heappop(pq)

        if d > dist_to_end[u]:
            continue

        for v, current_cost, _, _ in adj[u]:
            if dist_to_end[u] + current_cost < dist_to_end[v]:
                dist_to_end[v] = dist_to_end[u] + current_cost
                count_sp_to_end[v] = count_sp_to_end[u]
                heapq.heappush(pq, (dist_to_end[v], v))
            elif dist_to_end[u] + current_cost == dist_to_end[v]:
                count_sp_to_end[v] += count_sp_to_end[u]


    affected_roads_set = set()

    for i, road_info in enumerate(roads):
        u, v, L, T = road_info
        road_idx = i + 1
        current_cost = L + T 


        if dist_from_start[u] != float('inf') and dist_to_end[v] != float('inf'):
            if dist_from_start[u] + current_cost + dist_to_end[v] == D_initial:
                if (count_sp_from_start[u] * count_sp_to_end[v]) == total_shortest_paths:
                    affected_roads_set.add(road_idx)
        

        if dist_from_start[v] != float('inf') and dist_to_end[u] != float('inf'):
            if dist_from_start[v] + current_cost + dist_to_end[u] == D_initial:
                if (count_sp_from_start[v] * count_sp_to_end[u]) == total_shortest_paths:
                    affected_roads_set.add(road_idx)
    
        if dist_from_start[u] != float('inf') and dist_to_end[v] != float('inf'):
            if dist_from_start[u] + L + dist_to_end[v] < D_initial:
                affected_roads_set.add(road_idx)
        

        if dist_from_start[v] != float('inf') and dist_to_end[u] != float('inf'):
            if dist_from_start[v] + L + dist_to_end[u] < D_initial:
                affected_roads_set.add(road_idx)
    
    result = sorted(list(affected_roads_set))

    if not result:
        return [-1]
    
    return result