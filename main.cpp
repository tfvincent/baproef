#include <iostream>
#include <vector>
#include "btree.h"
#include "map.h"
#include "vectorUtil.h"
#include "leapfrog_join.h"
#include "genericJoin.h"
#include "

typedef btree::map<int, int> IntMap;
using namespace std;

int CountDuplicates() {
    IntMap iset;
    iset[42] = 43;
    for (int i = 2; i < 20; ++i) {
        iset[i] = 43;
    }
    for (int i = 2; i < 43; ++i) {
        cout << iset[i] << "\n";
    }

    auto iterator69 = iset.find(41);
    iterator69.operator++();
    assert(iterator69->second == 43);
    return 2;
}

int main(){

    Table grades1;
    Table grades2;
    Table grades3;
    Table gradesA;
    Table gradesB;
    Table gradesC;

    gradesA = {
            {1},
            {22},
            {28},
            {31},
            {31},
            {44},
            {58}};

    gradesB = {
            {1},
            {23},
            {28},
            {32},
            {32},
            {45},
            {60}};

    gradesC = {
            {1},
            {22},
            {28},
            {31},
            {32},
            {45},
            {60}};

    // FIXED: index is on column 1 not zero
    auto newIndex =  makeIndex(&gradesA, 1);
    auto newIndex2 =  makeIndex(&gradesB, 1);
    auto newIndex3 = makeIndex(&gradesC, 1);


    // FIXED: made pairs of iterator and pointers to Index, otherwise the btree is copied and
    // the .end() will never match with anything!
    pair<IndexMap::iterator, Index*> indexPair = pair<IndexMap::iterator, Index*>(newIndex->index.begin(),newIndex);
    pair<IndexMap::iterator, Index*> indexPair2 = pair<IndexMap::iterator, Index*>(newIndex2->index.begin(), newIndex2);
    pair<IndexMap::iterator, Index*> indexPair3 = pair<IndexMap::iterator, Index*>(newIndex3->index.begin(), newIndex3);



    vector<pair<IndexMap::iterator, Index*>> indexVec;

    indexVec.push_back(indexPair);
    indexVec.push_back(indexPair2);
    indexVec.push_back(indexPair3);


    printTable(leapfrog_join(indexVec));

    grades1 = {
            {1, 2},
            {22, 82},
            {28, 31},
            {31, 22},
            {31, 82},
            {44, 4},
            {58, 9}};
    grades2 = {
            {2,    3},
            {22, 103},
            {2, 104},
            {4, 101},
            {31, 102},
            {82, 142},
            {58, 107}};
    grades3 = {
            {3, 1},
            {142, 22},
            {8, 28},
            {4, 58}};

    vector<Table> genericJoinTables;
    genericJoinTables.push_back(grades1);
    genericJoinTables.push_back(grades2);
    genericJoinTables.push_back(grades3);

    HyperGraph * hyperGraph = generateHyperGraph(genericJoinTables);

    printTable(genericJoin(hyperGraph, genericJoinTables, 1));

    generateTrie(grades1, 1);
    //unsigned long long avgJoinTime;
    //avgJoinTime = join(grades1, grades2, grades3);
    //for (int i = 0; i < 10000; ++i) {
    //  avgJoinTime = avgJoinTime + join(grades1, grades2, grades3);
    //}
    //cout<<setprecision (7) <<"Average time nested loop join: "<< avgJoinTime << "µs\n";

    return 0;
}
