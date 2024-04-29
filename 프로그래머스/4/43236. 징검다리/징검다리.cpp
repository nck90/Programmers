#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(int distance, vector<int> rocks, int n) {
    int answer = 0;
    
    sort(rocks.begin(), rocks.end()); 
    int start = 0;
    int end = distance;
    
    while (start <= end) {
        int mid = (start + end) / 2; 
        
        
        int adj = 0;
        int cnt = 0;
        int size = rocks.size();
        for (int i=0; i<size; i++) {
            
            if (rocks[i] - adj < mid) { 
                cnt++;
            }
            else { 
                adj = rocks[i]; 
            }
        }
   
        if (distance - adj < mid) {
            cnt++;
        }
        
        if (cnt <= n) { 
            if (mid > answer) {
                answer = mid;
            }
            start = mid + 1;
        }
        else { 
            end = mid - 1;
        }
    }
    
    return answer;
}