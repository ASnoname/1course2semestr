#ifndef LONG_ARITHMETICS
#define LONG_ARITHMETICS

#define CHUNK_SIZE (10)
#define CHUNK_LENGTH (1)

#define POSITIVE_SIGN (1)
#define NEGATIVE_SIGN (-1)
#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

typedef struct _long_number
{
	char sign;
	char *integer;
	int integer_size;
	char *fractional;
	int fractional_size;
	int fractional_length;
} LongNumber;

LongNumber parse(char *string);
void print(LongNumber number);

int compare(LongNumber a, LongNumber b);

LongNumber sum(LongNumber a, LongNumber b);
LongNumber sub(LongNumber a, LongNumber b);

#endif //LONG_ARITHMETICS
