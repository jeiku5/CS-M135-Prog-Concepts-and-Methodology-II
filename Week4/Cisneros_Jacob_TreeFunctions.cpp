// Student Name: Jacob Cisneros
// Student ID: 900863638
// Date: Jul 17, 2026
// Assignment: Week 4 | Tree Functions Project | Traverse Tree: LNR

#include <iostream>
using namespace std;

class Node{
    public:
    int value;
    Node* left;
    Node* right;
    Node() { left = nullptr; right = nullptr; value = 0; }
};

// Function Left-Node-Right | Handle left side, print, then handle right side
void LNR(Node* current){
    // L
    if (current->left != nullptr){
        LNR(current->left);
    }
    
    // N
    cout << current->value << " ";

    // R
    if (current->right != nullptr){
        LNR(current->right);
    }


}

int main(){

    Node* root = new Node();

    Node* node30 = new Node();
    Node* node20 = new Node();
    Node* node40 = new Node();

    Node* node70 = new Node();
    Node* node60 = new Node();
    Node* node80 = new Node();

    root->value = 50;

    node30->value = 30;
    node20->value = 20;
    node40->value = 40;

    node70->value = 70;
    node60->value = 60;
    node80->value = 80;

    root->left = node30;
    node30->left = node20;
    node30->right = node40;

    root->right = node70;
    node70->left = node60;
    node70->right = node80;

    LNR(root);
    cout << endl;

    return 0;
}