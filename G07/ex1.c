#include<stdio.h>

int c = 0;

int func1(int n){
	int res = 1;
	if(n > 2){
		res = 0; 
		int k;
		for(k = 0; k <= n-3; k++){
			c++;
			res += (func1(k) * func1(n-3-k));
		}
		res += (func1(n-1) + func1(n-2));
	}
	return res;
}

int func2(int n){
	int a[n+1];
	int y;
	for(y = 0; y <= n; y++){
		if(y>2){
			a[y] = 0;
			int k;
			for(k = 0; k <= y-3; k++){
				c++;
				a[y] += a[k] * a[y-3-k];
			}
				a[y] += a[y-1] + a[y-2];
		}else{
			a[y] = 1;
	}
	
	return a[n];
}

int main(void){
	int n;
	int a[1];
	
	printf("Limite de n: ");
	scanf("%d", &n);
	
	printf("n\tF1(n)\t\tMult\n");
	int i;
	
	for(i = 0; i <= n; i++){
		printf("%d",i);
		int y = func1(i);
		printf("\t%d\t\t%d\n",y,c);
		c=0;
	}
	
	printf("\n\nn\tF2(n)\t\tMult\n");
	
	for(i = 0; i <= n; i++){
		printf("%d",i);
		int y = func2(i);
		printf("\t%d\t\t%d\n",y,c);
		c=0;
	}
}
