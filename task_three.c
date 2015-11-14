#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void printMas(int *mas, int len) {
	int i;
	for (i = 0; i < len; i++ ) 
		printf("%d\n", mas[i]);
}

void doDijkstra(int *a, int N) {
	
	int i,j,t;
	int temp, k;
	i = N - 2;
	while (i >= 0 && a[i] >= a[i+1]) 
		i--;

	if (i >= 0) {
		int j = i+1;
		while (a[i] < a[j+1]) 
			j++;
		temp = a[i];
		a[i] = a[j];
		a[j] = temp;
	}	
	else
		return;

	for (j = i+1, k = N-1; j < k; j=j+1, k=k-1) {
		temp = a[j];
		a[j] = a[k];
		a[k] = temp;
	}
	printMas(a, N);
	doDijkstra(a, N);
}

void Dijkstra(int N) {
	int i;
	int *set = malloc(sizeof(int)*N);
	printf("Длина = %d\n", N);

	
	for (i = 0; i < N; i++){
		set[i] = i+1;
		printMas(set,N);
		doDijkstra(set, N);
	}	
}

void recover (int *inv, int *result, int N){
	int current = 1;
	int i, k, j;

	for (i=0;i<N;i++)
		result[i] = 0;

	for (k=0; k<N; k++)
	{
		j=0;
		for (i=0;i<N;i++)
		{
			if(result[i]==0)
			{
				if (j==inv[k]){
					result[i] = current;
					break;
				}
				else
					j++;
			}
		}
		current++;	
	}
}
void nextInv(int *inv, int*P, int N){
	int i = N-2;
	int flag = 1;
	int x,k;

	while(flag == 1 ) {
		x = inv[i]+1;
		if (x > N-i-1) {
			inv[i] = 0;
			i--;
		}
		else
		{
			inv[i] = x;
			flag = 0;
		}
	}
	recover(inv,P, N);

	printMas(P,N);

	k=0;
	for(i=N-1; i>0;i--)
		if (inv[i-1] > inv[i])
			k++;
	if (k == N-1)
		return;
	nextInv(inv,P, N);
}

void Enumerating(int N) {
	int *inv = malloc(sizeof(int)*N);
	int *P = malloc(sizeof(int)*N);
	int i;

	for (i=0; i < N; i++ )
		inv[i] = 0;

	recover(inv,P, N);
	printMas(P,N);
	nextInv(inv, P, N);

}

int main(){
	int N;
	char ch;

	puts("Введите N:");
	scanf("%d",&N);

	puts("Выберите тип перестановки");
	puts("1 - Дейкстра");
	puts("2 - Перебор всех таблиц инверсий");

	scanf("%i",ch);
	switch(ch){
	case '1':
		puts("Вы выбрали Дейкстру");
		Dijkstra(N);
		break;
	case '2':
		puts("Вы выбрали перебор всех таблиц инверсий");
		Enumerating(N);
		break;
	default:
		puts("Что-то не то :)");		
	}
	puts("Press any key to exit");
	getch();
	return 0;
}