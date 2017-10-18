


#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include "hashTable.h"
#include "bonusHashTable.h"


using namespace std;
ostringstream loadDict(string&, hashTable&);
ostringstream spellCheck(string&, hashTable&);


int main(int argc, const char* argv[])
{



	//first file is dictionary file
	string dict = argv[1];
	//second file is file to check for misspellings
	string fToCheck = argv[2];
	ostringstream os;
	ofstream of;
	hashTable dictionary;
	

	cout << "beginning to build dictionary..." << endl;

	os << (loadDict(dict, dictionary)).str(); //calling function to load dictionary

	cout << "data has been loaded" << endl << endl;

	cout << "beginning spell check..." << endl;

	os << (spellCheck(fToCheck, dictionary)).str(); //calling function to spell check secondary file
	
	//cout << os.str();
	of.open("dictionaryLog.txt"); //output file

	of << os.str(); //writing to output file

	of.close(); //closing output file


	cout << "You will find an output log with file name: dictionaryLog.txt, that contains all output data" << endl;

	cin.get(); //keeps window open in visual studio

	return 0;


}

ostringstream loadDict(string &dict, hashTable &dictionary) //loads dictionary
{
	int totalWords;
	double loadFactor;
	ifstream dictFile;
	string data;
	ostringstream os;
	dictFile.open(dict);

	if (!dictFile) //checking if file opened
	{
		os << "The input file failed to open. ";
		os << "Check to ensure the file:\n" << dict << "\nis valid." << endl;
	}

	else //if file opened
	{
		int counter = 0;
		int wordCounter = 0;
		//getting total number of words in the file
		dictFile >> totalWords;



		os << "total Words: " << totalWords << endl;
		dictionary = hashTable(totalWords);
		os << "table size: " << dictionary.tableSize << endl << endl;

		//os << "building dictionary..." << endl;

		while (dictFile >> data) //for (int i = 0; i < 30; i++)	//
		{
			//cout << data << "\t";

			counter++;

			//j
			//cout << counter << ": ";

			int pos = data.find('/');

			if (pos != -1)
				data = data.substr(0, pos);

			transform(data.begin(), data.end(), data.begin(), toupper); //makes all words upper case
			//cout << data << endl;

			dictionary.insert(data);
			wordCounter++;



		}
		//calculating load factor
		loadFactor = static_cast <double>(wordCounter) / dictionary.tableSize;
		//os << wordCounter << endl;
		//os << dictionary.tableSize<< endl;

		//all outputs
		os << "dictionary complete" << endl;
		os << "number of collisions: " << dictionary.collisions << endl;
		os << "largest chain length: " << dictionary.maxCollision << endl;
		os << "number of words loaded: " << wordCounter << endl;
		os << "Load factor (lambda): " << fixed << setprecision(6) << loadFactor << endl << endl;

		cout << os.str();
		return os;

	}
}



ostringstream spellCheck(string &fname, hashTable &dictionary) //spell check function
{
	int mispelled = 0;
	int count = 0;
	ifstream checkFile;
	string data;
	string data2;
	string word;
	string line;
	checkFile.open(fname);
	int pos = 0;
	int lineNum = 0;
	stringstream sstream;
	ostringstream os;

	if (!checkFile) //checking if file opened
	{
		cout << "The input file failed to open. ";
		cout << "Check to ensure the file:\n" << fname << "\nis valid." << endl;
	}

	else //if file opened
	{

		while (getline(checkFile, line)) //getting each line
		{
			//os << line << endl;
			sstream << line; //pushing in sstream
			//data.clear();
			lineNum++;
		//	cout << lineNum << endl;
		//	cout << line << ": ";

			while (sstream >> data) //reading out sstream to get individual words
			{
				count++;
		//		cout << data << endl;
				
				//parsing words for extraneous characters
				pos = data.find("/");
				if (pos != -1)
					data = data.substr(0, pos);

				pos = data.find(",");
				if (pos != -1)
					data = data.substr(0, pos);

				pos = data.find(".");
				if (pos != -1)
					data = data.substr(0, pos);

				pos = data.find("!");
				if (pos != -1)
					data = data.substr(0, pos);

				pos = data.find("?");
				if (pos != -1)
					data = data.substr(0, pos);

				pos = data.find("-");
				if (pos != -1)
					data = data.substr(0, pos);

				pos = data.find("\"");
				if (pos != -1 && pos == 0)
					data = data.substr(1);

				pos = data.find("\"");
				if (pos != -1 && pos != 0)
					data = data.substr(0, pos);

				//storing word before removing " ' "
				word = data2 = data;

				pos = data.find("'");
				if (pos != -1 && pos == data.size()-2)
					data = data.substr(0, pos);


				//checking dictionary for both the word without " ' " and word with " ' "

				if (!dictionary.find(data) && !dictionary.find(data2))
				{
					mispelled++;
					os << endl << "line: " << setw(5) << left << lineNum <<  word << " is misspelled " << endl;
					//cin.get();
				}
				else 
				{
					// << word << " is spelled correctly on line number: " << lineNum << endl;
				}
			}

			sstream.clear();
		}

		//outputting data
		os << endl << endl << "Total Words checked: " << count << endl;
		os << "Total words misspelled: " << mispelled << endl;
		os << "Unsuccessful Probes: " << mispelled << endl;
		os << "Successful Probes: " << count - mispelled << endl;

		cout << os.str();
		return os;

	}
}