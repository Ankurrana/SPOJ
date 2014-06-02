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
 

typedef unsigned long long int lld;
typedef unsigned long int ld;
using namespace std;
 


int main(){
	int i,z,n,j,k,t,h,ans = 0;
	int a,b,c,d;
	int fa,fb,fc,fd;
	unsigned int la,lb,lc,ld;

	int mask;
	printf("Enter the mask\n");
	scanf("%d",&mask);

	printf("Enter any IP from the corresponding IP addr\n");
	scanf("%d%d%d%d",&a,&b,&c,&d);

	int totalmask = ((1<<mask)-1)<<(32-mask);

	
	int bytemask;

	bytemask = (255 & totalmask);
		fd = d & bytemask;
		ld = (d | (255^bytemask));

	totalmask >>= 8;
	bytemask = 255 & totalmask;
		fc = c & bytemask;
		lc = (c | (255^bytemask));

	totalmask >>= 8;
	bytemask = 255 & totalmask;
		fb = b & bytemask;
		lb = (b | (255^bytemask));

		totalmask >>= 8;
	bytemask = 255 & totalmask;
		fa = a & bytemask;
		la = (a | (255^bytemask));
		

		printf("First addr =%d.%d.%d.%d\n",fa,fb,fc,fd);
 		printf("Last addr  =%d.%d.%d.%d\n",la,lb,lc,ld);


	
 
	return 0;
} 

