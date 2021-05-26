#include <iostream>
#include <vector>
#include <iomanip>
#include "btree.h"
#include "map.h"
#include "vectorUtil.h"
#include "leapfrog_join.h"
#include "genericJoin.h"
#include "leapfrog_triejoin.h"
#include "nestedLoopJoin.h"
#include "benchmark.h"
#include "timer.h"
#include "join.h"

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

int main() {

    /*Table grades1;
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
    auto newIndex = makeIndex(&gradesA, 1);
    auto newIndex2 = makeIndex(&gradesB, 1);
    auto newIndex3 = makeIndex(&gradesC, 1);


    // FIXED: made pairs of iterator and pointers to Index, otherwise the btree is copied and
    // the .end() will never match with anything!
    pair<IndexMap::iterator, Index *> indexPair = pair<IndexMap::iterator, Index *>(newIndex->index.begin(), newIndex);
    pair<IndexMap::iterator, Index *> indexPair2 = pair<IndexMap::iterator, Index *>(newIndex2->index.begin(),
                                                                                     newIndex2);
    pair<IndexMap::iterator, Index *> indexPair3 = pair<IndexMap::iterator, Index *>(newIndex3->index.begin(),
                                                                                     newIndex3);


    vector<pair<IndexMap::iterator, Index *>> indexVec;

    indexVec.push_back(indexPair);
    indexVec.push_back(indexPair2);
    indexVec.push_back(indexPair3);

    Table * grades1 = generateRandomTable(100, {1,2}, 20);
    printTable(grades1);
    Table * grades2 = generateRandomTable(100, {2,3}, 20);
    Table * grades3 = generateRandomTable(100, {1,3}, 20);

    vector<int> varOrder = {1, 2, 3};

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
/*
    vector<Table> genericJoinTables;
    genericJoinTables.push_back(grades1);
    genericJoinTables.push_back(grades2);
    genericJoinTables.push_back(grades3);

    HyperGraph *hyperGraph = generateHyperGraph(genericJoinTables);

    printTable(genericJoin(hyperGraph, genericJoinTables, 1));

    struct node *rootNode = generateTrie(grades1, 1);
    struct node *rootNode1 = generateTrie(grades2, 2);
    struct node *rootNode2 = generateTrie(grades3, 3);

    TrieIterator *trie1 = new TrieIterator(rootNode);
    TrieIterator *trie2 = new TrieIterator(rootNode1);
    TrieIterator *trie3 = new TrieIterator(rootNode2);

    vector<TrieIterator *> tries;
    tries.push_back(trie1);
    tries.push_back(trie2);
    tries.push_back(trie3);

    vector<vector<TrieIterator *>> trieTable = getTrieTable(tries, varOrder);

    unsigned long long averageLeapfrog = 0;
    for (int i = 0; i < 1; ++i) {
        {

            Timer timer("Leapfrog triejoin");
            leapfrogTriejoin(trieTable, tries);
            auto duration = timer.Stop();
            averageLeapfrog = averageLeapfrog + duration;
        }
    }

    cout<<setprecision (7) <<"Average time leapfrog trie join: "<< averageLeapfrog << "ns\n";

    unsigned long long average = 0;
    for (int i = 0; i < 1; ++i) {
        {
            Timer timer("Leapfrog triejoin");
            join(grades1, grades2, grades3);
            auto duration = timer.Stop();
            average = average + duration;
        }
    }

    cout<<setprecision (7) <<"Average time nested loop join: "<< average << "ns\n";


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
*/
    /*********************************************************************************
     *                                   BENCHMARKING                                *
     *********************************************************************************/
    /**
     * DATA
     */
        int size = 100;
        int datasize = 20;
        vector<vector<int>> vars;
        vector<int> varOrder = {1, 2, 3};
        vector<int> ij = {1,2};
        vector<int> ik = {2,3};
        vector<int> il = {1,3};
        vars.push_back(ij);
        vars.push_back(ik);
        vars.push_back(il);

    /**
    * SKEW BENCHMARKING
    */
    printf("Benchmarking on skew data: \n");

    unsigned long long averageLeapfrogSkew = 0;
    for (int i = 0; i < 100; ++i) {
        {
            vector<Table*> tablesNormalSkew = restartSkewTables(size, vars);
            vector<struct node *> rootNodesNewSkew = restartNodes(tablesNormalSkew);
            vector<TrieIterator*> triesSkew = restartTrieIterators(rootNodesNewSkew);
            vector<vector<TrieIterator*>> trieTableSkew = getTrieTable(triesSkew, varOrder);
            restartDepth();

            Timer timer("Leapfrog triejoin");
            leapfrogTriejoin(trieTableSkew, triesSkew);
            auto duration = timer.Stop();
            if (i > 1) {
                averageLeapfrogSkew = averageLeapfrogSkew + duration;
            }
            printf("Leapfrog triejoin on skew data took %d nanseconds on run %d\n", duration, i);
        }
    }
    printf("\n");
    cout<<setprecision (7) <<"Average time leapfrog trie join on skew data: "<< averageLeapfrogSkew/98 << "ns\n";
    printf("\n");

    unsigned long long averageNestedSkew = 0;
    for (int i = 0; i < 100; ++i) {
        {
            vector<Table*> tablesSkew = restartSkewTables(size, vars);
            Table * table1Skew = tablesSkew[0];
            Table * table2Skew = tablesSkew[1];
            Table * table3Skew = tablesSkew[2];
            Timer timer("Leapfrog triejoin");
            join(*table1Skew, *table2Skew, *table3Skew);
            auto duration = timer.Stop();
            if (i > 1) {
                averageNestedSkew = averageNestedSkew + duration;
            }
            printf("NestedLoop join on skew data took %d nanseconds on run %d\n", duration, i);

        }
    }
    printf("\n");
    cout<<setprecision (7) <<"Average time nested loop join on skew data: "<< averageNestedSkew/98 << " nanoseconds\n";
    printf("\n");

    /**
     * BENCHMARKING NORMAL DATA
     */
    unsigned long long averageLeapfrog = 0;
    for (int i = 0; i < 100; ++i) {
        {
            vector<Table*> tablesNormal = restartTables(size, vars, datasize);
            vector<struct node *> rootNodesNew = restartNodes(tablesNormal);
            vector<TrieIterator*> tries = restartTrieIterators(rootNodesNew);
            vector<vector<TrieIterator*>> trieTable = getTrieTable(tries, varOrder);
            restartDepth();

            Timer timer("Leapfrog triejoin");
            leapfrogTriejoin(trieTable, tries);
            auto duration = timer.Stop();
            if (i > 1) {
                averageLeapfrog = averageLeapfrog + duration;
            }
            printf("Leapfrog triejoin on normal data took %d nanseconds on run %d\n", duration, i);

        }
    }
    printf("\n");
    cout<<setprecision (7) <<"Average time leapfrog trie join on normal data: "<< averageLeapfrog/98 << "ns\n";
    printf("\n");

    unsigned long long averageNestedNormal = 0;
    for (int i = 0; i < 100; ++i) {
        {
            vector<Table*> tablesNormal = restartTables(size, vars, datasize);
            Table * table1 = tablesNormal[0];
            Table * table2 = tablesNormal[1];
            Table * table3 = tablesNormal[2];
            Timer timer("Leapfrog triejoin");
            join(*table1, *table2, *table3);
            auto duration = timer.Stop();
            if (i > 1) {
                averageNestedNormal = averageNestedNormal + duration;
            }
            printf("NestedLoop join on normal data took %d nanseconds on run %d\n", duration, i);

        }
    }
    printf("\n");
    cout<<setprecision (7) <<"Average time nested loop join on normal data: "<< averageNestedNormal/98 << "ns\n";
    printf("\n");

    return 0;
}
