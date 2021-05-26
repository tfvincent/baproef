//
// Created by tf_vincent on 5/17/21.
//

#ifndef BAPROEF_LEAPFROG_TRIEJOIN_H
#define BAPROEF_LEAPFROG_TRIEJOIN_H

#include "TrieIterator.h"

struct node * generateTrie(Table, int);
vector<TrieIterator*> restartTrieIterators(vector<struct node *>);
vector<struct node *> restartNodes(vector<Table*>);
vector<Table*> restartTables(int , Table, int);
vector<Table*> restartSkewTables(int, Table);
void restartDepth();
vector<vector<TrieIterator*>> getTrieTable(vector<TrieIterator*>, vector<int>);
void leapfrogTriejoin(vector<vector<TrieIterator*>>& , vector<TrieIterator*> &);


#endif //BAPROEF_LEAPFROG_TRIEJOIN_H
