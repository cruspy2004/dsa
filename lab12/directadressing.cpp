#include <iostream>
using namespace std; 
#define maxSize 1000
int map[maxSize];

void initializeMap() {
	for (int i = 0; i < maxSize; i++) {
		map[i] = -1;
	}
}

void insert (int key, int value){
	if (key < 0 || key >= maxSize) {
		cerr << "Invalid key. Key must be between 0 and " << maxSize - 1 << "." << endl;
		return;
	}
	map[key] = value;
	cout << "Inserted key-value pair (" << key << ", " << value << ") into the map." << endl;
}

void search (int key) {
	if (key < 0 || key >= maxSize) {
		cerr << "Invalid key. Key must be between 0 and " << maxSize - 1 << "." << endl;
		return;
	}
	if (map[key] != -1) {
		cout << "Value for key " << key << " is: " << map[key] << endl;
	} else {
		cout << "Key " << key << " not found in the map, with value: " << map[key] << endl;
	}
}

void remove(int key, int value){
	if (key < 0 || key >= maxSize) {
		cerr << "Invalid key. Key must be between 0 and " << maxSize - 1 << "." << endl;
		return;
	}
	if (map[key] == value) {
		map[key] = -1; // Remove the key-value pair
		cout << "Removed key-value pair (" << key << ", " << value << ") from the map." << endl;
	} else {
		cout << "Key " << key << " not found with value: " << value << endl;
	}
}

int main() {
	initializeMap();

	// Test insert
	insert(42, 99);
	insert(5, 123);

	// Test search
	search(42);
	search(10); // should return -1
	// Test delete
	remove(42, 99);
	search(42); // should return -1

	return 0;
}
