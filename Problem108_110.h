#pragma once
// 108
// In the following equation x, y, and n are positive integers.
// 1/x + 1/y = 1/n
// For n = 4 there are exactly three distinct solutions:
// 1/5 + 1/20 = 1/4
// 1/6 + 1/12 = 1/4
// 1/8 + 1/8 = 1/4
//What is the least value of n for which the number of distinct solutions exceeds one-thousand?

// 110
//In the following equation x, y, and n are positive integers.
// 1/x + 1/y = 1/n
// It can be verified that when n = 1260 there are 113 distinct solutions and this is the least value of n for which the total number of distinct solutions exceeds one hundred.
// What is the least value of n for which the number of distinct solutions exceeds four million?

// Main equation for these problems: D(n) = p1^e1 * p2^e2 = (e1 + 1) * (e2 + 1), where
// D(n) - dividers count, p1 - prime divider, e1 - primes power, p2 e2 - another prime and power
// For example 120 = 2^3 * 3*1 * 5^1 = (3+1)(1+1)(1+1) = 16 dividers.
// From 1/x + 1/y = 1/n, we can compute that if x * n divided by x - n, then x is solution. From this
// we define x from n+1 to 2n, and then (n+i)*n % (n + i) - n, where i = [1, n], receive new base equatioon:
// if i divides n*n, then i is the solution, so we need just to find dividers count of n*n.

#include "Primes.h"

QWORD GetNum(const vector<unsigned int> &primes, const vector<unsigned int> &v)
{
	QWORD res = 1;
	for (size_t i = 0; i < v.size(); i++)
	{
		QWORD r = 1;
		for (unsigned int j = 0; j < v[i]; j++)
			r *= primes[i];
		res *= r;
	}
	return res;
}

QWORD GetSolutions(const vector<unsigned int> &v)
{
	QWORD r = 1;
	for (size_t i = 0; i < v.size(); i++)
	{
		r *= v[i] * 2 + 1;
	}
	return (r + 1) / 2;
}

bool GetNextVector(const vector<unsigned int> &primes, QWORD maxNum,
	vector<unsigned int> &v, unsigned int increaseIndex)
{
	if (increaseIndex >= v.size())
		return false;
	v[increaseIndex]++;
	auto r = GetNum(primes, v);
	if (r > maxNum)
	{
		for (unsigned int i = 0; i <= increaseIndex; i++)
			v[i] = 0;
		return GetNextVector(primes, maxNum, v, increaseIndex + 1);
	}
	return true;
}
void FindSolutionFor(QWORD qwStopSolutions)
{
	Primes pr(100);
	QWORD qwSols = 1;
	int iStopIndex = 0;
	unsigned long long maxNum = 1;
	auto arrPrimes = pr.GetPrimes();
	for (; qwSols < qwStopSolutions; iStopIndex++)
	{
		maxNum *= arrPrimes[iStopIndex];
		qwSols *= 3;
	}

	// Need to find solution between qwStopSolutions and maxSol
	QWORD maxSol = qwSols;
	iStopIndex--;
	vector<unsigned int> vExponents(iStopIndex);
	while (GetNextVector(arrPrimes, maxNum, vExponents, 0))
	{
		auto s = GetSolutions(vExponents);
		if (s >= qwStopSolutions)
		{
			maxNum = GetNum(arrPrimes, vExponents);
			maxSol = s;
		}
	}
	cout << "Num = " << maxNum << ", solutions = " << maxSol << endl;
}
void Problem108()
{
	FindSolutionFor(1000);
}
void Problem110()
{
	FindSolutionFor(4000000);
}