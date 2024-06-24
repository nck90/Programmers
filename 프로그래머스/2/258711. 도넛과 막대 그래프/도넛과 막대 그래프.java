import java.util.*;

public class Solution {
    public int[] solution(int[][] edges) {
        int[] answer = {0, 0, 0, 0};
        HashMap<Integer, int[]> exchangeCnts = new HashMap<>();
        
        for (int[] edge : edges) {
            int a = edge[0];
            int b = edge[1];
            
            exchangeCnts.putIfAbsent(a, new int[]{0, 0});
            exchangeCnts.putIfAbsent(b, new int[]{0, 0});
            
            exchangeCnts.get(a)[0] += 1;
            exchangeCnts.get(b)[1] += 1;
        }
        
        for (Map.Entry<Integer, int[]> entry : exchangeCnts.entrySet()) {
            int key = entry.getKey();
            int[] exchangeCnt = entry.getValue();
            
          
            if (exchangeCnt[0] >= 2 && exchangeCnt[1] == 0) {
                answer[0] = key;
            }
            
            else if (exchangeCnt[0] == 0 && exchangeCnt[1] > 0) {
                answer[2] += 1;
            }
       
            else if (exchangeCnt[0] >= 2 && exchangeCnt[1] >= 2) {
                answer[3] += 1;
            }
        }
        
        
        answer[1] = (exchangeCnts.get(answer[0])[0] - answer[2] - answer[3]);
        
        return answer;
    }
}
