//
// Created by tf_vincent on 4/30/21.
//

#include "map.h"
#include "vectorUtil.h"

bool atEnd(IndexMap::iterator& iter, IndexMap index){
    return iter.key() == index.end();
}

void seek(int seekKey, IndexMap::iterator& iter, IndexMap index) {
    while (seekKey > iter.key() && !atEnd(iter, index)) {
        iter.operator++();
    }
}




