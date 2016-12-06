//
// Created by Jason on 12/6/2016.
//

#ifndef HASHNODE_H
#define HASHNODE_H

template <typename K, typename V>
class HashNode {
public:
    HashNode(const K &key, const V &value) : key(key), value(value), next(nullptr) {}

    K getKey() const {
        return key;
    }

    V getValue() const {
        return value;
    }

    void setValue(V value) {
        HashNode::value = value;
    }

    HashNode *getNext() const {
        return next;
    }

    void setNext(HashNode *next) {
        HashNode::next = next;
    }

private:
    K key;
    V value;
    HashNode *next;
};

#endif //HASHNODE_H
