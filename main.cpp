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

using namespace std;

int main(){

  vector<vector<int>> grades1;
  vector<vector<int>> grades2;
  vector<vector<int>> grades3;

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

    for (int i = 0; i < 10000; ++i) {
        avgJoinTime = avgJoinTime + join(grades1, grades2, grades3);
    }
    cout<<setprecision (7) <<"Average time nested loop join: "<< avgJoinTime/10000 << "µs\n";

    return 1;
}
