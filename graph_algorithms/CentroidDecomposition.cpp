#include <bits/stdc++.h>
using namespace std;
#define vi vector<int> 
#define ll long long 

const int N = (int)1e5;
int n;
vi G[N];
bool blocked[N];
int parent[N];
int subTreeSize[N];
int val[N];
ll sum[N];
int bits[N][20];

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

ll solveTree(int u, int p){
    sum[u] = 0;
    for(int v: G[u]){

    }
}

void solve(int entry){
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
    cout<<1+centroid<<endl;
    blocked[centroid] = true;

    for(int v:G[centroid]){
        if(!blocked[v])
            solve(v);
    }
}

int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>val[i];
    }
    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        u--;v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    solve(0);
    
    return 0;
}
