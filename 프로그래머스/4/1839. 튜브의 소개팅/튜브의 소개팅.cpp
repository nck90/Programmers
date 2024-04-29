#include <vector>
#include <algorithm>
#include <iostream>
#include <string.h>

using namespace std;

pair<int, int> direction[4] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
vector<vector<int>> map;
long long dp[50][50][2501];
int M, N, S;
long long MAX = 0x7FFFFFFF;

bool inRange(int x, int y){
    return (0 <= x && x < M && 0 <= y && y < N);
}

long long solve(int x, int y, int dist){
    
    long long &ref = dp[x][y][dist];
    
    if(x == M - 1 && y == N - 1 && dist == 0) 
        return ref = 0;
    if(ref != -1)
        return ref;
    
    ref = MAX; 
    
    for(int i=0;i<4;i++){
        
        int next_x = x + direction[i].first;
        int next_y = y + direction[i].second;

        if(!inRange(next_x, next_y) || map[next_x][next_y] == -1 || dist < 1)
            continue;
        long long ret = solve(next_x, next_y, dist - 1) + map[x][y];
        if(ret <= S)
            ref = min(ref, ret); 
    }
    
    return ref;
}

vector<int> solution(int m, int n, int s, vector<vector<int>> time_map) {
    memset(dp, -1, sizeof(dp));
    map = time_map;
    M = m; N = n; S = s;
    
    int move_distance = MAX;
    int sum_of_talk_time = MAX;
    
    for(int i= M+N-2; i <= M*N; i++){
        long long ret = solve(0,0,i); 
      
        if(ret < MAX){
            move_distance = i;
            sum_of_talk_time = ret;
            break;
        }
    }
    
    vector<int> answer(2);
    answer[0] = move_distance;
    answer[1] = sum_of_talk_time;
    
    return answer;
}