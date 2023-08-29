#pragma once
#include <string>
using namespace std;

class Node {
public:
	string name;
	int length;
	string genre;
	string authorlastname;

	Node* next;
	Node* prev;

	Node() : name("null"), length(0), genre("null"), authorlastname("null") {}
	Node(string name) : name(name), length(0), genre("null"), authorlastname("null") {}
	Node(string name, int length, string genre, string authorlastname) : name(name), length(length), genre(genre), authorlastname(authorlastname) {} //FIXME change from last name to name
};

class LinkedList {
private:
	Node* head;
	Node* tail;

public:
	int size;
	LinkedList() : head(nullptr), tail(nullptr), size(0) {}
	~LinkedList();

	bool insert(string name, string author = "null", string genre = "null", int length = 0, int defaultFlag = 0);
	bool searchByStat(string stat, string value);
	bool remove(string name);
	void display();
	bool setStat(string name, string stat, string value);
	bool clear();
	Node* getHead();

};



