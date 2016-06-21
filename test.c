#include "LongNumber.h"

int main(int argc, char *argv[])
{
	LongNumber a = parse("13.120");
	LongNumber b = parse("ю.");

	print(a);
	print(b);

	print(sum(a, b));

	print(sub(a, b));

	return 0;
}
