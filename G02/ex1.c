#include<stdio.h>

int f3c = 0;
int f4c = 0;

unsigned int f1 (unsigned int n){
	unsigned int i, j, r = 0;
	for (i = 1; i <= n; i++){
		for (j = 1; j <= n; j++){
			r += 1;
		}
	}
	return r;
}

unsigned int f2 (unsigned int n) {
	unsigned int i, j, r = 0;
	for (i = 1; i <= n; i++){
		for (j = 1; j <= i; j++){
			r += 1;
		}
	}
	return r;
}

unsigned int f3 (unsigned int n) {
	unsigned int i, j, r = 0;
	for (i = 1; i <= n; i++){
		for (j = i; j <= n; j++){
			r += j;
			f3c++;
		}
	}
	return r;
}

unsigned int f4 (unsigned int n) {
	unsigned int i, j, r = 0;
	for (i = 1; i <= n; i++){
		for (j = i; j >= 1; j /= 10){
			r += i;
			f4c++;
		}
	}
	return r;
}

int main(void){
	int n = 0, x = 0;
	printf("Valor de n: ");
	scanf("%d", &n);
	printf("n\tf1(n)\t#f1\tf2(n)\t#f2\tf3(n)\t#f3\tf4(n)\t#f4\n");
	
	while(x <= n){
		int a = f1(x);
		int b = f2(x);
		int c = f3(x);
		int d = f4(x);
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", x, a, a, b, b, c, f3c, d, f4c);
		f3c = 0;
		f4c = 0;
		x++;
	}
}
