#pragma once
//The proper divisors of a number are all the divisors excluding the number itself. For example, the proper
//divisors of 28 are 1, 2, 4, 7, and 14. As the sum of these divisors is equal to 28, we call it a perfect number.
//
//Interestingly the sum of the proper divisors of 220 is 284 and the sum of the proper divisors of 284 is 220,
//forming a chain of two numbers. For this reason, 220 and 284 are called an amicable pair.
//
//Perhaps less well known are longer chains. For example, starting with 12496, we form a chain of five numbers:
//
//12496 → 14288 → 15472 → 14536 → 14264 (→ 12496 → ...)
//
//Since this chain returns to its starting point, it is called an amicable chain.
//
//Find the smallest member of the longest amicable chain with no element exceeding one million.

vector<int> GetNum2SumDivs(int iTo)
{
	vector<int> arrSums(iTo);
	for (int i = 2; i < iTo; i++)
	{
		for (int j = i * 2; j < iTo; j += i)
		{
			arrSums[j] += i;
		}
	}
	for (int i = 2; i < iTo; i++)
	{
		if (arrSums[i])
			arrSums[i]++;
	}
	return arrSums;
}

void Problem95()
{
	int iTo = 1000000;
	auto arrSums = GetNum2SumDivs(iTo);
	pair<int, int> max;
	for (int i = 2; i < iTo; i++)
	{
		int Sum = arrSums[i];
		if (!Sum)
			continue;
		int Len = 1;
		set<int> arrPrev;		
		for (int next = Sum; next != i; Len++)
		{
			if (next > iTo || !arrSums[next] || arrPrev.find(next) != arrPrev.end())
			{
				Len = 0;
				break;
			}
			arrPrev.insert(next);
			next = arrSums[next];			
		}
		if (Len > max.second)
		{
			max.first = i;
			max.second = Len;
		}
	}
	cout << "Num = " << max.first << ", len = " << max.second << endl;
	return;
}