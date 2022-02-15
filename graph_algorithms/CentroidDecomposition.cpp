#include <bits/stdc++.h>
using namespace std;
#define vi vector<int> 

const int N = (int)1e5;
int n;
vi G[N];
bool blocked[N];
int parent[N];
int subTreeSize[N];
void calcsum(int u, int p){
    parent[u] = p;
    subTreeSize[u] = 1;
    for(int v:G[u]){
        if(v!=p && !blocked[v]){
            calcsum(v,u);
            subTreeSize[u]+=subTreeSize[v];
        }
    }
}
char ans[N];

void solve(int entry,char letter){
    calcsum(entry,entry);
    int centroid = entry;
    int bestSize = subTreeSize[entry];
    int compsize = 0;
    queue<int> q;
    q.push(entry);
    while(!q.empty()){
        int u = q.front(); q.pop();
        compsize++;
        int size = subTreeSize[entry]-subTreeSize[u];
        for(int v:G[u]){
            if(v!=parent[u] && !blocked[v]){
                size = max(size,subTreeSize[v]);
                q.push(v);
            }
        }
        if(size<bestSize){
            centroid = u;
            bestSize = size;
        }
    }

    /*
    int ways = solveTree(centroid,compsize);
    */
    blocked[centroid] = true;
    ans[centroid] = letter;

    for(int v:G[centroid]){
        if(!blocked[v])
            solve(v,letter+1);
    }
}

int main()
{
    cin>>n;
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        u--;v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    solve(0,'A');
    for(int i=0;i<n;i++) cout<<ans[i]<<" ";
    cout<<endl;
    
    return 0;
}
