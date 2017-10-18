#pragma once
#include "word.h"


class UHN  // Hash Table Node (keep track of a and b in here for universal hashing function) 
{

private:
	bool isPrime(int);
	int getPrime(int);


public:
	int a;
	int b;
	int p;
	int collisions;
	word* uniHT;

	void insert(word&);
	bool find(word&);


	UHN();
	~UHN();

};




UHN::UHN()
{

	a = rand();
	b = rand();
	p = 0;
	collisions = 0;

}

UHN::~UHN()
{

}


bool UHN::isPrime(int num)
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
int UHN::getPrime(int i)
{

	
	int j = i+1;
	while ((j) < i || !isPrime(j))
	{
		j++;
	}

	return (j);
}






void UHN::insert(word& w)
{
	//cout << "inside insert" << endl;

	//cout << "inserting " << w.key << "with word value: " << w.wordVal() << endl;
	//cout << "a = " << a << endl;
	//cout << "b = " << b << endl << endl;


	
	int size = pow(collisions+1, 2);
	this->p = this->getPrime(size);
	bool conflict = false;




	int index = (((a*w.wordVal() + b) % p) % size);
	word* newHash = NULL;

	cout << "    index = " << index;
	cout << "    size = " << size;

	if (uniHT[index].key == "")
	{
		cout <<  "\t\t\tconflict has not occured" << endl;
		uniHT[index] = w;
	}
	else
	{
		cout << "\t\t\tconflict HAS occured: " << uniHT[index].key << endl << endl;

		conflict = true;

		while (conflict == true)
		{
			
			collisions++;

			conflict = false;
			this->a = rand();
			this->b = rand();
			this->p = this->getPrime(p);

			newHash = new word[size];
			
			for (int i = 0; i < size; i++)
			{
				cout << i << ": " << uniHT[i].wordVal() << "  \t";

				index = (((a*uniHT[i].wordVal()+ b ) % p) % size);
				cout << index << "    " ;

				cout << "p: " << p << "\t" << "size: " << size << "\t";
				cout << (a*uniHT[i].wordVal() + b) << "\t";

				if (newHash[index].key == "")
				{
					cout << "\t\t\tinside if statement" << endl;
					
					newHash[index] = uniHT[i];
				}
				else
				{
					cout << "\t\t\tinside else statement" << endl;
					conflict = true;
				}
			}

			index = (((w.wordVal() + b) % p) % size);
			if (newHash[index].key != "")
			{
				conflict = true;
				delete[] newHash;
			}
			else
			{
				conflict = false;
				newHash[index] = w;
			}

		}

		
		
		cout << "conflict resolved" << endl;
		delete [] uniHT;
		
		uniHT = newHash;
	}

	//cout << "the number of words in this chain is: " << chainSize << endl;
	
}

bool UHN::find(word& w)
{
	//secondHash* current = head;
	//bool inTable = false;
	//transform(w.begin(), w.end(), w.begin(), toupper);

	//if (this->head == NULL)
	//	inTable = false;
	//else
	//{
	//	while (current != NULL)
	//	{
	//		if (w.compare(current->word) == 0)
	//		{
	//			inTable = true;
	//			//cout << current->word << " == " << w << endl;
	//		}
	//		current = current->next;
	//	}

	//}
	return true;
	//return inTable;

}
