//
// Created by Jason on 12/6/2016.
//

#ifndef HASHMAP_H
#define HASHMAP_H

#include "HashNode.h"

const int TABLE_SIZE = 1000;

//???
struct MyKeyHash {
    unsigned long operator()(const int& k) const
    {
        return k % 10;
    }
};

template <typename K>
struct KeyHash {
    unsigned long operator()(const K &key) const {
        return reinterpret_cast<unsigned  long>(key) % TABLE_SIZE;
    }
};

template <typename K, typename V, typename F = KeyHash<K>>
class HashMap {
public:
    HashMap() {
        table = new HashNode<K, V> *[TABLE_SIZE]();
    }

    ~HashMap() {
        for (int i=0; i<TABLE_SIZE; ++i) {
            HashNode<K, V> *entry = table[i];
            while (entry != nullptr) {
                HashNode<K, V> *prev= entry;
                entry = entry->getNext();
                delete prev;
            }
            table[i] = nullptr;
        }
        delete[] table;
    }

    bool get(const K &key, V &value) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *entry = table[hashValue];
        while (entry != nullptr) {
            if (entry->getKey() == key) {
                value = entry->getValue();
                return true;
            }
            entry = entry->getNext();
        }
        return false;
    }

    void put(const K &key, const V &value) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = nullptr;
        HashNode<K, V> *entry = table[hashValue];
        while (entry != nullptr && entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }
        if (entry == nullptr) {
            entry = new HashNode<K, V>(key, value);
            if (prev == nullptr) { //won't prev always be null bucket doens't exist?
                table[hashValue] = entry;
            } else {
                prev->setNext(entry);
            }
        } else {
            entry->setValue(value);
        }
    }

    void remove(const K &key) {
        unsigned long hashValue = hashFunc(key);
        HashNode<K, V> *prev = nullptr;
        HashNode<K, V> *entry = table[hashValue];
        while (entry != nullptr && entry->getKey() != key) {
            prev = entry;
            entry = entry->getNext();
        }
        if (entry == nullptr) {
            return; //not found
        } else {
            if (prev == nullptr) {
                //remove first bucket
                table[hashValue] = entry->getNext();
            } else {
                prev->setNext(entry->getNext());
            }
        }
    }

private:
    HashNode<K, V> **table;
    F hashFunc;
};

#endif //HASHMAP_H
