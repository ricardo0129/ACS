#include <vector>
#include <iostream>

using namespace std;

#define vi vector<int>
#define pii pair<int,int>
#define ll long long

const int INF = (int)3e4;

vi dist;
vector<pii> G[101];
int n,m;

void solve(int src){
    dist.assign(n+1,INF);
    dist[src] = 0;
    for(int i=0;i<n-1;i++){
        for(int u=0;u<n;u++){
            for(pii x: G[u]){
                int v = x.first, w = x.second; 
                dist[v] = min(dist[v],dist[u]+w);
            }
        }
    }
    //check for negative cycle
    // for(int u=0;u<n;u++){
    //     for(pii x:G[u]){
            
    //     }
    // }

}

int main()
{
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        G[u].push_back({v,w});
    }
    solve(1);
    for(int i=1;i<=n;i++) printf("%d ",dist[i]);
    printf("\n");
    
    return 0;
}