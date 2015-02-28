//ASCII Cipher Thing: Cleaned Up and Revised 02.18.15

#include <iostream>		//cout and cin.
#include <fstream>		//ofstream and ifstream.
#include <string>		//Since I don't like character arrays and find strings easier to work with. 

//Even though this can be considered bad practice, I'm too lazy to type out std:: every time so I use this.
using namespace std;

//I can't be bothered to use a real ASCII table so here's a replacement whatever. It's kinda a global, so I put it out here.
string STable = " !#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[]^_`abcdefghijklmnopqrstuvwxyz{|}~";


//Function prototypes.
string File2String(const char *file);
void String2File(string str, const char *file);
int Char2Index(string inputchar);
string Index2Char(int index);
int NormalizeIndex(int index);

void CodeMessage(int cKey, const char *inputfile, const char *outputfile);
void DecodeMessage(int cKey, const char *inputfile, const char *outputfile);


//Clean and simple.
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

//Encode the message yeah.
void CodeMessage(int cKey, const char *inputfile, const char *outputfile)
{
	//Get the string we want.
	string inputString = File2String(inputfile);

	//Now generate the encoded string (outputString) using the STable.
	string outputString = "";
	//Go through each character of our input string. 
	for (int i = 0; i < (int)inputString.length(); i++)
	{
		//substr(pos, length) let's us get a sub string of the string at a given position and length. We get the index of each character and add the cipher key to it to generate a new index.
		int newIndex = Char2Index(inputString.substr(i, 1)) + cKey;
		newIndex = NormalizeIndex(newIndex);
		//Now that new index is used to generate a new character, which is then appended to outputString.
		outputString = outputString + Index2Char(NormalizeIndex(newIndex));
	}

	//Write the encoded message to the output file.
	String2File(outputString, outputfile);
}

//Literally copy and pasted from CodeMessage, the only difference being that we now subtract the cipher key from the index rather than adding it.
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

//As the name says, read a string from a file.
string File2String(const char *file)
{
	string str;							
	ifstream inputstream;					//Create the input stream object.
	inputstream.open(file);
	if (inputstream.is_open())
	{
		while (!inputstream.eof())
		{
			getline(inputstream, str);		//Reads a line of the file into a string. There is only support for a single line since I am lazy.
		}
	}
	inputstream.close();					

	return str;
}

//As the name says, write a string to a file.
void String2File(string str, const char *file)
{
	//Output is easier than input it seems.
	ofstream outputstream;
	outputstream.open(file, ofstream::out);
	outputstream << str;					//Writing to a file is so much easier. It's like cout, except to a file.
	outputstream.close();
}

//Finds the index of a certain character within the STable of characters so that we can do math on it later.
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

//Turns a given index to its corresponding character in the STable. Comparatively simple.
string Index2Char(int index)
{
	return STable.substr(index, 1);
}

//So Indexes can't go out of bounds.
int NormalizeIndex(int index)
{
	int tIndex = index;
	//Subtract the number of indexes in STable from the index until the index we want is no greater than the number of possible indexes in STable.
	if (tIndex > (int)STable.length())
	{
		while (tIndex > (int)STable.length())
		{
			tIndex -= STable.length();
		}
	}
	//Add the number of indexes in STable from the index until the index we want is no longer less than 0.
	if (tIndex < 0)
	{
		while (tIndex < 0)
		{
			tIndex += STable.length();
		}
	}
	return tIndex;
}
