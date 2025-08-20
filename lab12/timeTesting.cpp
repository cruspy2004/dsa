#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace std::chrono;

// ======================= Direct Addressing =======================
class DirectAddressing {
private:
    vector<int> table;
public:
    DirectAddressing(int maxKey) {
        table.assign(maxKey + 1, -1);
    }
    void insert(int key) {
        table[key] = key;
    }
    bool search(int key) {
        return table[key] != -1;
    }
};

// ======================= Linear Probing =======================
class LinearProbing {
private:
    vector<int> table;
    int size;
public:
    LinearProbing(int s) {
        size = s;
        table.assign(size, -1);
    }
    int hash(int key) {
        return key % size;
    }
    void insert(int key) {
        int index = hash(key);
        int i = 0;
        while (table[(index + i) % size] != -1) {
            i++;
        }
        table[(index + i) % size] = key;
    }
    bool search(int key) {
        int index = hash(key);
        int i = 0;
        while (table[(index + i) % size] != -1 && i < size) {
            if (table[(index + i) % size] == key) return true;
            i++;
        }
        return false;
    }
};

// ======================= Quadratic Probing =======================
class QuadraticProbing {
private:
    vector<int> table;
    int size;
public:
    QuadraticProbing(int s) {
        size = s;
        table.assign(size, -1);
    }
    int hash(int key) {
        return key % size;
    }
    void insert(int key) {
        int index = hash(key);
        int i = 0;
        while (table[(index + i*i) % size] != -1 && i < size) {
            i++;
        }
        table[(index + i*i) % size] = key;
    }
    bool search(int key) {
        int index = hash(key);
        int i = 0;
        while (table[(index + i*i) % size] != -1 && i < size) {
            if (table[(index + i*i) % size] == key) return true;
            i++;
        }
        return false;
    }
};

// ======================= Double Hashing =======================
class DoubleHashing {
private:
    vector<int> table;
    int size;
    int prime;
public:
    DoubleHashing(int s, int p) {
        size = s;
        prime = p;
        table.assign(size, -1);
    }
    int hash1(int key) {
        return key % size;
    }
    int hash2(int key) {
        return prime - (key % prime);
    }
    void insert(int key) {
        int index = hash1(key);
        if (table[index] == -1) {
            table[index] = key;
            return;
        }
        int step = hash2(key);
        int i = 1;
        while (i < size) {
            int newIndex = (index + i * step) % size;
            if (table[newIndex] == -1) {
                table[newIndex] = key;
                return;
            }
            i++;
        }
    }
    bool search(int key) {
        int index = hash1(key);
        int step = hash2(key);
        int i = 0;
        while (table[(index + i * step) % size] != -1 && i < size) {
            if (table[(index + i * step) % size] == key) return true;
            i++;
        }
        return false;
    }
};

// ======================= Main Program =======================
int main() {
    srand(time(0));

    int numKeys = 1000;
    int tableSize = 2003; // prime number for better distribution
    int maxKeyValue = 10000;

    // Generate random keys
    vector<int> keys(numKeys);
    for (int i = 0; i < numKeys; i++) {
        keys[i] = rand() % maxKeyValue;
    }

    // Initialize all hash tables
    DirectAddressing da(maxKeyValue);
    LinearProbing lp(tableSize);
    QuadraticProbing qp(tableSize);
    DoubleHashing dh(tableSize, 1999); // prime < tableSize

    // Insert into all tables
    for (int key : keys) {
        da.insert(key);
        lp.insert(key);
        qp.insert(key);
        dh.insert(key);
    }

    // Measure lookup times
    auto measureTime = [&](auto& tableObj) {
        auto start = high_resolution_clock::now();
        for (int key : keys) {
            tableObj.search(key);
        }
        auto end = high_resolution_clock::now();
        return duration_cast<nanoseconds>(end - start).count();
    };

    long long timeDA = measureTime(da);
    long long timeLP = measureTime(lp);
    long long timeQP = measureTime(qp);
    long long timeDH = measureTime(dh);

    // Print results
    cout << "Lookup Time (nanoseconds):\n";
    cout << "Direct Addressing : " << timeDA << "\n";
    cout << "Linear Probing    : " << timeLP << "\n";
    cout << "Quadratic Probing : " << timeQP << "\n";
    cout << "Double Hashing    : " << timeDH << "\n";

    return 0;
}
