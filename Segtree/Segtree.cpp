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
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)

 


inline int scan2(){
	int n=0,s=1;
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
	int lrange;
	int rrange;
	int numelements;
	int mid;
} SegTree[2000000] ;
 
int a[MAX];
int b[MAX];
//SegTree is starting from 1. (Assumed)
// inintial buildtree(1,1,n)
lld buildtree(int n,int i,int j){
	if(i==j){
		SegTree[n].sum = a[i];
		SegTree[n].lrange = i;
		SegTree[n].rrange = j;
		SegTree[n].numelements = 1;
		SegTree[n].add = 0;
		SegTree[n].mid = -1;
		return SegTree[n].sum;
	}else{
		int mid = (i+j)>>1;
		SegTree[n].sum = buildtree(2*n,i,mid) + buildtree(2*n+1,mid+1,j);
		SegTree[n].lrange = i;
		SegTree[n].rrange = j;
		SegTree[n].numelements = j-i+1;
		SegTree[n].add = 0;
		SegTree[n].mid = (i+j)/2;
		return SegTree[n].sum;
	}
} 


void update(int n,int s, int e,lld addent){
	//#s and #e represents the range of the query
	if(s==SegTree[n].lrange && e==SegTree[n].rrange){
		SegTree[n].add = addent;
		SegTree[n].sum += (e-s+1)*addent;
		return ;
	}

	if( e < SegTree[n].lrange || s > SegTree[n].rrange )  //Lying outside the damn range 
		return;
	
	// if( SegTree[n].lrange > s && SegTree[n].rrange > e ){
	// 	SegTree[n].sum += (e-s+1)*addent;
	// 	update(2*n,s,)

	// }


	if(s >  SegTree[n].mid ){
		SegTree[n].sum += (e-s+1)*addent;
		update(2*n+1,s,e,addent);
	}else if( e<=SegTree[n].mid ){
		SegTree[n].sum += (e-s+1)*addent;
		update(2*n,s,e,addent);
	}else {
		SegTree[n].sum += (e-s+1)*addent;
		update(2*n,s,SegTree[n].mid,addent);
		update(2*n+1,SegTree[n].mid+1,e,addent);
		// ps("Asdasd");
	}
	
}





lld RangeSum(int n,int s,int e,int add){
	// #sum initially zero. s and e are the query range
	// call method = RangeSum(1,1,n,0) for sum between 1 to n
	if(s==SegTree[n].lrange && e==SegTree[n].rrange){
		return SegTree[n].sum + add*(e-s+1);
	}
	if( e < SegTree[n].lrange || s > SegTree[n].rrange )  //Lying outside the damn range 
		return 0;

	if(s>SegTree[n].mid){
		return RangeSum(2*n+1,s,e,add+SegTree[n].add);
	}else if(e<=SegTree[n].mid){
		return RangeSum(2*n,s,e,add+SegTree[n].add);
	}else{
		return  RangeSum(2*n,s,SegTree[n].mid,add+SegTree[n].add) + RangeSum(2*n+1,SegTree[n].mid+1,e,add+SegTree[n].add);
	}

}





void printSegTree(int n){
	d_iterate(1,n){
		printf("NodeNumber = %lld     Sum = %lld     add = %lld\n",i,SegTree[i].sum,SegTree[i].add);
	}
}




/*
	Brute force code

*/

	void b_update(int s,int e,int add){
		FOR(i,s,e){
			b[i] += add;
		}
	}

	lld b_RangeSum(int s,int e){
		lld ans = 0;
		FOR(i,s,e){
			ans += b[i];
		}
		return ans;
	}	

/*
	End of Brute Force Approach

*/
 
int main(){
	lld i,z,n,j,k,t,h,ans = 0;

	get(t);

	while(t--){

		scanf("%lld",&n);


		FOR(i,1,n){
			// k = rand()%10;
			a[i] = 0;
			b[i] = 0;
			// cout << a[i] << " " ;
		}
		// cout << endl;




		buildtree(1,1,n);

		// FOR(i,1,25)
		// 	printf("#%d , sum = %lld\n",i,SegTree[i].sum);


		// iterate(3){
		// 	lld left = 1 + rand()%9;
		// 	lld right = left + rand()%(10-left);
		// 	lld increment = rand()%10;
		// 	update(1,left,right,increment);
		// 	b_update(left,right,increment);		
		// 	printf("#left = %lld\t #right = %lld \t #increment = %lld\n",left,right,increment);

		// }

		int r,q,w,e;
		scanf("%d",&r);	
		int f;

		iterate(r){
				scanf("%d",&f);
				// scanf("%d%d%d%d",&f,&q,&w,&e);
					if( f == 0 ){
						// scanf("%d%d%d",&q,&w,&e);
						get(q);
						get(w);
						get(e);
						update(1,q,w,e);
					}
					else{
					// FOR(t,1,25)
						// printf("#%d , sum = %lld\n",t,SegTree[t].sum);
						// scanf("%d%d",&q,&w);
						get(q);
						get(w);
						printf("%lld\n",RangeSum(1,q,w,0));
						// cout << RangeSum(1,q,w,0) << endl;
					}
		}



	}

	// FOR(i,1,10){
	// 	FOR(j,i,10){
	// 		cout << "Sum Between "  <<  i << " and " << j << " " << RangeSum(1,i,j,0) << " == "  
	// 		<< b_RangeSum(i,j) <<endl;
	// 	}
	// }
	// printSegTree(9);

	return 0;
	
} 

