#include <stdio.h>

int main(void){
	int n = 2;
	int c = 0;
	int ne = 0;
	
	// Array input
	printf("Size of the array: ");
	scanf("%d", &n);
	int a[n];
	for(int i = 0; i < n; i++){
		printf("n[%d]: ", i);
		scanf("%d", &a[i]);
	}
	
	// Array operations
	for(int i = 1; i <= n-2; i++){
		c++;
		if(a[i] == (a[i-1] + a[i+1])){
			ne++;
		}
	}
	
	printf("Nº de elementos: %d\nNº de comparações: %d\n", ne, c);
}