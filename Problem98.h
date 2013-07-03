#pragma once
//By replacing each of the letters in the word CARE with 1, 2, 9, and 6 respectively, we form a square number: 1296 = 36^2.
//What is remarkable is that, by using the same digital substitutions, the anagram, RACE, also forms a square number: 9216 = 96^2.
//We shall call CARE (and RACE) a square anagram word pair and specify further that leading zeroes are not permitted,
//neither may a different letter have the same digital value as another letter.
//
//Using words.txt (http://projecteuler.net/project/words.txt), a 16K text file containing nearly two-thousand common English words,
//find all the square anagram word pairs (a palindromic word is NOT considered to be an anagram of itself).
//
//What is the largest square number formed by any member of such a pair?
//
//NOTE: All anagrams formed must be contained in the given text file.
#include <fstream>

bool IsAnagram(const string &str1, const string &str2)
{
	if (str1.length() != str2.length())
		return false;
	bool isPalindrom = true;
	char arr1[26] = {0};
	char arr2[26] = {0};
	for (size_t i = 0; i < str1.length(); i++)
	{
		if (str1[i] != str2[str2.length() - i - 1])
			isPalindrom = false;
		arr1[str1[i] - 'A']++;
		arr2[str2[i] - 'A']++;
	}
	if (isPalindrom)
		return false;

	for (size_t i = 0; i < chDIMOF(arr1); i++)
	{
		if (arr1[i] != arr2[i])
			return false;
	}
	return true;
}

map<string, set<string>> FindAnagrams(const vector<string> &arr)
{
	map<string, set<string>> anagrams;
	for (size_t i = 0; i < arr.size(); i++)
	{
		const string &s1 = arr[i];
		for (size_t j = i + 1; j < arr.size() && arr[j].length() == s1.length(); j++)
		{
			const string &s2 = arr[j];
			if (IsAnagram(s1, s2))
			{
				anagrams[s1].insert(s2);
				anagrams[s2].insert(s1);
			}
		}
	}
	return anagrams;
}

void SortArrByLen(vector<string> &arr)
{
	sort(arr.begin(), arr.end(), [](const string &str1, const string &str2){
		if (str1.length() != str2.length())
			return str1.length() < str2.length();
		return str1 < str2;
	});
}

map<string, set<string>> GetStringsFromFile(const char *szFile)
{
	ifstream file;
	file.open(szFile);
	string s;
	getline(file, s);
	file.close();

	size_t iBeg = 0;
	size_t iEnd = s.find(',');
	vector<string> arr;
	do
	{
		arr.push_back(s.substr(iBeg + 1, iEnd != string::npos ? iEnd - iBeg - 2: s.length() - iBeg - 2));
		iBeg = iEnd + 1;
		iEnd = s.find(',', iBeg);
	} while (iEnd != string::npos);
	SortArrByLen(arr);
	return FindAnagrams(arr);
}

vector<string> GetUniqueAnagrams(const map<string, set<string>> &anagrams)
{
	set<string> ignore;
	vector<string> arr;
	for (auto an : anagrams)
	{
		if (ignore.find(an.first) != ignore.end())
			continue;
		arr.push_back(an.first);
		ignore.insert(an.second.begin(), an.second.end());
	}
	SortArrByLen(arr);
	return arr;
}

size_t GetCharactersNum(unsigned long i)
{
	if (i < 10) return 1;
	if (i < 100) return 2;
	if (i < 1000) return 3;
	if (i < 10000) return 4;
	if (i < 100000) return 5;
	if (i < 1000000) return 6;
	if (i < 10000000) return 7;
	if (i < 100000000) return 8;
	if (i < 1000000000) return 9;
	return 10;
}

bool IsCanMap(int num, const string &str, map<char, int> &c2i)
{
	map<int, char> i2c;
	for (auto it = str.rbegin(); it != str.rend(); ++it)
	{
		int i = num % 10;
		if ((c2i.find(*it) != c2i.end() && c2i[*it] != i) ||
			(i2c.find(i) != i2c.end() && i2c[i] != *it))
			return false;
		c2i[*it] = i;
		i2c[i] = *it;
		num /= 10;
	}
	return true;
}

int GetNumFromAnagram(const string &str, map<char, int> &c2i)
{
	int ret = 0;
	for (auto c : str)
		ret = ret * 10 + c2i[c];
	return ret;
}

bool CheckAnagramsWithMap(int num, const string &word, map<char, int> &c2i, const set<string> &anagrams)
{
	bool bCanMap = false;
	int lMax = num;
	string maxWord = word;
	for (auto an : anagrams)
	{
		auto n = GetNumFromAnagram(an, c2i);
		if (GetCharactersNum(n) != word.length())
			continue; // Can't have leading zero
		auto ul = (unsigned long) sqrt(n);
		if (ul * ul != n)
			continue;
		bCanMap = true;
		if (lMax < n)
		{
			lMax = n;
			maxWord = an;
		}
	}
	if (bCanMap)
		cout << "Square = " << lMax << ", word = " << maxWord << endl;
	return bCanMap;
}

void Problem98()
{
	auto anagrams = GetStringsFromFile("words.txt");
	auto uniqAnagr = GetUniqueAnagrams(anagrams);

	const int maxSquare = 31622; // Maximum anagram length in words.txt has 9 characters, so sqrt(1000000000) = 31622
	// Search right anagram
	bool bFind = false;
	for (auto it = uniqAnagr.rbegin(); !bFind && it != uniqAnagr.rend(); ++it)
	{
		size_t len = it->length();
		for (int i = maxSquare; i >= 0; i--)
		{
			int sq = i * i;
			size_t l = GetCharactersNum(sq);
			if (l < len)
				break;
			if (l == len)
			{
				map<char, int> c2i;
				if (IsCanMap(sq, *it, c2i))
				{
					// Check all others anagrams with this number
					if (CheckAnagramsWithMap(sq, *it, c2i, anagrams[*it]))
					{
						bFind = true;
						break;
					}
				}
			}
		}
	}
}