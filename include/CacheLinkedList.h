//
// Created by Olcay Taner Yıldız on 29.10.2018.
//

#ifndef DATASTRUCTURE_CACHELINKEDLIST_H
#define DATASTRUCTURE_CACHELINKEDLIST_H


#include "CacheNode.h"

template<class K, class T> class CacheLinkedList {
private:
    CacheNode<K, T>* head = nullptr;
    CacheNode<K, T>* tail = nullptr;
public:
    virtual ~CacheLinkedList();
    void remove(CacheNode<K, T>* cacheNode);
    void add(CacheNode<K, T>* cacheNode);
    CacheNode<K, T>* remove();
};

/**
 * The remove method takes a CacheNode type input cacheNode. If cacheNode has a previous node, then assigns cacheNode's
 * next node as previous node's next node. If cacheNode has not got a previous node, then assigns its next node as head node.
 * Moreover, if cacheNode has a next node, then assigns cacheNode's previous node as next node's previous node; if not
 * assigns tail node's previous node as tail. By doing so it removes the cacheNode from doubly {@link LinkedList}.
 *
 * @param cacheNode {@link CacheNode} type input to remove.
 */
template<class K, class T> void CacheLinkedList<K, T>::remove(CacheNode<K, T> *cacheNode) {
    CacheNode<K, T>* previous = cacheNode->getPrevious();
    CacheNode<K, T>* next = cacheNode->getNext();
    if (previous != nullptr) {
        previous->setNext(next);
    } else {
        head = head->getNext();
    }
    if (next != nullptr) {
        next->setPrevious(previous);
    } else {
        tail = tail->getPrevious();
    }
}

/**
 * The add method adds given {@link CacheNode} type input cacheNode to the beginning of the doubly {@link LinkedList}.
 * First it sets cacheNode's previous node as null and cacheNode's next node as head node. If head node is not null then it assigns
 * cacheNode's previous node as head node and if tail is null then it assigns cacheNode as tail.
 *
 * @param cacheNode {@link CacheNode} type input to add to the doubly {@link LinkedList}.
 */
template<class K, class T> void CacheLinkedList<K, T>::add(CacheNode<K, T> *cacheNode) {
    cacheNode->setPrevious(nullptr);
    cacheNode->setNext(head);
    if (head != nullptr) {
        head->setPrevious(cacheNode);
    }
    head = cacheNode;
    if (tail == nullptr) {
        tail = cacheNode;
    }
}

/**
 * The remove method removes the last element of the doubly {@link LinkedList}. It assigns the previous node of
 * current tail as new tail. If the current tail is null then it assigns head to null.
 *
 * @return {@link CacheNode} type output tail which is removd from doubly {@link LinkedList}.
 */
template<class K, class T> CacheNode<K, T> *CacheLinkedList<K, T>::remove() {
    CacheNode<K, T>* removed = tail;
    tail = tail->getPrevious();
    if (tail == nullptr) {
        head = nullptr;
    }
    return removed;
}

template<class K, class T> CacheLinkedList<K, T>::~CacheLinkedList() {
    while (head != nullptr){
        CacheNode<K, T>* removed = head;
        head = head->getNext();
        delete removed;
    }
}

#endif //DATASTRUCTURE_CACHELINKEDLIST_H
