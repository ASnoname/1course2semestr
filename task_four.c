#include <stdio.h>
#include <math.h>

void First_function(double number){

	long long int znak; 
	long long int expon; 
	long long int mantis; 
	long long int *bity = NULL;
	long long int mask_mantis = 0xfffffffffffff;
	double *trans=NULL;
	double mantis_now;

	bity = &number;
	znak = *bity >> 63;
	expon = *bity >> 52;
	mantis = *bity;
	mantis &= mask_mantis;
	mantis = mantis | 0x3fe0000000000000;
	trans = &mantis;
	mantis_now = *trans;
	expon -= 1022;
	if (znak == 0) {
		printf("\nznak: +\n");
	}
	else {
		printf("\nznak: -\n");
	}
	printf("expon: %lli \nmantis: %lf ", expon, mantis_now);
}

void Second_function(long long int znak, long long int expon, double mantis){
	long long int *bity = NULL;
	long long int mantis_now;
	long long int trans_one;
	long long int mask_mantis = 0xfffffffffffff;
	double number;
	double *trans_two=NULL;
		expon += 1022; 
		bity = &mantis;
		mantis_now = *bity & mask_mantis;
		trans_one = ((znak << 63) | (expon << 52) | mantis_now);
		trans_two = &trans_one;
		number = *trans_two;
	printf("%f\n", number);
}

void main(void) {
	int p; printf("1 or 2\n"); scanf("%i",&p);
	if (p == 1){
		double number;
		printf("\nWrite number: ");
		scanf("%lf", &number);
		First_function(number);
	}	
	else if (p == 2){
		long long int znak; 
		long long int expon; 
		double mantis; double number;
		printf("\nWrite znak: "); scanf("%lli",&znak);
		printf("\nWrite mantis: "); scanf("%lf",&mantis);
		printf("\nWrite expon: "); scanf("%lli",&expon);
		Second_function(znak,expon,mantis);
	}	
}