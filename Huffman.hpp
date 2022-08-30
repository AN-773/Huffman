#include "Node.hpp"
#include <string>
#include <fstream>

#define CHARACTERS 256

using std::ifstream;
using std::string;

class Huffman {
    int minNodeIndex(Node **nodes) {
        int minFreq = INT32_MAX;
        int minIndex = -1;
        for (int i = 0; i < CHARACTERS; i++) {
            if (nodes[i] && nodes[i]->freq < minFreq) {
                minIndex = i;
                minFreq = nodes[i]->freq;
            }
        }
        return minIndex;
    }

    void getCodes(Node *n, string code, string *codes) {
        if (n == nullptr) {
            return;
        } else if (n->left || n->right) {
            getCodes(n->left, code + "0", codes);
            getCodes(n->right, code + "1", codes);
        } else {
            codes[n->c] = code;
        }
    }

public:
    string *encode(string path) {
        int freq[CHARACTERS];
        for (int i = 0; i < CHARACTERS; i++) {
            freq[i] = 0;
        }
        string line;
        ifstream f(path);
        while (getline(f, line)) {
            for (int i = 0; i < line.size(); i++) {
                freq[line[i]]++;
            }
            //This will ignore new line
        }

        Node *nodes[CHARACTERS];

        for (int i = 0; i < CHARACTERS; i++) {
            if (freq[i] > 0) {
                nodes[i] = new Node(i, freq[i], nullptr, nullptr);
            } else {
                nodes[i] = nullptr;
            }
        }
        Node *root;
        while (true) {
            int minIndex = minNodeIndex(nodes);
            Node *min1 = minIndex == -1 ? nullptr : nodes[minIndex];
            nodes[minIndex] = nullptr;
            minIndex = minNodeIndex(nodes);
            Node *min2 = minIndex == -1 ? nullptr : nodes[minIndex];
            nodes[minIndex] = nullptr;
            if (!min2) {
                root = min1;
                break;
            }
            nodes[minIndex] = new Node(0, min1->freq + min2->freq, min1, min2);
        }
        auto *codes = new string[CHARACTERS];
        string *out = new string(); // Why using a pointer because C++ when I use normal string it throws segmentation fault
        getCodes(root, "", codes);
        f.clear();
        f.seekg(0);
        int xi = 0;
        while (getline(f, line)) {
            for (int i = 0; i < line.size(); i++) {
                *out += codes[line[i]];
            }
        }
        //Not cleaning the mem yet
        return out;
    }

    void decode(string in_path, string out_path) {
        //Not implemented yet
    }
};