#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mmm(int lenNewStr, int lenSearch){
	int m = lenNewStr - lenSearch;
	return m;
}
 int xxx(char *strIn, char *search, int lenIn, int lenSearch){
 	int i,j; int x = 0;

 	for (i = 0; i < lenIn; i++)
	{
		if (strIn[i] == search[0]) {
			for (j = 1; j < lenSearch; j++) {
				if (strIn[i + j] != search[j])
					break;
			}
		}
		if (j == lenSearch) {
			x++;
			j = 0;
		}
	}

	return x;
 }

int count(char* strIn, char *search, char *newStr){
	int m; int x = 0;

	int lenIn = strlen(strIn);
	int lenSearch = strlen(search);
	int lenNewStr = strlen(newStr);
	int i = 0, j = 0, t;

	m = mmm(lenNewStr,lenSearch);
	x = xxx(strIn,search,lenIn,lenSearch);

	t = x*m;
	
	return t;
}

int findAndReplace(char* strIn, char *search, char *newStr, int t) {

printf("dd");
	if (strIn == NULL)
		return 0;

	int i = 0, j = 0; int x; int m;
	int lenIn = strlen(strIn);
	int lenSearch = strlen(search);
	int lenNewStr = strlen(newStr);

	m = mmm(lenNewStr,lenSearch);
	x = xxx(strIn,search,lenIn,lenSearch);

	printf("String in: %s\n", strIn);
	printf("String for search: %s\n", search);
	printf("String for replace: %s\n", newStr);

	if(lenIn>t)
		t = lenIn;

	char *strTemp = malloc(sizeof(char)*t);
	char *strTemper = malloc(sizeof(char)*t);
	memset(strTemper, 0, t);
	memset(strTemp, 0, t);
	
	for (i = 0; i < lenIn; i++)
		strTemper[i] = strIn[i];

	i = 0;

	while (strTemper[i] != '\0') {
		if (strTemper[i] == search[0]) {
			for (j = 1; j < lenSearch; j++) {
				if (strTemper[i + j] != search[j])
					break;
			}
			if (j == lenSearch) {
				memcpy(strTemp, strTemper, i);
				memcpy(&strTemp[i], newStr, lenNewStr);
				memcpy(&strTemp[i + lenNewStr], &strTemper[i + lenSearch], strlen(strTemper) - i - lenSearch+1);
				memcpy(strTemper, strTemp, strlen(strTemp));
				i += lenNewStr - 1;
			}
		}
		i++;
	}
	
	strTemper[t+x*m] = '\0';

	free(strTemp);

	return strTemper;
}
/*
int isSmall(char ch) {
	if ((ch >= 97 && ch <= 122) || (ch >= 224 && ch <= 255)) 
		return 1;
	else 
		return 0;
}

char getUpper (char ch) {
	char retVal;
	if (ch >= 97 && ch <= 122) {
		retVal = ch - 32;
	} else if (ch >= 224 && ch <= 255) {
		retVal = ch - 32;
	} else {
		retVal = '0';
	}
	return retVal;
}

void Capitalization() {
	char str[] = "hi. hi";
	int len = strlen(str);
	int i;

	printf("String in: %s\n", str);
	for(i=0;i<len;i++){
		if ( isSmall(str[i]) == 1 ) 
		{
			if (i==0 || (i==1 && str[0] == ' ')) 
				str[i] =getUpper(str[i]);
			if (i>1)
				if (str[i-1] == ' ' && str[i-2]=='.')
					str[i] = getUpper(str[i]);
		}
	}
	printf("New String: %s\n", str);
	free(str);	
}

int isSpecSymblol(char ch) {
	switch (ch) {
	case '.':
		return 1;
	case ',':
		return 1;
	case '!':
		return 1;
	case '?':
		return 1;
	case ':':
		return 1;
	default:
		return 0;
	}
}

void Spacing(char* str) {

	int len = strlen(str);
	int i;
	printf("String in: %s\n", str);
	for (i = 0; i < len; i++)
	{
		if (str[i] == ' ')
		{
			if (str[i+1] == ' '){
				printf("%c",str[i]);
				i++;
			}
			else if (isSpecSymblol(str[i+1]) == 1)
			{
				printf("%c", str[i+1]);
				printf(" ");
				i +=2;
			}
		}
		if (isSpecSymblol(str[i]) == 1)
		{
			if ((str[i+1] != ' ') && (isSpecSymblol(str[i+1]) == 0))
			{
				printf("%c", str[i]);
				printf(" ");
			}
		}
		else 
			printf("%c", str[i]);
	}
	free(str);
}


void toTranslit() {
	char *str = "Привет"; 
	int len = strlen(str);
	int i;
	printf("String in: %s\n", str);
	printf("New String: ");
	for (i=0; i<len;i++) {

		switch(str[i]) {
		case 'а': printf("a"); break;
		case 'б': printf("b"); break;
		case 'в': printf("v"); break;
		case 'г': printf("g"); break;
		case 'д': printf("d"); break;
		case 'е': printf("e"); break;
		case 'ё': printf("e"); break;
		case 'з': printf("z"); break;
		case 'и': printf("i"); break;
		case 'й': printf("i"); break;
		case 'к': printf("k"); break;
		case 'л': printf("l"); break;
		case 'м': printf("m"); break;
		case 'н': printf("n"); break;
		case 'о': printf("o"); break;
		case 'п': printf("p"); break;
		case 'р': printf("r"); break;
		case 'с': printf("s"); break;
		case 'т': printf("t"); break;
		case 'у': printf("u"); break;
		case 'ф': printf("f"); break;
		case 'х': printf("h"); break;
		case 'ъ': break;
		case 'ы': printf("y"); break;
		case 'ь': break;
		case 'э': printf("e"); break;
		case 'ж': printf("zh"); break;
		case 'ц': printf("tc"); break;
		case 'ч': printf("ch"); break;
		case 'ш': printf("sh"); break;
		case 'ю': printf("yu"); break;
		case 'я': printf("ya"); break;
		case 'щ': printf("shch"); break;
		case 'А': printf("A"); break;
		case 'Б': printf("B"); break;
		case 'В': printf("V"); break;
		case 'Г': printf("G"); break;
		case 'Д': printf("D"); break;
		case 'Е': printf("E"); break;
		case 'Ё': printf("E"); break;
		case 'З': printf("Z"); break;
		case 'И': printf("I"); break;
		case 'Й': printf("I"); break;
		case 'К': printf("K"); break;
		case 'Л': printf("L"); break;
		case 'М': printf("M"); break;
		case 'Н': printf("N"); break;
		case 'О': printf("O"); break;
		case 'П': printf("P"); break;
		case 'Р': printf("R"); break;
		case 'С': printf("S"); break;
		case 'Т': printf("T"); break;
		case 'У': printf("U"); break;
		case 'Ф': printf("F"); break;
		case 'Х': printf("H"); break;
		case 'Ъ': break;
		case 'Ы': printf("Y"); break;
		case 'Ь': break;
		case 'Э': printf("E"); break;
		case 'Ж': printf("Zh"); break;
		case 'Ц': printf("Tc"); break;
		case 'Ч': printf("Ch"); break;
		case 'Ш': printf("Sh"); break;
		case 'Ю': printf("Yu"); break;
		case 'Я': printf("Ya"); break;
		case 'Щ': printf("Shch"); break;
		default:
			printf("%c",str[i]);
		}
	}
	free(str);
}

void fromTranslit(char* str) {
	
	int len=strlen(str);
	int i,j;
	printf("String in: %s\n", str);
	printf("New String: ");
	for(i=0; i< len; i++) {
		switch(str[i]) {
		case 'a': printf("а"); break;
		case 'b': printf("б"); break;
		case 'v': printf("в"); break;
		case 'g': printf("г"); break;
		case 'd': printf("д"); break;
		case 'e': printf("е"); break;
		case 'i': printf("и"); break;
		case 'k': printf("к"); break;
		case 'l': printf("л"); break;
		case 'm': printf("м"); break;
		case 'n': printf("н"); break;
		case 'o': printf("о"); break;
		case 'p': printf("п"); break;
		case 'r': printf("р"); break;
		case 'u': printf("у"); break;
		case 'f': printf("ф"); break;
		case 'h': printf("х"); break;
		case 'A': printf("А"); break;
		case 'B': printf("Б"); break;
		case 'V': printf("В"); break;
		case 'G': printf("Г"); break;
		case 'D': printf("Д"); break;
		case 'E': printf("Е"); break;
		case 'I': printf("И"); break;
		case 'K': printf("К"); break;
		case 'L': printf("Л"); break;
		case 'M': printf("М"); break;
		case 'N': printf("Н"); break;
		case 'O': printf("О"); break;
		case 'P': printf("П"); break;
		case 'R': printf("Р"); break;
		case 'U': printf("У"); break;
		case 'F': printf("Ф"); break;
		case 'H': printf("Х"); break;

		case 'c': 
			if (str[i+1] == 'h'){
				printf("ч");
				i++;
			}
			break;
		case 'C': 
			if (str[i+1] == 'h'){
				printf("Ч"); 
				i++;
			}
			break;
		case 'z': 
			if (str[i+1] == 'h') {
				printf("ж");
				i++;
			}
			else
				printf("з");		
			break;
		case 'Z': 
			if (str[i+1] == 'h') {
				printf("Ж");
				i++;
			}
			else
				printf("З");		
			break;
		case 'Y': 
			if(str[i+1] == 'a' ) {
				printf("Я");
				i++;
			}
			else if (str[i+1] == 'u') {
				printf("Ю");
				i++;
			} else
				printf("Э");
			break;
		case 'y': 
			if(str[i+1] == 'a' ) {
				printf("я");
				i++;
			}
			else if (str[i+1] == 'u') {
				printf("ю");
				i++;
			} else
				printf("э");
			break;

		case 't': 
			if (str[i+1] == 's') {
				printf("ц");
				i++;
			}
			else
				printf("т");
			break;
		case 'T': 
			if (str[i+1] == 's') {
				printf("Ц");
				i++;
			}
			else
				printf("Т");
		case 's':
			if (str[i+1]=='h') {
				if (str[i+2]=='c' && str[i+3]=='h') {
					printf("щ");
					i += 3;
				}	
				else{
					printf("ш");
					i++;
				}	
			}
			else
				printf("с");
			break;
		case 'S':
			if (str[i+1]=='h') {
				if (str[i+2]=='c' && str[i+3]=='h') {
					printf("Щ");
				    i += 3;
				}    
				else{
					printf("Ш");
					i++;
				}
			}
			else
				printf("С");
			break;

		default:
			printf("%c",str[i]);
		}
	}
	free(str);
} */

int main(){
//	char *str = "Shchirokaya";
//	char *string = "In this string ,perhaps,many spaces.";
	char *strIn = "hi, peace!";
	int i; char *search[2]; char *newStr[2];
	search[0] = "hi";
	search[1] = "peace";
	newStr[0] = "bye";
	newStr[1] = "war";
	int t2; int t = 0; int k; int lenIn = strlen(strIn);

	for (k = 0; k < 2; k++)
	{
		t2 = count(strIn,search[k],newStr[k]);
		t += t2;
	}
	t += lenIn + 1;

	char *perem = malloc(sizeof(char)*t);
	char *perem2 = malloc(sizeof(char)*t);

//	puts("Test1 - find and replace");

	perem = findAndReplace(strIn,search[0],newStr[0],t);  

	for ( i = 1; i < 2; i++){
		perem2 = findAndReplace(perem,search[i],newStr[i],t);  
		free(perem);
		perem = perem2;
	}	

	printf("NEW String: %s\n", perem);     
	free(perem);      

//	puts("\nTest2 - Capitalization");      
//	Capitalization();                      

//	puts("\nTest3 - Space corection");     
//	Spacing(string);						   

//	puts("\nTest4.1 - to Translit");       
//	toTranslit();                          

//	puts("\nTest4.2 - from Translit");     
//	fromTranslit(str);                        
 
//	puts("\nPress any key to exit");
	getch();
	return 0;
}