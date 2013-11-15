#pragma once
// Find the number of integers 1 < n < 10^7, for which n and n + 1 have the same number of
// positive divisors. For example, 14 has the positive divisors 1, 2, 7, 14 while
// 15 has 1, 3, 5, 15.
#include "Primes.h"

int GetDivPower(unsigned int &iNum, unsigned int div)
{
	int exp = 0;
	for (; !(iNum % div); exp++)
	{
		iNum /= div;
	}
	return exp + 1;
}

int GetDivCount(unsigned int iNum, const std::vector<unsigned int> &arr)
{
	int iNumDivs = 1;
	unsigned int stop = (unsigned int) sqrt(iNum) + 1;
	for (size_t curDivIndex = 0; iNum > 1 && arr[curDivIndex] < stop; curDivIndex++)
	{
		iNumDivs *= GetDivPower(iNum, arr[curDivIndex]);
	}
	if (iNum > 1)
		iNumDivs *= 2;
	return iNumDivs;
}

void Problem179()
{
	Primes pr(500000);
	auto arr = pr.GetPrimes();
	int iPrev = 1;
	int iCount = 0;
	for (unsigned int i = 2; i < 10000000; i++)
	{
		int iCur = GetDivCount(i, arr);
		if (iCur == iPrev)
			iCount++;
		iPrev = iCur;
	}
	cout << "Count = " << iCount << endl;
}