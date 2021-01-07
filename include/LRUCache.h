//
// Created by Olcay Taner Yıldız on 29.10.2018.
//

#ifndef DATASTRUCTURE_LRUCACHE_H
#define DATASTRUCTURE_LRUCACHE_H
#include <map>
#include "CacheNode.h"
#include "CacheLinkedList.h"
using namespace std;

template<class K, class T> class LRUCache {
private:
    int cacheSize = 10000;
    map<K, CacheNode<K, T>*> _map;
    CacheLinkedList<K, T> cache;
public:
    explicit LRUCache(int cacheSize);
    LRUCache() = default;
    bool contains(K key);
    T get(K key);
    int getCacheSize();
    void add(K key, T data);
};

/**
 * A constructor of {@link LRUCache} class which takes cacheSize as input. It creates new
 * {@link CacheLinkedList} and {@link map}.
 *
 * @param cacheSize Integer input defining cache size.
 */
template<class K, class T> LRUCache<K, T>::LRUCache(int cacheSize) {
    this->cacheSize = cacheSize;
}

/**
 * The contains method takes a K type input key and returns true if the {@link map} has the given key,
 * false otherwise.
 *
 * @param key K type input key.
 * @return true if the {@link map} has the given key, false otherwise.
 */
template<class K, class T> bool LRUCache<K, T>::contains(K key) {
    return _map.find(key) != _map.end();
}

/**
 * The get method takes K type input key and returns the least recently used value. First it checks
 * whether the {@link map} has the given key, if so it gets the corresponding cacheNode. It removes
 * that cacheNode from {@link LinkedList} and adds it again to the beginning of the list since it is
 * more likely to be used again. At the end, returns the data value of that cacheNode.
 *
 * @param key K type input key.
 * @return data value if the {@link map} has the given key, nullptr otherwise.
 */
template<class K, class T> T LRUCache<K, T>::get(K key) {
    if (_map.find(key) != _map.end()) {
        CacheNode<K, T>* cacheNode = _map.find(key)->second;
        cache.remove(cacheNode);
        cache.add(cacheNode);
        return cacheNode->getData();
    }
}

/**
 * The add method take a key and a data as inputs. First it checks the size of the {@link map}, if it is
 * full (i.e equal to the given cacheSize) then it removes the last cacheNode in the @link LinkedList}. If
 * it has space for new entries, it creates new cacheNode with given inputs and adds this cacheNode to the
 * {@link LinkedList} and also puts it to the {@link map}.
 *
 * @param key  K type input.
 * @param data T type input.
 */
template<class K, class T> void LRUCache<K, T>::add(K key, T data) {
    if (_map.size() == cacheSize) {
        CacheNode<K, T>* removed = cache.remove();
        _map.erase(removed->getKey());
    }
    auto* cacheNode = new CacheNode<K, T>(key, data);
    cache.add(cacheNode);
    _map.insert_or_assign(key, cacheNode);
}

template<class K, class T>
int LRUCache<K, T>::getCacheSize() {
    return cacheSize;
}

#endif //DATASTRUCTURE_LRUCACHE_H
