#include <iostream>     // (1) brings in the standard input/output library so we can use cout
using namespace std;    // (2) lets us write cout instead of std::cout every time

// (3) A Node is one "link" in the linked list. Each node holds one character
//     and a pointer to the node underneath it in the stack.
class Node
{
public:
    char c;     // the value this node stores
    Node* next; // pointer to the next node below this one

    Node() { next = nullptr; c = ' '; }             // default constructor: empty node
    Node(char value) { c = value; next = nullptr; } // constructor that stores a value right away
};

// (4) The Stack is built out of Nodes. It only ever tracks ONE thing:
//     a pointer to the top node. Everything else is reached through next pointers.
class Stack
{
public:
    Node* topNode; // pointer to whichever node is currently on top

    Stack() { topNode = nullptr; } // (5) constructor: runs when the stack is created, starts it empty

    // (6) push = add to the top.
    void push(char value)
    {
        Node* newNode = new Node(value); // make a new node holding the value
        newNode->next = topNode;         // new node points down at the old top
        topNode = newNode;               // new node becomes the top
    }

    // (7) pop = remove the top and give its value back.
    char pop()
    {
        char value = topNode->c;  // save the top's value before deleting it
        Node* temp = topNode;     // remember the old top so we can delete it
        topNode = topNode->next;  // the node below becomes the new top
        delete temp;              // free the old top's memory
        return value;             // hand the value back to whoever called pop
    }

    // (8) isEmpty = true when topNode points at nothing (no nodes left).
    bool isEmpty()
    {
        return topNode == nullptr;
    }

    // (9) Prints the stack bottom-to-top using recursion (the function calls itself),
    //     then rebuilds the stack so it's unchanged when we're done.
    void printBackwards()
    {
        if (isEmpty())
        {
            return; // base case: no nodes left, stop recursing
        }

        char value = pop();     // step 1: take the top off and hold it
        printBackwards();       // step 2: repeat on everything below first
        cout << value << " ";   // step 3: print on the way back up (bottom prints first)
        push(value);            // step 4: put the value back so the stack is restored
    }
};

// (10) main is where the program starts running.
int main() {

    Stack myStack; // (11) create a Stack object — its constructor sets topNode to nullptr

    // (12) push A, then B on top of A, then C, then D. D ends up on top.
    myStack.push('A');
    myStack.push('B');
    myStack.push('C');
    myStack.push('D');

    // (13) backwards = bottom first, so this prints A B C D
    cout << "Printed backwards: ";
    myStack.printBackwards();
    cout << endl;

    // (14) pop everything top-down (D C B A) to prove printBackwards
    //      put the stack back exactly how it was
    cout << "Now popping normally to prove the stack is returned to the original state: ";
    while (!myStack.isEmpty())
    {
        cout << myStack.pop() << " ";
    }
    cout << endl;

    return 0;
}
