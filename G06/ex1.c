#include<stdio.h>
#include<assert.h>

int c = 0;

int T1(int n){
	if(n != 0){
		c++;
		n = T1(n/4) + n;
	}
	return n;
}

int T2(int n){
	if(n > 3){
		c += 2;
		n = T2(n/4) + T2((n+3)/4) + n;
	}
	return n;
}

int T3(int n){
	if(n > 3){
		if(n%4 == 0){
			c++;
			n = 2 * T3(n/4) + n;
		}else{
			c += 2;
			n = T3(n/4) + T3((n+3)/4) + n;
		}
	}
	return n;
}

int main(void){
	int n = 2;

	printf("Value of n: ");
	scanf("%d", &n);
	
	assert(n>2);
	
	printf("N\tT1(N)\t#T1\tT2(N)\t#T2\tT3(N)\t#T3\n");
	for(int i = 0; i <= n; i++){
		c = 0;
		printf("%d\t%d\t", i, T1(i));
		printf("%d", c);
		c = 0;
		printf("\t%d\t",T2(i));
		printf("%d", c);
		c = 0;
		printf("\t%d\t",T3(i));
		printf("%d\n", c);
	}
}