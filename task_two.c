#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define DIG "0123456789ABCDEFGHIGKLMNOPQRSTUVWXYZ"

void Proverka_one(int i){ 
    if(i<2||i>36){
        puts("Ошибка: СС должна быть в пределе [2...36]");
        exit(1);
    }
}

void Proverka_two(char* a, int ss_one){  
	int i,len;
	int block2 = 0;
	int error = 0;

	if (ss_one > 10 )
		block2 = ss_one - 10;
	len = strlen(a);

    if(ss_one<=36){
        for(i=0; i<len; i++){
			if(a[i]<48) {
				if (a[i]!='.'){
					error = -1; 
					break;
				}
			}
			else if (a[i]>57 && a[i]<65) {
				error = -1; 
				break;
			}
			else if(a[i]>(64+block2)) {
				error = -1; 
				break;
			}
        }		
    }
	if (error != 0) {
                printf("Ошибка: все символы числа должны быть заключены между [0...%d]", ss_one-1);
                exit(1);
	}
}
 
int MyAtoi(char *s, int p){
    int i, a, digit[256] = {0};
    for(i = 0; DIG[i]; i++)
        digit[DIG[i]] = i;
    for(i = a = 0; s[i]; i++)
        a = a * p + digit[s[i]];
    return a;
}

 
void MyItoa(int a, int p, char *s) {
   static int i = 0, n;
   if (a) {
      ++i;
	MyItoa(a / p, p, s);
      s[n - i--] = DIG[a % p];
   }
   else
      s[n = i] = '\0';
}

double MyAtof(char *s, int p){
	double retValue= 0.0000000;
	double d = (1/(double)p); 

	int len = strlen(s), i;
	int a, digit[256] = {0};
	for(i = 0; DIG[i]; i++)
        	digit[DIG[i]] = i;
	for (i=0;i<len;i++) {
		retValue += digit[s[i]]*d;
		d = (d/(double)p);
	} 
	return retValue;
}

void MyFtoa(double a, int p, char *s){
	double res = a;
	int i = 0, k;
	do {
		res *= (double)p;
		if (res < 1.0000000)	
			s[i]='0';
		else {
			k = (int)res;
			s[i] = DIG[k];
			res -= (double)k;
		}			
		i++;		
	} while ( (res - 0.0000000) > 0.00000001 && i < 30);
}



void transfer(int base, char *value, int to) { 
	char real[1024]={'\0'}, integer[1024]={'\0'};
	char s1[1024]={'\0'}, s2[32]={'\0'};
	double d;
	
	int i, j, len, dot;

	dot = 0;
	len = strlen(value);
	j=0;	
	for (i=0;i<len;i++) {
		if(value[i]=='.') {
			dot = 1;
		}
		else {
			if(dot == 0) {
				integer[i] = value[i];
			}
			else {
				real[j] =  value[i];
				j++;
			}
		}
	}

	MyItoa(MyAtoi(integer, base), to, s1);
	if(dot!= 0) {
		d = MyAtof(real, base);
		MyFtoa(d,to,s2);
		printf("%s.%s\n",s1,s2);
	}
	else
		printf("%s\n",s1);
}
 
int main(){
   	int i=0, ss_one, ss_two;
	char a[100]={'\0'}, b[100], *p=a;

	scanf("%i",&ss_one);
	Proverka_one(ss_one);

	scanf("%s",a);
	Proverka_two(a, ss_one);

	scanf("%i",&ss_two);
	Proverka_one(ss_two);

	transfer(ss_one, a, ss_two);
	puts("Нажмите на любую клавишу");
	getch();
	
	return 0;
}