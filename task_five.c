#include "LongNumber.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int check(char *string)
{
    int len = strlen(string);
 
    if (0 == len)
    {
        return len;
    }
 
    int index = 0;
 
    if ('-' == string[0])
    {
        index++;
    }
 
    for (; index < len; index++)
    {
        if ('.' == string[index])
        {
            index++;
            break;
        }
 
        if (!isdigit(string[index]))
        {
            return 0;
        }
    }
 
    for (; index < len; index++)
    {
        if (!isdigit(string[index]))
        {
            return 0;
        }
    }

    return 1;
}

LongNumber strip(LongNumber number)
{
	int preceding = 0;
	int following = 0;

	int i;
	for (i = number.integer_size - 1; i >= 0 && 0 == number.integer[i]; i--)
	{
		preceding++;
	}

	for (i = number.fractional_size - 1; i >= 0 && 0 == number.fractional[i]; i--)
	{
		following++;
	}

	if (preceding > 0)
	{
		number.integer_size -= preceding;
		number.integer = realloc(number.integer, number.integer_size);
	}

	if (following > 0)
	{
		number.fractional_size -= following;
		number.fractional = realloc(number.fractional, number.fractional_size);
	}

	if (0 == number.fractional_size && 0 == number.integer_size)
	{
		number.sign = 1;
	}

	return number;
}

int abs_compare(LongNumber a, LongNumber b)
{
	if (a.integer_size == b.integer_size)
	{
		int i;
		for (i = a.integer_size - 1; i >= 0; i--)
		{
			int diff = a.integer[i] - b.integer[i];

			if (0 != diff)
			{
				return diff;
			}
		}

		int delim = min(a.fractional_size, b.fractional_size);

		for (i = 0; i < delim; i++)
		{
			int diff = a.fractional[i] - b.fractional[i];

			if (0 != diff)
			{
				return diff;
			}
		}

		return a.fractional_size - b.fractional_size;
	}

	return a.integer_size - b.integer_size;
}

int compare(LongNumber a, LongNumber b)
{
	if (a.sign != b.sign)
	{
		return a.sign * 2 + b.sign;
	}

	return abs_compare(a, b);
}

LongNumber zero()
{
	LongNumber result;

	result.sign = 1;
	result.fractional_size = 0;
	result.integer_size = 0;
	result.fractional = NULL;
	result.integer = NULL;

	return result;
}

LongNumber parse(char *string)
{
	LongNumber result;

	#define SIGN '-'

	char *sign = strchr(string, SIGN);

	if (NULL != sign)
	{
		result.sign = NEGATIVE_SIGN;
		sign++;
	}
	else
	{
		result.sign = 1;
		sign = string;
	}

	char *point = strpbrk(string, ",.");

	int totalLength = strlen(string);

	int integerLength = point - sign;
	int fractionalLength = string + totalLength - (point + 1);

	result.integer_size = integerLength;
	result.fractional_size = fractionalLength;

	result.integer = calloc(result.integer_size, sizeof(*result.integer));
	result.fractional = calloc(result.fractional_size, sizeof(*result.fractional));

	char buffer[CHUNK_LENGTH + 1] = { 0 };

	int base = 10;

	result.integer[result.integer_size - 1] = strtol(buffer, NULL, base);

	int i;
	for (i = result.integer_size - 1; i >= 0; i--)
	{
		char *current_token = sign + result.integer_size - 1 - i;

		strncpy(buffer, current_token, CHUNK_LENGTH);

		result.integer[i] = strtol(buffer, NULL, base);
	}

	for (i = 0; i < result.fractional_size; i++)
	{
		int chunkOffset = i;

		char *current_token = point + 1 + chunkOffset;

		strncpy(buffer, current_token, CHUNK_LENGTH);

		result.fractional[i] = strtol(buffer, NULL, base);
	}

	return strip(result);
}

void print(LongNumber number)
{
	if (NEGATIVE_SIGN == number.sign)
	{
		printf("-");
	}

	int i;
	for (i = number.integer_size - 1; i >= 0; i--)
	{
		printf("%d", number.integer[i]);
	}

	if (0 == number.integer_size)
	{
		printf("0");
	}

	if (number.fractional_size > 0)
	{
		printf(".");
	}

	for (i = 0; i < number.fractional_size; i++)
	{
		printf("%d", number.fractional[i]); 
	}

	printf("\n");
}

LongNumber sum(LongNumber a, LongNumber b)
{
	LongNumber result = zero();

	if (a.sign != b.sign)
	{
		if (NEGATIVE_SIGN == b.sign)
		{
			b.sign *= -1;

			return sub(a, b);
		}
		else
		{
			a.sign *= -1;

			return sub(b, a);
		}
	}
	
	result.sign = a.sign;

	result.integer_size = max(a.integer_size, b.integer_size);
	result.fractional_size = max(a.fractional_size, b.fractional_size);

	result.integer = calloc(result.integer_size, sizeof(*result.integer));
	result.fractional = calloc(result.fractional_size, sizeof(*result.fractional));

	int i;
	for (i = 0; i < result.integer_size; i++)
	{
		if (i < a.integer_size)
		{
			result.integer[i] += a.integer[i];
		}

		if (i < b.integer_size)
		{
			result.integer[i] += b.integer[i];
		}
	}

	for (i = 0; i < result.fractional_size; i++)
	{
		if (i < a.fractional_size)
		{
			result.fractional[i] += a.fractional[i];
		}

		if (i < b.fractional_size)
		{
			result.fractional[i] += b.fractional[i];
		}
	}

	for (i = result.fractional_size - 2; i >= 0; i--)
	{
		result.fractional[i] += result.fractional[i + 1] / CHUNK_SIZE;
		result.fractional[i + 1] %= CHUNK_SIZE;
	}
	
	if (result.fractional_size > 0 && result.fractional[0] >= CHUNK_SIZE)
	{
		if (0 == result.integer_size)
		{
			result.integer_size++;
			result.integer = realloc(result.integer, result.integer_size);
		}
		result.integer[0] += result.fractional[0] / CHUNK_SIZE;
		result.fractional[0] %= CHUNK_SIZE;
	}

	for (i = 1; i < result.integer_size; i++)
	{
		result.integer[i] += result.integer[i - 1] / CHUNK_SIZE;
		result.integer[i - 1] %= CHUNK_SIZE;
	}

	if (result.integer[result.integer_size - 1] > CHUNK_SIZE)
	{
		result.integer_size++;

		result.integer = realloc(result.integer, result.integer_size);

		result.integer[result.integer_size - 1] = result.integer[result.integer_size - 2] / CHUNK_SIZE;
		result.integer[result.integer_size - 2] %= CHUNK_SIZE;
	}

	return result;
}

LongNumber sub(LongNumber a, LongNumber b)
{
	if (POSITIVE_SIGN == a.sign && NEGATIVE_SIGN == b.sign)
	{
		b.sign *= -1;

		return sum(a, b);
	}

	if (NEGATIVE_SIGN == a.sign && POSITIVE_SIGN == b.sign)
	{
		a.sign *= -1;
		
		LongNumber result = sum(a, b);

		result.sign *= -1;

		return result;
	}

	if (NEGATIVE_SIGN == a.sign && NEGATIVE_SIGN == b.sign)
	{
		a.sign *= -1;
		b.sign *= -1;

		return sub(b, a);
	}
	
	LongNumber bigger;
	LongNumber smaller;
	LongNumber result = zero();

	if (abs_compare(a, b) > 0)
	{
		bigger = a;
		smaller = b;
		result.sign = POSITIVE_SIGN;
	}
	else
	{
		bigger = b;
		smaller = a;
		result.sign = NEGATIVE_SIGN;
	}	

	result.integer_size = max(a.integer_size, b.integer_size);
	result.fractional_size = max(a.fractional_size, b.fractional_size);

	result.integer = calloc(result.integer_size, sizeof(*result.integer));
	result.fractional = calloc(result.fractional_size, sizeof(*result.fractional));
	
	int i;
	for (i = 0; i < result.integer_size; i++)
	{
		if (i < bigger.integer_size)
		{
			result.integer[i] += bigger.integer[i];
		}

		if (i < smaller.integer_size)
		{
			result.integer[i] -= smaller.integer[i];
		}
	}

	for (i = 0; i < result.fractional_size; i++)
	{
		if (i < bigger.fractional_size)
		{
			result.fractional[i] += bigger.fractional[i];
		}
	
		if (i < smaller.fractional_size)
		{
			result.fractional[i] -= smaller.fractional[i];
		}
	}

	for (i = result.fractional_size - 1; i >= 1; i--)
	{
		if (result.fractional[i] < 0)
		{
			result.fractional[i - 1]--;
			result.fractional[i] += CHUNK_SIZE;
		}
	}

	if (result.fractional_size > 0 && result.fractional[0] < 0)
	{
		result.integer[0]--;
		result.fractional[0] += CHUNK_SIZE;
	}

	for (i = 0; i < result.integer_size - 1; i++)
	{
		if (result.integer[i] < 0)
		{
			result.integer[i + 1]--;
			result.integer[i] += CHUNK_SIZE;
		}
	}

	return strip(result);
}

LongNumber mul(LongNumber a, LongNumber b, int precision)
{
	LongNumber result = zero();

	result.sign = a.sign * b.sign;

	result.integer_size = a.integer_size + b.integer_size;
	result.fractional_size = a.fractional_size + b.fractional_size;

	result.integer = calloc(result.integer_size, sizeof(*result.integer));
	result.fractional = calloc(result.fractional_size, sizeof(*result.fractional));

	char *rawA = calloc(a.integer_size + a.fractional_size, sizeof(*a.integer));
	char *rawB = calloc(b.integer_size + b.fractional_size, sizeof(*b.integer));

	char *rawResult = calloc(result.integer_size + result.fractional_size, sizeof(*result.integer));

	memcpy(rawA + a.fractional_size, a.integer, a.integer_size * sizeof(*a.integer));
	
	int i;
	for (i = 0; i < a.fractional_size; i++)
	{
		rawA[a.fractional_size - 1 - i] = a.fractional[i];
	}

	memcpy(rawB + b.fractional_size, b.integer, b.integer_size * sizeof(*b.integer));

	for (i = 0; i < b.fractional_size; i++)
	{
		rawB[b.fractional_size - 1 - i] = b.fractional[i];
	}

	int j;
	for (j = 0; j < a.integer_size + a.fractional_size; j++)
	{
		int carry = 0;

		for (i = 0; i < b.integer_size + b.fractional_size; i++)
		{
			int t = rawA[j] * rawB[i] + rawResult[i + j] + carry;

			rawResult[i + j] = t % CHUNK_SIZE;
			carry = t / CHUNK_SIZE;
		}
	}

	for (i = 0; i < result.fractional_size; i++)
	{
		result.fractional[result.fractional_size - 1 - i] = rawResult[i];
	}

	memcpy(result.integer, rawResult + result.fractional_size, result.integer_size * sizeof(*result.integer));

	if (result.fractional_size > precision)
	{
	  result.fractional_size = precision;

	  if (result.fractional[result.fractional_size] >= 5)

		{

	    result.fractional[result.fractional_size - 1]++;
	    
		}

		result.fractional = realloc(result.fractional, result.fractional_size);
	}

	return strip(result);
}

LongNumber divide(LongNumber a, LongNumber b, int precision)
{

	if (b.integer_size > a.integer_size + precision)
		return zero();

	int m = a.integer_size + a.fractional_size;
	int n = b.integer_size + b.fractional_size;

	if (0 == b.fractional_size && 0 == b.integer_size){
		fprintf(stderr, "error");
		return zero();
	}	

	int precisionOffset = max(precision - (a.fractional_size - b.fractional_size), 0);

	m += precisionOffset;
	
	char *u = calloc(m, sizeof(*a.integer));
	char *v = calloc(n + 1, sizeof(*b.integer));

	char *rawResult = calloc(m - n + 1, sizeof(*a.integer));

	memcpy(u + a.fractional_size, a.integer, a.integer_size * sizeof(*a.integer));

	int i;
	for (i = 0; i < a.fractional_size; i++)
	{
		u[a.fractional_size - 1 - i] = a.fractional[i];
	}

	for (i = m - 1; i >= precisionOffset; i--)
	{
		u[i] = u[i - precisionOffset];
	}

	for (i = 0; i < precisionOffset; i++)
	{
		u[i] = 0;
	}

	memcpy(v + b.fractional_size, b.integer, b.integer_size * sizeof(*b.integer));

	for (i = 0; i < b.fractional_size; i++)
	{
		v[b.fractional_size - 1 - i] = b.fractional[i];
	}	

	char *buffer = calloc(n + 1, sizeof(*b.integer));

	for (i = 0; i < n - 1; i++)
	{
		buffer[n - 2 - i] = u[m - 1 - i];
	}

	int j;
	for (j = m - n; j >= 0; j--)
	{
		for (i = n; i >= 1; i--)
		{
			buffer[i] = buffer[i - 1];
		}

		buffer[0] = u[j];

		int enough = 0;

		while (!enough)
		{
			for (i = n; i >= 0; i--)
			{
				if (buffer[i] < v[i])
				{
					enough = 1;
					break;
				}

				if (buffer[i] > v[i])
				{
					break;
				}
			}

			if (enough)
			{
				break;
			}

			for (i = 0; i < n; i++)
			{
				buffer[i] -= v[i];

				if (buffer[i] < 0)
				{
					buffer[i + 1]--;
					buffer[i] += CHUNK_SIZE;
				}
			}

			rawResult[j]++;	
		}
	}

	LongNumber result = zero();

	result.sign = a.sign * b.sign;

	result.fractional_size = a.fractional_size - b.fractional_size + precisionOffset;
	result.integer_size = max(m - n - result.fractional_size + 1,0);

	result.integer = calloc(result.integer_size, sizeof(*result.integer));
	result.fractional = calloc(result.fractional_size, sizeof(*result.fractional));

	for (i = 0; i < result.fractional_size; i++)
	{
		result.fractional[result.fractional_size - 1 - i] = rawResult[i];
	}

	memcpy(result.integer, rawResult + result.fractional_size, result.integer_size * sizeof(*result.integer));

	if (result.fractional_size > precision)
 	{

 		result.fractional_size = precision;

  		if (result.fractional[result.fractional_size] >= 5)
   		{

   		result.fractional[result.fractional_size - 1]++;

   		}

    	result.fractional = realloc(result.fractional, result.fractional_size);
 	}

	return strip(result);
}