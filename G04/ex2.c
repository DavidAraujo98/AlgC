#include <stdio.h>

int main(void){
	int n = 2;
	int c = 0;
	int ne = 0;
	
	
	// Array input
	printf("Tamanho do array: ");
	scanf("%d", &n);
	int a[n];
	
	for(int i = 0; i < n; i++){
		a[i] = (i+1);
	}
	
	// Array operations
	for(int k = 2; k < n; k++){
		for(int j = 1; j < k; j++){
			for(int i = 0; i < j; i++ ){
				c++;
				if(a[k] == a[i] + a[j]){
					ne++;
				}
			}
		}
	}
	
	printf("\nNº de comparações: %d\nNº de ternos: %d\n", c, ne);
}

/*
Elementos	Comparações		Nº Ternos
5			10				4
10			120				20
20			1140			90
30			4060			210
40			9880			380
80			82160			1560
160			669920			6320
*/
