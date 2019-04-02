#include "linkedlist.h"
#include <iostream>
using namespace std;

Node *LinkedList::getFirst() const
{
    return first;
}

void LinkedList::setFirst(Node *value)
{
    first = value;
}

int LinkedList::getT() const
{
    return t;
}

void LinkedList::setT(int value)
{
    t = value;
}

void LinkedList::Add(void *data)
{
    Node* tmp=new Node(data);
    tmp->setNext(this->first);
    this->first=tmp;
    this->t++;
}

void *LinkedList::Delete()
{
    if(t>0){
        Node* tmp=this->first;
        this->first=this->first->getNext();
        this->t--;
        return tmp;
    }
    return nullptr;
}

void LinkedList::Print()
{
    Node* tmp=this->first;
    while (tmp!=nullptr){
        cout<<tmp<<endl;
        tmp=tmp->getNext();
    }
}

LinkedList::LinkedList()
{
    this->t=0;
    this->first=0;
}
