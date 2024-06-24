import java.util.Arrays;

class Solution {

    int[][] dp;
    int[] topList;
    
    int dfs(int ind, int num) {
        if (num == 1 && topList[ind] == 0) return dp[ind][num] = 0;
        if (ind == 0) return 1;
        if (dp[ind][num] != -1) return dp[ind][num];

        int result = 0;
        for (int i = 0; i < 4; i++) {
            if (num == 2 && i == 3) continue;
            result = (dfs(ind-1, i) + result) % 10007;
        }
        return dp[ind][num] = result;
    }

    public int solution(int n, int[] tops) {
        dp = new int[n+1][4];
        topList = tops;
        for (int i = 0; i <= n; i++)
            Arrays.fill(dp[i], -1);
        return dfs(n, 0); 
    }
}
