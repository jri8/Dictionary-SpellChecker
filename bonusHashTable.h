#pragma once


#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <cstdlib> 
#include "UNH.h"
#include "word.h"

using std::string;
using std::cout;
using std::endl;

//to make hash table just make an array of hash table nodes
//


class bonusHashTable
{

private:
	int buildTableSize();
	bool isPrime(int);
	//unsigned long wordVal(word&);
	

public:

	UHN* table;
	int tableSize;
	int words;
	int collisions;
	int maxCollision;

	bonusHashTable();
	bonusHashTable(int); //passes in size of table;

	void insert(string&);
	void checkCollisions(string&);
	void constructSecondaryHashes();
	bool find(string&);

	~bonusHashTable();
};



bonusHashTable::bonusHashTable()
{
	words = 0;
	table = NULL;
	tableSize = 0;
	collisions = 0;
	maxCollision = 0;
}

bonusHashTable::bonusHashTable(int w)
{
	words = w;
	tableSize = buildTableSize();
	table = new UHN[tableSize];
	//collisions = 0;
	//maxCollision = 0;

}

bonusHashTable::~bonusHashTable()
{

}

int bonusHashTable::buildTableSize()
{
	int j = words / 4;
	while ((4 * j + 3) < this->words || !isPrime(4 * j + 3))
	{
		j++;
	}

	return (4 * j + 3);
}

bool bonusHashTable::isPrime(int num)
{
	bool isPrime = true;
	int max = sqrt(num) + 1;
	for (int i = 2; i < max && isPrime; i++)
	{
		if ((num%i) == 0)
			isPrime = false;
	}

	return isPrime;
}




void bonusHashTable::checkCollisions(string& w)
{
	word wordObj(w);
	unsigned long wordValue = wordObj.wordVal();
	int index = wordValue % tableSize;
	table[index].collisions++;

}

void bonusHashTable::constructSecondaryHashes()
{
	int secondTableSize = 0;
	for (int i = 0; i < tableSize; i++)
	{
		secondTableSize = table[i].collisions+1;
		secondTableSize = pow(secondTableSize, 2);
		table[i].uniHT = new word[secondTableSize];
	}
}



void bonusHashTable::insert(string& w)
{
	word wordObj(w);
	unsigned long wordValue = wordObj.wordVal();
	int index = wordValue % tableSize;
	//cout << "The index " << w << " will be insered at is: " << index << endl;

	this->table[index].insert(wordObj);

	/*if (this->table[index].chainSize > 1)
	{
		collisions++;
		if (maxCollision < table[index].chainSize)
			maxCollision = table[index].chainSize;
	}*/
}

bool bonusHashTable::find(string& w)
{
	
	transform(w.begin(), w.end(), w.begin(), toupper);
	word wordObj(w);
	unsigned long wordValue = wordObj.wordVal();
	int index = wordValue % tableSize;

	return this->table[index].find(wordObj);
}













//cout << endl << endl;
//cout << "bonus hash Table" << endl;
//
//ifstream dictFile;
//dictFile.open(dict);
//string data;
//int size;
//
//dictFile >> size;
//dictionary2 = bonusHashTable(size);
//
//while (dictFile >> data)
//{
//	int pos = data.find('/');
//
//	if (pos != -1)
//		data = data.substr(0, pos);
//
//	transform(data.begin(), data.end(), data.begin(), toupper);
//
//	dictionary2.checkCollisions(data);
//}
//
//
//
//
//dictionary2.constructSecondaryHashes();
//
//dictFile.close();
//dictFile.open(dict);
//
//dictFile >> size;
//
//
//int i = 0;
//
//while (dictFile >> data)
//{
//
//	int pos = data.find('/');
//
//	if (pos != -1)
//		data = data.substr(0, pos);
//
//	transform(data.begin(), data.end(), data.begin(), toupper);
//	cout << i << ":       " << data;
//	dictionary2.insert(data);
//	i++;
//
//
//
//}
//
//cout << "finished inserting" << endl; 




