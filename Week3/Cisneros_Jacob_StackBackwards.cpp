#include <iostream>
using namespace std;

class Node
{
public:
    char c;  // value stored in node
    Node* next; // pointer to the node below

    Node() { next = nullptr; c = ' '; } // default constructor
    Node(char value) {c = value; next = nullptr; } // value on constructor

};

class Stack
{
    public:
    Node* topNode;

    Stack() { topNode = nullptr; } // starting empty

    void push(char value)
    {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
    }

    char pop()
    {
        char value = topNode->c;
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
        return value;
    }

    bool isEmpty()
    {
        return topNode == nullptr;

    }

    void printBackwards()
    {
        if (isEmpty())
        {
            return; // base case
        }

        char value = pop();     // step 1: hold this temporarily
        printBackwards();       // step 2: handle everything below first
        cout << value << " ";   // step 3: now prints it, on the way back up
        push(value);            // step 4: put it back where it belongs


    }

};

int main() {

    Stack myStack;

    myStack.push('A');
    myStack.push('B');
    myStack.push('C');
    myStack.push('D');

    cout << "Printed backwards: ";
    myStack.printBackwards();
    cout << endl;

    cout << "Now popping normally to prove the stack is returned to the original state: ";
    while (!myStack.isEmpty())
    {
        cout << myStack.pop() << " ";

    }
    cout << endl;

return 0;

}