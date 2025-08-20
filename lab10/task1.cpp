#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
using namespace std;

// Node structure for Huffman Tree
struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char c, int f) : ch(c), freq(f), left(NULL), right(NULL) {}
};

// Custom compare for priority queue (min-heap)
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;
    }
};

// Function to generate Huffman Codes
void generateCodes(HuffmanNode* root, string code, unordered_map<char, string>& huffmanCode) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCode[root->ch] = code;
    }

    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

// Function to build Huffman Tree
void buildHuffmanTree(const string& text) {
    // Step 1: Count frequencies
    unordered_map<char, int> freq;
    for (char ch : text) {
        freq[ch]++;
    }

    // Step 2: Push all characters into priority queue
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

    for (auto pair : freq) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    // Step 3: Combine nodes
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();

        HuffmanNode* merged = new HuffmanNode('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;

        pq.push(merged);
    }

    // Step 4: Generate codes
    HuffmanNode* root = pq.top();
    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    // Step 5: Output table
    cout << "Character\tFrequency\tHuffman Code\n";
    cout << "---------------------------------------------\n";
    for (auto pair : freq) {
        cout << "'" << (pair.first == ' ' ? "space" : string(1, pair.first)) << "'\t\t"
             << pair.second << "\t\t" << huffmanCode[pair.first] << "\n";
    }
}

int main() {
    string text = "hello world";
    buildHuffmanTree(text);
    return 0;
}
