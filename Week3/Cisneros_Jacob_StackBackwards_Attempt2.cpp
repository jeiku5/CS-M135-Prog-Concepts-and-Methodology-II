#include <iostream> // this tells my code that I am using iostream which allows cin and cout, etc.
using namespace std; // namespace std tells my code that I don't have to repeat std:: before everything like std::cin or std::cout

class Node // this is a custom class named Node that I am creating which are custom data types such as int, double, etc.
{
    public:  // Setting my members to public so other classes can touch next
    Node* next; // next stores the address of the node below this one / the previous thing pushed
    char c;
    Node() { next = nullptr; c = ' '; }// Constructor here, runs automatically when a node is created, started empty.
};

class Stack{ // class stack to keep track whats currently on top of the stack, the info needs to live outside the node since pop deletes nodes.
    public:
    Node* topNode;
    Stack() {topNode = nullptr;}


void push(char value)
{
    Node* n = new Node();
    n->c = value;
    n->next = topNode;
    topNode = n;
}

bool isEmpty()
{
    return topNode == nullptr;

}

char pop()
{
    char letter = topNode->c;
    Node* temp = topNode;
    topNode = topNode->next;
    delete temp;
    return letter;

}

void printBackwards()
{
    if (isEmpty())
    {
        return;
    }
    char held = pop();
    printBackwards();
    cout << held << " ";
    push(held);
}
};



int main() // This is my main function
{
    Stack myStack;
    myStack.push('A');
    myStack.push('B');
    myStack.push('C');
    myStack.push('D');

    cout << "Backwards: ";
    myStack.printBackwards();
    cout << endl;

    cout << "Popping to prove it survived: ";
    while (!myStack.isEmpty())
    {
        cout << myStack.pop() << " ";

    }
    cout << endl;



    return 0;
}