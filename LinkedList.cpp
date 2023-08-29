#include "LinkedList.h"
#include <string>
#include <iostream>

LinkedList::~LinkedList() {
	Node* tmp = head;
	while (tmp != nullptr) {
		head = head->next;
		delete tmp;
		tmp = head;
	}
	tail = nullptr;
}

bool LinkedList::insert(string name, string author, string genre, int length, int defaultFlag) {
	Node* newNode;
    if (defaultFlag == 1) {
		newNode = new Node(name, length, genre, author);
	}
	else {
		newNode = new Node(name);
	}
	Node* tmp = head;
	if (tmp == nullptr) {
		head = newNode;
		newNode->next = nullptr;
        newNode->prev = nullptr;
        tail = newNode;
		return true;
	}
	Node* previ = nullptr;
	while (tmp != nullptr) {
		if (name < tmp->name) {
			newNode->next = tmp;
			head = newNode;
			return true;
		}
		else if (name == tmp->name) {
			return false;
		}
		else {
//			previ = previ->next;
//            if (tmp->prev != nullptr){
//                previ = tmp->prev;
//            }
			tmp = tmp->next;
		}
	}
	tail->next = newNode;
    newNode->prev = tail;
	tail = newNode;
	newNode->next = nullptr;
	return true;
}

bool LinkedList::searchByStat(string stat, string value) {
	Node* tmp = head;
	if (stat == "genre") {
        cout << "Search results:" << endl;
		while (tmp != nullptr) {
			if (tmp->genre == value) {
				cout << tmp->name << endl;
			}
			else {
				tmp = tmp->next;
			}
		}
	}
	else if (stat == "name") {
        cout << "Search results:" << endl;
		while (tmp != nullptr) {
			if (tmp->name == value) {
				cout << tmp->name << endl;
			}
			else {
				tmp = tmp->next;
			}
		}
	}
	else {
		return false;
	}
	return true;
}

bool LinkedList::remove(string name) {
	Node* tmp = head;
	while (tmp != nullptr) {
		if (tmp->name != name) { //gets temp to proper node
			tmp = tmp->next;
		}
		else if (tmp->name == name) {
			if (tmp->prev == nullptr) { // if PC is head
				if (tmp->next == nullptr) { // if PC is only one in list
					delete tmp;
					return true;
				}
				head = tmp->next;
				head->prev = nullptr;
				delete tmp;
				return true;
			}
			else if (tmp->next == nullptr) { // if PC is tail
				tmp->prev->next = nullptr;
				delete tmp;
				return true;
			}
			else { // if PC is in middle
				tmp->prev->next = tmp->next;
				tmp->next->prev = tmp->prev;
				delete tmp;
				return true;
			}
		}
	}
	return false;
}

void LinkedList::display() {
	Node* tmp = head;
	while (tmp != nullptr) {
		cout << "\"" << tmp->name << "\"\n";
		if (tmp->authorlastname != "null") {
			cout << "\tAuthor: " << tmp->authorlastname << endl;
		}
		if (tmp->genre != "null") {
			cout << "\tGenre: " << tmp->genre << endl;
		}
		if (tmp->length != 0) {
			cout << "\tLength: " << tmp->length << " pgs" << endl;
		}
		cout << endl;
		tmp = tmp->next;
	}
}

bool LinkedList::setStat(string name, string stat, string value) {
	Node* tmp = head;
	while (tmp != nullptr) {
		if (name == tmp->name) {
			if (stat == "length") {
				tmp->length = stoi(value);
				return true;
			}
			if (stat == "author") {
				tmp->authorlastname = value;
				return true;
			}
			if (stat == "genre") {
				tmp->genre = value;
				return true;
			}
		}
		tmp = tmp->next;
	}
	return false;
}

bool LinkedList::clear() {
	if (head == nullptr) {
		return true;
	}
	Node* tmp = head->next;
	if (head->next == nullptr) {
		delete tmp;
		head = nullptr;
		tail = nullptr;
		return true;
	}
	while (tmp != nullptr) {
		delete tmp->prev;
		if (tmp->next == nullptr) {
			delete tmp;
			break;
		}
		tmp = tmp->next;
	}
	head = nullptr;
	tail = nullptr;
	return true;
}


Node* LinkedList::getHead() {
	return head;
}
