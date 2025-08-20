#include <iostream>
using namespace std;

class DoubleHashing {
private:
    int* table;
    int size;
    int prime; // for second hash function

    // First hash function
    int hash1(int key) {
        return key % size;
    }

    // Second hash function
    int hash2(int key) {
        return prime - (key % prime);
    }

public:
    DoubleHashing(int tableSize, int primeNum) {
        size = tableSize;
        prime = primeNum;
        table = new int[size];
        for (int i = 0; i < size; i++) {
            table[i] = -1; // -1 means empty
        }
    }

    void insert(int key) {
        int index = hash1(key);

        // If no collision
        if (table[index] == -1) {
            table[index] = key;
            return;
        }

        // Collision → apply double hashing
        int stepSize = hash2(key);
        int i = 1;

        while (i < size) {
            int newIndex = (index + i * stepSize) % size;
            if (table[newIndex] == -1) {
                table[newIndex] = key;
                return;
            }
            i++;
        }

        cout << "Hash table is full, cannot insert " << key << endl;
    }

    void search(int key) {
        int index = hash1(key);
        int stepSize = hash2(key);
        int i = 0;

        while (table[(index + i * stepSize) % size] != -1 && i < size) {
            if (table[(index + i * stepSize) % size] == key) {
                cout << "Found " << key << " at index " << (index + i * stepSize) % size << endl;
                return;
            }
            i++;
        }

        cout << key << " not found in hash table." << endl;
    }

    void display() {
        for (int i = 0; i < size; i++) {
            cout << i << " : " << table[i] << endl;
        }
    }
};

int main() {
    int tableSize = 7; // Table size
    int primeNum = 5;  // Prime number less than tableSize
    DoubleHashing dh(tableSize, primeNum);

    dh.insert(7);
    dh.insert(12);
    dh.insert(17);
    dh.insert(19);
    dh.insert(26);
    dh.insert(31);
    dh.insert(38); // should show full if table is filled

    cout << "\nHash Table:\n";
    dh.display();

    cout << "\nSearch tests:\n";
    dh.search(19);
    dh.search(100);

    return 0;
}
