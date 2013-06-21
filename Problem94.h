#pragma once
//It is easily proved that no equilateral triangle exists with integral length sides and integral area.
//However, the almost equilateral triangle 5-5-6 has an area of 12 square units.
//
//We shall define an almost equilateral triangle to be a triangle for which two sides are equal and the third differs by no more than one unit.
//
//Find the sum of the perimeters of all almost equilateral triangles with integral side lengths and area and whose perimeters do not exceed one billion (1,000,000,000).
#include <math.h>

bool IsSquare(unsigned long long a)
{
	double d = sqrt(a);
	unsigned long long dd = (unsigned long long) d;
	return dd * dd == a;
}

unsigned long long ComputePerimeter(set<int> &arrPerims, unsigned long long a, unsigned long long b)
{
	auto a1 = a;
	auto b1 = b;
	unsigned long long Perimeter = a + b;
	if (a & 1)
	{
		Perimeter += a;
		b /= 2;
		a *= a;
		b *= b;
		a -= b;		
	}
	else
	{
		Perimeter += b;
		a /= 2;
		a *= a;
		b *= b;
		a = b - a;
	}
	if (IsSquare(a))
	{
		cout << "a = " << a1 << ", b = " << b1 << ", Perimeter = " << Perimeter << endl;
		arrPerims.insert(Perimeter);
	}
	return Perimeter;
}

void Problem94()
{
	set<int> arrPerims;
	for (int i = 3; i < 500000000; i++)
	{
		if (ComputePerimeter(arrPerims, i, i - 1) > 1000000000)
			break;
	}
	unsigned long long Sum = 0;
	for (auto i : arrPerims)
		Sum += i;
	cout << "Sum = " << Sum << endl;
}