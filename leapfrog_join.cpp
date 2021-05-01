//
// Created by tf_vincent on 4/30/21.
//
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "iterator_interface.h"
#include "map.h"
#include "vectorUtil.h"

static int p;
static bool theEnd;

void leapfrog_search(vector<pair<IndexMap::iterator, Index index>>& iterVec){
    int maxKey = iterVec[(p-1) % iterVec.size()].first.key();
    while(true) {
        int key = iterVec[p].first.key();
        if(key == maxKey){
            return;
        } else {
            seek(maxKey, iterVec[p].first, iterVec[p].second.index);
            if(atEnd(iterVec[p].first, iterVec[p].second.index)){
                theEnd = true;
                return;
            } else {
                maxKey = iterVec[p].first.key();
                p = (p + 1) % iterVec.size();
            }
        }
    }
}

void leapfrog_next(vector<pair<IndexMap::iterator, Index index>>& iterVec){
    iterVec[p].first.operator++();
    if (atEnd(iterVec[p].first, iterVec[p].second.index)){
        theEnd = true;
    } else {
        p = (p + 1) % iterVec.size();
        leapfrog_search(& iterVec);
    }
}

void leapfrog_init(vector<pair<IndexMap::iterator, Index>>& iterVec){
    if (find_if(iterVec.begin(), iterVec.end(), [] (Index::iterator & a) -> bool {
        return atEnd(a->first, a->second)
    })) {
        theEnd = true;
    } else {
        theEnd = false;
        sort(iterVec.begin(), iterVec.end(),
             [](pair<Index::iterator, Index> &a, pair<Index::iterator, Index> &b) -> bool {
                 return a.first.key() < b.first.key();
             });
        p = 0;
        leapfrog_search(iterVec);
    }
}

Table leapfrog_join(vector<pair<IndexMap::iterator, Index index>>& iterVec){
    Table result;
    leapfrog_init(& iterVec);
    while (!theEnd){
        for (auto x: iterVec) {
            //todo product(x.first->second);
        }
        leapfrog_next(& iterVec);
    }
}




