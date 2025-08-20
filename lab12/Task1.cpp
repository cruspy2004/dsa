#include <iostream>
using namespace std;

const int TABLE_SIZE = 7;
int hashTable[TABLE_SIZE];

// hash function
int hashFunc(int key) {
    return key % TABLE_SIZE;
}

void initTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = -1;
    }
}


void insert(int key) {
    int index = hashFunc(key);
    int startIndex = index;

    while (hashTable[index] != -1 && hashTable[index] != -2) {
        index = (index + 1) % TABLE_SIZE;
        if (index == startIndex) {
            cout << "Hash table is full!\n";
            return;
        }
    }
    hashTable[index] = key;
}



int search(int key) {
    int index = hashFunc(key);
    int startIndex = index;

    while (hashTable[index] != -1) {
        if (hashTable[index] == key) {
            return index;
        }
        index = (index + 1) % TABLE_SIZE;
        if (index == startIndex) {
            break;
        }
    }
    return -1; // not found
}



void removeKey(int key) {
    int pos = search(key);
    if (pos == -1) {
        cout << "Key not found\n";
    } else {
        hashTable[pos] = -2; // mark as deleted
    }
}

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
    insert(15); // collision example
    display();

    cout << "Searching 15 → index " << search(15) << endl;

    removeKey(20);
    display();

    insert(27); // should reuse deleted slot
    display();

    return 0;
}
