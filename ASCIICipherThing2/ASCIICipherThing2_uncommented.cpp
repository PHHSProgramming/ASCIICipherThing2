//ASCII Cipher Thing: Cleaned Up and Revised Uncommented 02.18.15

#include <iostream>	
#include <fstream>	
#include <string>	

using namespace std;

string STable = " !#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmnopqrstuvwxyz{|}~";



string File2String(const char *file);
void String2File(string str, const char *file);
int Char2Index(string inputchar);
string Index2Char(int index);
int NormalizeIndex(int index);

void CodeMessage(int cKey, const char *inputfile, const char *outputfile);
void DecodeMessage(int cKey, const char *inputfile, const char *outputfile);


int main(int argc, char* argv[])
{
	int cipherKey;
	cout << "Enter the Cipher Key: ";
	cin >> cipherKey;

	CodeMessage(cipherKey, "message.txt", "encoded.txt");
	DecodeMessage(cipherKey, "encoded.txt", "decoded.txt");

	return 0;
}

/*----------------------------------------------------------------------------*/

void CodeMessage(int cKey, const char *inputfile, const char *outputfile)
{

	string inputString = File2String(inputfile);


	string outputString = "";

	for (int i = 0; i < (int)inputString.length(); i++)
	{
	
		int newIndex = Char2Index(inputString.substr(i, 1)) + cKey;
		newIndex = NormalizeIndex(newIndex);
	
		outputString = outputString + Index2Char(NormalizeIndex(newIndex));
	}


	String2File(outputString, outputfile);
}

void DecodeMessage(int cKey, const char *inputfile, const char *outputfile)
{
	string inputString = File2String(inputfile);
	string outputString = "";
	for (int i = 0; i < (int)inputString.length(); i++)
	{
		int newIndex = Char2Index(inputString.substr(i, 1)) - cKey;
		newIndex = NormalizeIndex(newIndex);
		outputString = outputString + Index2Char(newIndex);
	}
	String2File(outputString, outputfile);
}

/*----------------------------------------------------------------------------*/

string File2String(const char *file)
{
	string str;							
	ifstream inputstream;				
	inputstream.open(file);
	if (inputstream.is_open())
	{
		while (!inputstream.eof())
		{
			getline(inputstream, str);	
		}
	}
	inputstream.close();					

	return str;
}

void String2File(string str, const char *file)
{

	ofstream outputstream;
	outputstream.open(file, ofstream::out);
	outputstream << str;				
	outputstream.close();
}

int Char2Index(string inputchar)
{
	int index = 0;
	for (int k = 0; k < (int)STable.length(); k++)
	{
		if (inputchar == STable.substr(k, 1))
		{
			index = k;
		}
	}
	return index;
}

string Index2Char(int index)
{
	return STable.substr(index, 1);
}

int NormalizeIndex(int index)
{
	int tIndex = index;

	if (tIndex > (int)STable.length())
	{
		while (tIndex > (int)STable.length())
		{
			tIndex -= STable.length();
		}
	}

	if (tIndex < 0)
	{
		while (tIndex < 0)
		{
			tIndex += STable.length();
		}
	}
	return tIndex;
}
