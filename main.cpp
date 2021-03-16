#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "nestedLoopJoin.h"
#include "sortMergeJoin.h"
#include "timer.h"

using namespace std;

int main(){

  vector<vector<int>> grades1;
  vector<vector<int>> grades2;
  vector<vector<int>> grades3;

  grades1 = {
            {22, 2},
            {28, 5},
            {31, 8},
            {31, 82},
            {44, 4},
            {58, 9}};
  grades2 = {
            {28, 103},
            {28, 104},
            {31, 101},
            {31, 102},
            {42, 142},
            {58, 107}};
  grades3 = {
            {1, 1, 1},
            {8, 8, 8},
            {4, 4, 4}};

  nestedLoopJoin(grades1, grades2, 0);
  sortMergeJoin(grades1, grades2, 0);
  return 1;
}
