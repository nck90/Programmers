#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

#define MAX 305

using namespace std;

int Answer;
int Group_Cnt = 1;
int Visit[MAX][MAX];
int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };

vector<int> Parent;
vector<pair<int, pair<int, int>>> Edge;

void BFS(int a, int b, int Num, vector<vector<int>> MAP, int height) {
    queue<pair<int, int>> Q;
    Q.push(make_pair(a, b));
    Visit[a][b] = Num;

    while (!Q.empty()) {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && ny >= 0 && nx < MAP.size() && ny < MAP.size()) {
                if (Visit[nx][ny] == 0 && abs(MAP[x][y] - MAP[nx][ny]) <= height) {
                    Visit[nx][ny] = Num;
                    Q.push(make_pair(nx, ny));
                }
            }
        }
    }
}

void Make_Group(vector<vector<int>> land, int height) {
    for (int i = 0; i < land.size(); i++) {
        for (int j = 0; j < land[i].size(); j++) {
            if (Visit[i][j] == 0) BFS(i, j, Group_Cnt++, land, height);
        }
    }
}

void Find_Group_Distance(vector<vector<int>> land, int height) {
    for (int x = 0; x < land.size(); x++) {
        for (int y = 0; y < land.size(); y++) {
            for (int k = 0; k < 4; k++) {
                int nx = x + dx[k];
                int ny = y + dy[k];
                if (nx >= 0 && ny >= 0 && nx < land.size() && ny < land.size()) {
                    if (Visit[x][y] != Visit[nx][ny]) {
                        Edge.push_back(make_pair(abs(land[x][y] - land[nx][ny]), make_pair(Visit[x][y], Visit[nx][ny])));
                    }
                }
            }
        }
    }
}

int Find_Parent(int A) {
    if (A == Parent[A]) return A;
    return Parent[A] = Find_Parent(Parent[A]);
}

void Union(int A, int B) {
    A = Find_Parent(A);
    B = Find_Parent(B);
    Parent[B] = A;
}

bool Same_Parent(int A, int B) {
    A = Find_Parent(A);
    B = Find_Parent(B);
    if (A == B) return true;
    return false;
}

void Kruskal() {
    Parent.resize(Group_Cnt);
    sort(Edge.begin(), Edge.end());
    for (int i = 1; i < Group_Cnt; i++) Parent[i] = i;

    for (int i = 0; i < Edge.size(); i++) {
        int N1 = Edge[i].second.first;
        int N2 = Edge[i].second.second;
        int Cost = Edge[i].first;

        if (!Same_Parent(N1, N2)) {
            Union(N1, N2);
            Answer += Cost;
        }
    }
}

int solution(vector<vector<int>> land, int height) {
    Make_Group(land, height);
    Find_Group_Distance(land, height);
    Kruskal();
    return Answer;
}
