#pragma once
// Let pn be the nth prime : 2, 3, 5, 7, 11, ..., and let r be the remainder when(pn−1)^n + (pn + 1)^n is divided by pn^2.
// For example, when n = 3, p3 = 5, and 4^3 + 6^3 = 280 ≡ 5 mod 25.
// The least value of n for which the remainder first exceeds 109 is 7037.
// Find the least value of n for which the remainder first exceeds 1010.

#include "Primes.h"

QWORD GetRemainder(unsigned int pn, size_t n)
{
	QWORD pn2 = pn;
	pn2 *= pn2;
	QWORD p1 = pn - 1;
	QWORD p2 = pn + 1;
	for (size_t i = 1; i < n; i++)
	{
		p1 *= pn - 1;
		p2 *= pn + 1;
		p1 %= pn2;
		p2 %= pn2;
	}
	return (p1 + p2) % pn2;
}

void Problem123()
{
	Primes pr(1000000);
	auto arr = pr.GetPrimes();
	size_t n = 0;
	for (; n < arr.size(); n++)
	{
		if (GetRemainder(arr[n], n + 1) > 10000000000)
			break;
	}
	if (n < arr.size())
		cout << "n = " << n + 1 << ", remainder = " << GetRemainder(arr[n], n + 1) << endl;
	else
		cout << "Unable to find n from 0 to " << arr.size() << endl;
}