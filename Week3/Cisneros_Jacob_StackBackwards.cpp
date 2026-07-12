#include <iostream>     // (1) lets me use cout and cin for input/output
using namespace std;    // (2) lets us write code without having to repeat std:: everytime

// (3) A class is like making my own data type, like how int and double exist.
//     Node is one piece of the stack. It holds one letter and points to the piece under it.
class Node
{
public:
    char c;     // the letter this node is holding
    Node* next; // points to the node under this one

    Node() { next = nullptr; c = ' '; }             // makes an empty node
    Node(char value) { c = value; next = nullptr; } // makes a node with a letter already in it
};

// (4) The Stack class is my stack, built out of Nodes stacked on each other.
//     It only remembers one thing: which node is on top.
class Stack
{
public:
    Node* topNode; // pointer that keeps track of the top of the stack

    Stack() { topNode = nullptr; } // (5) runs automatically when I make a stack, starts it out empty

    // (6) push = put a new letter on top of the stack (like adding a plate to a pile)
    void push(char value)
    {
        Node* newNode = new Node(value); // make the new node with the letter in it
        newNode->next = topNode;         // the new node sits on top of the old top
        topNode = newNode;               // now the new node IS the top
    }

    // (7) pop = take the top letter off the stack and give it back to me
    char pop()
    {
        char value = topNode->c;  // grab the letter before we delete the node
        Node* temp = topNode;     // keep track of the old top so we can delete it
        topNode = topNode->next;  // the one under it becomes the new top
        delete temp;              // delete the old top so we don't waste memory
        return value;             // give the letter back
    }

    // (8) just checks if the stack has nothing in it (true or false)
    bool isEmpty()
    {
        return topNode == nullptr;
    }

    // (9) this prints the stack from the BOTTOM up, which you normally can't do
    //     since a stack only lets you touch the top. it works by calling itself
    //     over and over (recursion) and it puts everything back when its done
    void printBackwards()
    {
        if (isEmpty())
        {
            return; // stack is empty, stop calling ourselves (this ends the recursion)
        }

        char value = pop();     // step 1: take the top letter off and hold onto it
        printBackwards();       // step 2: do this same thing to the rest of the stack
        cout << value << " ";   // step 3: print AFTER coming back, so the bottom prints first
        push(value);            // step 4: put the letter back so the stack isn't ruined
    }
};

// (10) main is where the program actually starts running
int main() {

    Stack myStack; // (11) making my stack, it starts empty because of line 23

    // (12) putting A B C D on the stack one at a time, D ends up on top
    myStack.push('A');
    myStack.push('B');
    myStack.push('C');
    myStack.push('D');

    // (13) prints A B C D since backwards means bottom first
    cout << "Printed backwards: ";
    myStack.printBackwards();
    cout << endl;

    // (14) now I pop everything the normal way (top first) and it prints D C B A,
    //      which proves printBackwards put the stack back exactly how it was
    cout << "Now popping normally to prove the stack is returned to the original state: ";
    while (!myStack.isEmpty())
    {
        cout << myStack.pop() << " ";
    }
    cout << endl;

    return 0;
}
