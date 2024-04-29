#include <cmath>

int result;

void dfs(int n, int cnt) { 
    if (n < 3 || pow(3, cnt / 2) > n) return;
    if (n == 3) {
        if (cnt == 2) result++; 
        return;
    }
    if (n % 3 == 0 && cnt >= 2) dfs(n / 3, cnt - 2);

    dfs(n - 1, cnt + 1);
}

int solution(int n) {
    result = 0;
    dfs(n - 2, 2); 
    return result;
}
