#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "vectorUtil.h"
#include "nestedLoopJoin.h"

void nestedLoopJoin(vector<vector<int>> table1, vector<vector<int>> table2, int key) {
  printf("NESTEDLOOPJOIN: \n");
  printTable(table1);
  printTable(table2);
  printf("RESULT: \n");
  vector<vector<int>> result;
  for(int i=0; i < table1.size(); i++){
    for(int j=0; j < table2.size(); j++){
      if (table1[i][key] == table2[j][key]){
        vector<int> match;
        copy(table1[i].begin(), table1[i].end(), back_inserter(match));
        match.insert(match.end(), table2[j].begin(), table2[j].end());
        match.erase(match.begin() + key, match.begin() + (key +1));
        result.push_back(match);
      }
    }
  }
  printTable(result);
}
