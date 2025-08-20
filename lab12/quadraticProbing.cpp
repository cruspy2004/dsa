#include <iostream>
using namespace std;

const int TABLE_SIZE = 7;
int hashTable[TABLE_SIZE];

// Hash function
int hashFunc(int key) {
    return key % TABLE_SIZE;
}

// Initialize hash table
void initTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = -1; // empty
    }
}

// Insert using Quadratic Probing
void insert(int key) {
    int index = hashFunc(key);

    if (hashTable[index] == -1 || hashTable[index] == -2) {
        hashTable[index] = key;
        return;
    }

    // Collision -> quadratic probing
    for (int i = 1; i < TABLE_SIZE; i++) {
        int newIndex = (index + i * i) % TABLE_SIZE;
        if (hashTable[newIndex] == -1 || hashTable[newIndex] == -2) {
            hashTable[newIndex] = key;
            return;
        }
    }
    cout << "Hash table is full! Cannot insert " << key << endl;
}

// Search using Quadratic Probing
int search(int key) {
    int index = hashFunc(key);

    if (hashTable[index] == key) return index;

    for (int i = 1; i < TABLE_SIZE; i++) {
        int newIndex = (index + i * i) % TABLE_SIZE;
        if (hashTable[newIndex] == key) return newIndex;
        if (hashTable[newIndex] == -1) return -1; // empty slot means not found
    }
    return -1;
}

// Delete key
void removeKey(int key) {
    int pos = search(key);
    if (pos == -1) {
        cout << "Key not found\n";
    } else {
        hashTable[pos] = -2; // mark as deleted
    }
}

// Display hash table
void display() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << i << ": " << hashTable[i] << endl;
    }
}

int main() {
    initTable();

    insert(10);
    insert(20);
    insert(5);
    insert(15);
    insert(7);
    insert(17); // will use quadratic probing

    cout << "Hash Table after insertions:\n";
    display();

    cout << "\nSearching 15 → index " << search(15) << endl;
    cout << "Searching 99 → index " << search(99) << endl;

    cout << "\nDeleting 20...\n";
    removeKey(20);
    display();

    cout << "\nInserting 27 (should reuse deleted slot):\n";
    insert(27);
    display();

    return 0;
}
