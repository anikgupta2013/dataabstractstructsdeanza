// Program for Bad Character Heuristic of Boyer Moore String Matching 
// Algorithm 

#include <iostream>
#include <climits>
#include <string>
#include <cstdio>
#include <vector>
#include <algorithm>
#include "ConsoleColor.h"
using namespace std;

#define NO_OF_CHARS 128

/*
Bad character heuristics
It is applied if the bad character, i.e. the text symbol that causes 
a mismatch, occurs somewhere else in the pattern. Then the pattern 
can be shifted so that it is aligned to this text symbol.

The idea of bad character heuristic is simple. The character of the text 
which doesn’t match with the current character of pattern is called the 
Bad Character. Upon mismatch we shift the pattern until –
1) The mismatch become a match
2) Pattern P move past the mismatch character.
*/

void Output(string stext, int startindex)
{
	for (int i = startindex; i < stext.length(); i++)
	{
		cout << yellow << stext[i];
	}
	cout << white << endl;
}

class BoyerMoore
{
	vector<int> badchar;
public:
	BoyerMoore()
	{
		badchar.resize(NO_OF_CHARS);
		for (int i = 0; i < NO_OF_CHARS; i++)
			badchar[i] = -1;
	}
	// The preprocessing function for Boyer Moore's bad character heuristic
	void badCharHeuristic(string pat)
	{
		// Fill the actual value of last occurrence of a character
		for (int i = 0; i < pat.length(); i++)
		{
			badchar[(int)pat[i]] = i;
			cout << "badchar[" << (int)pat[i] << "] <" << pat[i] <<"> = " << i << endl;
		}
		for (int i=0; i<NO_OF_CHARS; i++)
			if (((int)badchar[i]) > -1)
				cout << blue << "badchar[" << char(i) << ',' << i << "] = skip " << badchar[i] << endl;
		cout << white << endl;
	}

	// A pattern searching function that uses Bad Character Heuristic of
	// Boyer Moore Algorithm 
	void search(string text, string pattern)
	{
		// Fill the bad character array by calling the preprocessing
		// function badCharHeuristic() for given pattern 
		badCharHeuristic(pattern);
		int plength = pattern.length();
		int tlength = text.length();
		int shift = 0;  // shift of the pattern with respect to text
		while (shift <= (tlength - plength))
		{
			int right = plength - 1;
			cout << red << "reset right = " << right << white << endl;
			// Keep reducing index 'right' of pattern while characters of
			// pattern and text are matching at this shift 
			while (right >= 0 && pattern[right] == text[shift + right])
			{
				cout << "=====\n";
				cout << green << "pattern[" << right << "] = " << pattern[right] << endl;
				cout << blue << "text[" << shift + right << "] = " << text[shift + right] << endl;
				Output(text, shift + right);
				right--;
				cout << red << "right = " << right << white << endl;
			}

			// If the pattern is present at current shift, then index 'right'
			// will become -1 after the above loop 
			if (right < 0)
			{
				cout << "\n pattern occurs starting at index: " << shift << endl;
				// Shift the pattern so that the next character in text
				// aligns with the last occurrence of it in pattern.
				// The condition s+m < n is necessary for the case when
				// pattern occurs at the end of text 
				shift += (shift + plength < tlength) ? plength - badchar[text[shift + plength]] : 1;
				cout << red << "\n <Shifting: " << shift << white << endl;
				Output(text, shift);
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
				cout << red << "\t>Shifting: " << shift << white << endl;
				Output(text, shift);
			}
		}
	}
};

void main()
{
	BoyerMoore bm;
	string text = "TRUSTHARDTOOTHBRUSHES"; 
	string pattern = "TOOTH";
	bm.search(text, pattern);
}


