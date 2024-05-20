#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
int answer=1;

vector<int> DFS(int parNode, int nowNode, vector<vector<int>> &graph)
{
    vector<int> nv(3,1), tempV; 
    vector<vector<int>> v;
    int childNode=0;
    int maxV3=1;
    for (int i=0; i<graph[nowNode].size(); i++)
    {
        childNode=graph[nowNode][i];
        if (childNode!=parNode)
        {
            v.push_back(DFS(nowNode,childNode, graph));
        }
    }
    
    if (!v.empty())
    {
        // v3값 계산
        sort(v.begin(),v.end(),[](vector<int>a,vector<int>b){
            return a[2]==b[2]?a[0]>b[0]:a[2]>b[2];
        });
        int maxDepth=0;
        int maxV2=v[0][2]; //max nv[2]값
        if (v.size()>2)
        {
            for (int i=2; i<v.size(); i++)
            {
                maxDepth=max(maxDepth,v[i][0]);
            }
            answer=max({answer,1+max(maxDepth,v[1][0])+v[0][2], 1+max(maxDepth,v[0][0])+v[1][2]});
        }
        else if (v.size()==2)
        {
            answer=max({answer,1+v[1][0]+v[0][2], 1+v[0][0]+v[1][2]});
        }
        else if (v.size()==1)
        {
            answer=max(answer,1+v[0][2]);
        }
        
        sort(v.begin(),v.end(),[](vector<int>a,vector<int>b){
        return a[1]==b[1]?a[0]>b[0]:a[1]>b[1];
        });
        
        maxDepth=0;
        if (v.size()>2)
        {
            for (int i=3; i<v.size(); i++)
            {
                maxDepth=max(maxDepth,v[i][0]);
            }
            
            answer=max({answer,
                        1+max(maxDepth,v[2][0])+v[0][1]+v[1][1],
                        1+max(maxDepth,v[0][0])+v[1][1]+v[2][1],
                        1+max(maxDepth,v[1][0])+v[0][1]+v[2][1]});
            
            nv[0]=1+max({maxDepth,v[0][0], v[1][0], v[2][0]});
            nv[1]=1+max( max({maxDepth, v[0][0],v[2][0]}) + v[1][1],  max({maxDepth,v[1][0],v[2][0]}) +v[0][1]);
            nv[2]=max(maxV2+1, v[0][1]+v[1][1]+1);
            return nv;
        }
        else if (v.size()==2)
        {
            answer=max(answer, 1+v[0][1]+v[1][1]);
            
            nv[1]=1+max(v[0][0]+v[1][1],v[0][1]+v[1][0]);
            nv[0]=1+max(v[0][0],v[1][0]);
            nv[2]=max(maxV2+1, v[0][1]+v[1][1]+1);
            return nv;
        }
        else
        {
            nv[0]=1+v[0][0], nv[1]=1+v[0][1];
            answer=max(answer,nv[1]);
            nv[2]=max(maxV2+1, v[0][1]+1);
            return nv;
        }
    }
    return nv;        
}

int solution(vector<vector<int>> t) {
    vector<vector<int>>graph(200000); 
    for (int i=0; i<t.size(); i++)
        graph[t[i][0]].push_back(t[i][1]), graph[t[i][1]].push_back(t[i][0]);
    DFS(-1,t[0][0],graph);
    
    return answer;
}