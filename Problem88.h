#pragma once
//A natural number, N, that can be written as the sum and product of a given set of at least two natural numbers, {a1, a2, ... , ak} is
//called a product-sum number: N = a1 + a2 + ... + ak = a1 × a2 × ... × ak.
//
//For example, 6 = 1 + 2 + 3 = 1 × 2 × 3.
//
//For a given set of size, k, we shall call the smallest N with this property a minimal product-sum number.
//The minimal product-sum numbers for sets of size, k = 2, 3, 4, 5, and 6 are as follows.
//
//k=2: 4 = 2 × 2 = 2 + 2
//k=3: 6 = 1 × 2 × 3 = 1 + 2 + 3
//k=4: 8 = 1 × 1 × 2 × 4 = 1 + 1 + 2 + 4
//k=5: 8 = 1 × 1 × 2 × 2 × 2 = 1 + 1 + 2 + 2 + 2
//k=6: 12 = 1 × 1 × 1 × 1 × 2 × 6 = 1 + 1 + 1 + 1 + 2 + 6
//
//Hence for 2≤k≤6, the sum of all the minimal product-sum numbers is 4+6+8+12 = 30; note that 8 is only counted once in the sum.
//
//In fact, as the complete set of minimal product-sum numbers for 2≤k≤12 is {4, 6, 8, 12, 15, 16}, the sum is 61.
//
//What is the sum of all the minimal product-sum numbers for 2≤k≤12000?

//Use brute force algorithm
class ComputeSum
{
	int iSumPrev;
	int ik;
	bool IncreaseIndex(vector<int> &arr, int iMinSum)
	{
		arr[0]++;
		while (arr[0] > ik || iSumPrev > iMinSum)
		{
			int j = 1;
			for (; j < ik && arr[j] >= ik; j++);
			if (j == ik)
				return false;
			arr[j]++;
			for (int jj = 0; jj < j; jj++)
				arr[jj] = arr[j];

			iSumPrev = 0;
			int iMul = 1;
			for (int x = 0; x < ik; x++)
			{
				if (arr[x] == 1)
				{
					iSumPrev += ik - x;
					break;
				}

				iSumPrev += arr[x];
				iMul *= arr[x];
				
				if (iMul > ik * ik)
				{
					iSumPrev = iMul;
					break;
				}
			}
			if (iMul > iSumPrev)
				iSumPrev = iMul;
			if (iSumPrev > iMinSum)
			{
				for (int jj = 0; jj <= j; jj++)
					arr[jj] = ik + 1;
				continue;
			}
			break;
		}
		return true;
	}
public:
	ComputeSum(int k) : iSumPrev(0), ik(k) {}
	int GetSum()
	{
		vector<int> arr(ik, 1);
		int iMinSum = INT_MAX;
		for (; ;)
		{
			if (!IncreaseIndex(arr, iMinSum))
				break;
			int iMul = 1;
			int iSum = 0;
			int index = 0;
			for (; index < ik; index++)
			{
				int num = arr[index];
				if (num == 1)
				{
					iSum += ik - index;
					index = ik;
					break;
				}
				iMul *= num;
				iSum += num;
				if (iMul > iMinSum)
					break;
			}
			if (index < ik || iSum != iMul)
				continue;
			if (iSum < iMinSum)
				iMinSum = iSum;
		}
		return iMinSum;
	}
};
#include <mutex>
set<int> arrSums;
std::mutex g_m;
struct ThreadArgs
{
	int from;
	int to;
	ThreadArgs(int f, int t) : from(f), to(t) {}
};

void ThreadFunc(const ThreadArgs &args)
{
	for (int i = args.from; i < args.to; i++)
	{
		ComputeSum cs(i);
		int iSum = cs.GetSum();
		g_m.lock();
		arrSums.insert(iSum);
		cout << "i = " << i << ", sum = " << iSum << endl;
		g_m.unlock();
	}
}

void Problem88()
{
	int iStep = 600;
	int iStop = 12000;
	int i = 2;
	for (; i < iStop - iStep; i += iStep)
	{
		boost::thread thr1(ThreadFunc, ThreadArgs(i, i + iStep / 3));
		boost::thread thr2(ThreadFunc, ThreadArgs(i + iStep / 3, i + (iStep / 3) * 2));
		boost::thread thr3(ThreadFunc, ThreadArgs(i + (iStep / 3) * 2, i + iStep));
		thr1.join();
		thr2.join();
		thr3.join();
	}
	boost::thread thr1(ThreadFunc, ThreadArgs(i, i + iStep / 3));
	boost::thread thr2(ThreadFunc, ThreadArgs(i + iStep / 3, iStop + 1));
	thr1.join();
	thr2.join();
	unsigned long long iSum = 0;
	for_each(arrSums.begin(), arrSums.end(), [&](int i) {iSum += i;});
	cout << "Sum = " << iSum << endl;
}