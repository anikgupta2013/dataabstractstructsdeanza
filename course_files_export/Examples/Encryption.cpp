#include <iostream>
#include <vector>
#include <string>
#include <bitset>
using namespace std;

class Encrypt
{
	vector<char> alphabet;
public:
	Encrypt()
	{
		alphabet.resize(26);
		for (char c = 'A'; c <= 'Z'; c++)
			alphabet[c-'A'] = c;
	}
	string ECaesar(string sline,int offset)
	{
		string encrypt = "";
		// e(x) = (x + k) mod 26
		for (int x = 0; x < sline.length(); x++)
		{
			if (isalpha(sline[x]))
			{
				int index = (sline[x] - 'A' + offset) % 26;
				encrypt += alphabet[index];
			}
		}
		return encrypt;
	}
	string DCaesar(string sline, int offset)
	{
		string encrypt = "";
		for (int x = 0; x < sline.length(); x++)
		{
			if (isalpha(sline[x]))
			{
				int index = (sline[x] + 'A' - offset) % 26;
				encrypt += alphabet[index];
			}
		}
		return encrypt;
	}
	string EFiveBit(string sline)
	{
		string encrypt = "";
		for (int x = 0; x < sline.length(); x++)
		{
			if (isalpha(sline[x]))
			{
				bitset<5> bset(sline[x] - 'A');
				encrypt += char(bset.to_ulong());
			}
		}
		return encrypt;
	}
	string DFiveBit(string sline)
	{
		string encrypt = "";
		for (int x = 0; x < sline.length(); x++)
		{
			char c = char(sline[x]) + 'A';
			encrypt += c;
		}
		return encrypt;
	}
	string EXOR(string sline, char cxor)
	{
		char e = sline[0] ^ cxor;
		char c = e ^ cxor;
		string encrypt = "";
		for (int x = 0; x < sline.length(); x++)
		{
			encrypt += sline[x] ^ cxor;
		}
		return encrypt;
	}
	string Exchange(string sline)
	{
		string encrypt = "";
		for (int x = 0; x < sline.length(); x++)
		{
			char c = sline[x];
			char lower = c & 0x0F;
			char upper = (c & 0xF0) >> 4;
			char combo = (lower << 4) + upper;
			encrypt += combo;
		}
		return encrypt;
	}
};

void main()
{
	string master = "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOGS";
	Encrypt encrypt;
	string estring = encrypt.ECaesar(master, 4);
	string dstring = encrypt.DCaesar(estring, 4);
	estring = encrypt.EFiveBit(master);
	dstring = encrypt.DFiveBit(estring);
	estring = encrypt.EXOR(master, 'A');
	dstring = encrypt.EXOR(estring, 'A');
	estring = encrypt.Exchange(master);
	dstring = encrypt.Exchange(estring);
}
