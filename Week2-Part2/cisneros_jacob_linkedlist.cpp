#include <iostream>
using namespace std;

// Node class — blueprint for each element in the linked list
class Node
{
public:
    char c;
    Node* next;
    Node() { next = nullptr; c = ' '; }


};

// displayList function — traverses and prints the list graphically
void displayList(Node* start)
{
    cout << "List: ";
    while (start != nullptr)
    {
        cout << start->c << " -> ";
        start = start->next;
    }
    cout << "NULL" << endl;
}

int main() {

// Create nodes and assign values    
Node* ptrA = new Node();
ptrA->c = 'A';

Node* ptrB = new Node();
ptrB->c = 'B';

Node* ptrC = new Node();
ptrC->c = 'C';

Node* ptrD = new Node();
ptrD->c = 'D';

// Chain nodes together to form the linked list
ptrA->next = ptrB;
ptrB->next = ptrC;
ptrC->next = ptrD;

// Call displayList starting from the first node
displayList(ptrA);

return 0;

}