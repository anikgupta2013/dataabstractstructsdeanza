
#include <cstdlib>
#include <vector>
#include <iostream>
#include <array>
#include <string>

using namespace std;

static int maximum = 0;

int getHash(string key)
{
	int sum = key[0] - 'A' + 1;
	for (int c = 1; c < key.length(); c++)
	{
		if (c % 2)
			sum += (key[c] - 'A');
		else
			sum += ((key[c] - 'A') * 2);

	}
	if (sum > maximum)
		maximum = sum;
	return sum;
}

class HashEntry 
{
private:
      int key;
      string value;
public:
      HashEntry(int k=0, string v="") 
	  {
            key = k;
            value = v;
      }
      int getKey() 
	  {	
            return key;
      }

      string getValue() 
	  {
            return value;
      }
	  operator int() { return getKey(); }
};

template <typename T>
class DynamicArray
{
	T* base;
	int size;
public:
	DynamicArray(int s=1) : size(s) { allocate(size); }
	~DynamicArray() { delete[] base; }
	T getValue(int offset) { return base[offset]; }
	T operator[] (int offset) { return base[offset]; }
	void set(string value) 
	{
		int hash = getHash(value);
		if (base[hash].getValue() == "")
			base[hash] = HashEntry(hash, value);
		else
			cout << "Collision: " << base[hash].getValue() << '\t' << value << endl;
	}
	int length() { return size; }
	void allocate(int s) { size = s; base = new T[size]; }
};

class HashTable 
{
private:
      DynamicArray<HashEntry> table;
public:
	HashTable(int s = 1) { table.allocate(s); }
	int size() { return table.length(); }
	string get(string key) 
	{
		int hash = getHash(key);
		return table[hash].getValue();
	}
	HashEntry get(int index)
	{
		return table[index];
	}
	void put(string value) 
	{
		table.set(value);
	}     
	HashEntry operator [] (int index)
	{
		return get(index);
	}
};

const unsigned TABLE_SIZE = 0x0400; 

void main()
{
	array<string,117> elements = 
	{ 
		"Silver",
		"Aluminium",
		"Americium",
		"Argon",
		"Arsenic",
		"Astatine",
		"Gold",
		"Boron",
		"Barium",
		"Beryllium",
		"Bohrium",
		"Bismuth",
		"Berkelium",
		"Bromine",
		"Carbon",
		"Calcium",
		"Cadmium",
		"Cerium",
		"Californium",
		"Chlorine",
		"Curium",
		"Copernicium",
		"Cobalt",
		"Chromium",
		"Caesium",
		"Copper",
		"Dubnium",
		"Darmstadtium",
		"Dysprosium",
		"Erbium",
		"Einsteinium",
		"Europium",
		"Fluorine",
		"Iron",
		"Flerovium",
		"Fermium",
		"Francium",
		"Gallium",
		"Gadolinium",
		"Germanium",
		"Hydrogen",
		"Helium",
		"Hafnium",
		"Mercury",
		"Holmium",
		"Hassium",
		"Iodine",
		"Indium",
		"Iridium",
		"Potassium",
		"Krypton",
		"Lanthanum",
		"Lithium",
		"Lawrencium",
		"Lutetium",
		"Livermorium",
		"Moscovium",
		"Mendelevium",
		"Magnesium",
		"Manganese",
		"Molybdenum",
		"Meitnerium",
		"Nitrogen",
		"Sodium",
		"Niobium",
		"Neodymium",
		"Neon",
		"Nihonium",
		"Nickel",
		"Nobelium",
		"Neptunium",
		"Oxygen",
		"Oganesson",
		"Osmium",
		"Phosphorus",
		"Protactinium",
		"Lead",
		"Palladium",
		"Promethium",
		"Polonium",
		"Praseodymium",
		"Platinum",
		"Plutonium",
		"Radium",
		"Rubidium",
		"Rhenium",
		"Rutherfordium",
		"Roentgenium",
		"Rhodium",
		"Radon",
		"Ruthenium",
		"Sulfur",
		"Antimony",
		"Scandium",
		"Selenium",
		"Seaborgium",
		"Silicon",
		"Samarium",
		"Tin",
		"Strontium",
		"Tantalum",
		"Terbium",
		"Technetium",
		"Tellurium",
		"Thorium",
		"Titanium",
		"Thallium",
		"Thulium",
		"Tennessine",
		"Uranium",
		"Vanadium",
		"Tungsten",
		"Xenon",
		"Yttrium",
		"Ytterbium",
		"Zinc",
		"Zirconium"
	};

	HashTable htable(TABLE_SIZE);
	for (int x=0; x<elements.size(); x++)
		htable.put(elements[x]);
	for (int x = 0; x < htable.size(); x++)
	{
		HashEntry hentry = htable.get(x);
		if (hentry.getKey())
			cout << "[" << hentry.getKey() << "] " << '\t' << hentry.getValue() << endl;
		else
			cout << "[" << x << "]" << endl;
	}
	cout << "Maximum = " << maximum << endl;
}