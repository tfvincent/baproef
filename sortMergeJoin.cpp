#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include "vectorUtil.h"
#include "sortMergeJoin.h"

void sortMergeJoin(vector<vector<int>>& table1, vector<vector<int>>& table2, int key) {
  printf("SORTMERGEJOIN: \n");
  vector<vector<int>> copyTable1;
  vector<vector<int>> copyTable2;
  vector<vector<int>> result;
  copy(table1.begin(), table1.end(), back_inserter(copyTable1));
  copy(table2.begin(), table2.end(), back_inserter(copyTable2));

  printf("BEFORE SORTING: \n");
  printTable(copyTable1);
  printTable(copyTable2);

  sort(copyTable1.begin(), copyTable1.end(), [key](const vector<int>& a, const vector<int>& b) {
  return a[key] < b[key];
  });
  sort(copyTable2.begin(), copyTable2.end(), [key](const vector<int>& a, const vector<int>& b) {
  return a[key] < b[key];
  });

  printf("AFTER SORTING: \n");
  printTable(copyTable1);
  printTable(copyTable2);

  int mark = 999;
  int table1idx = 0;
  int table2idx = 0;

  printf("RESULT: \n");
  do {

    if (mark == 999) {
      while(copyTable1[table1idx][key] < copyTable2[table2idx][key]) {
        table1idx += 1;
      }
      while(copyTable1[table1idx][key] > copyTable2[table2idx][key]) {
        table2idx += 1;
      }
      mark = table2idx;
    }
    if (copyTable1[table1idx][key] == copyTable2[table2idx][key]) {
      vector<int> match;
      copy(copyTable1[table1idx].begin(), copyTable1[table1idx].end(), back_inserter(match));
      match.insert(match.end(), copyTable2[table2idx].begin(), copyTable2[table2idx].end());
      match.erase(match.begin() + key, match.begin() + (key +1));
      result.push_back(match);
      table2idx += 1;
    } else {
      table2idx = mark;
      table1idx += 1;
      mark = 999;
    }
  }
  while (table1idx < copyTable1.size());

  printTable(result);

}
