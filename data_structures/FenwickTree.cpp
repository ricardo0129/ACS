#include <vector>
using namespace std;

#define vi vector<int>

class FenwickTree{
public:
	vi ft;

	int LSOne(int s){
		return s&(-s);
	}

	//return RSQ(1,b)
	int rsq(int b){
		int sum = 0;
		for(;b;b-=LSOne(b))	
			sum+=ft[b];
		return sum;
	}

	int rsq(int a, int b){
		return rsq(b)-(a==1?0:rsq(a-1));
	}

	void update(int v, int k){
		for(;k<(int)ft.size();k+=LSOne(k)) 
			ft[k]+=v;
	}

	FenwickTree(int n){
		ft.assign(n+1,0);
	}
};

int main()
{
	FenwickTree t(50);
	return 0;
}