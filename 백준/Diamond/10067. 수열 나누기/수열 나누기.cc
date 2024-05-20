#include <algorithm>
#include <cstring>
#include <deque>
#include <iostream>
#include <vector>
#define MAXN 100000
#define MAXK 200
#define K(k) ((k)&1)
#define END (candid.size() - 1)
#define SQ(x) ((x) * (x))
typedef long long ll;
using namespace std;

ll S[MAXN + 1], D[2][MAXN + 1];
int OPT[MAXK + 1][MAXN + 1];
int N, K;

inline bool canSkip(int k, int i, int j, int threshold) {
    return (D[K(k-1)][i] - D[K(k-1)][j] + S[N] * (S[j] - S[i])) 
        <= threshold * (S[j] - S[i]);
}

inline bool canRemoveLastCandidate(int k, int i, int j, int l) {
    return (D[K(k-1)][i] - D[K(k-1)][j] + S[N] * (S[j] - S[i])) * (S[l] - S[j])
        <= (D[K(k-1)][j] - D[K(k-1)][l] + S[N] * (S[l] - S[j])) * (S[j] - S[i]);
}

void dp(int k) {
    deque<int> candid;
    candid.push_back(k-1);
    for (int i = k; i <= N; i++) {
        while (candid.size() > 1 && canSkip(k, candid[0], candid[1], S[i])) 
            candid.pop_front();
        int j = candid.front();
        OPT[k][i] = j;
        D[K(k)][i] = D[K(k-1)][j] + S[i] * S[j] - S[N] * S[j] + S[N] * S[i] - SQ(S[i]);
        while (candid.size() > 1 
                && canRemoveLastCandidate(k, i, candid[END], candid[END-1]))
            candid.pop_back();
        candid.push_back(i);
    }
}

vector<int> backtrace(int ind) {
    vector<int> ret;
    ret.reserve(K);
    int k = K;
    while(k > 0) {
        ret.push_back(ind);
        ind = OPT[k--][ind];
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

void solve() {
    for (int k = 1; k <= K; k++) {
        memset(D[K(k)], 0, sizeof(ll) * (MAXN + 1));
        dp(k);
    }
    ll ret = 0; int ind = 1;
    for (int i = 1; i <= N; i++) if (ret < D[K(K)][i]) ret = D[K(K)][i], ind = i;

    cout << ret << '\n';
    auto opt = backtrace(ind);
    for (int x : opt) cout << x << ' ';
}

void input() {
    cin>>N>>K;
    for (int i = 1; i <= N; i++) cin>>S[i], S[i] += S[i-1];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    input();
    solve();
}
