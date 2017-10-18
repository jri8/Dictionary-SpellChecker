#pragma once



class word //can either make a chain or a universal hashing funciton
{

private:


public:
	unsigned long wordVal();

	string key;
	word();
	word(string&);
	~word();
};



unsigned long word::wordVal()
{
	unsigned long wordValue = 0;

	for (int i = key.size() - 1; i >= 0; i--)
	{
		wordValue += (pow(37, i) * key[i]);   //pow(3, i)
	}

	//cout << "The word value of " << w << " is: " << wordValue << endl;

	return wordValue;
}


word::word()
{
	key = "";
}

word::word(string& k)
{
	key = k;
}

word::~word()
{

}
