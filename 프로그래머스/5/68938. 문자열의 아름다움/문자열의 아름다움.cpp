
 
 

#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;
struct node
{
    long long samePoint=0; 
    long long difPoint=0; 
    long long sameCnt=0;
    long long difCnt=0;
    int ed=0;
};

long long solution(string s) {
    long long answer = 0;
    char prevChar=s[0];
    vector<bool> isFirst(26,false);
    vector<long long> nuHap(300001,0); 
    map<int, map<int, int>> sMap; 
    vector<node> nodeInfo(26);
    
    int conCnt=1; 
    for (int i=1; i<s.length(); i++)
    {
        nuHap[i]=nuHap[i-1]+i;
        int prevAlpha=prevChar-'a';
        int prevI=i-1;
        if (prevChar==s[i]) 
        {
            conCnt+=1;
        }
        else 
        {
            if (!isFirst[prevAlpha]) 
            {
                isFirst[prevAlpha]=true;
                nodeInfo[prevAlpha].difPoint=nuHap[prevI]-nuHap[conCnt-1];
                nodeInfo[prevAlpha].sameCnt=conCnt;
                nodeInfo[prevAlpha].difCnt=prevI-conCnt+1;
                nodeInfo[prevAlpha].ed=prevI;
                sMap[prevAlpha][conCnt]+=1;
            }
            else
            {
                int eed=nodeInfo[prevAlpha].ed;
                nodeInfo[prevAlpha].difPoint+=(prevI-eed)*nodeInfo[prevAlpha].difCnt+nuHap[prevI-eed-1]-nuHap[conCnt-1];
                nodeInfo[prevAlpha].samePoint+=(prevI-eed)*nodeInfo[prevAlpha].sameCnt;
                
                sMap[prevAlpha][conCnt]+=1;
                
                
                nodeInfo[prevAlpha].sameCnt+=conCnt;
                nodeInfo[prevAlpha].difCnt=prevI+1-nodeInfo[prevAlpha].sameCnt;
                nodeInfo[prevAlpha].ed=prevI;
            }
            prevChar=s[i];
            conCnt=1;
        }
        int nowAlpha=s[i]-'a';
        
        long long ccct=0;
        
        
        
        int eed=nodeInfo[nowAlpha].ed;
        if (!isFirst[nowAlpha])
        {
            ccct=nuHap[i]-nuHap[conCnt-1];
        }
        else
        {
            ccct+=nodeInfo[nowAlpha].difPoint+(i-eed)*nodeInfo[nowAlpha].difCnt;
            ccct+=nuHap[i-eed-1]-nuHap[conCnt-1];
        } 
             
        for (map<int, int>::iterator it=sMap[nowAlpha].begin(); it!=sMap[nowAlpha].end(); it++)
        {
            pair<int, int> np =*it; 
            if (conCnt<np.first)
            {
                ccct+=(nuHap[(i-conCnt)-(eed-np.first+1)]-nuHap[i-(eed+1)])*np.second;
            }
            ccct+=(i-(eed+1))*np.second*min(conCnt, np.first);
        }
        ccct+=nodeInfo[nowAlpha].samePoint; 
        answer+=ccct;
    }
    
    return answer;
}