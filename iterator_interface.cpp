//
// Created by tf_vincent on 4/30/21.
//

#include "map.h"
#include "vectorUtil.h"

bool isNotAtEnd(IndexMap::iterator& iter, IndexMap index){
    return iter.key() <= index.end().key();
}

void seek(int seekKey, IndexMap::iterator * iter, IndexMap * index) {
    while (seekKey > iter->key() && *iter != index->end()) {
        iter->operator++();
    }

    if (*iter == index->end()) {
        iter--;
        printf("At end\n");
    }
}
