#pragma once
//The number 512 is interesting because it is equal to the sum of its digits raised to some power : 5 + 1 + 2 = 8, and 83 = 512. Another example of a number with this property is 614656 = 284.
//We shall define an to be the nth term of this sequence and insist that a number must contain at least two digits to have a sum.
//You are given that a2 = 512 and a10 = 614656.
//Find a30.

QWORD GetSumDigits(QWORD qw)
{
	QWORD qwSum = 0;
	for (; qw; qw /= 10)
	{
		qwSum += qw % 10;
	}
	return qwSum;
}

void Problem119()
{
	map<QWORD, set<QWORD>> htPower2Num;
	QWORD qwStop = QWORD(1) << 55;
	for (QWORD i = 2; i < 200; i++)
	{
		QWORD q = i;
		for (int j = 0; q < qwStop; j++)
		{
			q *= i;
			htPower2Num[q].insert(i);
		}
	}
	int iCount = 0;
	QWORD qwLast = 0;
	for (auto it = htPower2Num.begin(); iCount < 30 && it != htPower2Num.end(); ++it)
	{
		auto nIt = it->second.find(GetSumDigits(it->first));
		if (nIt != it->second.end())
		{
			iCount++;
			qwLast = it->first;
			cout << "Num" << iCount << " = " << qwLast << ", n = " << *nIt << endl;
		}
	}
	cout << "Result = " << qwLast << endl;
}
