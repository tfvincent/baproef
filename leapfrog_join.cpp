//
// Created by tf_vincent on 4/30/21.
//
#include <vector>
#include <algorithm>

#include "iterator_interface.h"
#include "map.h"
#include "vectorUtil.h"

static int p;
static bool theEnd;

void leapfrog_search(vector<pair<IndexMap::iterator, Index*>> &iterVec){
    printf("Search init p = %d, p-1=%d \n", p, (p-1) % iterVec.size());
    // FIXED: The "%" is the remainder of division and NOT the same as the modulo
    // such that -1 % iterVec.size() is undefined (in our case this was always zero)
    // to avoid this iterVec.size() can be added by p-1 to make it positive again,
    // with the same result.
    int maxKey = iterVec[(iterVec.size() + (p-1)) % iterVec.size()].first.key();
    printf("Init maxkey %d\n", maxKey);
    while(!theEnd) {
        int key = iterVec[p].first.key();
        if(key == maxKey){
            printf("Settled on %d\n", maxKey);
            return;
        } else {
            if(iterVec[p].first == iterVec[p].second->index.end()){
                theEnd = true;
                return;
            } else {
                printf("seeking for p = %d, to %d\n", p, maxKey);
                seek(maxKey, & iterVec[p].first, & iterVec[p].second->index);
                // FIXED: After seeking, we could be at the end of this iterator, in t hat case we MUST stop, otherwise it will use an invalid key
                if(iterVec[p].first == iterVec[p].second->index.end()){
                    theEnd = true;
                    return;
                }
                maxKey = iterVec[p].first.key();
                printf("New max key %d\n", maxKey);
                p = (p + 1) % iterVec.size();
            }
        }
    }
}

void leapfrog_next(vector<pair<IndexMap::iterator, Index*>> &iterVec){
    IndexMap::iterator end = iterVec[p].second->index.end();
    iterVec[p].first.operator++() ;
    printf("Key of p = %d, key = %d\n", p, iterVec[p].first.key());
    if (iterVec[p].first == end){
        theEnd = true;
    } else {
        p = (p + 1) % iterVec.size();
        leapfrog_search( iterVec);
    }
}

void leapfrog_init(vector<pair<IndexMap::iterator, Index*>> &iterVec){
    if (find_if(iterVec.begin(), iterVec.end(), [] (pair<IndexMap::iterator, Index*>& a) -> bool {
        return a.first == a.second->index.end();
    }) != iterVec.end()) {
        theEnd = true;
    } else {
        theEnd = false;
        sort(iterVec.begin(), iterVec.end(),
             [](pair<IndexMap ::iterator, Index*> &a, pair<IndexMap ::iterator, Index*> &b) -> bool {
                 return a.first.key() < b.first.key();
             });
        p = 0;
        leapfrog_search(iterVec);
    }
}

Table leapfrog_join(vector<pair<IndexMap::iterator, Index*>> &iterVec){
    Table result;
    leapfrog_init( iterVec);
    while (!theEnd){
        printf("p = %d, key = %d\n", p, iterVec[p].first.key());
        vector<Table> tables;
        for (auto x: iterVec) {
            Table tmp;
            for(auto y: *(*x.first).second) {
                vector<int> clone;
                copy(x.second->table->operator[](y).begin(), x.second->table->operator[](y).end(), back_inserter(clone));
                tmp.push_back(clone);
            }
            tables.push_back(tmp);
        }
        for (auto x: product(tables)){
            result.push_back(x);
        }
        leapfrog_next( iterVec);
    }
    return result;
}
