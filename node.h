#ifndef NODE_H
#define NODE_H


class Node
{
private:
    Node* next;
    void* data;
public:
    Node(void* data);
    Node *getNext() const;
    void setNext(Node *value);
    void *getData() const;
    void setData(void *value);
};

#endif // NODE_H
