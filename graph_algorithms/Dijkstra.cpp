#include <bits/stdc++.h>
using namespace std;
#define vi vector<int> 
#define pii pair<int,int>
#define ll long long 
const ll INF = (ll)1e16;
const int N = (int)1e5+1;

vector<pair<int,ll>> G[N];
int n,m;
vector<ll> dist;
vi parent;
void makeEdge(int u, int v, ll w){
    G[u].push_back({v,w});
}

void dijkstra(int s){
    dist.assign(n,INF);
    parent.assign(n,-1);
    dist[s] = 0;
    parent[s] = s;
    set<pair<ll,int>> pq;
    pq.insert({0,s});
    while(!pq.empty()){
        int u = pq.begin()->second;
        pq.erase(pq.begin());
        for(pair<int,ll> e: G[u]){
            int v = e.first;
            ll w = e.second;
            if(dist[u]+w<dist[v]){
                pq.erase({dist[v],v});
                parent[v] = u;
                dist[v] = dist[u]+w;
                pq.insert({dist[v],v});

            }
        }
    }
}
void printPath(int start){
    vector<int> path;
    int u = start;
    for(;u!=parent[u];u=parent[u]){
        path.push_back(u+1);
    }
    path.push_back(u+1);
    for(int i=path.size()-1;i>=0;i--){
        cout<<path[i]<<" ";
    }
    cout<<endl;
}

int main()
{
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        u--;v--;
        makeEdge(u,v,w);
        makeEdge(v,u,w);
    }
    dijkstra(0);
    if(dist[n-1]==INF) cout<<-1<<endl;
    else
    printPath(n-1);
    return 0;
}