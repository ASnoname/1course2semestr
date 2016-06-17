#include "library2.h"

int proverka(char* stroka){

	if (((stroka[0] < '0') || (stroka[0] > '9')) && (stroka[0] != '-'))
		return -1;

	if ((stroka[0] == '0') && (stroka[1] != ','))
		return -1;
	
	if (((stroka[0] == '-') || (stroka[0] == '+')) && (stroka[1] == ','))
		return -1;
	
	if (((stroka[0] == '-') || (stroka[0] == '+')) && (stroka[1] == '0') && (stroka[2] != ','))
		return -1;

	int i; int k = 0;
	for (i = 1; i < strlen(stroka); i++)
	{
		if (((stroka[i] < '0') || (stroka[i] > '9')) && (stroka[i] != ','))
			return -1;	
		
		if (stroka[i] == ',')
			k++;

		if (k > 1)
			return -1;	
	}

	return 0;//+++
}

void write_str(long_number* prnum){

	int d;
	for (d = 0; d < prnum->length; d++)
		printf("%d\n", prnum->number[d]);
}

void reader(char* tempstroka, long_number* structure){//+++

	int h = 0;
	if (tempstroka[0] == '-'){
		h = 1;
		structure->znak = '-';
	}	
	else structure->znak = '+';

	int i = 1;
	while (tempstroka[i] != ',') i++;
	structure->comma = i-h;

	structure->number = calloc(strlen(tempstroka)-1-h,sizeof(int));

	int j;
	for (j = 0; j < structure->comma; j++)
		structure->number[j] = tempstroka[j+h] - 48;

	for (j = structure->comma; j < strlen(tempstroka)-1-h; j++)
		structure->number[j] = tempstroka[j+1+h] - 48;

	structure->length = strlen(tempstroka)-1-h;
}

int maxdiff(int a, int b){

	if (a >= b)
		return 1;
	else return 0;
}

void alignment(long_number* first, long_number* second){//+++

	int max = maxdiff(first->comma,second->comma);

	if (max == 1)
	{
		int diff = first->comma - second->comma;
		second->comma = first->comma;
		second->number = realloc(second->number,(second->length + diff)*sizeof(int));
		int i;

		for (i = second->length-1; i >= 0; i--)
			second->number[i+diff] = second->number[i];

		second->length += diff;

		for (i = 0; i < diff; i++)
			second->number[i] = 0;
	}
	else {
		int diff = second->comma - first->comma;
		first->comma = second->comma;
		first->number = realloc(first->number,(first->length + diff)*sizeof(int));
		int i;

		for (i = first->length-1; i >= 0; i--)
			first->number[i+diff] = first->number[i];

		first->length += diff;

		for (i = 0; i < diff; i++)
			first->number[i] = 0;
	}

	int diff = first->length - second->length;

	if (diff > 0)
	{
		second->number = realloc(second->number,sizeof(int)*(second->length + diff));
		second->length += diff;
		int i;		
		for (i = second->length - diff; i < second->length; i++)
			second->number[i] = 0;
	}
	else if (diff < 0)
	{
		first->length -= diff;
		first->number = realloc(first->number,sizeof(int)*(first->length - diff));
		int i;
		for (i = first->length + diff; i < first->length; i++)
			first->number[i] = 0;
	}
}

void cleaner(long_number* result,int i){//+++

	if (result->number[i] < 0)
	{
		result->number[i] += 10; 
		result->number[i-1] -= 1;
	}

	else if (result->number[i] > 9)
	{
		result->number[i] %= 10;
		result->number[i-1]++;
	}
}

char* int_to_string(long_number* result){

	int znachek = 0;
	if(result->znak == '-')
		znachek = 1;

	if ((result->number[0] == 0) && (result->number[1] == 0) && (result->comma = 2))
	{
		char* strochka = calloc((result->length + znachek),sizeof(char));

		int i = 0;
		if(znachek){
			strochka[i] = '-';
			i++;
		}

		strochka[i] = '0';
		i++;
		strochka[i] = ',';
		i++;

		int j = 2;
		while(j != result->length){

			strochka[i] = result->number[j] + 48;
			i++;
			j++;
		}	

		return strochka;
	}

	else if ((result->number[0] == 0) && (result->number[1] != 0))
	{
			char* strochka = calloc((result->length + znachek),sizeof(char));

			int i = 0;
			if(znachek){
				strochka[i] = '-';
				i++;
			}

			int j;
			for(j = 1; j < result->comma; j++){

				strochka[i] = result->number[j]+48;
				i++;
			}

			strochka[i] = ',';
			i++;

			while(j != result->length){

				strochka[i] = result->number[j] + 48;
				i++;
				j++;
			}	

			return strochka;
	}

	else if (result->number[0] != 0)
	{
		char* strochka = calloc((result->length+znachek+1),sizeof(char));
		
		int i = 0;
		if(znachek){
			strochka[i] = '-';
			i++;
		}

		int j;
		for(j = 0; j < result->comma; j++){

			strochka[i] = result->number[j]+48;
		
			i++;
		}

		strochka[i] = ',';
		i++;

		while(j != result->length){

			strochka[i] = result->number[j] + 48;
							
			i++;
			j++;
		}	
		return strochka;
	}
}	

// void clean_nuls(long_number** chiselka){
// 	int i = (*chiselka)->length;
// 	while((i > ((*chiselka)->comma))&&((*chiselka)->number[i-1] == 0))
// 		i--;

// 	(*chiselka)->length = i;
// 	(*chiselka)->number = realloc((*chiselka)->number,(*chiselka)->length*sizeof(int));
// }

// void rounding(long_number** chiselka, int after_point){
	
// 	int after = (*chiselka)->length - (*chiselka)->comma;
// 	int diff = after_point - after;

// 	if(diff > 0){//если занков после запятой меньше чем надо
// 		(*chiselka)->number = realloc((*chiselka)->number,((*chiselka)->length+diff)*sizeof(int));
// 		int i;
// 		for(i = (*chiselka)->length; i < (*chiselka)->length + diff; i++)
// 			(*chiselka)->number[i] = 0;
// 		(*chiselka)->length += diff;
// 	}

// 	else if(diff < 0){//после запятой больше чем надо
// 		if((*chiselka)->number[(*chiselka)->comma + after_point] >= 4)
// 			(*chiselka)->number[(*chiselka)->comma + after_point-1]++;
// 		(*chiselka)->number = realloc((*chiselka)->number,((*chiselka)->length+diff)*sizeof(int));
// 		(*chiselka)->length +=diff;
// 	}
// }

char* summa(long_number* first, long_number* second, char operation){

	alignment(first, second);

	long_number* result = calloc(1,sizeof(long_number));

	result->number = calloc(first->length+1,sizeof(int));  
	result->length = first->length+1;

	int joys = 1;
	if (second->znak == '-')
		joys = -1;

	int joyf = 1;
	if (first->znak == '-')
		joyf = -1;

	if (operation == '-')
		joys *= -1;

	int i;
	for (i = first->length-1; i >= 0; i--)
		result->number[i+1] = joyf*first->number[i] + joys*second->number[i];
	
	for (i = result->length-1; i > 0 ; i--)
		cleaner(result,i);

	int k = 0;
	while(result->number[k] == 0)
		k++;

	if (k != result->length+1){	
		if(result->number[k] < 0){
		if(result->znak == '-')
			result->znak = '+';
		else result->znak = '-';

		while(k != result->length){ 
			result->number[k] *= -1;
			k++;
		}
	}
}

	for (i = result->length-1; i > 0 ; i--)
		cleaner(result,i);


	result->comma = first->comma + 1;

	return int_to_string(result);
}

void numeral_multi(long_number* first,long_number* second, long_number* result, int i, int h){

	int j; int p;
	for (j = first->length; j > 0; j--)
	{
		p = first->number[j-1] * second->number[i];

		result->number[j+i] += p;
	}
}

void cleaner_multi(long_number* result, int i){

	if (result->number[i] >= 10)
	{
		result->number[i-1] += result->number[i] / 10;
		result->number[i] %= 10;
	}
}

char* multiplication(long_number* tempone,long_number* temptwo, int accuracy){

	int i = 0; 
	int j = 0; int h = 0;

	long_number* result = calloc(1,sizeof(long_number));
	result->number = calloc((tempone->length+temptwo->length),sizeof(int));
	
	if (tempone->znak == temptwo->znak)
		result->znak = '+';
	if (tempone->znak != temptwo->znak)
		result->znak = '-';
	
	for (i = temptwo->length; i > 0; i-- ,h++)
		numeral_multi(tempone,temptwo, result, i-1,h);

	for (i = tempone->length+temptwo->length-1; i >= 0; i--) 
		cleaner_multi(result,i);

	result->comma = tempone->comma + temptwo->comma;

	result->length = tempone->length+temptwo->length;

	return int_to_string(result);
}

void point_move(long_number** tempone, long_number** temptwo){
	
	int after_point_one = (*tempone)->length - (*tempone)->comma;
	int after_point_two = (*temptwo)->length - (*temptwo)->comma;

	int deff = after_point_one - after_point_two;

	if(deff > 0){
		(*temptwo)->number = realloc((*temptwo)->number,((*temptwo)->length + deff)*sizeof(int));
		int i = (*temptwo)->length;
		(*temptwo)->length += deff;
		while(i != (*temptwo)->length){
			(*temptwo)->number[i] = 0;
			i++;
		}
	}

	if(deff < 0){
		(*tempone)->number = realloc((*tempone)->number,((*tempone)->length - deff)*sizeof(int));
		int i = (*tempone)->length;
		(*tempone)->length -= deff;
		while(i != (*tempone)->length){
			(*tempone)->number[i] = 0;
			i++;
		}
	}
}

int compare(long_number* tempone, long_number* temptwo){

	int i;
	int deff = temptwo->length - tempone->length;

	if(deff == 0){
		for (i = 0; i < tempone->length; i++)
			if (tempone->number[i] < temptwo->number[i])
				return 1;

		return 0;
	}	
	else if (deff > 0)
		return 1;
	else if(deff < 0)
		return 2;
}

long_number* mult_long_short(long_number* temptwo, int small){

	long_number* result = calloc(1,sizeof(long_number));
	result->number = calloc(temptwo->length+2,sizeof(int));
	result->length = temptwo->length+2;

	int i;
	for (i = temptwo->length; i > 0; i--)
		result->number[i] = temptwo->number[i-1]*small; 

	for(i = temptwo->length; i > 0; i--){

		if(result->number[i] > 9){
			result->number[i-1] += (result->number[i])/10;
			result->number[i] %= 10;
		}
	}

	if(result->number[0] == 0){

		for(i = 0; i < temptwo->length+1; i++)
			result->number[i] = result->number[i+1];

		result->length -=1;

		result->number = realloc(result->number,(result->length)*sizeof(int));
	} 

	result->comma = result->length - 1; // supermetka

	return result;
}

long_number* change_cifra(long_number* cut_number, char** result, long_number* temptwo, int* i){

	int cifra = 1;
	long_number* check = mult_long_short(temptwo, cifra);

	while ((compare(check, cut_number) != 2) && (cifra > 0)){ 

		cifra++;

		check = mult_long_short(temptwo, cifra);
	}

	(*result)[(*i)] = cifra+48;
	(*i)++;

	return mult_long_short(temptwo, cifra-1);
}

void delenie(char** result,	int result_after_point, int point_flag, long_number* tempone, long_number* temptwo, int* i){

	long_number* cut_number = calloc(1,sizeof(long_number));
	cut_number->number = calloc(temptwo->length,sizeof(int));

	int j;
	for (j = 0; j < temptwo->length; j++)
		cut_number->number[j] = tempone->number[j];

	cut_number->number = realloc(cut_number->number,(temptwo->length+1)*sizeof(int));
	cut_number->length = temptwo->length+1;

	long_number* multik = calloc(1,sizeof(long_number));
	multik->number = calloc(temptwo->length+1,sizeof(int));
	multik->length = temptwo->length;

	cut_number->number[temptwo->length] = 0; 
	multik->number[multik->length] = 0; 

	multik->length++;
	cut_number->comma = cut_number->length - 1; // supermetka

	write_str(cut_number);
	write_str(change_cifra(cut_number,result,temptwo,i));

	printf("%s\n", summa(cut_number,change_cifra(cut_number,result,temptwo,i),'-'));

	// reader(summa(cut_number,change_cifra(cut_number,result,temptwo,i),'-'),cut_number);

	printf("%s\n", cut_number);

	
}

char* division(long_number* tempone,long_number* temptwo, int accuracy){

	point_move(&tempone, &temptwo); 

	int point_flag = 0;
	int znak_flag = 0;
	int noliki = temptwo->length - tempone->length;

	if(noliki > accuracy+1)
		noliki = accuracy+1;
	
	char* result = calloc(MAX(tempone->length,temptwo->length) + accuracy,sizeof(char));

	int i;
	for(i = 0; i < (MAX(tempone->length,temptwo->length) + accuracy); i++)
		result[i] = '#';

	i = 0;
	if(tempone->znak != temptwo->znak){
		result[i] = '-';
		znak_flag++;
		i++;
	}

	if(noliki > 0){
		result[i] = '0';
		i++;
		result[i] = ',';
		i++;
		point_flag = 1;
		noliki--;
		int j = 0;
		while (j < noliki){
			result[i] = '0';
			j++;
			i++;
		} 

		if(j == accuracy+1){
			// char* resultik = calloc(j+point_flag+znak_flag+1,sizeof(char));
			// int m;
			// for(m = 0; m < j+point_flag+znak_flag+1; m++)
			// 	resultik[m] = result[m];

			return realloc(result,(j+point_flag+znak_flag+1)*sizeof(char));
		}

		tempone->number = realloc(tempone->number,(tempone->length + noliki)*sizeof(int));

		int k;
		for(k = tempone->length; k < noliki + tempone->length; k++)
			tempone->number[k] = 0;

		tempone->length += noliki;
	} 

	int result_after_point = 0;

	if (noliki < 0)
		result_after_point = -1 * noliki;
	else result_after_point = noliki;

	int p = compare(tempone, temptwo);

	if(p == 1){
		result[i] = '0';
		result_after_point++;
		tempone->number = realloc(tempone->number,(tempone->length + 1)*sizeof(int));

		tempone->number[tempone->length] = 0;
		tempone->length++;
	}//обрабатывает случаи, когда надо дописать нолики для уравнивания длинны и дописывает нолики в ответ и первое число

	delenie(&result,result_after_point,point_flag,tempone,temptwo,&i);

	return "123123";
}

char* lib(char* firstlongnumber, char* secondlongnumber, char operation, int accuracy){

	int t1 = proverka(firstlongnumber); 
	if (t1 == -1) 
		return "error";
	int t2 = proverka(secondlongnumber); 
	if (t2 == -1) 
		return "error";
	if ((operation != '*') && (operation != '+') && (operation != '-') && (operation != '/'))
		return "error";

	long_number* tempone = calloc(1,sizeof(long_number));
	long_number* temptwo = calloc(1,sizeof(long_number));

	reader(firstlongnumber,tempone);  
	reader(secondlongnumber,temptwo); 

	if (operation == '*')
		return multiplication(tempone,temptwo,accuracy);

	if ((operation == '+') || (operation == '-')){
		char* result = summa(tempone,temptwo,operation);
		return result;
	}	

	if (operation == '/')
		return division(tempone,temptwo,accuracy);
}