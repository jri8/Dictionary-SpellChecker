#pragma once

#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>

using std::string;
using std::cout;
using std::endl;

//to make hash table just make an array of hash table nodes
//




class chainNode //node of the chain from the hash table, used for storing the key
{

private:


public:
	chainNode* next; //holds pointer for linked list
	string word; //holds key

	chainNode(); //constructor
	chainNode(string&); //constructor with parameters
	~chainNode(); //destructor
};


class HTN  // Hash Table Node, holds a pointer to the chain node and constructs the hash table
{

private:
	

public:
	int chainSize; //holds size of the chain
	chainNode* head; //holds pointer to head of chain
	void insert(string&); //inserts key
	bool find(string&); //finds key

	HTN(); //constructor
	~HTN(); //destructor
	
};


class hashTable //stores an array of hash table nodes
{

private:
	int buildTableSize();
	bool isPrime(int); //helper function for creating table size
	unsigned long wordVal(string&); //helper function for calculating word value

public:
	
	HTN* table; //used to make array of hash table nodes
	int tableSize; //stores table size
	int words; //stores number of words
	int collisions; //stores number of collisions
	int maxCollision; //stores most collisions at one index

	hashTable();
	hashTable(int); //passes in size of table;

	void insert(string&); //inserts word
	bool find(string&); //finds word

	~hashTable();
};



hashTable::hashTable()
{
	words = 0;
	table = NULL;
	tableSize = 0;
	collisions = 0;
	maxCollision = 0;
}

hashTable::hashTable(int w)
{
	words = w;
	tableSize = buildTableSize();
	table = new HTN[tableSize];
	collisions = 0;
	maxCollision = 0;

}

hashTable::~hashTable()
{
	if (table != NULL)
	{
		for (int i = 0; i < tableSize; i++)
		{
			table[i].~HTN();
		}
	}
}

int hashTable::buildTableSize() //constructs a table size that is a prime number of form 4* j + 3 that is bigger than the number of words
{
	int j = words/4;
	while ((4 * j + 3) < this->words || !isPrime(4 * j + 3))
	{
		j++;
	}

	return (4 * j + 3);
}

bool hashTable::isPrime(int num) //helper function for buildtablesize
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

unsigned long hashTable::wordVal(string& w) //calculates word value
{
	unsigned long wordValue = 0;
	for (int i = w.size() - 1; i >= 0; i--)
	{
		wordValue +=  (pow(37, i) * w[i]);   
	}

	//cout << "The word value of " << w << " is: " << wordValue << endl;

	return wordValue;
}


void hashTable::insert(string& w) //inserts key into hash table
{
	
	unsigned long wordValue = this->wordVal(w);
	int index =  wordValue % tableSize;
	//cout << "The index " << w << " will be insered at is: " << index;     //flag


	this->table[index].insert(w); //calls HTN insert function

	if (this->table[index].chainSize > 1) //if there is mroe than one node in the chain then there was a collision
	{
		collisions++;
		if (maxCollision < table[index].chainSize)
			maxCollision = table[index].chainSize;
	}
}

bool hashTable::find(string& w) //find function
{
	transform(w.begin(), w.end(), w.begin(), toupper);
	unsigned long wordValue = this->wordVal(w);
	int index = wordValue % tableSize;

	return this->table[index].find(w);
}



HTN::HTN()
{
	head = NULL;
	chainSize = 0;
}

HTN::~HTN()
{
	chainNode* current = head;
	if (head != NULL)
	{
		while (current != NULL)
		{
			current = current->next;
			delete head;
			head = current;
		}
	}
}
void HTN::insert(string& w) //HTN insert function (adds key to linked list)
{
	//cout << "inside insert" << endl;
	chainNode* current = head;
	if (this->head == NULL)
		head = new chainNode(w);
	else
	{
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new chainNode(w);
	}
	chainSize++;
	//cout << "chain length of  " << w << "is: " << chainSize << endl;        //flag
}
bool HTN::find(string& w) //HTN find function (searches for key in linked list)
{
	chainNode* current = head;
	bool inTable = false;
	transform(w.begin(), w.end(), w.begin(), toupper);

	if (this->head == NULL)
		inTable = false;
	else
	{
		while (current != NULL)
		{
			if (w.compare(current->word) == 0)
			{
				inTable = true;
				//cout << current->word << " == " << w << endl;    //flag
			}
			current = current->next;
		}
		
	}

	return inTable;

}



chainNode::chainNode()
{
	next = NULL;
	word = " ";
}
chainNode::chainNode(string& w) //Holds a key and a pointer to the next chainNode in the list
{
	next = NULL;
	word = w;
}
chainNode::~chainNode()
{

}
