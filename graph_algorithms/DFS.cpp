#include <vector>
#include <iostream>
using namespace std;

#define vi vector<int>
#define pii pair<int,int>
#define ll long long 

const int N = (int)1e5;

vi G[N];
bool visited[N];

void makeUndirectedEdge(int u, int v){
	G[u].push_back(v);
	G[v].push_back(u);
}

void dfs(int u){
	visited[u] = true;
	for(int v:G[u]){
		if(!visited[v]){
			dfs(v);
		}
	}
}

int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int u,v;
		cin>>u>>v;
		makeUndirectedEdge(u,v);
	}
	return 0;
}