#include <algorithm>
#include <cctype>
#include <cstdio>

 

int main(){
	int i,z,n,j,k,t,h,ans = 0;
	int a,b,c,d;



	printf("Enter the number of bits in the checksum\n");
	scanf("%d",&k);

	printf("Enter the number of data\n");
	scanf("%d",&n);


	printf("Enter the data \n");
	int sum = 0;
	for(i=1;i<=n;i++){
		scanf("%d",&a);
		sum += a;
	}

 	int checksum  = 0;
 	int temp = (1<<k)-1; //thus if the size is 4 then 15( (bin)1111 )


 	while(sum > 0){
 		checksum += sum & temp;	
 		sum >>= k;
 	}
	
 	checksum ^= temp;

	printf("checksum = %d\n",checksum);

	printf("If this data was recieved at the recievers side then\n");
	if(checksum!=0)
		printf(" the data is incorrect\n");
	else
		printf(" the data is correct\n");


 
	return 0;
} 

