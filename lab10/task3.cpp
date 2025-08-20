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

// Encode string
string encodeString(const string& text, unordered_map<char, string>& huffmanCode) {
    string encoded = "";
    for (char ch : text)
        encoded += huffmanCode[ch];
    return encoded;
}

// Decode string
string decodeString(const string& encoded, HuffmanNode* root) {
    string decoded = "";
    HuffmanNode* current = root;
    for (char bit : encoded) {
        current = (bit == '0') ? current->left : current->right;

        if (!current->left && !current->right) {
            decoded += current->ch;
            current = root;
        }
    }
    return decoded;
}

// Main compressor
void huffmanCompression(const string& text) {
    cout << "Input: \"" << text << "\"\n";

    if (text.empty()) {
        cout << "Empty input. Skipping.\n\n";
        return;
    }

    unordered_map<char, int> freq;
    for (char ch : text)
        freq[ch]++;

    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
    for (auto pair : freq)
        pq.push(new HuffmanNode(pair.first, pair.second));

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        HuffmanNode* merged = new HuffmanNode('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }

    HuffmanNode* root = pq.top();

    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    string encoded = encodeString(text, huffmanCode);
    string decoded = decodeString(encoded, root);

    int originalBits = text.length() * 8;
    int encodedBits = encoded.length();

    double compressionRatio = (double)encodedBits / originalBits;

    cout << "\nOriginal size: " << originalBits << " bits";
    cout << "\nEncoded size:  " << encodedBits << " bits";
    cout << "\nCompression Ratio: " << compressionRatio << "\n";

    cout << "\nCharacter\tFrequency\tHuffman Code\n";
    cout << "---------------------------------------------\n";
    for (auto pair : freq) {
        cout << "'" << (pair.first == ' ' ? "space" : string(1, pair.first)) << "'\t\t"
             << pair.second << "\t\t" << huffmanCode[pair.first] << "\n";
    }

    cout << "\nEncoded String:   " << encoded;
    cout << "\nDecoded String:   " << decoded;
    cout << "\n✅ Match: " << (decoded == text ? "Yes" : "No") << "\n\n";
}
int main() {
    huffmanCompression("hello world");
    huffmanCompression("aaaaaaaaaaaaaa");
    huffmanCompression("the quick brown fox jumps over the lazy dog");
    huffmanCompression("Haadhee is learning Huffman encoding today.");
    return 0;
}
