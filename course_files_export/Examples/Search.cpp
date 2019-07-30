#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
// Vector is used because most traditional examples use arrays.
#include <vector>
using namespace std;

template <typename T>
class DynamicArray : public vector<T>
{};

DynamicArray<string> ParseRegex(string text, string split)
{
	DynamicArray<string> sdata;
	sregex_token_iterator end;
	regex pattern(split);
	for (sregex_token_iterator pos(text.begin(), text.end(), pattern); pos != end; ++pos)
	{
		if ((*pos).length() > 0)
		{
			if ((static_cast<string>(*pos))[0] != 0x20) // space char
				sdata.push_back(*pos);
		}
	}
	return sdata;
}

int CalculateHash(string s)
{
	DynamicArray<string> vs = ParseRegex(s, "[0-9]*");
	int sum = 0;
	for (int i = 0; i < vs.size(); i++)
	{
		string s = vs[i];
		for (int j = 0; j<s.length(); j++)
		{
			char c = s[j];
			sum += int(c - '0');
		}
	}
	return sum;
}

class Interface
{
public:
	virtual string getData() = 0; 
	virtual int getHash() = 0; 
};

class CreditCard : Interface
{
	string cardnumber;
	string name;
	int hash;
public:
	CreditCard()
	{
		cardnumber = "";
		name = "";
		hash = -1;
	}
	CreditCard(string s)
	{
		DynamicArray<string> vs = ParseRegex(s, "[^,]*");
		if (vs.size())
		{
			cardnumber = vs[0];
			name = vs[1];
			hash = CalculateHash(cardnumber);
		}
	}
	void operator = (CreditCard& c)
	{
		name = c.name;
		cardnumber = c.cardnumber;
		hash = c.hash;
	}
	string getName() { return name; }
	string getCard() { return cardnumber; }
	int getHash() { return hash; }
	string getData() { return getCard(); }
	friend ostream& operator << (ostream& os, CreditCard& c)
	{
		os << c.name << '\t';
		os << c.cardnumber << '\t';
		os << c.hash << '\t';
		cout << endl;
		return os;
	}
};

template <typename T>
class HashTable
{
	DynamicArray<T> table;
	int collisions;
public:
	HashTable(int n) : collisions(0) { table.resize(n * 2); }
	~HashTable() { cout << "Collisions = " << collisions << endl; }
	void Insert(T& t)
	{
		int index = t.getHash();
		int used = table[index].getHash();
		table[index] = t;
		if (used > 0)
			collisions++;
	}
	void SetHash(DynamicArray<T>& vdata)
	{
		for (auto c : vdata)
			Insert(c);
	}
	T Lookup(string s)
	{
		cout << ">>> HashTable <<<\n";
		int index = CalculateHash(s);
		cout << "    Hash = " << index << endl;
		return table[index];
	}
};

template <typename T>
int linearSearch(DynamicArray<T> vdata, string value)
{
	cout << ">>> Linear Search <<<\n";
	int index = 0;
	while (index < vdata.size())
	{
		if (vdata[index].getData().compare(value) == 0)
			break;
		index++;
	}
	if (index >= vdata.size())
		index = -1;
	cout << "Number of linear searches " << index << endl;
	return index;
}

/*********************
BINARY-SEARCH(x,T,p,r)
1	low = p
2 	high = max(p.r + 1)
3 	while low < high
4		mid = (low + high)/2
5 		if x <= T[mid]
6 			high = mid
7 		else low = mid + 1
8 	return high
**********************/
template <typename T>
int binarySearch(DynamicArray<T> vdata, string value)
{
	cout << ">>> Binary Search <<<\n";
	int first = 0, // First element       
	last = vdata.size() - 1,       // Last element       
	middle,                // Mid point of search       
	position = -1;         // Position of search value   
	bool found = false;    // Flag
	int count = 0;
	while (!found && first <= last)   
	{  
		count++;
		cout << ">>> Pass " << count << endl;
		cout << "    First: " << first << "\tLast: " << last << endl;
		middle = (first + last) / 2;     
		if ( (vdata[middle]).getData().compare(value) == 0)        
		{         
			found = true;         
			position = middle;      
		}      
		else if ( vdata[middle].getData().compare(value) > 0 )        
			last = middle - 1;      
		else         
			first = middle + 1;            
	}   
	cout << "Number of binary searches " << count << endl;
	return position;
} 

/*********************
The interpolation search algorithm tries to improve the binary search. 
The question is how to find this value? The bounds of the interval are 
defined by the following formula:

	Key = (data - low) / (high - low)

The Key is used to narrow down the search space. For binary search, 
this Key is (low + high) / 2.  On average the interpolation search 
makes about O(log N) comparisons (if the elements are uniformly 
distributed), where N is the number of elements to be searched.
**********************/

// utility function specific for CreditCards.csv
int getValue(string s)
{
	if (s.length())
	{
		// [7649] 8115 1051 9678
		vector<string> vdata = ParseRegex(s, "[0-9]*");
		return atoi(vdata[0].data());
	}
	else
		return -1;
}

// modified to use indices instead of data interpolation
template <typename T>
int interpolationSearch(DynamicArray<T> vdata, string value)
{
	int ncompares = 0;
	int ilow = getValue(vdata[0].getData());
	int ihigh = getValue(vdata[vdata.size() - 1].getData());
	int ivalue = getValue(value);
	int index = int(float(ivalue - ilow) / float(ihigh - ilow) * vdata.size());
	int previndex = 0;
	cout << ">>> Interpolation Search <<<\n";
	while (index != previndex)
	{
		cout << ">>> Pass: " << ncompares + 1 << endl;
		cout << "    Index = " << index << endl;
		if (getValue(vdata[index].getData()) == ivalue)
		{
			ncompares++;
			break;
		}
		if (getValue(vdata[index].getData()) < ivalue)
		{
			previndex = index;
			ncompares++;
			ilow = getValue(vdata[index].getData());
			int adjust = int(float(ivalue - ilow) / float(ihigh) * vdata.size());
			index += adjust;
		}
		else
		{
			previndex = index;
			ncompares++;
			ihigh = getValue(vdata[index].getData());
			int adjust = int(float(ihigh - ivalue) / float(ihigh) * vdata.size());
			index -= adjust;
		}
	}
	cout << "Number of interpolation searches " << ncompares << endl;
	if (index == previndex)
		return -1;
	return index;
}

template <typename T>
DynamicArray<T> readFile(string sfile)
{
	DynamicArray<T> data;
	string buffer;
	ifstream infile(sfile);
	while (!infile.eof())
	{
		getline(infile, buffer);
		if (buffer.length())
		{
			T t(buffer);
			data.push_back(t);
		}
		buffer = "";
	}
	infile.close();
	return data;
}

void main()
{
	{
		DynamicArray<CreditCard> cards = readFile<CreditCard>("CreditCards.csv");
		int lindex = linearSearch<CreditCard>(cards, "7649 8115 1051 9678");
		int bindex = binarySearch<CreditCard>(cards, "7649 8115 1051 9678");
		int iindex = interpolationSearch<CreditCard>(cards, "7649 8115 1051 9678");
		HashTable<CreditCard> htable(cards.size());
		htable.SetHash(cards);
		CreditCard card = htable.Lookup("7649 8115 1051 9678");
		cout << card;
	}
}