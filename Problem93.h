#pragma once
//By using each of the digits from the set, {1, 2, 3, 4}, exactly once, and making use of the four
//arithmetic operations (+, −, *, /) and brackets/parentheses, it is possible to form different positive integer targets.
//
//For example,
//
//8 = (4 * (1 + 3)) / 2
//14 = 4 * (3 + 1 / 2)
//19 = 4 * (2 + 3) − 1
//36 = 3 * 4 * (2 + 1)
//
//Note that concatenations of the digits, like 12 + 34, are not allowed.
//
//Using the set, {1, 2, 3, 4}, it is possible to obtain thirty-one different target numbers of which 36 is the maximum
//and each of the numbers 1 to 28 can be obtained before encountering the first non-expressible number.
//
//Find the set of four distinct digits, a < b < c < d, for which the longest set of consecutive positive integers,
//1 to n, can be obtained, giving your answer as a string: abcd.

///<summary>Indexes of all possible rearrangements for four digits.</summary>
const int g_arrRearrange[][4] = {
	{0, 1, 2, 3},
	{0, 1, 3, 2},
	{0, 3, 1, 2},
	{0, 3, 2, 1},
	{0, 2, 1, 3},
	{0, 2, 3, 1},

	{1, 0, 2, 3},
	{1, 0, 3, 2},
	{1, 3, 0, 2},
	{1, 3, 2, 0},
	{1, 2, 0, 3},
	{1, 2, 3, 0},

	{2, 0, 1, 3},
	{2, 0, 3, 1},
	{2, 1, 0, 3},
	{2, 1, 3, 0},
	{2, 3, 0, 1},
	{2, 3, 1, 0},

	{3, 0, 1, 2},
	{3, 0, 2, 1},
	{3, 1, 2, 0},
	{3, 1, 0, 2},
	{3, 2, 1, 0},
	{3, 2, 0, 1}
};

double Add(double x, double y) {return x + y;}
double Sub(double x, double y) {return x - y;}
double Mul(double x, double y) {return x * y;}
double Div(double x, double y)
{
	if (!y)
		throw 1;
	return x / y;
}

typedef double (*FuncPtr)(double, double);
FuncPtr g_arrInitFuncs[] = {Add, Sub, Mul, Div};

void AddToRes(set<int> &res, double r)
{
	int ir = (int) r;
	if (ir >= 1 && (r - ir == 0))
		res.insert(ir);
}
// Compute with different braces
void Compute(set<int> &res, int *nums, FuncPtr *arrFuncs)
{
	try
	{
		double r = arrFuncs[0](nums[0], nums[1]);
		r = arrFuncs[1](r, nums[2]);
		r = arrFuncs[2](r, nums[3]);
		AddToRes(res, r);
	}
	catch (...)
	{}
	try
	{
		double r = arrFuncs[1](nums[1], nums[2]);
		r = arrFuncs[0](nums[0], r);
		r = arrFuncs[2](r, nums[3]);
		AddToRes(res, r);
	}
	catch (...)
	{}
	try
	{
		double r = arrFuncs[1](nums[1], nums[2]);
		r = arrFuncs[2](r, nums[3]);
		r = arrFuncs[0](nums[0], r);
		AddToRes(res, r);
	}
	catch (...)
	{}
	try
	{
		double r2 = arrFuncs[2](nums[2], nums[3]);
		double r1 = arrFuncs[0](nums[0], nums[1]);
		r1 = arrFuncs[1](r1, r2);
		AddToRes(res, r1);
	}
	catch (...)
	{}
	try
	{
		double r = arrFuncs[2](nums[2], nums[3]);
		r = arrFuncs[1](nums[1], r);
		r = arrFuncs[0](nums[0], r);
		AddToRes(res, r);
	}
	catch (...)
	{}
}

set<int> GetAllVariants(int *nums)
{
	set<int> res;
	int arrTemp[4];
	FuncPtr arrFuncs[3];
	for (auto arr : g_arrRearrange)
	{
		for (int i = 0; i < 4; i++)
			arrTemp[i] = nums[arr[i]]; // Make new arrangement

		for (int j = 0; j < 64; j++)
		{
			// Each Func = 2 bit. 00 - Add, 01 - Sub, 10 - Mul, 11 - Div
			arrFuncs[0] = g_arrInitFuncs[j & 0x3];
			arrFuncs[1] = g_arrInitFuncs[(j >> 2) & 0x3];
			arrFuncs[2] = g_arrInitFuncs[j >> 4];
			Compute(res, arrTemp, arrFuncs);
		}
	}
	return res;
}

int GetLongestLen(int *nums)
{
	int iNext = 1;
	for (int i : GetAllVariants(nums))
	{
		if (iNext != i)
			break;
		iNext++;
	}
	return iNext - 1;
}

bool ComputeNextNums(int *nums)
{
	int arr[4];
	for (int j = 0; j < 4; j++)
		arr[j] = nums[j];
	int i = 3;
	for (; i >= 0; i--)
	{
		if (arr[i] + 4 - i < 10)
		{
			arr[i]++;
			break;
		}
		else
			arr[i] = 0;
	}
	if (i < 0)
		return false; // End of digits
	for (i++; i < 4; i++)
	{
		arr[i] = arr[i - 1] + 1;
	}
	for (int j = 0; j < 4; j++)
		nums[j] = arr[j];
	return true;
}

void Problem93()
{
	int arrNums[4] = {1, 2, 3, 4};
	int arrMax[4];
	int iMax = 0;
	do
	{
		int len = GetLongestLen(arrNums);
		if (len > iMax)
		{
			iMax = len;
			for (int i = 0; i < 4; i++)
				arrMax[i] = arrNums[i];
		}
	} while (ComputeNextNums(arrNums));
	cout << arrMax[0] << arrMax[1] << arrMax[2] << arrMax[3] << " max = " << iMax << endl;
}