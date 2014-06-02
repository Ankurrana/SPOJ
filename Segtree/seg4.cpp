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
 

typedef long long int lld;
typedef long int ld;
using namespace std;
 

#define getw getchar_unlocked
#define iterate(n) for(lld i=0;i<n;i++)
#define d_iterate(p,q) for(lld i=p;i<=q;i++)
#define r_iterate(n,z) for(lld i=n-1;i>=n-z;i--) /* z number of elements to the left of n */
#define p(n) printf("%lld\n",n);
#define get(n) n = scan2();
#define print_array(k,n) iterate(n){ p(k[i]);}
#define ps(s) printf("%s\n",s);
#define mp make_pair;
#define pb push_back;
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define MAX 262145

/*
	Lazy Propogation is a technnique wherein instead of updating all 
	the nodes we just update upto which its neccessary. Use a separate variable add
	to each node which denotes that all the numbers below it shall be added with this number.
	Thus T[leftChild].add += v ,T[RightChild].add += v . and we'll update the parent node as 
	T[node].sum += (qr-ql + 1)*v;
	@ql QueryLeft
	@qr QueryRight

*/
/*
	We need not build the tree because its always 0 at all nodes. Simply Iterate 0 to all nodes

*/


inline lld scan2(){
	lld n=0,s=1;
	char p=getw();
	if(p=='-') s=-1;
	while((p<'0'||p>'9')&&p!=EOF&&p!='-') p=getw();
	if(p=='-') s=-1,p=getw();
	while(p>='0'&&p<='9') { n = (n<< 3) + (n<< 1) + (p - '0'); p=getw(); }
	return n*s;
}


 struct SegTree{
 	lld sum;
 	lld add;
 }T[MAX];



// void update(lld node, lld ql,lld qr, lld nl,lld nr,lld v){
// 	if( qr<nl || nr<ql ) return;  /*  If query range is completely out of range  */

// 	if( nl<= ql && nr >= ql ){
// 		lld leftchild = node << 1;
// 		lld rightchild = leftchild + 1;
// 		if( nl != nr ){   /* The node is not a leaf node  */
// 			T[leftchild].add += v;
// 			T[rightchild].add += v;
// 		}
// 	}
// }



void update(lld Node, lld QL, lld QR, lld NL, lld NR,lld v){
	lld LeftChild = Node << 1;
	lld RightChild = LeftChild + 1;
	bool isleaf = (NL== NR)?true:false;
	lld NumElements = QR-QL+1; 
	lld mid = (NL + NR) >> 1; 



	T[Node].sum += NumElements*v; 


	if( (NL == QL) && (NR==QR) ){
		if(!isleaf){
			T[LeftChild].add += v;
			T[RightChild].add += v;
		}
		return;
	}

	if(QL <=mid && !isleaf) update(LeftChild,QL,min(QR,mid),NL,mid,v);
	if(QR > mid && !isleaf) update(RightChild,max(QL,mid+1),QR,mid+1,NR,v);
}



lld RangeSum(lld Node,lld QL,lld QR, lld NL,lld NR,lld tempadd){
	lld LeftChild = Node << 1;
	lld RightChild = LeftChild+1;
	bool isleaf = (NL==NR)?true:false;
	lld NumElements = QR-QL+1;
	lld mid = (NL + NR) >> 1;
	lld ans = 0;
	tempadd += T[Node].add;

	if( (NL == QL) && (NR==QR) ){
		return NumElements*tempadd + T[Node].sum;
	}

	if(QL <=mid && !isleaf) ans += RangeSum(LeftChild,QL,min(QR,mid),NL,mid,tempadd);
	if(QR > mid && !isleaf) ans += RangeSum(RightChild,max(QL,mid+1),QR,mid+1,NR,tempadd);

	return ans;

}

void PrintSegTree(lld i){
	for(lld j=1;j<=i;j++)
		cout << "#" << j << " " << T[j].sum << " " << T[j].add << endl;
}


 
int main(){
	lld i,z,n,j,k,t,h,ans = 0;
	lld a,b,c,d,q;

	// update(1,1,2,1,4,1);
	// update(1,2,4,1,4,1);
	// update(1,1,4,1,4,3);


	// PrintSegTree(7);


	// FOR(i,1,4){
	// 	FOR(j,i,4)
	// 		cout << i << " and " <<  j << " " << RangeSum(1,i,j,1,4,0) << endl;
	// }

	cin >> t;
	while(t--){
		cin >> n >> q;
		// get(n);
		// get(q);

		lld maxsize = 2 * pow(2,ceil(n));

		FOR(i,1,maxsize){
			T[i].sum = T[i].add = 0;			
		}
		while(q--){
			cin >> k >> a >> b;
			// get(k);
			// get(a);
			// get(b);
			if(k==0){
				cin >> z;
				// get(z);
				update(1,a,b,1,n,z);
			}else{
				// cout << RangeSum(1,a,b,1,n,0) << endl;
				cout << (RangeSum(1,a,b,1,n,0)) << "\n";
			}
		}

	}


 
	return 0;
} 
