#pragma once
#include <vector>
#include <cassert>

class Primes
{
	std::vector<unsigned int> m_arrPrimes;
	static const int scm_iUnloopCount = 8;
	/// <summary>Numbers for unloop by 2,3,5.</summary>
	static const unsigned int unloop(size_t index)
	{
		static const unsigned int scArrUnloop[] = {4, 2, 4, 2, 4, 6, 2, 6};
		return scArrUnloop[index];
	}
	bool IsPrime(const std::vector<unsigned int> &arr, unsigned int i) const
	{
		return !(arr[i / 64] & (1 << ((i % 64) >> 1)));
	}
	void FillArrForNum(std::vector<unsigned int> &arr, unsigned int &i, unsigned int to, unsigned int step)
	{
		if (IsPrime(arr, i))
		{
			for (unsigned int j = i*3; j < to; j += 2*i)
				arr[j / 64] |= 1 << ((j % 64) >> 1);
		}
		i += step;
	}
	void FillEratosphenArray(std::vector<unsigned int> &arr, unsigned int to)
	{
		unsigned int t = (unsigned int) sqrt(to);
		// Unloop by 2, 3, 5
		unsigned int i = 7;
		while (i + 30 < t)
		{
			for (size_t j = 0; j < scm_iUnloopCount; j++)
				FillArrForNum(arr, i, to, unloop(j));
		}
		for (size_t j = 0; j < scm_iUnloopCount; j++)
		{
			if (i > t)
				break;
			FillArrForNum(arr, i, to, unloop(j));
		}
	}
	void CheckPrime(std::vector<unsigned int> &arr, unsigned int &i, unsigned int step)
	{
		if (IsPrime(arr, i))
			m_arrPrimes.push_back(i);
		i += step;
	}
public:
	Primes(unsigned int to)
	{
		assert(to < 2000000000);
		std::vector<unsigned int> arr(to / 64 + 1);
		FillEratosphenArray(arr, to);
		// Fill primes
		m_arrPrimes.push_back(2);
		m_arrPrimes.push_back(3);
		m_arrPrimes.push_back(5);
		unsigned int i = 7;
		while (i + 30 < to)
		{
			for (size_t j = 0; j < scm_iUnloopCount; j++)
				CheckPrime(arr, i, unloop(j));
		}
		for (size_t j = 0; j < scm_iUnloopCount; j++)
		{
			if (i > to)
				break;
			CheckPrime(arr, i, unloop(j));
		}
	}
	const std::vector<unsigned int>& GetPrimes() const {return m_arrPrimes;}
};