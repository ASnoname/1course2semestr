#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const max_strok = 500;
const max_stroki = 100;
const max_file = 5;

void heapify (char* arr[], char* arrHelp[], int heapsize, int index) {
	int left = (index + 1) * 2 - 1;
	int right = (index + 1) *2;
	int max = 0;
	char* temp; char* tempHelp;
	if (left < heapsize && strcmp(arrHelp[left], arrHelp[index]) > 0){
		max = left;
	} else
		max = index;
	
	if (right < heapsize && strcmp(arrHelp[right], arrHelp[max]) > 0) 
		max = right;
	
	if (index != max){
		temp = arr[index];
		arr[index] = arr[max];
		arr[max] = temp;
		tempHelp = arrHelp[index];
		arrHelp[index] = arrHelp[max];
		arrHelp[max] = temp;
		heapify (arr, arrHelp, heapsize, max);
	}
}

void heapsort (char* arr[], char* arrHelp[], int left, int right) {
	int heapsize = right + 1; int i;
	char* temp; char* tempHelp;
	for (i = (heapsize - 1) / 2; i >= left; i--){
		heapify (arr, arrHelp, heapsize, i);
	}
	for (i = right; i > 0; i--){
		temp = arr[i];
		arr[i] = arr[left];
		arr[left] = temp;
		tempHelp = arrHelp[i];
		arrHelp[i] = arrHelp[left];
		arrHelp[left] = tempHelp;
		heapsize--;
		heapify (arr, arrHelp, heapsize, 0);
	}
}

int partition (char* arr[], char* arrHelp[], int left, int right) {
	char* pivot = arr[right];
	char* pivotHelp = arrHelp[right];
	char* temp; char* tempHelp;
	int i = left; int j;
	for (j = left; j < right; j++){
		if (strcmp(arrHelp[j], pivotHelp) <= 0){
			temp = arr[j];
			arr[j] = arr[i];
			arr[i] = temp;
			tempHelp = arrHelp[j];
			arrHelp[j] = arrHelp[i];
			arrHelp[i] = tempHelp;
			i++;
		}
	}
	arr[right] = arr[i];
	arr[i] = pivot;
	arrHelp[right] = arrHelp[i];
	arrHelp[i] = pivotHelp;
	return i;
}

void introsort_r (char* arr[], char* arrHelp[], int left, int right, int maxdepth) {
	if (right > left){
		if (maxdepth == 0){
			heapsort (&arr[left], &arrHelp[left], 0, right - left);
			return;
		}
		int pivot = partition (arr, arrHelp, left, right);
		introsort_r (arr, arrHelp, left, pivot - 1, maxdepth - 1);
		introsort_r (arr, arrHelp, pivot, right, maxdepth - 1);
	}
}


void introsort (char* arr[], char* arrHelp[], int length) {
	int maxdepth = 2 * log(length);
	introsort_r (arr, arrHelp, 0, length - 1, maxdepth);
}


int find_max (char *arr[], int length) {
	char* max;
	int index = 0; int i;
	for (i = 0; i < length; i++){
		if (arr[i] == NULL){
			continue;
		}
		if (strcmp (arr[i], max) < 0){
			max = arr[i];
			index = i;
		}
	}
	return index;
}

int split (FILE* input_file, int stolb) {
	int file_count = 1;
	int j = 1; int i = 0; int eof = 0;
	char *arr[max_strok];
	char *arrHelp[max_strok];
	char* rc; int arr_size;
	char str[max_file];
	while (1){
		i = 0;
		eof = 0;
		while(1){
			if (max_strok == i)
				break;
			arr[i] = calloc (max_stroki, 2);
			arrHelp[i] = arr[i];
			rc = fgets(arr[i], max_stroki, input_file);
			j = 1;
			if (rc == NULL){
				eof = 1;
				break;
			}
			while (1){
				if (j == stolb) break;
				if (*(arrHelp[i]++) == 9) j++;
			} 
			i++;
		}
		arr_size = i;
		introsort(arr, arrHelp, i);
		sprintf (str, "%d", file_count);
		file_count++;
		FILE* temp = fopen (str, "w");
		if (temp == NULL){
			printf("ERROR 4");
			for (i = 0; i < arr_size; i++)
				free (arr[i]);
			fclose (temp);
			return -1;
		}
		for (i = 0; i < arr_size; i++){
	        fprintf(temp, "%s", arr[i]);
			free (arr[i]);
	    }
		fclose (temp);
		if (1 == eof){
			return --file_count;
			break;
		}
	}
}

void cleanup (int file_count) {
	int i;
	for (i = 1; i <= file_count; i++){
		char str[max_file];
		sprintf (str, "%d", i);
		remove (str);
	}
}

int merge (FILE* output_file, int file_count) {
	FILE* file_arr[file_count];
	int j = 0; int i; char str[max_file];
	for (i = 1; i <= file_count; i++){
		sprintf (str, "%d", i);
		file_arr[j] = fopen (str, "r");
		if (file_arr[j] == NULL){
			printf("ERROR 5");
			return -1;
		}
		j++;
	}
	char* str_arr[file_count];
	char* rc;
	for (i = 0; i < file_count; i++){
		str_arr[i] = calloc (max_stroki, 1);
		rc = fgets (str_arr[i], max_stroki, file_arr[i]);
		if (rc == NULL){
			free (str_arr[i]);
			str_arr[i] = NULL;
		}
	}
	int empty = 0;
	int index;
	while (1) {
		index = find_max (str_arr, file_count);
		if (str_arr[index] == NULL)
			break;
		fprintf(output_file, "%s", str_arr[index]);
		rc = fgets (str_arr[index], max_stroki, file_arr[index]);
		if (rc == NULL){
			free (str_arr[index]);
			str_arr[index] = NULL;
			empty++;
		}
		if (empty >= file_count)
			break;
	}
	for (i = 0; i < file_count; i++){
		free(str_arr[i]);
		fclose (file_arr[i]);
	}
	return 0;
}

int main (int argc, char* argv[]) {
	if (4 != argc){
		printf("ERROR 1");
		return -1;
	}
	FILE* input_file = fopen (argv[1], "r");
	if (input_file == NULL){
		printf("ERROR 2");
		return -1;
	}
	int help = argv[3][0]-'0';
	int file_count = split (input_file, help);
	if (file_count == -1){
		fclose (input_file);
		return -1;
	}
	if (file_count > max_strok){
		printf("ERROR 3");
		cleanup (file_count);
		fclose (input_file);
		return -1;
	}
	FILE* output_file = fopen (argv[2], "w");
	int rc = merge (output_file, file_count);
	if (rc == -1){
		cleanup (file_count);
		fclose (input_file);
		return -1;
	}
	cleanup (file_count);
	fclose (input_file);
    return 0;
}