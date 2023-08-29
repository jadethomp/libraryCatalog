/*
Student Name: Jade Thompson
Student NetID: jet475
Compiler Used: Visual Studio
Program Description: ##FIXME
*/

#include "Tokenizer.h"
#include <string>
#include <iostream>
using namespace std;
Tokenizer::Tokenizer() {
	ss.str("");
	ss.exceptions(ios::failbit);
};
Tokenizer::Tokenizer(string userStr) {
	str = userStr;
	ss.str(str);
	ss.exceptions(ios::failbit);
};

bool Tokenizer::readWord(string& val) {
	try {
		ss >> val;
	}
	catch (ios_base::failure) {
		ss.clear();
		return false;
	}
	return true;
};
bool Tokenizer::readInteger(int& val) {
	try {
		ss >> val;
	}
	catch (ios_base::failure) {
		ss.clear();
		return false;
	}
	return true;
};
bool Tokenizer::readDouble(double& val) {
	try {
		ss >> val;
	}
	catch (ios_base::failure) {
		ss.clear();
		return false;
	}
	return true;
};
bool Tokenizer::readLine(string& val) {
	try {
		getline(ss, val);
	}
	catch (ios_base::failure) {
		ss.clear();
		return false;
	}
	return true;
};

void Tokenizer::setString(string& userStr) {
	str = userStr;
	ss.clear();
	ss.str(str);
};
void Tokenizer::clear() {
	ss.clear();
};
void Tokenizer::rewind() {
	clear();
	ss.str(str);
};
bool Tokenizer::isEmpty() {
	if (ss.eof()) {
		return true;
	}
	else {
		return false;
	}
};

