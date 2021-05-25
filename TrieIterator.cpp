//
// Created by tf_vincent on 5/16/21.
//

#include "TrieIterator.h"
#include <stdbool.h>

TrieIterator::TrieIterator(struct node * root){
    this->current = root;
    this->parent = NULL;
    this->index = 0;
}
bool TrieIterator::atEnd() {
    bool res = this->index == this->current->parent->children.size();

    return res;
}

bool TrieIterator::nextAtEnd(){
    return this->index == this->current->parent->children.size()-1;
}

void TrieIterator::next() {
    if (!this->nextAtEnd()) {
        this->index = this->index +1;
        this->current = this->current->parent->children[this->index];

    } else {
        this->index = this->index +1;
    }
}

void TrieIterator::open() {
    if (! this->current->children.empty()) {
        this->parent = this->current;
        this->current = this->current->children[0];
        this->index = 0;
    } else {
        throw "There are no children"s;
    }
}

void TrieIterator::seek(int seekKey) {
    while(!this->atEnd() && this->current->data < seekKey){
        this->next();
    }
}

void TrieIterator::up() {
    struct node * tmp = this->current;
    if (this->parent->var != NULL) {
        this->index = this->parent->index;
        this->parent = this->parent->parent;
        this->current = tmp->parent;
    } else {
        this->current = tmp->parent;
        this->parent = NULL;
        this->index = NULL;
    }
}

int TrieIterator::getRootVar(){
    struct node * curr = this->current;
    while (curr->parent->var != NULL) {
        curr = curr->parent;
    }
    return curr->data;
}