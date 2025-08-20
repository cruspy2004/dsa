#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
using namespace std;

// Node for Huffman Tree
struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char c, int f) : ch(c), freq(f), left(NULL), right(NULL) {}
};

// Comparator for min-heap
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;
    }
};

// Generate Huffman Codes
void generateCodes(HuffmanNode* root, string code, unordered_map<char, string>& huffmanCode) {
    if (!root) return;

    if (!root->left && !root->right)
        huffmanCode[root->ch] = code;

    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

// Encode input string
string encodeString(const string& text, unordered_map<char, string>& huffmanCode) {
    string encoded = "";
    for (char ch : text) {
        encoded += huffmanCode[ch];
    }
    return encoded;
}

// Decode encoded string
string decodeString(const string& encoded, HuffmanNode* root) {
    string decoded = "";
    HuffmanNode* current = root;

    for (char bit : encoded) {
        if (bit == '0')
            current = current->left;
        else
            current = current->right;

        // Leaf node reached
        if (!current->left && !current->right) {
            decoded += current->ch;
            current = root;
        }
    }

    return decoded;
}

// Main function to build the Huffman Tree and handle encode/decode
void huffmanCompression(const string& text) {
    // Frequency table
    unordered_map<char, int> freq;
    for (char ch : text)
        freq[ch]++;

    // Min-heap for tree building
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
    for (auto pair : freq)
        pq.push(new HuffmanNode(pair.first, pair.second));

    // Build tree
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();

        HuffmanNode* merged = new HuffmanNode('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;

        pq.push(merged);
    }

    // Final root of the tree
    HuffmanNode* root = pq.top();

    // Generate codes
    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    // Encode the input string
    string encoded = encodeString(text, huffmanCode);

    // Decode the encoded string
    string decoded = decodeString(encoded, root);

    // Output
    cout << "Original String:  " << text << endl;
    cout << "Encoded String:   " << encoded << endl;
    cout << "Decoded String:   " << decoded << endl;

    cout << "\nCharacter\tFrequency\tHuffman Code\n";
    cout << "---------------------------------------------\n";
    for (auto pair : freq) {
        cout << "'" << (pair.first == ' ' ? "space" : string(1, pair.first)) << "'\t\t"
             << pair.second << "\t\t" << huffmanCode[pair.first] << "\n";
    }
}

int main() {
    string text = "hello world";
    huffmanCompression(text);
    return 0;
}
