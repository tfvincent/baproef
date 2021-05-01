#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

#include "nestedLoopJoin.h"
#include "sortMergeJoin.h"
#include "timer.h"
#include "join.h"
#include "btree.h"
#include "set.h"
#include "map.h"
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

  grades1 = {
            {1, 0},
            {22, 2},
            {28, 5},
            {31, 8},
            {31, 82},
            {44, 4},
            {58, 9}};
  grades2 = {
            {1,    2},
            {28, 103},
            {28, 104},
            {31, 101},
            {31, 102},
            {82, 142},
            {58, 107}};
  grades3 = {
            {1, 5},
            {31, 1},
            {8, 8},
            {4, 4}};

    unsigned long long avgJoinTime;
    avgJoinTime = join(grades1, grades2, grades3);
    //for (int i = 0; i < 10000; ++i) {
      //  avgJoinTime = avgJoinTime + join(grades1, grades2, grades3);
    //}
    cout<<setprecision (7) <<"Average time nested loop join: "<< avgJoinTime << "µs\n";

    auto newIndex = makeIndex(grades1, 1);
    auto iterator69 = newIndex.find(44);
    printVector(*iterator69->second);

    return 0;
}
