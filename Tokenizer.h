/*
Student Name: Jade Thompson
Student NetID: jet475
Compiler Used: Visual Studio
Program Description: ##FIXME
*/

#pragma once
#include <string>
#include <sstream>
using namespace std;
class Tokenizer
{
private:
	string str;
	stringstream ss;
public:
	Tokenizer();
	Tokenizer(string userStr);

	bool readWord(string& val);
	bool readInteger(int& val);
	bool readDouble(double& val);
	bool readLine(string& val);

	void setString(string& userStr);
	void clear();
	void rewind();
	bool isEmpty();
};

