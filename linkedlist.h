#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"



class LinkedList
{
private:
    Node* first;
    int t;
public:
    void Add(void* data);
    void* Delete();
    void Print();
    LinkedList();
    Node *getFirst() const;
    void setFirst(Node *value);
    int getT() const;
    void setT(int value);
};

#endif // LINKEDLIST_H
