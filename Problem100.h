#pragma once
//If a box contains twenty-one coloured discs, composed of fifteen blue discs and six red discs, and two discs were taken at random,
//it can be seen that the probability of taking two blue discs, P(BB) = (15/21)×(14/20) = 1/2.
//
//The next such arrangement, for which there is exactly 50% chance of taking two blue discs at random, is a box containing eighty-five
//blue discs and thirty-five red discs.
//
//By finding the first arrangement to contain over 1012 = 1,000,000,000,000 discs in total, determine the number of blue discs that the box would contain.

size_t gcd(size_t a, size_t b)
{
	size_t c;
	while (b != 0)
	{
		c = a % b;
		a = b;
		b = c;
	}
	return a;
}

void Problem100()
{
	double d = sqrt(2) / 2;
	int iAdd = 3;
	for (size_t i = 20; i < 1000000000000000; i += iAdd)
	{
		iAdd = iAdd == 3 ? 1 : 3;
		auto j = (size_t)(d * i) + 1;
		auto j1 = j;
		auto j2 = j - 1;
		// Divide by 2 j1 or j2
		if (j1 & 1)
			j2 >>= 1;
		else
			j1 >>= 1;

		auto i1 = i;
		auto i2 = i - 1;
		// Divide by 4 i1 or i2
		if (i1 & 3)
			i2 >>= 2;
		else
			i1 >>= 2;

		auto cd = gcd(j1, i1);
		if (cd == 1)
			continue;
		j1 = j1 / cd;
		i1 = i1 / cd;
		i1 *= i2;
		if (j1 * j2 == i1)
		{
			cout << "Blue = " << j << ", total = " << i << endl;
			size_t next = (((size_t) (double(i) * 5.8284)) & ~3) - 3; // Nums repeat after multiplication on 5.8284
			if (i > 1000000000000 || next < i)
				break; // stop or overflow
			iAdd = 3;
			i = next;
		}
	}
}