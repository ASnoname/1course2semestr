#include "LongNumber.h"

int main(void)
{
	LongNumber a = parse("13.120");
	LongNumber b = parse("12.255");

	print(sum(a, b));

	print(sub(a, b));
	
	print(mul(a, b));
	
	print(divide(a, b, 5));

	return 0;
}
