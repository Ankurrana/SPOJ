#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <unistd.h>
#include <utility>
#include <vector>
#include <map>
#include <cmath>
 

typedef  unsigned long long int lld;
typedef  unsigned long int ld;
using namespace std;
 

#define getw getchar_unlocked
#define iterate(n) for(lld i=0;i<n;i++)
#define d_iterate(p,q) for(lld i=p;i<=q;i++)
#define r_iterate(n,z) for(lld i=n-1;i>=n-z;i--) /* z number of elements to the left of n */
#define p(n) printf("%d\n",n);
#define get(n) n = scan2();
#define print_array(k,n) iterate(n){ p(k[i]);}
#define ps(s) printf("%s\n",s);
#define mp make_pair;
#define pb push_back;
#define FOR(i,a,b) for(lld i=(a);i<=(b);i++)

 


inline lld scan2(){
	lld n=0,s=1;
	char p=getw();
	if(p=='-') s=-1;
	while((p<'0'||p>'9')&&p!=EOF&&p!='-') p=getw();
	if(p=='-') s=-1,p=getw();
	while(p>='0'&&p<='9') { n = (n<< 3) + (n<< 1) + (p - '0'); p=getw(); }
	return n*s;
}

#define MAX 100100

struct node{
	lld sum;
	lld add;
} SegTree[4000000];
 
lld a[MAX];
//SegTree is starting from 1. (Assumed)
// initial buildtree(1,1,n)
lld buildtree(lld n,lld i,lld j){
	if(i==j){
		SegTree[n].sum = a[i];
		SegTree[n].add = 0;
		return SegTree[n].sum;
	}else{
		lld mid = (i+j)>>1;
		SegTree[n].sum = buildtree(2*n,i,mid) + buildtree(2*n+1,mid+1,j);
		SegTree[n].add = 0;
		return SegTree[n].sum;
	}
} 


void update(lld n,lld s,lld e,lld i,lld j,lld addent){
	lld mid = (i+j)>>1;

	if(s==i && e==j){
		SegTree[n].add = addent;
		SegTree[n].sum += (e-s+1)*addent;
		return ;
	}

	if( e < i || s > j )  
		return;


	if(s >  mid ){
		SegTree[n].sum += (e-s+1)*addent;
		update(2*n+1,s,e,mid+1,j,addent);
	}else if( e<=mid ){
		SegTree[n].sum += (e-s+1)*addent;
		update(2*n,s,e,i,mid,addent);
	}else {
		SegTree[n].sum += (e-s+1)*addent;
		update(2*n,s,mid,i,mid,addent);
		update(2*n+1,mid+1,e,mid+1,j,addent);
	}
	
}





lld RangeSum(lld n,lld s,lld e,lld i,lld j ,lld add){
	lld mid  = (i+j)>>1;
	if(s==i && e==j){
		return SegTree[n].sum + add*(e-s+1);
	}
	if( e < i || s > j )  
		return 0;

	if(s>mid){
		return RangeSum(2*n+1,s,e,mid+1,j,add+SegTree[n].add);
	}else if(e<=mid){
		return RangeSum(2*n,s,e,i,mid,add+SegTree[n].add);
	}else{
		return  RangeSum(2*n,s,mid,i,mid,add+SegTree[n].add) + RangeSum(2*n+1,mid+1,e,mid+1,j,add+SegTree[n].add);
	}

}


int main(){
	lld i,z,n,j,k,t,h,ans = 0;

	// get(t);
	cin >> t;

	while(t--){

		// scanf("%lld",&n);
		cin >> n;

		FOR(i,1,n){
			a[i] = 0;
		}

		buildtree(1,1,n);

	

		lld r,q,w,e;
		// scanf("%d",&r);	
		cin >> r;
		lld f;

		iterate(r){
				// scanf("%d",&f);
				cin >> f;
					if( f == 0 ){
						// get(q);
						// get(w);
						// get(e);
						cin >> q >> w >> e;
						update(1,q,w,1,n,e);
					}
					else{
						// get(q);
						// get(w);
						cin >> q >> w;
						// printf("%lld\n",RangeSum(1,q,w,1,n,0));
						cout << RangeSum(1,q,w,1,n,0) << endl;
					}
		}

	}

	return 0;
	
} 

