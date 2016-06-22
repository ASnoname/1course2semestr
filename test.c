#include "LongNumber.h"

int main(void)
{
	LongNumber a = parse("1.0");
	LongNumber b = parse("1000000.0");

	print(sum(a, b));

	print(sub(a, b));
	
	print(mul(a, b, 4));
	
	print(divide(a, b, 4));

	return 0;
}
