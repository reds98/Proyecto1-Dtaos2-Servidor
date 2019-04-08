#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"



class LinkedList
{
private:
    Node* first;
    int t;
public:
    /**
     * @brief Add añade un elemento al incio de la lista
     * @param data
     */
    void Add(void* data);
    /**
     * @brief Delete elimina el primer elemento de la lista
     * @return el nodo eliminado
     */
    void* Delete();
    /**
     * @brief Print imprime la lista
     */
    void Print();
    LinkedList();
    Node *getFirst() const;
    void setFirst(Node *value);
    int getT() const;
    void setT(int value);
};

#endif // LINKEDLIST_H
