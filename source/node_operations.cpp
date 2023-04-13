//------------------------------------------------------------------------------
// node_operations.cpp
//
// Demos deletion and insertion of linked list nodes.
//------------------------------------------------------------------------------
#include <iostream>
using std::cin;
using std::cout;

//------------------------------------------------------------------------------
// constants
//------------------------------------------------------------------------------
constexpr char CRLF = '\n';

//------------------------------------------------------------------------------
// Node : linked list item
//------------------------------------------------------------------------------
class Node {
public:
    char  data;
    Node* pNext;

    Node(char _data) : data(_data), pNext(nullptr) { }
};

//------------------------------------------------------------------------------
// local function prototypes
//------------------------------------------------------------------------------
void insertNode(Node*& pHead, char newData, char beforeData);
void deleteNode(Node*& pHead, char deleteData);
void displayNodes(Node* pHead);
void deleteListNodes(Node*& pHead);

//------------------------------------------------------------------------------
// entry point 
//------------------------------------------------------------------------------
int main() {

    // track the list head so we don't lose our list 
    Node* pHead = nullptr;

    // add some nodes to the list in alphabetical order

    // parameter order: pointer to list head, new data, data to insert before
    insertNode(pHead, 'C', 'x');
    insertNode(pHead, 'a', 'C');
    insertNode(pHead, 'n', 'a');
    insertNode(pHead, 'd', 'a');
    insertNode(pHead, 'L', 'n');
    insertNode(pHead, 'i', 'n');

    // display the list
    displayNodes(pHead);

    // delete the last Node (tail)
    deleteNode(pHead, 'C');
    displayNodes(pHead);

    // delete the head Node
    deleteNode(pHead, 'L');
    displayNodes(pHead);

    // delete a Node that's between two others
    deleteNode(pHead, 'n');
    displayNodes(pHead);

    // free all memory we allocated with new
    deleteListNodes(pHead);

    // pause until user types a key
    cin.get();

    return 0;
}

//------------------------------------------------------------------------------
// - creates a Node and insert it before the Node with passed data value
// - if the list is empty, adds the new Node as the list head
// - if the passed data value is not found, adds the new Node at list end
// - returns the new list head pointer in reference parameter pHead
//------------------------------------------------------------------------------
void insertNode(Node*& pHead, char newData, char beforeData) {

    // create the new node
    Node* pNewNode = new Node(newData);

    // check for empty list
    if (pHead == nullptr) {
        pHead = pNewNode;
        return;
    }

    // if we get here, the list has Nodes so find the insertion point

    // we need to track our current position in the list
    Node* pCurrent = pHead;
    // we also need to track which Node is just before the current one
    Node* pPrevious = nullptr;

    // always check for pointer to zero before following the link
    while (pCurrent != nullptr && pCurrent->data != beforeData) {
        pPrevious = pCurrent;
        pCurrent = pCurrent->pNext;
    }

    // if we went past the last Node, make the new Node the new list end
    if (pCurrent == nullptr) {
        pPrevious->pNext = pNewNode;
        return;
    }

    // if we get here, pCurrent points to the Node with passed data value

    // if the new Node will be the new list head, update the pHead pointer
    if (pCurrent == pHead) {
        pNewNode->pNext = pHead;
        pHead = pNewNode;
        return;
    }

    // otherwise, pPrevious points to the Node we'll add the new Node after

    // replace the previous Node's pointer to pCurrent
    // with the pointer to the new Node
    pPrevious->pNext = pNewNode;

    // link the new Node to the rest of the list, which starts with pCurrent
    pNewNode->pNext = pCurrent;
}

//------------------------------------------------------------------------------
// - deletes the Node with data that matches passed value
// - if head Node was deleted, update reference parameter pHead
//------------------------------------------------------------------------------
void deleteNode(Node*& pHead, char deleteData) {

    // we need to track our current position in the list
    Node* pCurrent = pHead;
    // we also need to track which Node is just before the current one
    Node* pPrevious = nullptr;

    while (pCurrent != nullptr && pCurrent->data != deleteData) {
        pPrevious = pCurrent;
        pCurrent = pCurrent->pNext;
    }

    // if we went past the list end, the data was not found
    if (pCurrent == nullptr) {
        return;
    }

    // if we get here, our data is in the pCurrent Node
    // so we'll delete the current Node from the list

    // if we're deleting the head Node, 
    // the next Node after the old head becomes the new list head
    if (pCurrent == pHead) {
        pHead = pHead->pNext;
    }

    // if there's otherwise, link the previous Node to the one after the current one
    else {
        pPrevious->pNext = pCurrent->pNext;
    }

    // free the current Node's memory
    delete pCurrent;
}


//------------------------------------------------------------------------------
// display each node data in the list that begins with the item at pHead
//------------------------------------------------------------------------------
void displayNodes(Node* pHead) {

    Node* p = pHead;
    while (p != nullptr) {
        cout << p->data;
        p = p->pNext;
    }
    cout << "\n\n";
}

//------------------------------------------------------------------------------
// - frees all Node memory in the list with head at pHead
// - sets pHead to nullptr
//------------------------------------------------------------------------------
void deleteListNodes(Node*& pHead) {
    while (pHead != nullptr) {
        Node* p = pHead->pNext;
        delete pHead;
        pHead = p;
    }
}
