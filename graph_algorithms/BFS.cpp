#include <iostream>
#include <vector>
#include <queue>
using  namespace std;

#define vi vector<int>
#define pii pair<int,int>
const int INF = (int)1e9+7;


vi G[(int)1e5+7];
vi dist;
int n,m;

int main()
{
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        //for undirected graph add edges (u,v) && (v,u)
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dist.assign(n,INF);
    queue<int> q;
    while(!q.empty()){

        int u = q.front(); q.pop();

        for(int v:G[u]){
            if(dist[v]==INF){
                dist[v] = dist[u]+1;
                q.push(v);
            }
        }

    }

    return 0;
}
