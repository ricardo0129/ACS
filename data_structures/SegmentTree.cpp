#include <vector>
using namespace std;

#define vi vector<int>

const int INF = (int)1e9+7;
/*
SegTree implementation for range min queryes 
This implementation is not concrete and should be changed according 
to the specific problem. 
*/
class SegmentTree{
	public:
	int n;
	vi A, St;

	int left(int p){return p<<1;}
	int right(int p){return (p<<1)|1;}

	void build(int L, int R, int p){
		if(L==R){
			St[p] = A[L];
			return;
		}
		int M = (L+R)/2;
		build(L,M,left(p));
		build(M+1,R,right(p));
		St[p] = min(St[left(p)],St[right(p)]);
	}

	//I J   L R   I J
	int query(int L, int R, int p, int i, int j){
		if(i<=L && R<=j) return St[p];
		if(L>j || i>R) return INT_MAX;
		int M = (L+R)/2;
		int qL = query(L,M,left(p),i,j);
		int qR = query(M+1,R,right(p),i,j);
		return min(qL,qR);
	}

	int query(int i, int j){
		return query(0,n-1,1,i,j);
	}

	void update(int L, int R, int p, int v, int k){
		if(L==R){
			St[p] = v;
			return;
		}
		int M = (R+L)/2;
		if(k<=M) update(L,M,left(p),v,k);
		else update(M+1,R,right(p),v,k);
		St[p] = min(St[left(p)],St[right(p)]);
	}

	void update(int v, int k){
		update(0,n-1,1,v,k);
	}

	SegmentTree(vi& B){
		A = B;
		n = B.size();
		St.resize(4*n);
		build(0,n-1,1);
	}
};

int main()
{
	vi C(12,0);
	SegmentTree tree(C);

	return 0;
}