#include <iostream>
#include "RBT.h"

using namespace std;


int main() {
	RBTree <string, float> bst;
	bst.insert("January", 327.2);
	bst.insert("February", 368.2);
	bst.insert("March", 197.6);
	bst.insert("Apil", 178.4);
	bst.insert("May", 100.0);
	bst.insert("June", 69.9);
	bst.insert("July", 32.3);
	bst.insert("August", 37.3);
	bst.insert("September", 19.0);
	bst.insert("October", 37.0);
	bst.insert("November", 73.2);
	bst.insert("December", 110.9);
	bst.insert("Annual", 1551.0);
	bst.insert("One more month", 3478.3);
	cout << "The list of keys:" << endl;
	bst.get_keys();
	cout << "The list of values:" << endl;
	bst.get_values();
	cout << "Now let's remove key One more month" << endl;
	bst.remove("One more month");
	bst.Print();
	cout << "Let's look for key HelloWorld" << endl;
	bst.find("HelloWorld");
	cout << "Now let's clear the map and print it" << endl;
	bst.clear();
	bst.Print(); 

	return 0;
}