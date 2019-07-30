#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include "ConsoleColor.h"
using namespace std;

// the number of characters in input alphabet 
#define ascii 128  // lower ascii

// utility
void Output(string stext, int startindex)
{
	for (int i = 0; i < stext.length(); i++)
	{
		if (i < startindex)
			cout << yellow << stext[i];
		else
			cout << red << stext[i];
	}
	cout << white << endl;
}

// A linear approach:  Seach character by character
void BruteForce(string pattern, string text)
{
	int ncompares = 0;
	// iterate text
	for (int i = 0; i < text.length(); i++)
	{
		int j = 0;
		// increment pattern index
		for (; j < pattern.length(); j++)
		{
			ncompares++;
			if (text[i + j] != pattern[j])
				break;
		}
		if (j == pattern.length())
			cout << "Pattern found at index " << i << endl;
	}
	cout << "BruteForce compares = " << ncompares << endl;
}

// Optimized BF:  skips some characters when match is found
void BFOptimized(string pattern, string text)
{
	int ncompares = 0;
	// length of pattern
	int M = pattern.length()-1;
	// iterate text
	for (int i = 0; i < text.length(); i++)
	{
		// check first character of pattern
		ncompares++;
		if (text[i] == pattern[0])
		{
			ncompares++;
			// check last character of pattern
			if (text[i + M] == pattern[M])
			{
				bool bfound = true;
				// check middle characters
				for (int j = 1; j < M; j++)
				{
					ncompares++;
					if (text[i + j] != pattern[j])
					{
						bfound = false;
						break;
					}
				}
				if (bfound)
				{
					cout << "Pattern found at index " << i << endl;
					// skip ahead length of pattern
					// usually this is a bad idea to repurpose
					// for-loop index by skipping ahead
					i += M; 
				}
			}
		}
	}
	cout << "BFOptimized compares = " << ncompares << endl;
}

class BoyerMooreHorspool
{
	vector<int> badchar;
public:
	BoyerMooreHorspool()
	{
		badchar.resize(ascii);
		for (int i : badchar)
			badchar[i] = -1;
	}
	void badSuffix(string pat)
	{
		for (int i = 0; i < pat.length(); i++)
			badchar[pat[i]] = i;
		for (int i = 0; i < ascii; i++)
		{
			if (((int)badchar[i]) > 0)
				cout << blue << "badchar[" << char(i) << ',' << i << "] = skip " << badchar[i] << endl;
		}
		cout << white << endl;
	}
	void search(string text, string pattern)
	{
		int ncompares = 0;
		badSuffix(pattern);
		int plength = pattern.length();
		int tlength = text.length();
		int shift = 0;  // shift of the pattern with respect to text
		while (shift <= (tlength - plength))
		{
			int right = plength - 1;
			while (right >= 0 && pattern[right] == text[shift + right])
			{
				cout << white << "=====\n";
				cout << green << "pattern[" << right << "] = " << pattern[right] << endl;
				cout << blue << "text[" << shift + right << "] = " << text[shift + right] << endl;
				cout << red << "<< shift = " << shift << '\t';
				cout << yellow << "right = " << right << endl;
				cout << blue << "<< " << shift + right << " >>" << white << endl;
				Output(text, shift + right);
				right--;
				ncompares++;
			}

			// If the pattern is present at current shift, then index 'right'
			// will become -1 after the above loop 
			if (right < 0)
			{
				// Shift the pattern so that the next character in text
				// aligns with the last occurrence of it in pattern.
				// The condition s+m < n is necessary for the case when
				// pattern occurs at the end of text 
				cout << "\n << Pattern occurs starting at index: " << shift << " >>" << endl;
				shift += (shift + plength < tlength) ? plength - badchar[text[shift + plength]] : 1;
			}
			else
			{
				// Shift the pattern so that the bad character in text
				// aligns with the last occurrence of it in pattern. The
				// max function is used to make sure that we get a positive
				// shift. We may get a negative shift if the last occurrence
				// of bad character in pattern is on the right side of the
				// current character.
				shift += max(1, right - badchar[text[shift + right]]);
			}
		}
		cout << "Number of compares: " << ncompares << endl;
	}
};

void BoyerMoore(string pattern, string text)
{
	BoyerMooreHorspool bmh;
	bmh.search(text, pattern);
}
// The Rabin–Karp algorithm seeks to speed up the testing of equality 
// of the pattern to the substrings in the text by using a hash function.
// A hash function is a function which converts every string into a numeric 
// value, called its hash value; for example, we might have hash("hello") = 5. 
// The algorithm exploits the fact that if two strings are equal, their hash 
// values are also equal.Thus, string matching is reduced(almost) to computing 
// the hash value of the search pattern and then looking for substrings of the 
// input string with that hash value.
void RabinKarp(string pattern, string text, int prime)
{
	int ncompares = 0;
	int index = 0;
	int jndex = 0;
	int phash = 0; // hash value for pattern
	int thash = 0; // hash value for txt
	int hash = 1;

	// The value of h would be "pow(d, M-1)%q"
	hash = int(pow(ascii, pattern.length() - 1)) % prime;

	// Calculate the hash value of pattern and first window of text
	for (index = 0; index < pattern.length(); index++)
	{
		phash = (ascii * phash + pattern[index]) % prime;
		thash = (ascii * thash + text[index]) % prime;
	}
	cout << blue << "phash = " << phash << '\t';
	cout << blue << "thash = " << thash << endl;

	// Slide the pattern over text one by one
	for (index = 0; index <= text.length() - pattern.length(); index++)
	{
		// Check the hash values of current window of text
		// and pattern. If the hash values match then only
		// check for characters on by one
		if (phash == thash)
		{
			// Check for characters one by one 
			for (jndex = 0; jndex < pattern.length(); jndex++)
			{
				ncompares++;
				if (text[index + jndex] != pattern[jndex])
					break;
			}
			// if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]
			if (jndex == pattern.length())
				cout << white << "Pattern found at index " << index << endl;
		}

		// Calculate hash value for next window of text: 
		// Remove leading digit, add trailing digit
		if (index < (text.length() - pattern.length()))
		{
			thash = (ascii * (thash - text[index] * hash) + text[index + pattern.length()]) % prime;

			// We might get negative value of t, converting it to positive
			if (thash < 0)
				thash = (thash  + prime);
			
			cout << yellow << "recomputing index = " << index << '\t';
			cout << green << "thash = " << thash << endl;
		}
	}
	cout << white << "RabinKarp compares = " << ncompares << endl;
}

void main()
{
	string text = "ACAAGATGCCATTGTCCCCCGGCCTCCTGCTGCTGCTGCTCTCCGGGGCCACGGCCACCGCGCCCTGCCCCTGGAGGGTGGCCCCACCGGCCGAGACAGCGAGCATATGCAGGAAGCGGCAGGAATAAGGAAAAGCAGCCTCCTGACTTTCCTCGCTTGGTGGTTTGAGTGGACCTCCCAGGCCAGTGCCGGGCCCCTCATAGGAGAGGAAGCTCGGGAGGTGGCCAGGCGGCAGGAAGGCGCACCCCCCCAGCAATCCGCGCGCCGGGACAGAATGCCCTGCAGGAACTTCTTCTGGAAGACCTTCTCCTCCTGCAAATAAAACCTCACCCATGAATGCTCACGCAAGTTTAATTACAGACCTGAA";
	string pattern = "GCAT";
	cout << "==========\n";
	BruteForce(pattern, text);
	cout << "==========\n";
	BFOptimized(pattern, text);
	cout << "==========\n";
	BoyerMoore(pattern, text);
	int prime = 157; // A prime number
	cout << "==========\n";
	RabinKarp(pattern, text, prime);
}


