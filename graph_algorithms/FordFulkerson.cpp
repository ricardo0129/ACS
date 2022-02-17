#include <bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define pii pair<int,int>
#define ll long long

const int N = 1000;
int cap[N][N];
bool seen[N];
int sink,source;
vector<string> A;
int n,p,k;

void addEdge(int u, int v, int c){
    cap[u][v]+=c;
}

int dfs(int u, int flow){
    if(u==sink){
        return flow;
    }
    seen[u] = true;
    int sent = 0;
    for(int v=0;v<=n;v++){
        if(cap[u][v]>0 && !seen[v]){
            sent = dfs(v,min(flow,cap[u][v]));
            if(sent>0){
                cap[u][v]-=sent;
                cap[v][u]+=sent;
                return sent;
            }
        }
    }
    return 0;
}

int maxFlow(int source){
    int total = 0;
    int curr_flow = -1;
    while(curr_flow!=0){
        memset(seen,false,sizeof seen);
        curr_flow = dfs(source,INT_MAX);
        total+=curr_flow;
    }
    return total;
}

int main()
{
    int f = maxFlow(source);
    return 0;
}