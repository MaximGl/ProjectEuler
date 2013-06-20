#pragma once
//
//
//Each of the six faces on a cube has a different digit (0 to 9) written on it; the same is done to a second cube.
//By placing the two cubes side-by-side in different positions we can form a variety of 2-digit numbers.
//
//For example, the square number 64 could be formed:
//
//In fact, by carefully choosing the digits on both cubes it is possible to display all of the square numbers below one-hundred: 01, 04, 09, 16, 25, 36, 49, 64, and 81.
//
//For example, one way this can be achieved is by placing {0, 5, 6, 7, 8, 9} on one cube and {1, 2, 3, 4, 8, 9} on the other cube.
//
//However, for this problem we shall allow the 6 or 9 to be turned upside-down so that an arrangement like
//{0, 5, 6, 7, 8, 9} and {1, 2, 3, 4, 6, 7} allows for all nine square numbers to be displayed; otherwise it would be impossible to obtain 09.
//
//In determining a distinct arrangement we are interested in the digits on each cube, not the order.
//
//{1, 2, 3, 4, 5, 6} is equivalent to {3, 6, 4, 1, 2, 5}
//{1, 2, 3, 4, 5, 6} is distinct from {1, 2, 3, 4, 5, 9}
//
//But because we are allowing 6 and 9 to be reversed, the two distinct sets in the last example both represent the extended set
//{1, 2, 3, 4, 5, 6, 9} for the purpose of forming 2-digit numbers.
//
//How many distinct arrangements of the two cubes allow for all of the square numbers to be displayed?

class Cube
{
	char m_arrDigits[7];
public:
	Cube(const char *arrDigits)
	{
		m_arrDigits[6] = -1;
		for (int i = 0; i < 6; i++)
		{
			m_arrDigits[i] = arrDigits[i];
			if (arrDigits[i] == 6)
				m_arrDigits[6] = 9;
			else if (arrDigits[i] == 9)
				m_arrDigits[6] = 6;
		}
	}
	int compare(const Cube &c) const
	{
		for (int i = 0; i < 7; i++)
		{
			if (m_arrDigits[i] != c.m_arrDigits[i])
				return m_arrDigits[i] < c.m_arrDigits[i] ? -1 : 1;
		}
		return 0;
	}
	bool HasDigit(char ch) const
	{
		for (auto c : m_arrDigits)
		{
			if (c == ch)
				return true;
		}
		return false;
	}
	void Print() const
	{
		for (int i = 0; i < 6; i++)
			cout << int(m_arrDigits[i]) << ' ';
	}
	Cube GetNextCube() const
	{
		char arr[6];
		for (int j = 0; j < 6; j++)
			arr[j] = m_arrDigits[j];
		int i = 5;
		for (; i >= 0; i--)
		{
			if (arr[i] + 6 - i < 10)
			{
				arr[i]++;
				break;
			}
			else
				arr[i] = 0;
		}
		if (i < 0)
		{
			// Invalid cube
			arr[0] = char(-1);
			return Cube(arr);
		}
		for (i++; i < 6; i++)
		{
			arr[i] = arr[i - 1] + 1;
		}
		return Cube(arr);
	}
	bool IsValid() const {return m_arrDigits[0] >= 0;}
};

char g_arrSquares[9][2] = {{0, 1}, {0, 4}, {0, 9}, {1, 6}, {2, 5}, {3, 6}, {4, 9}, {6, 4}, {8, 1}};

class DoubleCube
{
	Cube m_c1;
	Cube m_c2;
	bool CanRepresent(const char* arr) const
	{
		return ((m_c1.HasDigit(arr[0]) && m_c2.HasDigit(arr[1])) ||
			(m_c1.HasDigit(arr[1]) && m_c2.HasDigit(arr[0])));
	}
public:
	DoubleCube(const Cube &c1, const Cube &c2) : m_c1(c1), m_c2(c2) {}
	bool IsCanRepresentSquares() const
	{
		for (auto sq : g_arrSquares)
		{
			if (!CanRepresent(sq))
				return false;
		}
		return true;
	}
	bool operator<(const DoubleCube &dc) const
	{
		int i = m_c1.compare(dc.m_c1);
		if (i)
			return i < 0;
		return m_c2.compare(dc.m_c2) < 0;
	}
	void Print() const
	{
		cout << "Cube1 = ";
		m_c1.Print();
		cout << endl << "Cube2 = ";
		m_c2.Print();
		cout << endl << endl;
	}
	DoubleCube GetNextCubes() const
	{
		auto c2 = m_c2.GetNextCube();
		if (c2.IsValid())
			return DoubleCube(m_c1, c2);
		auto c1 = m_c1.GetNextCube();
		return DoubleCube(c1, c1);
	}
	bool IsValid() const
	{
		if (!m_c1.HasDigit(0))
			return false; // First cube must have 0
		return m_c1.IsValid();
	}
};

void Problem90()
{
	set<DoubleCube> res;
	char minCube[6] = {0, 1, 2, 3, 4, 5};
	Cube c1(minCube);
	DoubleCube dc(c1, c1);
//	size_t next = 0;
	for (int i = 0; dc.IsValid(); i++)
	{
		if (dc.IsCanRepresentSquares())
		{
			res.insert(dc);
			// Just for debug
			//if (res.size() > next)
			//{
			//	cout << res.size() << endl;
			//	dc.Print();
			//	next += 1;
			//}
		}
		dc = dc.GetNextCubes();
	}
	cout << res.size() << endl;
}