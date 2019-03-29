//
// Created by Olcay Taner Yıldız on 29.10.2018.
//

#ifndef DATASTRUCTURE_CACHENODE_H
#define DATASTRUCTURE_CACHENODE_H

template<class K, class T> class CacheNode {
private:
    T data;
    K key;
    CacheNode<K, T>* previous = nullptr;
    CacheNode<K, T>* next = nullptr;
public:
    CacheNode(K key, T data);
    T getData();
    K getKey();
    CacheNode<K, T>* getPrevious();
    CacheNode<K, T>* getNext();
    void setPrevious(CacheNode<K, T>* previous);
    void setNext(CacheNode<K, T>* next);
};

/**
 * A constructor of {@link CacheNode} class which takes a key and a data as inputs and initializes private fields with these inputs.
 *
 * @param key  K type input for representing keys.
 * @param data T type input values represented by keys.
 */
template<class K, class T>
CacheNode<K, T>::CacheNode(K key, T data) {
    this->key = key;
    this->data = data;
}

/**
 * Getter for data value.
 *
 * @return data value.
 */
template<class K, class T> T CacheNode<K, T>::getData() {
    return data;
}

/**
 * Getter for key value.
 *
 * @return key value.
 */
template<class K, class T> K CacheNode<K, T>::getKey() {
    return key;
}

/**
 * Getter for the previous CacheNode.
 *
 * @return previous CacheNode.
 */
template<class K, class T> CacheNode<K, T> *CacheNode<K, T>::getPrevious() {
    return previous;
}

/**
 * Getter for the next CacheNode.
 *
 * @return next CacheNode.
 */
template<class K, class T> CacheNode<K, T> *CacheNode<K, T>::getNext() {
    return next;
}

/**
 * Setter for the previous CacheNode.
 *
 * @param previous CacheNode.
 */
template<class K, class T> void CacheNode<K, T>::setPrevious(CacheNode<K, T> *previous) {
    this->previous = previous;
}

/**
 * Setter for the next CacheNode.
 *
 * @param next CacheNode.
 */
template<class K, class T> void CacheNode<K, T>::setNext(CacheNode<K, T> *next) {
    this->next = next;
}

#endif //DATASTRUCTURE_CACHENODE_H
