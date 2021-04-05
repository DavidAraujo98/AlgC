#include <stdio.h>
#include <math.h>
#include <time.h>

int c = 0;
double c1 = 0.24253562503633297352;
double c2 = 1.27019663313689157536;

int fibrc(int n){
	if(n == 0 || n == 1){
		return n;
	}
	else{
		c += 2;
		return 3 * fibrc(n-1) + 2 * fibrc(n-2);
	}
}

int fibit(int n){
	int pn = 0;
	int ul = 1;
	int temp = n;
	for(int i = 2; i <= n; i++){
		c += 2;
		temp = 3*ul + 2*pn;
		pn = ul;
		ul = temp;
	}
	return temp;
}

double fibre(int n){
	double x = pow((0.5 * (3 + sqrt(17))), n);
	double y = pow((0.5 * (3 - sqrt(17))), n); 
	x = x - y;
	c+=(n+1);
	return (x/sqrt(17));	
}

double fibeq(int n){
	c+=(n+1); 
	return floor((1/sqrt(17))*pow((0.5)*(3+sqrt(17)),n)+(0.5));
}

int fibrd(int n){
	c+=(1+(int)(c2*n));
	return (int)(c1*exp(c2*n));
}

int main(void){
	printf("Valor de n: ");
	int n = 0;
	scanf("%d", &n);
	
	printf("Recursiva\nn\tP(n)\t#Op\n");
	int t = time(NULL);
	for(int i = 0; i <= n; i++){
		printf("%d\t%d\t",i, fibrc(i));
		printf("%d\n", c);
	}
	printf("Time: %ld\n",(time(NULL)-t));

	printf("\nIterativa\n");
	t = time(NULL);
	for(int i = 0; i <= n; i++){
		c = 0;
		printf("%d\t%d\t", i, fibit(i));
		printf("%d\n", c);
	}
	printf("Time: %ld\n",(time(NULL)-t));
	

	printf("\nRecorrencia\n");
	t = time(NULL);
	for(int i = 0; i <=n; i++){
		c = 0;	
		printf("%d\t%d\t", i,(int)fibre(i));
		printf("%d\n", c);
	}
	printf("Time: %ld\n",(time(NULL)-t));

	printf("\nTermo mais importante da equação de recorrencia\n");
	t = time(NULL);
	for(int i = 0; i <= n; i++){
		c = 0;
		printf("%d\t%d\t", i, (int)fibeq(i));
		printf("%d\n", c);
	}
	printf("Time: %ld\n",(time(NULL)-t));

	printf("\nFormula fechada\n");
	t = time(NULL);
	for(int i = 0; i <= n; i++){
		c = 0;
		printf("%d\t%d\t", i, (int)fibrd(i));
		printf("%d\n", c);
	}
	printf("Time: %ld\n",(time(NULL)-t));
}
