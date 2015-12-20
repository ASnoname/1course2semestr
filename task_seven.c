#include <stdio.h>
#include <stdlib.h>

void swap (int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
}
void piramida(int n, int a[])
{
  int i, sh = 0, b = 0;

  while (1)
  {
    b = 0;
    for (i = 0; i < n; ++i)
    {
      if (i*2 + 2 + sh < n)
      {
        if (a[i+sh] > a[i*2 + 1 + sh] || a[i + sh] > a[i*2 + 2 + sh])
	       {
          	  if (a[i*2+1+sh] < a[i*2+2+sh])
          	  {
          	    swap (&a[i+sh], &a[i*2+1+sh]);
          	    b = 1;
          	  }
          	  else if (a[i*2+2+sh] < a[i*2+1+sh])
          	  {
          	    swap (&a[i+sh],&a[i*2+2+sh]);
          	    b = 1;
          	  }
	       }
      }
      else if (i * 2 + 1 + sh < n)
      {
        if (a[i+sh] > a[i*2+1+sh])
	      {
        	  swap (&a[i+sh], &a[i*2+1+sh]);
        	  b=1;
	      }
      }
    }
    if (!b) sh++;
    if (sh+2==n)
      break;
  }
}

void run(int a[], int first, int last)
{
    int i = first, j = last, x = a[(first + last) / 2]; int t;

    do {
        while (a[i] < x) i++;
        while (a[j] > x) j--;

        if(i <= j) {
            if (a[i] > a[j])
                swap(&a[i],&a[j]);
            i++;
            j--;
        }
    } while (i <= j);

    if (i < last)
        run(a, i, last);
    if (first < j)
        run(a, first, j);
}

int main(int argc, char *argv[]){

  char* first; char* second; int* third;

  if(argc != 4){
    printf("ERROR 1");
    return 0;
  }
  else {
    sscanf(argv[1], "%s", &first);
    sscanf(argv[2], "%s", &second);
    sscanf(argv[3], "%i", &third);
  }  

  FILE* file_in;
  file_in = fopen(argv[1], "rb");

  if(file_in == NULL){
    printf("ERROR 2");
    return 0;
  }

  int stolb = third;
  char x; int d = 0; int k,l,z; 

  const size = 10;  const max_sym = 100;
  char** count = malloc(sizeof(char*)*size); char* temp_count = malloc(sizeof(char)*max_sym);

  for (k = 0; k < size; k++)
  {
    for (l = 1; l < stolb; l++)
    {
      do{
        x = fgetc(file_in);
      } while(x != 9);
    }
    
    d = 0;

    for (z = 0; z < max_sym; z++)
      temp_count[z] = 0;

    do{
        x = fgetc(file_in);
        temp_count[d] = x;
        d++;
      } while(x != 9);
    temp_count[d] = '\0';  

    *count[k] = *temp_count;

    printf("%s\n", count[k]);
  
    do{
        x = fgetc(file_in);
      } while(x != '\n');
  }






    
  return 0;
}