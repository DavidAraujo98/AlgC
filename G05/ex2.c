#include<stdio.h>
#include <stdlib.h>
#include <time.h>

int comp = 0;

int * getRandom(int range){
	static int r[10];
	
	srand(time(0));
	
	for(int i = 0; i < 10; ++i){
		r[i] = rand() % range + 1;
	}
	
	return r;
}

int seq(int *array){
	int elem = 1;
	for(int i = 1; i < 10; i++){
		int dif = 1;
		for (int j = 0; j < i; j++){
			comp += 2;
			if( *(array+i) % *(array+j) == 0 || *(array+j) % *(array+i) == 0) {
				dif = 0	;
				break;
			}
		}
		if(dif == 1){
			*(array+elem) = *(array+i);
			elem++;
		}			
	}	
	return elem;
}

int main(void){
	int range = 10;

	printf("Range (from 0): ");
	scanf("%d", &range);

	int *a = getRandom(range);
	
	printf("Array is: [");
	for(int i = 0; i < 10; i++){
		printf("%d,", *(a+i));
	}
	printf("]\n");
	
	int nsize = seq(a);
	
	printf("New array is: [");
	for(int i = 0; i < nsize; i++){
		printf("%d,", *(a+i));
	}
	printf("]\n");

	printf("Comparações: %d\n", comp);
}
