#ifndef _STD_C_
#define _STD_C_

void ConvertIntToChar(int number, char *test, int size)
{
	int temp;
	int i = size-2;
	while (number != 0)
	{
		temp = number % 10;
		number /= 10;
		test[i] = '0' + temp;
		i--;
	}
	while (i >= 0)
	{
		test[i] = ' ';
		i--;
	}
	test[size-1] = 0;
}

#endif