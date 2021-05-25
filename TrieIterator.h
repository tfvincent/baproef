//
// Created by tf_vincent on 5/16/21.
//

#ifndef BAPROEF_TRIEITERATOR_H
#define BAPROEF_TRIEITERATOR_H

#include "vectorUtil.h"

class TrieIterator {
public:
    TrieIterator(struct node *);
    int index;
    struct node * parent = NULL;
    struct node * current;
    void seek(int);
    bool nextAtEnd();
    bool atEnd();
    void next();
    void open();
    void up();
    int getRootVar();
};


#endif //BAPROEF_TRIE_H
