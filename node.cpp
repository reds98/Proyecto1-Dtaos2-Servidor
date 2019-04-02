#include "node.h"

Node *Node::getNext() const
{
    return next;
}

void Node::setNext(Node *value)
{
    next = value;
}

void *Node::getData() const
{
    return data;
}

void Node::setData(void *value)
{
    data = value;
}

Node::Node(void* data)
{
    this->data=data;
    this->next=nullptr;
}
