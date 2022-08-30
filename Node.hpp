#include <iostream>

using std::cout;
using std::endl;

class Node{
public:
    char c = '\0';
    int freq = 0;
    Node * left;
    Node * right;
    Node(int chr, int f, Node* l, Node* r): c(chr), freq(f), left(l), right(r){
    }
};