#include "LongNumber.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
	result.fractional_length = 0;
	result.integer_size = 0;
	result.fractional = NULL;
	result.integer = NULL;

	return result;
}

LongNumber parse(char *string)
{
	if (NULL == string)
	{
		//todo:check
	}

	if (0 == strcmp(string, ""))
	{
		//todo:check
	}

	LongNumber result;

#define SIGN '-'

	char *sign = strchr(string, SIGN);

	if (NULL != sign)
	{
		result.sign = NEGATIVE_SIGN;
		sign++;//here we go to number
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
	
	if (result.fractional_size > 0 && result.fractional[0] > CHUNK_SIZE)
	{
		if (0 == result.integer_size)
		{
			result.integer_size++;
			result.integer = realloc(result.integer, result.integer_size);
		}
		result.integer[0] += result.fractional[0] / CHUNK_SIZE;
		result.fractional[0] %= CHUNK_SIZE;
	}
	//0.6+0.6

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
	LongNumber result;

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
		if (result.integer[i + 1] < 0)
		{
			result.integer[i + 1]--;
			result.integer[i] += CHUNK_SIZE;
		}
	}

	return strip(result);
}