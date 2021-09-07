#include <vector>
using namespace std;

#define vi vector<int>

class DSU{

public:
	vi size,parent;

	void make_set(int u){
		size[u] = 1;
		parent[u] = u;
	}

	int find_set(int u){
		if(parent[u]==u) return u;
		return parent[u] = find_set(parent[u]);
	}

	void merge_set(int u, int v){
		u = find_set(u); v = find_set(v);
		if(u!=v){
			if(size[u]<size[v]) swap(u,v);
			parent[v] = u;
			size[u] += size[v];
		}
	}

	DSU(int n){
		size.resize(n); parent.resize(n);
		for(int i=0;i<n;i++) make_set(i);
	}
};

int main()
{
	DSU dSet(50);

	return 0;
}