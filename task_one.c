*/5 задача*/
#include <stdio.h>
#include <math.h>
int masprnumber[2][8];
long long int sumpr = 1; int number,num;
int func(){
	int l=0,i,k; 
	scanf("%i/n",number);
	num = sqrt(number);
	for (i = 2; i < 20 ;i++){
		for (k = 2; k <= num; k++)
		{
		    if (number /= k == 0){
				continue;	
			}
			else {
				masprnumber[0][l];
				l++;
			}
		}

	}
	return 0;
}

int clean(){
	int i;
	for (i = 0; i < 8; i++)
	{
		masprnumber[1][i] = 0;
	}
	return 0;
}
int main(void){
	func();
	clean();
	int i;
	for (i = 0; i < 8; i++){
		int k=1;
		while(pow(masprnumber[0][i],k) < number)
		{
			k++;
			masprnumber[1][i]++;
		}
	}
		for (i = 0; i < 8; i++)
	{
		sumpr *= pow(masprnumber[0][i], masprnumber[1][i]);
	}
	printf("%i" , sumpr);
	return 0;
}

/*int func(){
	scanf("%i/n",number);
	int num,number,l=0;
	num = sqrt(number);
	for (int i = 2; i++){
		for (int k = 2; k <= num; k++)
		{
		    if (number /= k == 0){
				continue;	
			}
			else {
				masprnumber[0][l];
				l++;
			}
		}

	}
}

int clean(){
	for (int i = 0; i < 8; i++)
	{
		masprnumber[1][i] = 0;
	}
}
*/
//int*array= malloc(n*sizeof(int));
//array[0]=8