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
 

int modpower(int a,int p, int m){
	int ans = 1;
	while(p--){
		ans = (ans * a)%m;
	}
	return ans;	
}

int mulInverse(int a, int m){
	int num = 1;
	int den = a%m;

	while(den!=1){
		num = (num*den)%m;
		den = (den * den)%m;
	}
	return num%m;
}

int rsa(int p, int q,int e){
 	int n = p * q;
 	int phi = (p-1)*(q-1);
 	int d = mulInverse(e,phi);
 	return d;
 }
 
int encrypt(int data,int n,int e){
	return modpower(data,e,n);
}
int decrypt(int data,int n,int d){
	return modpower(data,d,n);
}

int main(){

	int p,q,n,e,m;

	printf("Enter the Value of p and q and e and then the message to be Encrypted");
	scanf("%d%d%d%d",&p,&q,&e,&m);	

	n = p*q;


	int d = rsa(p,q,e);
	int ED =  encrypt(m,n,e);

	printf("Encrypted Data is %d\n",ED);

 	
	
 
	return 0;
} 

