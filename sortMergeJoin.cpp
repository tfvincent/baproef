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
#include "timer.h"

unsigned long long sortMergeJoin(vector<vector<int>> table1, vector<vector<int>> table2) {

  //printf("SORTMERGEJOIN: \n");
  vector<vector<int>> copyTable1;

  vector<vector<int>> copyTable2;
  vector<vector<int>> presult;

  copy(table1.begin(), table1.end(), back_inserter(copyTable1));
  copy(table2.begin(), table2.end(), back_inserter(copyTable2));
  pair<int, int> keys = findKeys(table1, table2);
  //printf("BEFORE SORTING: \n");
  //printTable(copyTable1);
  //printTable(copyTable2);
  Timer timer("Sort_merge_join");

  sort(copyTable1.begin(), copyTable1.end(), [keys](const vector<int>& a, const vector<int>& b) {
  return a[keys.first] < b[keys.first];
  });

  sort(copyTable2.begin(), copyTable2.end(), [keys](const vector<int>& a, const vector<int>& b) {
  return a[keys.second] < b[keys.second];
  });
  //printf("AFTER SORTING: \n");
  //printTable(copyTable1);
  //printTable(copyTSable2);
  int mark = 999;
  int table1idx = 1;
  int table2idx = 1;

  do {

    if (mark == 999) {
      while(copyTable1[table1idx][keys.first] < copyTable2[table2idx][keys.second]) {
          table1idx += 1;
      }
      while(copyTable1[table1idx][keys.first] > copyTable2[table2idx][keys.second]) {
        table2idx += 1;
      }
      mark = table2idx;
    }
    if (copyTable1[table1idx][keys.first] == copyTable2[table2idx][keys.second]) {
      vector<int> match;
      match.reserve(5);
      copy(copyTable1[table1idx].begin(), copyTable1[table1idx].end(), back_inserter(match));
      match.insert(match.end(), copyTable2[table2idx].begin(), copyTable2[table2idx].end());
      //match.erase(match.begin() + key, match.begin() + (key +1));
      presult.push_back(match);
      table2idx += 1;
    } else {
      table2idx = mark;
      table1idx += 1;
      mark = 999;
    }
  }
  while (table1idx < copyTable1.size() && table2idx < copyTable2.size());

  long long duration = timer.Stop();
  return duration;

}
