﻿#pragma once
// A composite is a number containing at least two prime factors.For example, 15 = 3 × 5; 9 = 3 × 3; 12 = 2 × 2 × 3.
// There are ten composites below thirty containing precisely two, not necessarily distinct, prime factors : 4, 6, 9, 10, 14, 15, 21, 22, 25, 26.
// How many composite integers, n < 10^8, have precisely two, not necessarily distinct, prime factors ?

#include "Primes.h"

void Problem187()
{
	unsigned int iStop = 100000000;
	Primes pr(iStop / 2);
	auto arr = pr.GetPrimes();
	int iCount = 0;
	for (size_t i = 0; i < arr.size(); i++)
	{
		for (size_t j = i; j < arr.size(); j++, iCount++)
		{
			if (QWORD(arr[i]) * arr[j] >= iStop)
				break;
		}
	}
	cout << "Count = " << iCount << endl;
}