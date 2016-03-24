#include <stdio.h>
#include "D:\proga\library.h"

int main (int argc, char* argv[]){

	FILE* fileik; 
	fileik = fopen(argv[1], "rb");

	if( NULL == fileik ) { 
		printf( "Cannot open file\n" ); 
		return -1; 
	} 
	else reader(fileik);

	return 0;
}