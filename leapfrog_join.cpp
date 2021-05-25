//
// Created by tf_vincent on 4/30/21.
//
#include <vector>
#include <algorithm>

#include "iterator_interface.h"
#include "map.h"
#include "vectorUtil.h"
#include "TrieIterator.h"

static int p;
static bool theEnd;

void leapfrog_search(vector<TrieIterator*> &iterVec){
    // FIXED: The "%" is the remainder of division and NOT the same as the modulo
    // such that -1 % iterVec.size() is undefined (in our case this was always zero)
    // to avoid this iterVec.size() can be added by p-1 to make it positive again,
    // with the same result.
    int maxKey = iterVec[(iterVec.size() + (p-1)) % iterVec.size()]->current->data;
    while(true) {
        int key = iterVec[p]->current->data;
        if(key == maxKey){
            return;
        } else {
            if(iterVec[p]->atEnd()){
                theEnd = true;
                return;
            } else {
                iterVec[p]->seek(maxKey);
                // FIXED: After seeking, we could be at the end of this iterator, in t hat case we MUST stop, otherwise it will use an invalid key
                if(iterVec[p]->atEnd()){
                    theEnd = true;
                    return;
                }
                maxKey = iterVec[p]->current->data;
                p = (p + 1) % iterVec.size();
            }
        }
    }
}



void leapfrog_init(vector<TrieIterator*> &iterVec){
    if (find_if(iterVec.begin(), iterVec.end(), [] (TrieIterator* &a) -> bool {
        return a->atEnd();
    }) != iterVec.end()) {
        theEnd = true;
    } else {
        theEnd = false;
        sort(iterVec.begin(), iterVec.end(),
             [](TrieIterator* &a, TrieIterator* &b) -> bool {
                 return a->current->data < b->current->data;
             });
        p = 0;
        leapfrog_search(iterVec);
    }
}
bool leapfrog_next(vector<TrieIterator*> &iterVec){
    if (iterVec[p]->nextAtEnd()){
        theEnd = true;
        return false;
    } else {
        iterVec[p]->next();
        p = (p + 1) % iterVec.size();
        leapfrog_search( iterVec);
        if (iterVec[p]->atEnd()){
            return false;
        }
        return true;
    }
}

bool isAtEnd(vector<TrieIterator*> &itervec){
    return true;
}