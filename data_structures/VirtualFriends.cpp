/*
Example problem Virtual Friends 
https://open.kattis.com/problems/virtualfriends
*/
#include <bits/stdc++.h>
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
	int t;
	cin>>t;
	while(t--){
		int n;
		cin>>n;

		DSU friendSet(n);
		map<string,int> friends;
		string f,s;
		int x,y;
		map<string,int>::iterator it;
		for(int i=0;i<n;i++){
			cin>>f>>s;
			it = friends.find(f);
			if(it==friends.end()){
				friends[f]=friends.size()+1;    
				x = friends.size(); 
				friendSet.make_set(x);
			}
			else x = it->second;
			it = friends.find(s);
			if(it==friends.end()){
				friends[s]=friends.size()+1;
				y = friends.size();
				friendSet.make_set(y);
			}
			else y = it->second;
			friendSet.merge_set(x,y);
			cout<<friendSet.size[friendSet.find_set(x)]<<endl;
		}
	}


	return 0;
}
