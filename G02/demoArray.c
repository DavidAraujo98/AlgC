#include <stdio.h>

struct Array {
	int length;
	double array[1000]
};

void inputArray(struct Array *ap){
	int i;
	for(i = 0; i < 1000, i++){
		double v;
		int r = scanf("%lf", &v);
		if (r < 1) break;
		(*ap).array[i] = v;
	}
	(*ap).length = i;
}

void printArray(struct Array *ap){
	for(int i = 0; i < (*ap).length; i++){
		printf("%lf\n", (*ap).array[i]);
	}
}

int main(void){
	struct Array a;
	
	inputArray(&a);
	printArray(&a);
	
	return 0;
}