#include <iostream>
#include <vector>
#include "btree.h"
#include "map.h"
#include "vectorUtil.h"
#include "leapfrog_join.h"
#include "genericJoin.h"
#include "leapfrog_triejoin.h"
#include "nestedLoopJoin.h"
#include "benchmark.h"

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
    Table example;

    gradesA = {
            {1},
            {22},
            {28},
            {31},
            {32},
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

    grades1 = {
            {1, 2},
            {22, 82},
            {28, 31},
            {31, 22},
            {31, 82},
            {22, 4},
            {58, 9}};
    grades2 = {
            {2,    3},
            {82, 103},
            {82, 104},
            {82, 101},
            {4, 101},
            {82, 142},
            {82, 107}};
    grades3 = {
            {1, 3},
            {22, 82},
            {22, 101},
            {22, 142}};

    vector<int> varOrder = {1,2,3};

    example = {
            {1, 2, 3},
            {1, 3, 4},
            {1, 3, 5},
            {1, 4, 6},
            {1, 4, 8},
            {1, 4, 9},
            {1, 5, 2},
            {3, 5, 2}
    };

    vector<Table> genericJoinTables;
    genericJoinTables.push_back(grades1);
    genericJoinTables.push_back(grades2);
    genericJoinTables.push_back(grades3);

    HyperGraph * hyperGraph = generateHyperGraph(genericJoinTables);

    printTable(genericJoin(hyperGraph, genericJoinTables, 1));

    struct node * rootNode = generateTrie(grades1, 1);
    struct node * rootNode1 = generateTrie(grades2, 2);
    struct node * rootNode2 = generateTrie(grades3, 3);

    TrieIterator * trie1 = new TrieIterator(rootNode);
    TrieIterator * trie2 = new TrieIterator(rootNode1);
    TrieIterator * trie3 = new TrieIterator(rootNode2);

    vector<TrieIterator*> tries;
    tries.push_back(trie1);
    tries.push_back(trie2);
    tries.push_back(trie3);

    vector<vector<TrieIterator*>> trieTable = getTrieTable(tries, varOrder);

    printf("Leapfrog triejoin took: %f ms", leapfrogTriejoin(trieTable, tries));
    //printTable(nestedLoopJoin()
    printf("Leapfrog triejoin completed");


    vector<int> vars;
    vector<int> vars2;
    vector<int> vars3;

    Table grades20;
    Table grades21;
    Table grades22;
    Table grades23;

    vars.push_back(1);
    vars.push_back(2);
    vars2.push_back(2);
    vars2.push_back(3);
    vars3.push_back(3);
    vars3.push_back(1);

    grades20 = generateRandomTable(400, vars, 10000);
    grades21 = generateSkewTable(10000, vars);
    grades22 = generateSkewTable(10000, vars);
    grades23 = generateSkewTable(10000, vars);

    vector<Table> genericJoinTables1;
    genericJoinTables1.push_back(grades21);
    genericJoinTables1.push_back(grades22);
    genericJoinTables1.push_back(grades23);

    HyperGraph * hyperGraph1 = generateHyperGraph(genericJoinTables1);

    printTable(genericJoin(hyperGraph1, genericJoinTables1, 1));


    //unsigned long long avgJoinTime;
    //avgJoinTime = join(grades1, grades2, grades3);
    //for (int i = 0; i < 10000; ++i) {
    //  avgJoinTime = avgJoinTime + join(grades1, grades2, grades3);
    //}
    //cout<<setprecision (7) <<"Average time nested loop join: "<< avgJoinTime << "µs\n";

    return 0;
}
