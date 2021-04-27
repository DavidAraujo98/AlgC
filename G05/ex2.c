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

void seq(int *array, int *copy, int *size){
	int elem = 0;
	for(int i = 0; i < *size; i++){
		comp++;
		if(*(array+i) != 1){
			int dif = 1;
			for (int j = i-1; j >= 0; j--){
				comp++;
				if( *(array+i) % *(array+j) == 0) {
					dif = 0	;
					break;
				}
				comp++;
				if( *(array+j) % *(array+i) == 0) {
					dif = 0	;
					break;
				}
				comp++;
				if( *(array+j) == *(array+i)) {
					dif = 0	;
					break;
				}
			}
			comp++;
			if(dif == 1){
				*(copy+elem) = *(array+i);
				elem++;
			}	
		}else{
			elem++;
			break;
		}		
	}
	*(size) = elem;	
}

int main(void){
	int range = 10;
	int size = 10;
	static int b[10];

	printf("Range (from 0): ");
	scanf("%d", &range);

	int *a = getRandom(range);
	
	printf("Array is: [");
	for(int i = 0; i < size; i++){
		printf("%d,", *(a+i));
	}
	printf("]\n");
	
	seq(a, b, &size);
	
	printf("New array is: [");
	for(int i = 0; i < size; i++){
		printf("%d,", *(a+i));
	}
	printf("]\n");

	printf("Comparações: %d\n", comp);
	printf("Nº Elementos: %d\n", size);
	
}
